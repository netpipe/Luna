import cmath
def fibo(n):
    assert n > 0, "n cannot be smaller than 0"
    a, b = 0, 1
    while a < n:
        a, b = b, a+b
    return a

def factorial(num):
    answer = 1
    for i in range(1, num + 1):
        answer = answer * i
    return answer

def sqare(num):
    sqared = num * num
    return sqared

def cube(num):
    return num * num * num

def raise_to_power(num, nth_power):
    ans = num
    for i in range(nth_power):
        ans = num * ans
    return ans

def find_factors(num):
    answer = ''
    for i in range(1, num):
        if (num % i) == 0:
            answer += str(i)
            answer += ' '
    answer = answer.split()
    answers = [int(ans) for ans in answer]
    return answers

def quadratic(a, b, c):
    d = (b**2) - (4*a*c)
    root1 = (-b - cmath.sqrt(d)) / (2 * a)
    root2 = (-b + cmath.sqrt(d)) / (2 * a)
    return [root1, root2]
