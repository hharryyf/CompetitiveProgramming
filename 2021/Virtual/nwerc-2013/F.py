import datetime
import sys

days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def calcdj(yr, mo, dy):
    ret = (yr - 1) // 4 + 365 * (yr - 1)
    for i in range(1, mo):
        ret += days[i]
        if yr % 4 == 0 and i == 2:
            ret += 1
    ret += dy
    return ret

for line in sys.stdin:
    dst = ""
    for li in line:
        if li != '\n':
            dst += li
    ss = dst.split("-")
    yr, mo, dy = int(ss[0]), int(ss[1]), int(ss[2])
    #x = datetime.datetime.strptime(dst, "%Y-%m-%d").date()
    dlt = calcdj(yr, mo, dy) - calcdj(1582, 10, 4)
    target = datetime.timedelta(days=dlt) + datetime.datetime(1582, 10, 15)
    print(target.date())