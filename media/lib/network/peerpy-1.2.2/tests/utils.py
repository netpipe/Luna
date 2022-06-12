import time
from typing import List, Dict, Any, Callable

from peerpy import Peer


def with_peers(peers_args: Callable[[], List[Dict[str, Any]]]):
    def wrapper():
        peers = []
        for peer_args in peers_args():
            peer_args["timeout"] = peer_args.get("timeout", 1.)

            peer = Peer(**peer_args)
            peer.start()

            peers.append(peer)

        time.sleep(.5)  # wait for servers to be listening

        yield peers

        for peer in peers:
            peer.stop(_async=True)
    return wrapper
