from turtle import *
setup(450,700)
ps=17
width(ps)
pencolor('purple')
pu()
goto(50,-200)
pd()

# draw the body
for i in range(20):
    r=3*i+12
    circle(r,45)
for m in range(20,26): # want the mid of the body get fatter
    ps=ps+1
    pensize(ps)
    r=3*m+12
    circle(r,45)

# the 2nd part of the body (a bigger SPIRAL)
fd(10)
n=0
for j in range(26,35):
    ps=ps+2
    pensize(ps) # the body swell
    r=4*j+12
    circle(r,10)
    n=n+1

# the Python need a even fatter finge when closer to the head
circle(-r,80)
seth(90)
ks=0
for k in range(1,6):
    ps=ps+k*2-ks*2
    ks=k
    pensize(ps)
    fd(7)
width(ps-5)
fd(2)

print("j={},\nn={},\npensize={}.".format(j,n,ps))

# the tongue in red
pu()
seth(90)
fd(15)
pd()
pencolor('red')
width(3)
fd(17)
circle(-20,45)
# reset the paint draw
pu()
circle(-20,135)
seth(180)
fd(40)
seth(90)
pd()
width(2)
circle(35,50)

# reset the paint draw to the tail
pu()
goto(50,-200)
seth(0)
pd()

done()