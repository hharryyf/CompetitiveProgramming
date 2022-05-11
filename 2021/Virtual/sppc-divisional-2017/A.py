import re
N = int(input())
mp = {}
for i in range(N):
    ss = input()
    ss = ss.split()
    mp[ss[0]] = float(ss[1])

compound = input()
ret = ""
for i in range(0, len(compound)):
    ret += compound[i]
    if compound[i] > '9' or compound[i] < '0':
        if i == len(compound) - 1 or (compound[i+1] >= 'A' and compound[i+1] <= 'Z'):
            ret += '1'

cmp = re.split('[0-9\n]', ret)
num = re.split('[A-Za-z\n]', ret)
cmp1 = []
cmp2 = []
for v in cmp:
    if len(v) != 0:
        cmp1.append(v)

for v in num:
    if len(v) != 0:
        cmp2.append(float(v))

ans = 0
for i in range(len(cmp1)):
    ans += mp[cmp1[i]] * cmp2[i]

print(ans)