# Python Homework 5
# -*- coding: utf-8 -*-

import hashlib
import urllib.request
import time
from datetime import datetime

def getMD5(stream):#To get the MD5 value of the stream
    m = hashlib.md5()
    m.update(stream)
    return m.hexdigest()

def getHTTP(website):#the function to get the *.html file.
    req = urllib.request.Request(website)
    with urllib.request.urlopen(req) as response:
       the_page = response.read()
    return the_page

website = input('Please input the website you need to check:') #get the website
updateVal = (int)(input('Please input the update interval(seconds):')) #set the update interval
stream = getHTTP(website)
temp1 = getMD5(stream) #save the first md5 value
temp2 = temp1
while True:#Eternal loop
    time.sleep(updateVal)
    temp2 = temp1
    stream = getHTTP(website)
    temp1 = getMD5(stream)
    if(temp1 != temp2):#check if the last two md5 values are the same.
        print("This page updated at:",datetime.now())
    else:
        print("This page is still.")
