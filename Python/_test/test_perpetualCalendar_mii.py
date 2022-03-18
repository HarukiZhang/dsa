'New Version - using different scaler'
def leapyear(yy: int):
    if any((yy%4==0 and not yy%100==0, yy%400==0)):
        return True
    return False

# def date2ds(date: list, bof=1):
#     if leapyear(date[0]):
#         mmlst = [31,29,31,30,31,30,31,31,30,31,30,31]
#     else:
#         mmlst = [31,28,31,30,31,30,31,31,30,31,30,31]
#     ds = sum(mmlst[:date[1]-1]) + date[2]
#     if bof == -1: # bof means: backward or forward: -1 for forward and 1 for back
#         ds = sum(mmlst) - ds + 1
#     return ds

def validcheck(stri):
    try:
        imlst = list(map(int, stri.split()))
        if not len(imlst) == 3:
            raise Exception('length')
        yy = imlst[0]
        mm = imlst[1]
        dd = imlst[2]
        if any((mm>12, mm<1, dd<1, dd>31)):
            raise Exception('month or day')
        if mm in (4,6,9,11) and dd>30:
            raise Exception('30-month')
        if mm == 2:
            if leapyear(yy) and dd>29:
                raise Exception('leap year')
            elif dd > 28:
                raise Exception('leap year')
    except:
        return "Illegal"
    else:
        return imlst

def calcIntv(tar: list):
    # NOTE: when calc positive year, std='0001 01 01'; when negative, std='-0001 12 31'
    temp, std = tar, 0
    if temp[0] >= std:
        sign = 1
    else:
        temp[0], std = abs(temp[0]), 1
        sign = -1
    count = 0
    for i in range(std, temp[0]):
        if leapyear(i):
            count += 1
    midY = (temp[0] - std) * 365 + count
    # calc last year days
    if leapyear(temp[0]):
        mmlst = [31,29,31,30,31,30,31,31,30,31,30,31]
    else:
        mmlst = [31,28,31,30,31,30,31,31,30,31,30,31]
    lasY_ds = sum(mmlst[:temp[1]-1]) + temp[2]
    if sign == -1: # bof means: backward or forward: -1 for forward and 1 for back
        lasY_ds = sum(mmlst) - lasY_ds + 1
    return sign * (midY + lasY_ds - 1)

def getweek(intv: int):
    if intv >= 0:
        weeklst_pos = ["Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"]
        return weeklst_pos[intv%7]
    else:
        weeklst_nag = ["Friday","Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday"]
        return weeklst_nag[intv%7]

def proc(data):
    import time
    t00 = time.perf_counter()
    for datum in data:
        t0 = time.perf_counter()
        date = validcheck(datum)
        t1 = time.perf_counter()
        if len(date) == 3:
            intv = calcIntv(date)
            t2 = time.perf_counter()
            print(getweek(intv))
            print('    validcheck: {:.6f}s'.format(t1-t0))
            print('    calc_intv: {:.6f}s'.format(t2-t1))
            print('    getweek: {:.6f}s'.format(time.perf_counter()-t2))
        else:
            print(date)
            print('    validcheck: {:.6f}s'.format(t1-t0))
    print('total: {:.6f}s'.format(time.perf_counter()-t00))

testdata = ['2017 2 29',\
'2017 13 2',\
'0 1 1',\
'-2 3 4',\
'2017 10 18',\
'2015 12 31']

proc(testdata)

'''样例输出
Illegal
Illegal
Saturday
Wednesday
Wednesday
Thursday
'''