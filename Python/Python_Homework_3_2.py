# Python Homework 3_1
# coding = utf-8

import re

fl=open("list_pyHomework_3_2.txt",'r')
buffer = fl.readline()
sheetHeader = re.split(r'\s+',buffer)
buffer = fl.readlines()
sheetData = buffer

fl.close()
