from turtle import *
setup(300,300)
width(2)

seth(45)
for i in range(1,3):
    for n in range(2,4):
        fd(100)
        left(pow(-1,n)*90)
        circle(pow(-1,n)*100,45)
        left(pow(-1,n)*90)
        fd(100)
    right(90)

done()