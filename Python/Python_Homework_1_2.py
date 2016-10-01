# Homework 1_2
# coding = utf-8
#编写一个程序寻找一种特殊整数：一个n位的正整数等于其各位数字的n次方之和。例如：407=4^3+0^3+7^3，所以407就是一个符合要求的特殊整数。
#输入：正整数的位数n(n<=6)。
#输出：所有符合要求的n位特殊数。若不存在符合条件的特殊数，则输出提示：“No output.”；若存在，则从小到大进行输出，每个数占一行。
MAXDIGIT = 6
result = []
for x in range(10**MAXDIGIT+1):
    digit=len(str(x))
    buffer = x
    sum = 0
    while (buffer >= 10):
        sum = sum + (buffer%10)**digit
        buffer = buffer//10
    sum = sum + buffer**digit
    if (sum == x):
        result.append(x)
if len(result) == 0:
    print("No output.")
else:
    for buffer in result:
        print(buffer)
