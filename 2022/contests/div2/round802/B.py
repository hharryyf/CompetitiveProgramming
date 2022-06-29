T = int(input())
while T > 0:
    N = int(input())
    s = input()
    if s[0] == '9':
        t = '1' * (N + 1)
        print(int(t) - int(s))
    else:
        t = '9' * N
        print(int(t) - int(s))
    T -= 1