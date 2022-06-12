import socket
import threading
from typing import Any

from .data import Data
from .event_handler import EventHandler
from .utils import valid_data_types, build_data_header, split_header, build_header
from .protocol import headers, defaults
from .exceptions import DataSizeError


class Connection(EventHandler):

    def __init__(self, peer, target_name: str, sock: socket.socket, buffer_size: int, **kwargs):
        data_type = str(kwargs.get("data_type", "json"))
        if data_type not in valid_data_types:
            raise ValueError(f"data_type must be one of {valid_data_types}")

        stream = bool(kwargs.get("stream", False))
        data_size = int(kwargs["data_size"]) if "data_size" in kwargs else "auto"
        if stream and data_size != "auto" and data_size <= 0:
            raise ValueError(f"Data size should be > 0 or 'auto' (Received {data_size})!")

        handlers = {**defaults.connection_handlers, **dict(kwargs.get("handlers", {}))}
        super().__init__(["data", "close"], handlers)

        self.peer = peer
        self.target_name = str(target_name)
        self.sock = sock
        self.buffer_size = int(buffer_size)
        self._data_type = data_type
        self.strict = bool(kwargs.get("strict", True))
        self.stream = stream
        self.data_size = data_size
        self.active = True

        self.thread = threading.Thread(target=self._listen)

    @property
    def data_type(self) -> str:
        """Returns the data type each peers have agreed on for this connection.

        Returns:
            str: the string representation of the data type
        """
        return self._data_type

    @property
    def closed(self) -> bool:
        """Returns whether this connection is closed.

        Returns:
            bool: a boolean indicating whether the connection is closed.
        """
        return not self.active

    def start_thread(self):
        """Attempts to start this connection's main thread, if not already running."""
        if not self.thread.is_alive():
            self.thread.start()

    def send(self, data: Any):
        """Send data to the target peer, serializing it to this connection's default data format.

        Args:
            data (Any): the data to serialize and send.

        Raises:
            ValueError: if this connection's default format is bytes and the data is not bytes

        Returns:
            bool: whether data was successfully sent.
        """
        if self.closed:
            # raise ConnectionAbortedError("Connection was lost with remote peer.")
            # choice was made not to raise exception here because the user needs to properly handle
            # disconnection with event handlers. We'd keep returning False if the user keeps trying
            # to send data over a defective connection
            return False

        # send a header if the connection is not streaming
        # otherwise, data_type is fixed and known and data is of fixed size so header is useless
        # first encode data according to this connection's default data type
        data = Data(self.data_type, decoded_data=data).encode()

        data_size = len(data)
        if not self.stream or self.data_size == "auto":
            # then send information about data
            header = build_data_header(data_size, self.data_type)
            try:
                self.sock.sendall(header)
            except (ConnectionAbortedError, ConnectionResetError):
                self.close()
                return False

            if self.data_size == "auto":
                self.data_size = data_size
        elif self.data_size != data_size:
            raise DataSizeError(f"Data size ({data_size}) is different from the stream size ({self.data_size})")

        # set the socket as blocking so that we wait for the data to be received
        self.sock.setblocking(True)
        try:
            self.sock.sendall(data)  # raises an error if data ain't fully sent
        except (ConnectionAbortedError, ConnectionResetError):
            self.close()
            return False

        # reset the socket timeout
        self.sock.settimeout(self.peer.timeout)
        return True

    def _receive_data(self, header: str):
        """Internal method to start the receiving process

        Args:
            header (str): the header first received from the other peer

        Returns:
            Any: the data received and deserialized (according to the data type referenced in the header)
        """
        header = split_header(header)

        # don't process header if it does not contains the minimum needed key/values pairs
        if any([key not in header for key in headers.required_data_fields]):
            return None

        data_type, data_size = header["data_type"], header["data_size"]

        if self.data_size == "auto":
            self.data_size = data_size

        if self.strict and data_type != self.data_type:
            return None

        return self._receive(data_size, data_type)

    def _receive(self, data_size: int, data_type: str):
        """Receives data from the underlying socket, according to data_size and data_type.

        Args:
            data_size (int): the size of the data, in bytes.
            data_type (str): the type of data (one of ['raw', 'json', 'bytes']).

        Returns:
            Data: the data object received
        """
        data = Data(data_type)

        nb_chunks = data_size // self.buffer_size
        residue_size = data_size % self.buffer_size

        # TODO: set socket blocking?
        try:
            for _ in range(nb_chunks):
                data.buffer += self.sock.recv(self.buffer_size)
            if residue_size > 0:
                data.buffer += self.sock.recv(residue_size)
        except (ConnectionAbortedError, ConnectionResetError):
            self.close()
            return None

        return data

    def close(self, force: bool = False):
        """Closes the connection nicely.

        Args:
            force (bool, optional): whether to force close the connection.
            This setting should be considered dangerous, as data can be lost. Defaults to False.
        """
        self.active = False
        try:
            self.sock.settimeout(0)  # try to speed up closing process

            if force:
                self.sock.shutdown(socket.SHUT_RDWR)
        except OSError:
            # in case the socket was already termianted, an OSError is raised
            return

    def _listen(self):
        while self.active:
            # in case timeout has changed
            if self.peer.timeout != self.sock.gettimeout():
                self.sock.settimeout(self.peer.timeout)

            header, data = None, None
            try:
                # will block until any streaming data/header is received or socket timeout
                if self.stream and self.data_size != "auto":
                    data = self._receive(self.data_size, self.data_type)
                else:
                    header = self.sock.recv(headers.size).decode("utf-8")
            except (socket.timeout, UnicodeDecodeError):
                # socket.timeout: no header/streaming data received within timeout seconds
                # UnicodeDecodeError: data received is corrupted, don't process it

                # ping the connection to check if it is still alive
                # which otherwise raises ConnectionAbortedError, ConnectionResetError
                self.sock.sendall(build_header(headers.ping_header, {}))
                continue
            except (ConnectionAbortedError, ConnectionResetError):
                self.close()
                continue

            # if we received a data header, otherwise do nothing with the received packet
            if header is not None and header.startswith(headers.data_header):
                data = self._receive_data(header)

            if data is not None:
                self.handle("data", data.decode())

        self.sock.close()
        self.handle("close")
        del self.peer.connections[self.target_name]
