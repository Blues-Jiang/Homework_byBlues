# Python Homework 2_2
# coding = utf-8
import re
import types

def encrypt(text):
    text = text.lower()
    #buffer = text.split(' ')
    buffer = re.split(r'\s+',text)
    for i in range(len(buffer)):
        if re.match(r'^qu',buffer[i]):
            temp = re.match(r'^(qu)(.*)',buffer[i])
            buffer[i] = temp.group(2) + temp.group(1) + "ay"
        elif re.match(r'^[aeiou]',buffer[i]):
            buffer[i] += "hay"
        elif re.match(r'^[^aeiou]',buffer[i]):
            temp = re.match(r'^([^aeiou][^aeiouy]*)(.*)',buffer[i])
            buffer[i] = temp.group(2) + temp.group(1) + "ay"
    result = " "
    result = result.join(buffer)
    return result

plainText = input("Please input the proclaimed in writing(plain text):")
ciphertext = encrypt(plainText)
print(ciphertext)
