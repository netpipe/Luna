import time
import pytest

from ..utils import with_peers


@pytest.fixture
@with_peers
def peers():
    return [{}, {
        "handlers": {
            "offer": lambda peer, connection: False
        }
    }]


def test_deny(peers):
    """Tests the denial process of a connection request"""
    assert not peers[0].connect(peers[1].address)
