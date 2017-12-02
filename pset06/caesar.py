import sys

if len(sys.argv) != 2 :
    sys.exit("Erorr, Please choose a key !")
key = int(sys.argv[1])
str_text = input("plaintext: ")
text = list(str_text)
for i in [x for x in range (len(text)) if text[x].isalpha()]:
    temp = text[i].lower()
    ciphered = chr((ord(temp)-ord('a')+key)%26)
    if temp == text[i]:
        text[i]=chr(ord(ciphered)+ord('a'))
    else:
        text[i]=chr(ord(ciphered)+ord('A'))
str_text = ''.join(text)
print("ciphertext: {}".format(str_text))
