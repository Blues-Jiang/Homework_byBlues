# Python_Homework_ol1.py
# coding = utf-8
#import struct
from struct import *
#filename = input("Enter file name:")
filename = "./test.bmp"
f = open(filename,'rb')
tofile = open("half.bmp",'wb+')
f.seek(0,0)
f.read(14)  #read file header
temp = f.read(4)    #read information header
headinfolen = (int)(unpack('I', temp)[0])
temp = f.read(4)    #image weith
weith = (int)(unpack('I', temp)[0])
temp = f.read(4)    #image height
height = (int)(unpack('I', temp)[0]/2)
f.read(8)
temp = f.read(4)
imagesize = (int)(unpack('I', temp)[0]/2)

f.seek(0,0)
tofile.write(f.read(2))
f.read(4)
newfilesize= 14 + headinfolen + imagesize

tofile.write(pack('I', newfilesize))
tofile.write(f.read(16))
#tofile.write(f.read(4))
#tofile.write(f.read(4))
f.read(4)
tofile.write(pack('I',height))
tofile.write(f.read(8))
f.read(4)
tofile.write(pack('I',imagesize))
tofile.write(f.read(headinfolen - 24))

for i in range(0,imagesize):
    tofile.write(f.read(1))
f.close()
tofile.close()
