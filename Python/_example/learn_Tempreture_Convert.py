#TempConvert.py
TempStr = input("Please enter Temp with C or F:")
if TempStr[-1] in ['F', 'f']:
    C = (eval(TempStr[0:-1]) - 32)/1.8
    print("The Temp exchanged is {:.2f}C.".format(C))
elif TempStr[-1] in ['C', 'c']:
    F = 1.8*eval(TempStr[0:-1]) + 32
    print("The Temp exchanged is {:.2f}F.".format(F))
else:
    print("Input is invalid.")