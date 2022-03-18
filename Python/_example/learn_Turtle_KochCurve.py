# 请在...补充一行或多行代码

import turtle
def koch(size, n):
    if n == 0:
        turtle.fd(size)
    else:
        for k in [0,60,-120,60]:
            turtle.left(k)
            koch(1/3*size,n-1)

def main(level):
    turtle.setup(600,600)
    turtle.penup()
    turtle.goto(-200, 100)
    turtle.pendown()
    turtle.pensize(2)
    koch(300, level)
    
try:
    level = 4
    main(level)
except:
    print("错误")
turtle.done()