import time
import pytest

from ..utils import with_peers


@pytest.fixture
@with_peers
def peers():
    return [{}] * 2


def test_connect_successful(peers):
    """Tests the connection of a peer to another"""
    connection = peers[0].connect(peers[1].address)

    assert connection
    assert peers[1].address_name in peers[0].connections
    assert peers[0].address_name in peers[1].connections


def test_disconnect(peers):
    """Tests the disconnection of a peer and its detection from the other peer"""
    connection = peers[0].connect(peers[1].address)
    connection_ = peers[1].connections[peers[0].address_name]

    connection.close()

    time.sleep(1.2)

    assert connection.closed
    assert connection_.closed
    assert not connection.thread.is_alive()
    assert not connection_.thread.is_alive()
    assert (peers[1].address_name not in peers[0].connections)
    assert (peers[0].address_name not in peers[1].connections)


def test_connect_fails(peers):
    """Tests the failing connection of a peer to another"""
    connection = peers[0].connect(peers[0].address)

    assert not connection

    connection = peers[0].connect("localhost:1010")

    assert not connection

    connection1 = peers[0].connect(peers[1].address, data_type="json")
    connection2 = peers[0].connect(peers[1].address, data_type="json")

    assert connection1 == connection2

    peers[0].connect(peers[1].address, data_type="raw")

    time.sleep(.5)

    assert connection2.closed
