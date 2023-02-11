def sin(x):
    result = x
    positive = False
    exp = 3
    denom = 3
    for i in range(40):
        if positive:
            result += (x ** exp) / (factorial(denom))
            exp += 2
            denom += 2
            positive = False
        else: 
            result -= (x ** exp) / (factorial(denom))
            exp += 2
            denom += 2
            positive = True
    return round(result,12)
    

def cos(x):
    result = 1
    positive = False
    exp = 2
    denom = 2
    for i in range(40):
        if positive:
            result += (x ** exp) / (factorial(denom))
            exp += 2
            denom += 2
            positive = False
        else:
            result -= (x ** exp) / (factorial(denom))
            exp += 2
            denom += 2
            positive = True
    return round(result, 12)
    

def tan(x):
    try:
        result = round(sin(x) / cos(x), 12)
    except ZeroDivisionError:
        return "undefined"
    return result

def csc(x):
    try:
        result = round(1/sin(x),12)
    except ZeroDivisionError:
        return "undefined"
    return result

def sec(x):
    try:
        result = round(1/cos(x), 12)
    except ZeroDivisionError:
        return "undefined"
    return result

def cot(x):
    try:
        result = round(cos(x)/sin(x), 12)
    except ZeroDivisionError:
        return "undefined"
    return result

def factorial(x):
    product = 1
    for i in range(1,x + 1):
        product *= i
    return product