inp = input()
inp = inp.split()
N = int(input())

def check(st):
    m = len(st)
    for i in range(0, len(inp)):
        curr = ""
        for j in range(i, len(inp)):
            if len(curr) < m:
                curr += inp[j]
            else:
                break
        if len(curr) == m:
            if curr == st:
                continue
            s1 = sorted(curr)
            s2 = sorted(st)
            if s1 == s2:
                return True
    return False

for i in range(0, N):
    x = input()
    if check(x) == True:
        print(x)
        break