import pytest

from ..utils import with_peers


@pytest.fixture
@with_peers
def peers():
    return [{}] * 10


def test_ping_large_network(peers):
    """Tests the discovery protocol on a relatively large network"""
    assert sorted(peers[0].get_local_peers()) == sorted([peer.address_name for peer in peers[1:]])
