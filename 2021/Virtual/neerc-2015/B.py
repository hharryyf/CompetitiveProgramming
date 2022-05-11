inp = open("binary.in", 'r')
oup = open("binary.out", 'w')
a = [1]
b = []
c = [1]
pw = 1

def ok(x):
    return bin(x).endswith(str(x))

while len(c) <= 10000:
    for v in a:
        if ok(v + 10 ** pw - 10 ** (pw - 1)):
            b.append(v + 10 ** pw - 10 ** (pw - 1))
    for v in a:
        if ok(v + 10 ** pw):
            b.append(v + 10 ** pw)
    
    for v in b:
        c.append(v)
    a = b
    b = []
    pw += 1

[n] = map(int, inp.readline().split())
oup.write(str(c[n-1]))

