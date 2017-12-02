import cs50

print ("Height: ",end="")
height = cs50.get_int()
while height < 0 or height >23:
    print ("Height: ",end="")
    height = cs50.get_int()
for lines in range (2,height+2):
    for spaces in range (height+1-lines):
        print(" ",end="")
    for hashes in range (lines):
        print("#",end="")
    print("")