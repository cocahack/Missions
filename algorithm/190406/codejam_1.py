def solve(n):
    ret = 0
    copy_n = n
    base = 1
    while n:
        mod = n % 10
        if mod == 4:
            copy_n -= base
            ret += base
        base *= 10
        n -= mod
        n /= 10
    return copy_n, ret

t = int(input())
case = 1
while t > 0:
    n = int(input())
    a, b = solve(n)
    print("Case #%d: %d %d" % (case, a, b))
    case += 1
    t -= 1

