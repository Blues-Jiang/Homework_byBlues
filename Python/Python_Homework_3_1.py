# Python Homework 3_1
# coding = utf-8
import re

sentence = input("The sentence:")
for x in "@#$%^&*()_+-={}[]\|:"'<>,./?":
    sentence = sentence.replace(x," ")
buffer = re.split(r'\s+',sentence)
sumlength = 0
for x in buffer:
    sumlength += len(x)
print("This sentence has ",len(buffer)," words.The average length of words is ",sumlength / len(buffer),".")
