# Title: Arithmetic Addition
#
# Desc: In this module you can find functions for geometry formulas
#
# Authors: Demir Antay -- demir99antay@gmail.com -- @demirantay
#

PI = 3.14159265359


def area_of_triangle(b, h):
    '''
    definition: func(b, h) {...}
    objective :  returns you the are of a triangle on its base and height
                    A=1/2bh
    '''

    area = (1 / 2) * (b * h)

    return area


def area_of_circle(r):
    '''
    definition: func(r) {...}
    objective : returns you the area of a circle based on its r
                A=πr²
    '''

    area = PI * (r * r)

    return area


def circumfrence(r):
    '''
    definition: func(r) {...}
    objective : retursn you the circumfrence of a circle based on its r
                C = 2πr
    '''

    circumfrence = 2 * PI * r

    return circumfrence


def area_of_rect(l, w):
    '''
    definition: func(l, w) {...}
    objective: returns you the are of a rectangle on its length and height
                A= length x width
    '''

    area = l * w

    return area


def trapezoid_midsegment(b1, b2):
    '''
    definition: func(b1, b2) {...}
    objective : returns you the midsegment of a trapezoid on its two bases
                1/2 (base 1 + base 2)
    '''

    midsegment = (1 / 2) * (b1 + b2)

    return midsegment


def volume_of_rect_prism(l, w, h):
    '''
    definition: func(l, w, h) {...}
    objective : returns you the volume of a rectangular prism based on its
                length, width and height
                V = lwh
    '''

    volume = l * w * h

    return volume


def volume_of_tri_prism(b, h):
    '''
    definition: func(b, h) {...}
    objective : returns you the volume of a tringular prism based on its
                base and height values
                V=(1/2bh)h
    '''

    volume = ((1 / 2) * (b * h)) * h

    return volume


def volume_of_cylander(h):
    '''
    definition: func(h) {...}
    objective : returns you the volume of a cylander based on its height
                V=πr²h
    '''

    volume = (PI * (r * r)) * h

    return volume


def volume_of_cone(r, h):
    '''
    definition: func(r, h) {...}
    objective: returns you the volume of a cone
                1/3πr²h
    '''

    volume = (1 / 3) * (PI * (r * r)) * h

    return volume


def volume_of_rect_pyramid(l, w, h):
    '''
    definition: func(l, w, h) {...}
    objective: return you the volume of a rectangular pyramid
                V=1/3lwh
    '''

    volume = (1 / 3) * l * w * h

    return volume


def volume_of_tri_pyramid(b, h):
    '''
    definition: func(b, h) {...}
    objective: returns you the volume of a triungluar pyramid
                V=1/3(1/2bh)h
    '''

    volume = (1 / 3) * ((1 / 2) * b * h) * h

    return volume


def volume_of_sphere(r):
    '''
    definition: func(r) {...}
    objective: returns you the volume of a sphere based on its r
                V=4/3πr³
    '''

    volume = (4 / 3) * PI * (r * r * r)

    return volume


def volume_of_hemisphere(r):
    '''
    definition: func(r) {...}
    objective : returns you the volume of a hemisphere based on its r
                V=2/3πr³
    '''

    volume = (2 / 3) * PI * (r * r * r)

    return volume
