# Python Homework 3_1
# coding = utf-8

import re
from graphics import *
#from Tkinter import *

def GUI():
    win = GraphWin("Statistic result by Blues",600,480)
    win.setCoords(0.0,0.0,60.0,48.0)

fl=open("list_pyHomework_3_2.txt",'r')
buffer = fl.readline()
sheetHeader = re.split(r'\s+',buffer)   #Read the header of this sheet
buffer = fl.readlines()

sheetData = []
for x in buffer:
    sheetData.append(re.split(r'\s+',x))
fl.close()

subScoreList = {0:0,60:0,70:0,80:0,90:0,100:0,-1:0}
scoreIndex = sheetHeader.index("成绩")
for x in sheetData:
    temp = int(x[scoreIndex])
    if (temp < 60):
        subScoreList[0] = subScoreList[0] + 1
    else if (temp < 70):
        subScoreList[60] = subScoreList[60] + 1
    else if (temp < 80):
        subScoreList[70] = subScoreList[70] + 1
    else if (temp < 90):
        subScoreList[80] = subScoreList[80] + 1
    else if (temp < 100):
        subScoreList[90] = subScoreList[90] + 1
    else if (temp == 100):
        subScoreList[100] = subScoreList[100] + 1
    else
        subScoreList[-1] = subScoreList[-1] + 1
