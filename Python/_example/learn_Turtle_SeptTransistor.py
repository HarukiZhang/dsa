import turtle as t

def drawLine(draw: bool, length):
    t.pd() if draw else t.pu()
    t.fd(length)
    t.pu()

def corner(direction, fdl):
    t.pu()
    t.fd(fdl)
    t.seth(direction)
    t.fd(fdl)
    t.pd()

def drawDigit(digit, length, psz):
    t.pensize(psz)
    fdlen = int(psz * 6 / 5)
    interval = 2 * psz
    t.pu(); t.seth(270); t.fd(fdlen); t.pd()
    drawLine(1 if digit in [0,1,3,4,5,6,7,8,9] else 0, length)
    corner(180, fdlen)
    drawLine(1 if digit in [0,2,3,5,6,8] else 0, length)
    corner(90, fdlen)
    drawLine(1 if digit in [0,2,6,8] else 0, length)
    corner(0, fdlen)
    drawLine(1 if digit in [2,3,4,5,6,8,9] else 0, length)
    corner(90, fdlen)
    drawLine(1 if digit in [0,1,2,3,4,7,8,9] else 0, length)
    corner(180, fdlen)
    drawLine(1 if digit in [0,2,3,5,6,7,8,9] else 0, length)
    corner(270, fdlen)
    drawLine(1 if digit in [0,4,5,6,8,9] else 0, length)
    corner(0, fdlen)
    t.pu(); t.fd(2 * length + 3 * fdlen + interval)

def drawMDig(MD, length, psz):
    for i in MD:
        drawDigit(eval(i), length, psz)

def drawDot(dig_length, psz):
    length = int(1/3 * dig_length)
    fdlen = int(psz * 6 / 5)
    interval = 2 * psz
    t.pu(); t.bk(int(1/3 * dig_length))
    t.seth(270); t.bk(length + fdlen); t.pd()
    t.fd(length)
    t.pu(); t.fd(2 * fdlen); t.pd()
    t.fd(length)
    t.pu(); t.bk(length + fdlen); t.seth(0); t.fd(int(1/3 * dig_length))
    t.fd(dig_length + 2 * fdlen + interval)
    

# Initiation
t.setup(width=1000, height=500)
t.pu(); t.goto(-400, 0)
drawMDig('21', 50, 9)
drawDot(50, 9)
drawMDig('32', 50, 9)
t.done()