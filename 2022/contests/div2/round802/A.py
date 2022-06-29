T = int(input())
for i in range(0, T):
    N, M = map(int, input().split())
    print(M * (M + 1) // 2 + (M + N * M) * N // 2 - M)