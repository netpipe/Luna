import pytest

from src.kangaroo import Kangaroo


@pytest.fixture
def kangaroo() -> Kangaroo:
    """
    Create an instance to be used across the test suite
    :return: Kangaroo instance
    """
    kangaroo = Kangaroo()
    yield kangaroo


def test_send_with_success(kangaroo: Kangaroo) -> None:
    """
    Test if message is sent successfully
    """
    expected = "Hello"

    r = kangaroo.listen(3000)
    kangaroo.send(3000, expected)

    result = r.get_message()
    assert expected == result


def test_listen_with_success(kangaroo: Kangaroo) -> None:
    """
    Test if message is received successfully
    """
    expected = "World"

    r = kangaroo.listen(3001)
    kangaroo.send(3001, expected)

    assert r.has_new_message()


def test_get_message_fails(kangaroo: Kangaroo) -> None:
    """
    Test if the message is empty
    """
    r = kangaroo.listen(3003)
    assert r.get_message() == ""


def test_has_new_message_fails(kangaroo: Kangaroo) -> None:
    """
    Test if there's no new message
    """
    r = kangaroo.listen(3004)
    assert not r.has_new_message()
