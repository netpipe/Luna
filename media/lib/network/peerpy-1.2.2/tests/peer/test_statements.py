from peerpy import Peer


def test_with():
    """Tests the with statement used on peer"""
    with Peer() as peer:
        assert peer.server_thread.is_alive()
