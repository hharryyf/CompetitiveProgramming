T = int(input())
while T > 0:
    T -= 1
    s = input()
    t = input()
    b1, b2 = s.count('B'), t.count('B')
    if b1 % 2 != b2 % 2:
        print('NO')
        continue
    s = s.replace('B', '')
    t = t.replace('B', '')
    flag = True
    while flag:
        flag = False
        if 'AA' in s:
            s = s.replace('AA', '',1)
            flag = True
        elif 'CC' in s:
            s = s.replace('CC', '',1)
            flag = True
        if 'AA' in t:
            t = t.replace('AA', '',1)
            flag = True
        elif 'CC' in t:
            t = t.replace('CC', '',1)
            flag = True

    if s == t:
        print("YES")
    else:
        print("NO")