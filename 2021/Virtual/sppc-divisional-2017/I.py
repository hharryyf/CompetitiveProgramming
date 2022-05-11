v, d = map(int, input().split())
bk = 0
tol = v
while tol <= d:
    bk += 1
    v *= 2
    tol += v
print(bk)
