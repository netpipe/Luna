# Title: Arithmetic Addition
#
# Desc: In this module you can find functions for addition, subtraction,
#       multiplication, division (the basic arithmetic)
#
# Authors: Demir Antay -- demir99antay@gmail.com -- @demirantay
#


def add(num1, num2):
    '''
    definition: name(arg1, arg2) {...}
    objective : returns the sum of two arguments
    '''
    return num1 + num2


def add_nums(*arg):
    '''
    definition: name(*args, . . .) {...}
    objective : you can give as many arguments as you want to this function
                e.g. func(1, 5, 6) or func(9, 1002, 234)
    '''
    sum = 0

    for argument in arg:
        sum += argument

    return sum


def arr_sum(array):
    '''
    definition: name( array[] ) {...}
    objective : returns the sum of all elements in the given array
    '''

    sum = 0

    for element in array:
        sum += element

    return sum


def tup_sum(tuple):
    '''
    definition: name(tuple) {...}
    objective : returns the sum of all elements in the given tuple
    '''

    sum = 0

    for element in tuple:
        sum += element

    return sum


def subtract(num1, num2):
    '''
    definition: func(arg1, arg2) {...}
    objective : the function returns you arg1 - arg2
    '''
    return num1 - num2


def subtract_nums(*args):
    '''
    definition: func(*args, . . .) {...}
    objective : you can give as many arguments as you want to this function
                e.g. func(1, 5, 6) or func(9, 1002, 234) and every argument
                will get subtracted from the before argument
    '''

    result = args[0]

    for i in range(1, len(args), 1):
        result -= args[i]

    return result


def arr_subtract(array):
    '''
    definition: func( array[] ) {...}
    objective : returns the subtraction of all elements in the given array
    '''

    result = array[0]

    for i in range(1, len(array), 1):
        result -= array[i]

    return result


def tup_subtract(tuple):
    '''
    definition: func(tuple) {...}
    objective : returns the subtraction of all elements in the given tuple
    '''
    result = tuple[0]

    for i in range(1, len(tuple), 1):
        result -= tuple[i]

    return result


def multiply(num1, num2):
    '''
    definition: name(arg1, arg2)
    objective : returns the multiplication of two arguments
    '''
    return num1 * num2


def multiply_nums(*args):
    '''
    definition: name(*args, . . .) {...}
    objective : you can give as many arguments as you want to this function
                e.g. func(1, 5, 6) or func(9, 1002, 234)
    '''

    result = 1

    for argument in args:
        result *= argument

    return result


def arr_multiply(array):
    '''
    definition: func( array[] ) {...}
    objective : multiplies every element in the given array
    '''

    result = 1

    for element in array:
        result *= element

    return result


def tup_multiply(tuple):
    '''
    definition: func(tuple) {...}
    objective : multiplies every element in the given tuple
    '''

    result = 1

    for element in tuple:
        result *= element

    return result


def divide(num1, num2):
    '''
    definition: func(arg1, arg2) {...}
    objective : divides the given two elements
    '''
    return num1 / num2


def divide_nums(*args):
    '''
    definition: func(arg1, arg2, ...) {...}
    objective : you can give as many args as you want and the func divides
                the nums from left to right
    '''

    first_arg = args[0]

    for i in range(1, len(args), 1):
        first_arg /= args[i]

    return first_arg


def arr_divide(array):
    '''
    definition: func( array[] ) {...}
    objective : divides the elements of the array from left to right
    '''

    first_arg = array[0]

    for i in range(1, len(array), 1):
        first_arg /= array[i]

    return first_arg


def tup_divide(tuple):
    '''
    definition: func(tuple(...)) {...}
    objective : divides the elements of the tuple from left to right
    '''

    first_element = tuple[0]

    for i in range(1, len(tuple), 1):
        first_element /= tuple[i]

    return first_element
