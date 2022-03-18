import sys
'''
INPUT:
14
274238584359484875958348749595954893736597
13
111127423858435948487595834874959595489373659787
OUTPUT:
6511
25259
'''
# f = open("E:\\Downloads\\in.txt", "rt", encoding='UTF-8')
for line in sys.stdin:
    optN = int(line)
    numStr = sys.stdin.readline().strip('\n')
    numLen = len(numStr)
    numTar = int(numStr)
    numMtx = []
    for i in range(1, numLen + 1):
        inlst = []
        for j in range(1, i + 1):
            tmp = int(numStr[-i:(numLen - i + j)])
            inlst.append(tmp)
        numMtx.append(inlst)

    minSumMtx = []
    inlst2 = []
    for i in range(optN + 2):
        inlst2.append(float('inf'))
    minSumMtx.append(inlst2)

    for curLen in range(1, numLen + 1):
        inlst1 = []
        for curOptN in range(0, optN + 2):
            curOprd = 0
            if (curOptN == 0):
                curOprd = numMtx[curLen - 1][curLen - 1]
            elif (curLen <= curOptN):
                curOprd = float('inf')
            elif (curLen % (curOptN + 1) == 0):
                inv = curLen // (curOptN + 1)
                for i in range(curLen - 1, -1, -inv):
                    curOprd += numMtx[i][inv - 1]
            elif (curOptN == 1):
                inv = curLen // 2
                if (numStr[numLen - curLen] > numStr[numLen - curLen + inv]):
                    curOprd = numMtx[curLen - 1][inv - 1] + numMtx[curLen - inv][inv]
                else:
                    curOprd = numMtx[curLen - 1][inv] + numMtx[curLen - inv - 2][inv - 1]
            else:
                curOprd = float('inf')
                for i in range(0, curLen):
                    tmp = numMtx[curLen - 1][i] + minSumMtx[curLen - 1 - i][curOptN - 1]
                    if (tmp < curOprd):
                        curOprd = tmp
            inlst1.append(curOprd)
        minSumMtx.append(inlst1)

    print(minSumMtx[numLen][optN])

    # print("numMtx:\n")
    # for i in numMtx:
    #     for j in i:
    #         print(f'{j:6}', end=" ")
    #     print("\n")
    # print("minSumMtx:\n")
    # for i in minSumMtx:
    #     for j in i:
    #         print(f'{j:6}', end=" ")
    #     print("\n")