T = int(input())
for i in range(0, T):
    n, k = map(int, input().split())
    v = n - (k - 3)
    s = ''
    if v % 2 == 1:
        s = '1 ' * (k - 3) + str(v // 2) + " 1 " + str(v // 2)
    else:
        if v % 4 == 0:
            s = '1 ' * (k - 3) + str(v // 4) + " " + str(v // 2) + " " + str(v // 4)
        else:
            s = '1 ' * (k - 3) + str((v - 2) // 2) + " 2 " + str((v - 2) // 2)
    print(s)