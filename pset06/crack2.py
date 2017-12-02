# Crack a DES-based hashed password of length 4
import sys
import crypt

def list_to_string(*lst):
    return ''.join(lst)

if len(sys.argv) != 2:
    sys.exit("Expected a hashed password !")
lst,flag,inpute = [],False,sys.argv[1]
for a in [chr(x) for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
    for b in [chr(x) for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
        for c in [chr(x) for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
            for d in [chr(x) for x in range(ord('A'),ord('z')+1) if chr(x).isalpha()]:
                print(lst)
                hashe = crypt.crypt(list_to_string(*lst),"50")
                if hashe == inpute:
                    flag = True
                    break
                del lst[:]
            if flag:
                break
        if flag:
            break
    if flag:
        break
print(list_to_string(*lst))
