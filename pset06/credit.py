import cs50

credit = cs50.get_int()
str_credit = str(credit)
cnt = 0
for index in range(len(str_credit)):
    if index%2 == 0:
           cnt+=int(str_credit[len(str_credit)-index-1])
    else:
        temp = str(int(str_credit[(len(str_credit)-index)-1])*2)
        cnt = cnt + int(temp)%10 + int(temp)//10
if cnt%10 == 0 and len(str_credit)==15 and (str_credit[0:2]=="34" or str_credit[0:2]=="37"):
    print("AMEX")
elif cnt%10 == 0 and len(str_credit)==16 and (str_credit[0]=="5" and str_credit[1]<="5" and str_credit[1]>"0"):
    print("MASTERCARD")
elif cnt%10 == 0 and (len(str_credit)==13 or len(str_credit)==16) and str_credit[0]=="4":
    print("VISA")
else :
    print("INVALID")
