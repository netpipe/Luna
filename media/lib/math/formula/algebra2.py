# Title: Arithmetic Addition
#
# Desc: In this module you can find functions for algebra 2 formulas
#
# Authors: Demir Antay -- demir99antay@gmail.com -- @demirantay
#


def vertex(a, x, h, k):
    '''
    definition: func(a, x, h, k) {...}
    objective : returns the 'y' of the vertex formula
                y = a (x-h)^2 + k
    '''

    result = (a * ((x - h) * (x - h))) + k

    return result


def standart(x, a, b, c):
    '''
    definition: func(x, a, b, c) {...}
    objective: returns the 'y' of the standart formula
                y = ax^2 + bx +c
    '''

    result = (a * (x * x)) + (b * x) + c

    return result


def axis_symetry(a, b):
    '''
    definition: func(a, b) {...}
    objective : returns the 'x' of the axis symetry formula
                x = -b/2a
    '''

    result = -b / (2 * a)

    return result


def sum_of_cubes(a, b):
    '''
    definition: func(a, b) {...}
    objective : gives you the result of the arguments  sum of cubes
                (a+b)^3 = (a+b)(a^2 - ab + b^2)
    '''

    result = (a + b) * ((a * a) - (a * b) + (b * b))

    return result


def different_of_cubes(a, b):
    '''
    definition: func(a, b) {...}
    objective : gives you the result of the formula different of cubes
                (a-b)^3 = (a-b)(a^2 + ab + b^2)
    '''

    result = (a - b) * ((a * a) + (a * b) + (b * b))

    return result


def cube(x):
    '''
    definition: func(x) {...}
    objective : returns the cube of x
    '''

    result = x * x * x

    return result
