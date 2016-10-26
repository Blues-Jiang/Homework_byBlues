# Python Homework 2_3
# coding = utf-8

name = input("Please input your name:")
buffer = name.split(' ',2)
username = buffer[0][0]+buffer[1][:7]
print("The username is",username)
