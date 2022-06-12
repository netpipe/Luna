import socket
import requests

from typing import Dict, Any, Union, Tuple

from ..exceptions import HeaderSizeError
from ..protocol import headers, defaults

valid_data_types = ["raw", "json", "bytes"]


def get_local_ip() -> str:
    """Returns the local IP address of this device.

    Returns:
        str: the ipv4 used by this device.
    """
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        # works even with no internet connection
        sock.connect(("8.8.8.8", 80))
        return sock.getsockname()[0]


def get_public_ip() -> str:
    """Returns the local IP address of this device.

    Returns:
        str: the ipv4 used by this device.
    """
    try:
        return requests.get("http://ident.me").text
    except:
        return "localhost"


def check_address(address: str, port: int) -> Tuple[Tuple[str, int], str]:
    """Checks the given address and port allow multiple input types.

    Args:
        address (str): the ipv4 address, followed by the port if wanted
        port (int): the port to use (can be None if port is provided in address)

    Raises:
        ValueError: if port is None and no port can be found in address
        ValueError: if address is not ipv4:port nor (ipv4, port)

    Returns:
        Tuple[Tuple[str, int], str]: the normalized address and port in a tuple, the address and port in a string
    """
    if isinstance(address, str):
        if ":" in address:
            ipv4, port = address.split(":")[:2]
            address = (ipv4, int(port))
        elif port is None:
            raise ValueError("A port must be specified!")
        else:
            address = (address, int(port))
    elif not hasattr(address, "__getitem__"):
        raise ValueError("address should be a string ipv4:port or a tuple (ipv4, port)!")
    else:
        address = (str(address[0]), int(address[1]))

    address_name = f"{address[0]}:{address[1]}"
    return address, address_name


def build_header(header_type: str, contents: Dict[str, Any]) -> bytes:
    """Returns a normalized header of type header_type.

    Args:
        header (Dict[str, Any]): the data to put in the header.
        header_type (str, optional): the type of the header to generate. Defaults to data_header.

    Returns:
        bytes: the generated encoded header
    """
    header_elements = [key + headers.key_separator + str(value) for key, value in contents.items()]
    header_body = headers.values_separator.join(header_elements)
    if len(header_body) > 0:
        header_body = headers.separator + header_body

    header_bytes = (header_type + header_body).encode("utf-8")
    tail_size = headers.size - len(header_bytes)
    if tail_size < 0:
        raise HeaderSizeError(
            f"Header size ({len(header_bytes)}) is greater than the protocol's setting ({headers.size})!")

    return header_bytes + headers.separator.encode("utf-8") * tail_size


def build_hello_header(peer_name: str, data_type: str, strict: bool, stream: bool = False, **kwargs) -> bytes:
    """Builds a header used to handshake with another peer and set up a data connection.

    Args:
        peer_name (str): the name of the peer initiating the handshake.
        data_type (str): the data type to be sent.
        stream (bool): whether this connection is for streaming or not.

    Returns:
        bytes: the generated encoded header
    """
    header_contents = {
        # so that the other peer knows who we are
        "peer_name": peer_name,
        # so that the other peer knows what data type to handle
        "data_type": data_type,
        # so that the other peer knows if the connection is strict or not
        "strict": strict
    }

    if stream:
        # so that the other peer knows if the connection is a streaming connection
        header_contents["stream"] = stream

    return build_header(headers.hello_header, header_contents)


def build_data_header(data_size: int, data_type: str) -> bytes:
    """Builds a header used to indentify data that will be send.

    Args:
        data_size (int): the size of the data, in bytes.
        data_type (str): the data type to be sent.

    Returns:
        bytes: the generated encoded header
    """
    return build_header(headers.data_header, {
        # so that the other peer knows how much data to handle
        "data_size": data_size,
        # so that the other peer know which type of data to handle
        "data_type": data_type
    })


def split_header(header: str) -> Dict[str, Union[str, int]]:
    """Splits the given header into a dictionnary mapping keys to values.

    Args:
        header (str): the header received

    Returns:
        Dict[str, Union[str, int]]: the header mapping entries found in the original header
    """
    # TODO: what if header contains malicious data?? can crash the thread...
    if headers.separator in header:
        header = header.split(headers.separator)[1]

    values = {}
    for part in header.split(headers.values_separator):
        key, value = part.split(headers.key_separator)

        # convert data type if necessary
        if key in headers.data_types_parsers:
            value = headers.data_types_parsers[key](value)

        values[key] = value

    return values
