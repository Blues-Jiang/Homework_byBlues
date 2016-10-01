# Homework 1_3
# coding = utf-8
#在西方，星期五和数字13都代表着坏运气，两个不幸的个体最后结合成超级不幸的一天。所以，如果某一天是13日又恰逢星期五，就叫“黑色星期五”。要求编写程序，输入某年年号和该年的元旦是星期几（为1-7的数字），输出该年所有的“黑色星期五”的日期（年/月/日）。给定如下约束条件：
#1.1900年1月1日是星期一。
#2.1月、3月、5月、7月、8月、10月和12月是31天。
#3.4月、6月、9月和11月是30天。
#4.2月是28天，在闰年是29天。
#5.年号能被4整除且又不能被100整除是闰年。check
#6.能直接被400整除也是闰年。check
#输入：4位年号和该年元旦是星期几。
#输出：所有的“黑色星期五”的日期（年/月/日）。
import sys

weekList = ('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday')
#monthList = ('', 'January', 'February', 'March', 'April', 'May', 'June', 'July', 'Augest', 'September', 'October', 'November', 'December')
#monthShortList = ('', 'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sept', 'Oct', 'Nov', 'Dec')
#monthLenList = ('', 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)
monthWeekOffsetList = (0, 0, 3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3)
class Date(object):
    weekOfNYD = 1
    def __init__(self, year, month, day, week):
        self.year=year
        self.month = month
        self.day = day
        self.week=week
    def print_date(self):
        print("%6d/%02d/%02d %-10s"%(self.year, self.month, self.day, weekList[self.week]))

def checkRun(year):
    if ( year%4 == 0 and year%100 != 0 ) or year%400 == 0:
        isRun = True
    else:
        isRun = False
    return isRun
def checkDayOfNYD(year):   #Check the week of New Years' Day
#Because 365%7=1,so new year of 1901 is Tuesday...
#DayOfYear % 7 = 0~6 <=> Sunday to Saturday. 0 means Sunday.
    weekOfNYD = 1   #Year 1900 -> Jan 1st is Monday
    for xyear in range(1900,year):
        if (checkRun(xyear)):
            weekOfNYD = weekOfNYD + 2
        else:
            weekOfNYD = weekOfNYD + 1
    weekOfNYD = weekOfNYD % 7
    return weekOfNYD

print("The Black Friday List")
print("Made by Blues Jiang")
if len(sys.argv) == 1:
    year = int(input("Please input the year you want to check:"))
elif len(sys.argv) == 2:
    year = int(sys.argv[1])
BlackFriday=[]
if len(str(year))>4:
    print("Syntax ERROR.Exit.")
    exit()
elif year<1900:
    weekOf13 = ( int(input("Please provide the day of %d's New Year's Day (1~7):"%(year))) + 12 ) % 7
else:
    weekOf13 = ( checkDayOfNYD(year) + 12 ) % 7
for month in range(1,12):
    if month == 3 and checkRun(year):
        weekOf13 = ( weekOf13 + monthWeekOffsetList[month] + 1 ) % 7
    else:
        weekOf13 = ( weekOf13 + monthWeekOffsetList[month] ) % 7
    if weekOf13 == 5 :
        buffer = Date(year, month, 13, 5)
        BlackFriday.append(buffer)
if len(BlackFriday) == 0:
    print("There is no Black Friday in this year.")
else:
    print("These are Black Friday of %d:"%(year))
    for buffer in BlackFriday:
        buffer.print_date()
