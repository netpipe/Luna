"""
RSA
- http://en.wikipedia.org/wiki/RSA

Implementation RSA in Python
- http://stuvel.eu/rsa
- http://wangcong.org/blog/?p=253
"""
import math
import random
import sys


__all__ = [
    "rsa",
]


def rsa(m, p, q, d=False):
    """
    """
    e, n = long(p, 16), long(q, 16)  # pubkey
    l = (len(q) + 1) / 2  # is this same with k?
    o, inb = l - d, l - 1 + d  # inb is ignored for correct value, why?

    if not d:
        # k as described in RFC 2313
        k = int(math.log(n) / math.log(2) / 8 + 1)
        m = '\x00\x02' + random_bytes(k - len(m) - 3) + '\x00' + m  # padding

    ret, s = [], True               # init ret and while loop

    while s:
        s = m                       # s = m[:inb]
        m = None                    # m = m[inb:]
        s and map(ret.extend,
                  map(lambda i, b=pow(reduce(lambda x, y: (x << 8L) + y, map(ord, s)), e, n): chr(b >> 8 * i & 255),
                      range(o-1, -1, -1)
                      )
                  )

    ret = ''.join(ret)

    if d:
        return ret[ret.index('\x00', 2) + 1:]
    else:
        return ret


def random_bytes(size):
    size = max(8, size)
    return ''.join(chr(random.randrange(1, 256)) for i in xrange(size))


def encrypt(plain, e, n):
    return rsa(plain, e, n)


def decrypt(s, d, n):
    return rsa(s, d, n, True)



