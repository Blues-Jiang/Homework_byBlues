# Python Homework 3_1
# coding = utf-8

import re
from graphics import *


def initialGUI():

fl=open("list_pyHomework_3_2.txt",'r')
buffer = fl.readline()
sheetHeader = re.split(r'\s+',buffer)
buffer = fl.readlines()
sheetData = []
for x in buffer:
    sheetData.append(re.split(r'\s+',x))
subScoreList = {0:0,60:0,70:0,80:0,90:0,100:0}


fl.close()
