'Version 3 - using direct projection'
def leapyear(yy: int):
    if any((yy%4==0 and not yy%100==0, yy%400==0)):
        return True
    return False

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

def date_neg2pos(ndate:list):
    mmlst = [31,29,31,30,31,30,31,31,30,31,30,31] if leapyear(ndate[0]) else [31,28,31,30,31,30,31,31,30,31,30,31]
    ds = sum(mmlst) - (sum(mmlst[:ndate[1]-1]) + ndate[2]) + 1
    mindx = 0
    while ds > 0:
        ds_sv = ds
        ds -= mmlst[mindx]
        mindx += 1
    return [abs(ndate[0]), mindx, ds_sv]

def getweek_vII(date: list):
    import time
    mm = '{:0>2d}'.format(date[1])
    dd = '{:0>2d}'.format(date[2])
    timetpl = '%Y%m%d'
    if date[0] > 0:
        weeklst = ["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"]
        yy = '{:0>4d}'.format(date[0])        
    elif date[0] == 0:
        weeklst = ["Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday","Monday"]
        yy = '{:0>4d}'.format(date[0]+4)
    else: # date[0] < 0
        weeklst = ["Saturday","Friday","Thursday","Wednesday","Tuesday","Monday","Sunday"]
        yy = '{:0>4d}'.format(-date[0])
        pos_date = date_neg2pos(date)
        mm = '{:0>2d}'.format(pos_date[1])
        dd = '{:0>2d}'.format(pos_date[2])
    timestr = yy+mm+dd
    wnum = int(time.strftime('%w',time.strptime(timestr,timetpl)))
    return weeklst[wnum]

'''
Unused function
'''
def date2days(date: list, bof=-1):
    if leapyear(date[0]):
        mmlst = [31,29,31,30,31,30,31,31,30,31,30,31]
        lpy = True
    else:
        mmlst = [31,28,31,30,31,30,31,31,30,31,30,31]
        lpy = False
    ds = sum(mmlst[:date[1]-1]) + date[2]
    if bof == -1: # bof means: backward or forward: -1 for forward and 1 for back
        ds = sum(mmlst) - ds + 1
    return (ds, lpy)

def days2date(days: tuple, bof=1):
    if not any((len(days) == 2, isinstance(days[0],int), isinstance(days[1],bool))):
        raise Exception('input format error')
    mmlst = [31,29,31,30,31,30,31,31,30,31,30,31] if days[1] else [31,28,31,30,31,30,31,31,30,31,30,31]
    intv = days[0]
    ind = 0
    while intv > 0:
        intv_sv = intv
        intv - mmlst[ind]
        ind += 1
    return [0, ind, intv_sv]

'''
Old version following
'''
def date2ds(date: list, bof=1):
    if leapyear(date[0]):
        mmlst = [31,29,31,30,31,30,31,31,30,31,30,31]
    else:
        mmlst = [31,28,31,30,31,30,31,31,30,31,30,31]
    ds = sum(mmlst[:date[1]-1]) + date[2]
    if bof == -1: # bof means: backward or forward: -1 for forward and 1 for back
        ds = sum(mmlst) - ds + 1
    return ds

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

testdata = ['-1 12 31',\
'-1 12 30',\
'-1 12 29',\
'-1 1 2',\
'-1 1 1',\
'-2 12 31']

testdata0 = ['2017 2 29',\
'2017 13 2',\
'0 1 1',\
'-2 3 4',\
'2017 10 18',\
'2015 12 31']

def proc_II(data):
    for i in data:
        date = validcheck(i)
        if len(date) == 3:
            print(getweek_vII(date))
        else:
            print(date)

proc_II(testdata0)