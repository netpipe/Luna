import time

import socket
import threading

from typing import Tuple, List, Any, Dict

from .connection import Connection
from .event_handler import EventHandler
from .protocol import headers, defaults
from .exceptions import DataTypeError, DataSizeError
from .utils import get_local_ip, check_address, build_hello_header, build_header, split_header


class Peer(EventHandler):

    def __init__(self, address: str = None, port: int = 0, **kwargs):
        handlers = {**defaults.peer_handlers, **dict(kwargs.get("handlers", {}))}
        super().__init__(["listen", "offer", "connection", "stop"], handlers)

        if address is None:
            address = get_local_ip()
        elif ":" in address:
            address, port = address.split(":")[:2]

        timeout = float(kwargs.get("timeout", defaults.timeout))
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((address, int(port)))
        self.server.settimeout(timeout)

        self._address = self.server.getsockname()
        self.connections = {}
        self._server_active = False
        self.max_connections = int(kwargs.get("max_connections", 0))
        self.buffer_size = float(kwargs.get("buffer_size", defaults.buffer_size))

        self.server_thread = threading.Thread(target=self._listen_offers)
        self.pinger_thread = threading.Thread(target=self._listen_pings)
        # needs to be after pinger_thread because checks the pinger_thread state
        self.invisible = bool(kwargs.get("invisible", False))

    @property
    def address(self) -> Tuple[str, int]:
        """This peer' address, in a normalized format

        Returns:
            Tuple[str, int]: the normalized address (ipv4, port)
        """
        return self._address

    @property
    def address_name(self) -> str:
        """This peer's normalized address name

        Returns:
            str: the normalized address name ipv4:port
        """
        return f"{self.address[0]}:{self.address[1]}"

    @property
    def timeout(self) -> float:
        """This peer's default timeout

        Returns:
            float: the default timeout
        """
        return self.server.gettimeout()

    @timeout.setter
    def timeout(self, timeout: float):
        """Sets this peer's default timeout'

        Args:
            timeout (float): the default timeout to set
        """
        self.server.settimeout(timeout)

    @property
    def invisible(self) -> bool:
        """Whether this peer is invisible to other peers on the same local network

        Returns:
            bool: this peer's invisibility
        """
        return self._invisible

    @invisible.setter
    def invisible(self, invisible: bool):
        """Sets wether this peer is invisible to other peers on the same local network

        Args:
            invisible (bool): this peer's invisibility'
        """
        self._invisible = invisible

        # if this peer's now visible and the pinger thread is stopped, restart it
        if self._server_active and not invisible and not self.pinger_thread.is_alive():
            self.pinger_thread = threading.Thread(target=self._listen_pings)
            self.pinger_thread.start()

    def connect(self, address: str, port: int = None, data_type: str = "json", strict: bool = True, **kwargs) -> Connection:
        """Attempts to start a connection with a remote peer located at (address, port).
        Additional arguments are passed to the Connection constructor and sent to the remote peer right after successful
        connection, so that it knows with what data type to communicate with.

        Args:
            address (str): the ipv4 address of the remote peer, provided with the port if wanted (ipv4:port)
            port (int, optional): the port to use for the connection, if not provided in address. Defaults to None.
            data_type (str, optional): the data type to use for the connection. Defaults to "raw".
            strict (bool, optional): whether this connection is strict on data types. Defaults to True.
            buffer_size (int, optional): the buffer size to use to receive data. Defaults to this peer's buffer size.

        Returns:
            Connection: the connection, if established
        """
        address, address_name = check_address(address, port)

        if address_name == self.address_name:
            return False

        if address_name in self.connections:
            connection = self.connections[address_name]
            if connection.data_type != data_type:
                connection.close()
            else:
                return connection

        # TODO: use create_connection for ipv4 + ipv6 ??
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(self.timeout)
        try:
            sock.connect(address)
        except socket.timeout:
            return False

        buffer_size = int(kwargs.get("buffer_size", self.buffer_size))
        # will raise ValueError if stream and data_size are incompatible
        # will parse kwargs to their right properties
        connection = Connection(
            self, address_name, sock, buffer_size,
            data_type=data_type,
            strict=strict,
            **kwargs
        )

        header = build_hello_header(
            self.address_name,
            data_type,
            strict,
            stream=connection.stream
        )

        try:
            sock.sendall(header)
            header = sock.recv(headers.size).decode("utf-8")
        except (socket.timeout, ConnectionAbortedError, UnicodeDecodeError):
            # UnicodeDecodeError: data received is corrupted, don't process it
            sock.close()
            return False

        # only check if header is ACCEPT, otherwise cancel connection
        if header.startswith(headers.accept_header):
            self.connections[address_name] = connection
            connection.start_thread()

            self.handle("connection", connection)
        else:
            sock.close()

        return self.connections.get(address_name, False)

    def get_local_peers(self) -> List[str]:
        """Returns the list of peers visible on the same local network.

        Returns:
            List[str]: the list of visible peers' addresses
        """
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
            sock.settimeout(.5)

            sock.bind((get_local_ip(), 1024))

            address, port = sock.getsockname()
            ping_header = build_header(headers.ping_header, {"pinger": f"{address}:{port}"})
            sock.sendto(ping_header, ("<broadcast>", 1024))

            addresses = []
            while True:
                try:
                    pong_header = sock.recv(headers.size).decode("utf-8")
                except (socket.timeout, UnicodeDecodeError):
                    # UnicodeDecodeError: data received is corrupted, don't process it
                    break

                if pong_header.startswith(headers.pong_header):
                    pong_header = split_header(pong_header)

                    if pong_header["ponger"] != self.address_name:
                        addresses.append(pong_header["ponger"])

        return addresses

    def broadcast(self, data: Any):
        """Broadcasts data to all the connected peers.

        Args:
            data (Any): the data to broadcast
        """
        for connection in self.connections.values():
            try:
                connection.send(data)
            except (DataTypeError, DataSizeError):
                continue

    def start(self):
        """Attempts to start this peer's server and pinger (if needed)."""
        if not self._server_active:
            self._server_active = True
            self.server_thread.start()

            if not self.invisible:
                self.pinger_thread.start()

    def stop(self, _async=False):
        """Attempts to stop this peer and all its connections.

        Args:
            _async (bool, optional): whether to stop this peer asynchronously. Defaults to False.
        """
        self._server_active = False

        connections = list(self.connections.values())
        for connection in connections:
            connection.close()

        if _async:
            for connection in connections:
                connection.thread.join()

            if self.server_thread.is_alive():
                self.server_thread.join()
            if self.pinger_thread.is_alive():
                self.pinger_thread.join()

    def _handle_offer(self, offer_header: str, sock: socket.socket) -> bool:
        """Handles an offer received from a peer.

        Args:
            offer_header (str): the header received.
            sock (socket.socket): the socket holding the connection.

        Returns:
            bool: whether this offer was accepted or rejected.
        """
        header = split_header(offer_header)

        # don't process header if it does not contains the minimum needed key/values pairs
        if any([key not in header for key in headers.required_hello_fields]):
            return False

        peer_name = header["peer_name"]

        connection = Connection(
            self, peer_name, sock, self.buffer_size,
            **header
        )

        try:
            if self.handle("offer", connection):
                accept = build_header(headers.accept_header, {})
                sock.sendall(accept)

                self.connections[peer_name] = connection
                connection.start_thread()

                self.handle("connection", connection)
                return True
            else:
                deny = build_header(headers.deny_header, {})
                sock.sendall(deny)
        except ConnectionAbortedError:
            # sock.sendall raised ConnectionAbortedError: connection is lost
            pass

        sock.close()
        return False

    def _listen_pings(self):
        """Starts this peer's pinger, used to answer pings from other seeking peers."""
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as pinger:
            pinger.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            pinger.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
            pinger.settimeout(.5)

            # will raise EADDRINUSE error if 2 peers are from the same device on Windows
            pinger.bind(("", 1024))

            while self._server_active and not self.invisible:
                try:
                    ping_header = pinger.recv(512).decode("utf-8")
                except (socket.timeout, UnicodeDecodeError):
                    # UnicodeDecodeError: data received is corrupted, don't process it
                    continue

                # in case this peer's visibility changed within the timeout window
                if ping_header.startswith(headers.ping_header) and not self.invisible:
                    ping_header = split_header(ping_header)
                    address, port = ping_header["pinger"].split(":")

                    pong_header = build_header(headers.pong_header, {"ponger": self.address_name})
                    pinger.sendto(pong_header, (address, int(port)))

    def _listen_offers(self):
        """Starts this peer's server, used to listen for connection requests."""
        self.server.listen()
        self.handle("listen")

        while self._server_active:
            if len(self.connections) >= self.max_connections > 0:
                time.sleep(self.timeout)
                continue

            try:
                # will block until offer received AND accepted or socket timeout
                sock, peer_address = self.server.accept()
            except socket.timeout:
                # no offer received within timeout seconds
                continue

            sock.settimeout(self.timeout)

            try:
                # will block until a hello header is received
                header = sock.recv(headers.size).decode("utf-8")
            except (socket.timeout, UnicodeDecodeError, ConnectionAbortedError):
                # socket.timeout: no offer received within timeout seconds, we cancel the connection
                # data received is corrupted, don't process it
                sock.close()
                continue

            if header.startswith(headers.hello_header):
                self._handle_offer(header, sock)

        self.server.close()
        self.handle("stop")

    def __enter__(self):
        self.start()
        return self

    def __exit__(self, type, value, traceback):
        self.stop()
        return False  # always reraise exception
