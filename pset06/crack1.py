# Crack a DES-based hashed password of length [1,4]
import crypt
import sys

def list_to_string(*lst):
    return ''.join(lst)

lst=[""]*4
cnt=0
if len(sys.argv)!=2:
    print("Error, Expected a hashed password !")
    sys.exit(1)
inpute = sys.argv[1]
while True:
    for _1 in [x for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
        lst[0]=chr(_1)
        if cnt>0:
            for _2 in [x for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
                lst[1]=chr(_2)
                if cnt>1:
                    for _3 in [x for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
                        lst[2]=chr(_3)
                        if cnt>2:
                            for _4 in [x for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
                                lst[3]=chr(_4)
                                hashe = crypt.crypt(list_to_string(*lst),"50")
                                if hashe == input:
                                    break
                        hashe = crypt.crypt(list_to_string(*lst),"50")
                        if hashe == inpute:
                            break
                hashe = crypt.crypt(list_to_string(*lst),"50")
                if hashe == inpute:
                    break
        hashe = crypt.crypt(list_to_string(*lst),"50")
        if hashe == inpute:
            break
    if hashe == inpute:
        break
    cnt+=1
print(list_to_string(*lst))
