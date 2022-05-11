# Not my code, Dallas coded it in contest
MIN = -2**15
MAX = 2**15-1
inps = []
with open("hard.in","r") as f:
    for line in f:
        if not line.strip():
            continue
        line = line.strip().strip("||").split("&&")
        low = MIN
        high = MAX
        for el in line:
            if ">=" in el:
                low = int(el.split()[-1])
            else:
                high = int(el.split()[-1])
        if low <= high:
            inps.append([low,high])
inps.sort()
out = []
if len(inps):
    low = inps[0][0]
    high = inps[0][1]
    # print(inps)
    for el in inps[1:]:
        # print(low,high)
        if el[0] > high+1:
            out.append([low,high])
            low = el[0]
            high = el[1]
        else:
            high = max(high,el[1])
    out.append([low,high])
with open("hard.out","w") as f:
    if len(out) == 0:
        f.write("false\n")
    for i in range(len(out)):
        el = out[i]
        if el[0] != MIN and el[1] != MAX:
            f.write("x >= "+str(el[0])+" && x <= "+str(el[1]))
        elif el[0] == MIN and el[1] == MAX:
            f.write("true")
        elif el[0] == MIN:
            f.write("x <= "+str(el[1]))
        else:
            f.write("x >= "+str(el[0]))
        if i < len(out)-1:
            f.write(" ||\n")
        else:
            f.write("\n")