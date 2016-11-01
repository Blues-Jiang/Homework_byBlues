# Python_Homework_ol1.py
# coding = utf-8
#import struct
from struct import *
import types
#filename = input("Enter file name:")
filename = "./test.bmp"
f = open(filename,'rb')
tofile = open("half.bmp",'wb+')
f.seek(0,0)
f.read(14)  #read file header
temp = f.read(4)    #read information header
headinfolen = unpack('I', temp)[0]
temp = f.read(4)    #image weith
unpack('I', temp)[0]
temp = f.read(4)    #image height
height = unpack('I', temp)[0]/2
f.read(8)
temp = f.read(4)
imagesize = unpack('I', temp)[0]/2

f.seek(0,0)
tofile.write(f.read(2))
f.read(4)
newfilesize= 14 + headinfolen + imagesize

print(type(newfilesize))
for i in range(0,(int)(imagesize)):
    tofile.write(f.read(1))
f.close()
tofile.close()
