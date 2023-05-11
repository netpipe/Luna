
PI=3.141592653589793
def sin(x):
    if x>2*PI:
        x-=2*PI
    elif x<2*PI:
        x+=2*PI
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
    return float(result)
    

def cos(x):
    if x>2*PI:
        x-=2*PI
    elif x<2*PI:
        x+=2*PI
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
    return float(result)
    

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


def atan2(x,y):
    if x==0:
        if y>0:
            return PI/2
        else:
            return -PI/2
    
    slope=y/x
    if slope>180:
        slope=180
    elif slope < -180 :
        slope=-180
    result=0
    if slope>=1:
        result=PI/2
        for i in range(40):
            result-=((-1)**i)/((2*i+1)*slope**(2*i+1))
    elif slope <=-1:
        result=-PI/2
        for i in range(40):
            result-=((-1)**i)/((2*i+1)*slope**(2*i+1))
    else:
        result=0
        for i in range(40):
            result+=((-1)**i)*(slope**(2*i+1))/(2*i+1)

    if x<0:
        if y>=0:
            result+=PI
        else:
            result-=PI
    result%=2*PI
    if result>PI:
        result-=2*PI
    elif result<-PI:
        result+=2*PI
    return result