nTot, wLim = tuple(map(int, input().split()))
lstCharms = []
for i in range(nTot):
    charmIn = list(map(int, input().split()))
    lstCharms.append(charmIn)
lstCharms.sort(key=lambda x: [x[0], x[1]])

#Recursive:
def dearDaisy(i = nTot, w = wLim):
    if i == 0:
        return 0
    cW, cD = lstCharms[i - 1]
    idx = w - cW
    if idx < 0:
        return dearDaisy(i - 1, w)
    return dearDaisy(i - 1, w - cW) + cD


#DynaProg:
# for i in range(wLim + 2):
#     imlst = []
#     for j in range(wLim + 2):
#         imlst.append(0)
#     mtxDP.append(imlst)

#space-saving version:
#SketchPad : a 2-dim matrix with row == 2;
sketchPad = []
for j in range(2):
    imlst = []
    for i in range(wLim + 2):
        imlst.append(0)
    sketchPad.append(imlst)
#The main loop:
curR : int
for chrIdx in range(nTot):
    wi, di = lstCharms[chrIdx]
    #to control the idx of row to go up and down alternatively
    if chrIdx & 1:#odd
        curR = 0
        ofs = 1
    else:
        curR = 1
        ofs = -1
    for j in range(1, wLim + 1):
        if j - wi >= 0:
            sketchPad[curR][j] = sketchPad[curR + ofs][j - wi] + di
        else:
            sketchPad[curR][j] = sketchPad[curR + ofs][j]

print(sketchPad[curR][wLim])

#loop inference
# for i in range(1, nTot + 1):
#     for j in range(1, wLim + 1):
#         wi, di = lstCharms[i - 1]
#         if (j - wi >= 0):
#             mtxDP[i][j] = mtxDP[i - 1][j - wi] + di
#         else:
#             mtxDP[i][j] = mtxDP[i - 1][j]
# print(mtxDP[nTot][wLim])