# Python Homework 2_1
# coding = utf-8
import re

sum = 0
source = input("Please input a string:").lower()
if not source.isalpha():
    source = "".join(re.findall(r'[a-z]+',source))
for x in source:
    sum += ord(x) - 96 # ascii('a') = 97
print("The sum is",sum)
