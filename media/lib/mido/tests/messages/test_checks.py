from pytest import raises
from mido.messages.checks import check_time
from mido.py2 import PY2


def test_check_time():
    check_time(1)
    check_time(1.5)

    if PY2:
        # long should be allowed. (It doesn't exist in Python3,
        # so there's no need to check for it here.)
        check_time(long('9829389283L'))  # noqa: F821

    with raises(TypeError):
        check_time(None)

    with raises(TypeError):
        check_time('abc')

    with raises(TypeError):
        check_time(None)

    with raises(TypeError):
        check_time('abc')
