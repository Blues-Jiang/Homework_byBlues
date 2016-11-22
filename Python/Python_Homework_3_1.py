# Python Homework 3_1
# -*- coding: utf-8 -*-
import re

sentence = input("The sentence:")
for x in "@#$%^&*\"()_+-={}[B]\|:<>,./?":#remove every punctuation
    sentence = sentence.replace(x," ")
sentence.strip()
buffer = re.split(r'\s+',sentence)#split words into list
sumlength = 0
sumWord = 0
for x in buffer:#count the sum of length and the number of words
    if(x):
        sumlength += len(x)
        sumWord += 1
print("This sentence has",sumWord,"words.The average length of words is",round(sumlength/sumWord,3),".")#output 
