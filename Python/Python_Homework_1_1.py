# Python Homework 1_1
# coding = utf-8
UPPERLIMIT = 1000
sum = 0
for i in range(UPPERLIMIT+1):
    if i%3 == 0 or i%7 == 0:
        #print(i,end=' ')
        sum = sum + i
print(sum)
