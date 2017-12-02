import sys

if len(sys.argv) != 2:
    sys.exit("Error, Please enter a key !")
key = sys.argv[1]
str_text = input("plaintext: ")
text = list(str_text)
key_pointer = 0
for i in [x for x in range (len(text)) if text[x].isalpha()]:
    temp = text[i].lower()
    ciphered = chr( (ord(temp) - ord('a') + ord(key[key_pointer%len(key)].lower()) - ord('a')) %26 )
    if temp == text[i]:
        text[i] = chr(ord(ciphered)+ord('a'))
    else:
        text[i] = chr(ord(ciphered)+ord('A'))
    key_pointer+=1
str_text = ''.join(text)
print("ciphertext: {}".format(str_text))
