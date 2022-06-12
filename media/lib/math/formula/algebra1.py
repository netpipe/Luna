# Title: Arithmetic Addition
#
# Desc: In this module you can find functions for algebra 1 formulas
#
# Authors: Demir Antay -- demir99antay@gmail.com -- @demirantay
#

from fractions import Fraction


def slope_intercept(m, x, b):
    '''
    definition: func(m, x, b) {...}
    objective : returns the 'y' from the slope intercept formula:
                y = mx + b
    '''
    y = m * x + b
    return y


def point_slope(m, x1, x2):
    '''
    definition: func(m, x1, x2) {...}
    objective : returns the y1 - y2 's  value --
                y1 - y2 = m(x1 - x2)
    '''
    result = m * (x1 - x2)
    return result


def slope_formula(x1, x2, y1, y2):
    '''
    definition: func(x1, x2, y1, y2) {...}
    objective : returns the slope (m) from the slope formula
                m = y2 - y1 / x2 - x1
    '''
    slope = (y2 - y1) / (x2 - x1)
    return slope
