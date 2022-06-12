import time
import pytest

from ..utils import with_peers

datas = []


@pytest.fixture
@with_peers
def peers():
    datas.clear()

    def set_connection_handler(peer, connection):
        connection.handlers["data"] = lambda connection, data: datas.append(data)
        return True

    peer_adder_args = {
        "handlers": {
            "connection": set_connection_handler
        }
    }

    return [{}, peer_adder_args, peer_adder_args]


def test_receive_raw(peers):
    """Tests data sending from one peer to another"""
    connection = peers[0].connect(peers[1].address_name, data_type="raw")

    data_test = "2easy4u"
    connection.send(data_test)

    time.sleep(.1)

    assert len(datas) == 1 and datas[0] == data_test


def test_receive_json(peers):
    """Tests data sending from one peer to another"""
    connection = peers[0].connect(peers[1].address_name, data_type="json")

    data_test = "2easy4u"
    connection.send(data_test)

    time.sleep(.1)

    assert len(datas) == 1 and datas[0] == data_test


def test_receive_bytes(peers):
    """Tests data sending from one peer to another"""
    connection = peers[0].connect(peers[1].address_name, data_type="bytes")

    data_test = b"2easy4u"
    connection.send(data_test)

    time.sleep(.1)

    assert len(datas) == 1 and datas[0] == data_test


def test_receive_multiple(peers):
    """Tests data sending from one peer to another"""
    connection_0 = peers[0].connect(peers[1].address_name, data_type="json")
    connection_2 = peers[2].connect(peers[1].address_name, data_type="json")

    datas_test = [f"data{i}" for i in range(15)]
    for data in datas_test:
        connection_0.send(data)
        connection_2.send(data)

    time.sleep(.1)

    assert len(datas) == (len(peers) - 1) * len(datas_test)


def test_receive_stream(peers):
    connection = peers[0].connect(peers[1].address_name, data_type="raw", stream=True)

    datas_test = [f"data" for _ in range(15)]  # must be of same bytes length
    for data_test in datas_test:
        connection.send(data_test)

    time.sleep(.1)

    assert datas == datas_test
