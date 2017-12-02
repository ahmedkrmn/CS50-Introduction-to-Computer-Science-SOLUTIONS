import cs50

print("O hai! How much change is owed?")
owed = cs50.get_float();
while owed < 0 :
    print("How much change is owed?")
    owed = cs50.get_float();
cnt = 0
while owed>0:
    if owed>=0.25:
        owed-=0.25
    elif owed>=0.10:
        owed-=0.10
    elif owed>=0.05:
        owed-=0.05
    else:
        owed-=0.01
    cnt+=1
print(cnt)