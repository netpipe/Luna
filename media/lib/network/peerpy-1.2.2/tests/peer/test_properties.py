import time
import pytest

from ..utils import with_peers


@pytest.fixture
@with_peers
def peers():
    return [
        {
            "address": "localhost:11111",
            "timeout": 1.576
        }, {
            "invisible": True
        }, {}
    ]


def test_stop(peers):
    """Tests the instanciation, properties and asynchronous stop of a peer"""
    assert peers[0].server_thread.is_alive()
    assert peers[0].address == ("127.0.0.1", 11111)
    assert peers[0].address_name == "127.0.0.1:11111"
    assert peers[0].timeout == 1.576
    assert peers[1].invisible


def test_invisibility(peers):
    """Tests the invisibility argument at peer instanciation"""
    assert peers[2].get_local_peers() == [peers[0].address_name]


def test_invisibility_property(peers):
    """Tests the invisibility property when a peer is already running"""
    peers[2].invisible = True
    peers[2].invisible = False
    assert sorted(peers[1].get_local_peers()) == sorted([peers[0].address_name, peers[2].address_name])

    peers[2].invisible = True
    assert peers[1].get_local_peers() == [peers[0].address_name]

    time.sleep(.6)
    assert not peers[2].pinger_thread.is_alive()

    peers[2].invisible = False
    assert peers[2].pinger_thread.is_alive()


def test_timeout(peers):
    """Tests the timeout property of a peer"""
    peers[0].timeout = .1

    assert peers[0].timeout == .1
