# Python Homework 3_2
# -*- coding: utf-8 -*-

import re
import os
from graphics import *

# from Tkinter import *
listIndex = [0, 60, 70, 80, 90, 100]  # index of every range of score
# listIndex = [0,60,70,80,90,100,-1]
scoreTextList = {0: "0~59", 60: "60~69", 70: "70~79", 80: "80~89", 90: "90~99", 100: "100",
                 -1: "Error"}  # the text of every range
subScoreList = {0: 0, 60: 0, 70: 0, 80: 0, 90: 0, 100: 0, -1: 0}  # the sum of every range of score

# Read the file of score.The first line is the index of this sheet
fl = open("./list_pyHomework_3_2.txt", 'r')
buffer = fl.readline()
sheetHeader = re.split(r'\s+', buffer)  # Read the header of this sheet
buffer = fl.readlines()
sheetData = []
for x in buffer:
    sheetData.append(re.split(r'\s+', x))
fl.close()
# Count the number of every range of score
scoreIndex = sheetHeader.index("成绩")
for x in sheetData:
    temp = int(x[scoreIndex])
    if (temp < 60):
        subScoreList[0] = subScoreList[0] + 1
    elif (temp < 70):
        subScoreList[60] = subScoreList[60] + 1
    elif (temp < 80):
        subScoreList[70] = subScoreList[70] + 1
    elif (temp < 90):
        subScoreList[80] = subScoreList[80] + 1
    elif (temp < 100):
        subScoreList[90] = subScoreList[90] + 1
    elif (temp == 100):
        subScoreList[100] = subScoreList[100] + 1
    else:
        subScoreList[-1] = subScoreList[-1] + 1


# def printlist():

def GUI():  # creat the GUI of this chart.
    maxNum = 80
    win = GraphWin("Statistic Result Chart by Blues", 600, 480)
    win.setBackground('white')
    win.setCoords(0.0, 0.0, 60.0, 48.0)
    originPoint = Point(5, 5)  # set the origin point of the plot

    axisX = Line(originPoint, Point(55, 5))  # Draw X axis.
    axisX.setArrow('last')
    axisX.draw(win)
    axisY = Line(originPoint, Point(5, 45))  # Draw Y axis.
    axisY.setArrow('last')
    axisY.draw(win)

    tempY = Point(2.5, 5)
    for x in range(0, maxNum + 1, 10):  # scale of Y axis,the max of number is set as 80
        scaleText = Text(tempY, x)
        scaleText.draw(win)
        tempY.move(0, 5)

    tempX = Point(7.5, 2.5)
    for x in listIndex:  # scale of X axis
        scaleText = Text(tempX, scoreTextList[x])
        scaleText.draw(win)
        tempX.move(8, 0)

    # Print the Rectangle of Chart
    tempP1 = originPoint  # the first point of Rectangle
    for x in listIndex:
        tempP2 = tempP1.clone()
        height = subScoreList[x] / maxNum * 40  # calculate the height of Rectangle
        tempP2.move(5, height)  # set the weith&height of Rectangle
        temp = Rectangle(tempP1, tempP2)
        temp.setFill('gray')
        temp.draw(win)
        Text(Point(temp.getCenter().getX(), tempP2.getY() + 1), subScoreList[x]).draw(
            win)  # draw the number of each range
        tempP1.move(8, 0)

    win.getMouse()  # Pause to view result
    win.close()  # Close window when done


GUI();
