'Version 3 - using direct projection'
import time

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
    mmlst = (31,29,31,30,31,30,31,31,30,31,30,31) if leapyear(ndate[0]) else (31,28,31,30,31,30,31,31,30,31,30,31)
    ds = sum(mmlst) - (sum(mmlst[:ndate[1]-1]) + ndate[2]) + 1
    mindx = 0
    while ds > 0:
        ds_sv = ds
        ds -= mmlst[mindx]
        mindx += 1
    return [abs(ndate[0]), mindx, ds_sv]

def getweek_vII(date: list):
    mm = '{:0>2d}'.format(date[1])
    dd = '{:0>2d}'.format(date[2])
    timetpl = '%Y%m%d'
    if date[0] > 0:
        weeklst = ("Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday")
        yy = '{:0>4d}'.format(date[0])        
    elif date[0] == 0:
        weeklst = ("Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday","Monday")
        yy = '{:0>4d}'.format(date[0]+4)
    else: # date[0] < 0
        weeklst = ("Saturday","Friday","Thursday","Wednesday","Tuesday","Monday","Sunday")
        yy = '{:0>4d}'.format(-date[0])
        pos_date = date_neg2pos(date)
        mm = '{:0>2d}'.format(pos_date[1])
        dd = '{:0>2d}'.format(pos_date[2])
    timestr = yy+mm+dd
    wnum = int(time.strftime('%w',time.strptime(timestr,timetpl)))
    return weeklst[wnum]

def proc_II():
    loglst = []
    datalst = []
    for i in range(int(input())):
        datalst.append(input())
    for timestr in datalst:
        date = validcheck(timestr)
        if len(date) == 3:
            loglst.append(getweek_vII(date))            
        else:
            loglst.append(date)
    for item in loglst:
        print(item)



'''
TEST
'''
proc_II()