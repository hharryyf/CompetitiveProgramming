T = int(input())
while T > 0:
    n = int(input())
    if n % 2 == 0:
        # n / 2 'a' | 'b' | (n/2 - 1) 'a'
        v = n // 2
        print('a' * v + 'b' + 'a' * (v - 1))
    else:
        # n / 2 'a' | 'b' | 'c' | 'a' * (n / 2 - 1)
        v = n // 2
        if n == 1:
            print('a')
        else:
            print('a' * v + 'b' + 'c' + 'a' * (v - 1))
    T -= 1