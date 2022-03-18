vN, vM = tuple(map(int, input().split()))
skchP = []
for j in range(2):
    _lst = []
    for i in range(vM + 2):
        _lst.append(0)
    skchP.append(_lst)
for idx in range(vN):
    wi, di = tuple(map(int, input().split()))
    if idx & 1:
        cR = 0
        ofs = 1
    else:
        cR = 1
        ofs = -1
    for j in range(1, vM + 1):
        t = skchP[cR + ofs][j - wi] + di
        pv = skchP[cR + ofs][j]
        if j - wi >= 0 and t > pv:
            skchP[cR][j] = t
        else:
            skchP[cR][j] = pv
print(skchP[cR][vM])