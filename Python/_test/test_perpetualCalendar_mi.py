'Version 0: early version using one scaler and calcIntv'
def leapyear(yy: int):
    if any((yy%4==0 and not yy%100==0, yy%400==0)):
        return True
    return False

def date2ds(date: list, bof=False):
    if leapyear(date[0]):
        mmlst = [31,29,31,30,31,30,31,31,30,31,30,31]
    else:
        mmlst = [31,28,31,30,31,30,31,31,30,31,30,31]
    ds = sum(mmlst[:date[1]-1]) + date[2]
    if bof: # bof means: backward or forward: True for forward and False for back
        ds = sum(mmlst) - ds
    return ds

def validcheck(stri):
    import sys
    try:
        imlst = list(map(int, stri.split()))
        if not len(imlst) == 3:
            raise Exception('length error')
        yy = imlst[0]
        mm = imlst[1]
        dd = imlst[2]
        if any((mm>12, mm<1, dd<1, dd>31)):
            raise Exception('month or day error')
        if mm in (4,6,9,11) and dd>30:
            raise Exception('30-month error')
        if mm == 2:
            if leapyear(yy) and dd>29:
                raise Exception('leapyear error')
            elif dd > 28:
                raise Exception('leapyear error')
    except:
        return ("Illegal",sys.exc_info()[1])
    else:
        return imlst

def calcIntv(tar: list, std=[2020,11,18]):
    if tar[0] <= std[0]: # judge which date is earlier, target or standard
        i1, i2 = tar, std
        sign = -1
    else:
        i1, i2 = std, tar
        sign = 1
    count = 0 # calc how many days in the middle years, which means subtrating the first and the last year
    for i in range(i1[0], i2[0]):
        if leapyear(i):
            count += 1
    midY = (i2[0] - i1[0]) * 365 + count
    firY_ds = date2ds(i1) # calc how many days BEFORE the date
    lasY_ds = date2ds(i2)
    return sign * (-firY_ds + midY + lasY_ds)

def proc(data):
    t0 = tm.perf_counter()
    weeklst = ["Wednesday","Thursday","Friday","Saturday","Sunday","Monday","Tuesday"]
    loglst = []
    for item in data:
        datelst = validcheck(item)
        if len(datelst) == 3:
            interval = calcIntv(datelst, [2020,11,18])
            loglst.append(weeklst[interval % 7])
        else:
            loglst.append(datelst[0])
    print('total: {:.6f}'.format(tm.perf_counter()-t0))



'''
TEST
'''
import time as tm
import random as rd
def createComparLst(samplen: int,seeds=513):
    rd.seed(seeds)
    datalst =[]
    chklst = []
    for i in range(samplen):
        yy = rd.randint(0,9999)
        if rd.random() > 0.5:
            yy = -yy
        mm = rd.randint(1,12)
        dd = rd.randint(1,31)
        timedata = str(yy) +' '+ str(mm) +' '+ str(dd)
        yy = '{:0>4d}'.format(yy)
        mm = '{:0>2d}'.format(mm)
        dd = '{:0>2d}'.format(dd)
        timestr = yy + mm + dd
        try:
            week = tm.strftime('%A',tm.strptime(timestr,'%Y%m%d'))
        except:
            week = ' - minus'
        datalst.append(timedata)
        chklst.append(week)
    return datalst, chklst

t_s = tm.perf_counter()
tstdata, chklst = createComparLst(1000)
print('createlst: {:.6f}s'.format(tm.perf_counter()-t_s))
proc(tstdata)