import pytest

from ..utils import with_peers


@pytest.fixture
@with_peers
def peers():
    return [{}] * 2


def test_send_large(peers):
    """Tests relatively large data sending from one peer to another"""
    connection = peers[0].connect(peers[1].address_name, data_type="raw")

    connection.send(list(range(int(2e6))))


def test_stream(peers):
    """Tests relatively large data sending from one peer to another"""
    connection = peers[0].connect(peers[1].address_name, data_type="raw", stream=True)

    for _ in range(10):
        connection.send("2easy4u")
