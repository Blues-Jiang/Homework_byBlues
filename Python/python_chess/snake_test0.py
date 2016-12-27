# -*- coding:utf-8 -*-
'''''
Created on 2013-1-16

@author: jincheng
'''
import wx
import random

class SnakeWindow(wx.Window):
    '''''
    贪吃蛇
    '''
    def __init__(self,parent,size,offset):
        wx.Window.__init__(self,parent,-1,size=size)
        print self.GetBorder(wx.BOTTOM)
        self.area = (size[0]-offset,size[1]-offset)
        self.snakeColor='black'
        self.SetBackgroundColour('green')
        self.snakeThickness = 10
        self.snake = [(100,100),(100,110),(100,120)]
        self.snakeHead = (100,120)
        self.snakeSpace = 10
        self.snakeDebris = []

        self.foodLoc = ()
        self.foodWidth = 1

        self.FoodManufacture()

        self.pen = wx.Pen(self.snakeColor, self.snakeThickness, wx.SOLID)
        self.winsize = self.GetClientSize()
        self.buffer = wx.EmptyBitmap(*self.area)
        self.snakeDire = 317#蛇头向下
        #self.foodInstantiate()
        self.runtime = wx.Timer(self)
        self.runtime.Start(100)#100毫秒动一下

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_KEY_UP,self.OnKeyUp)
        self.Bind(wx.EVT_TIMER, self.OnTimer)
        #self.Bind(wx.EVT_LEFT_UP, self.OnLeftUp)

    def __RandPoint(self):
        x = random.randint(1,self.area[0]/10)*10
        y = random.randint(1,self.area[1]/10)*10
        return (x,y)

    def FoodManufacture(self):
        self.foodLoc = self.__RandPoint()

    def foodInstantiate(self,dc):
        food = self.foodLoc + (self.foodWidth,self.foodWidth)
        dc.DrawRectangle(*food)

    def __Fission(self):
        '''''
        抛洒尸骸
        '''
        point = self.__RandPoint()
        if point in self.snakeDebris or point == self.foodLoc:
            self.__Fission()
        else:
            return point

    def SnakeFission(self):
        '''''
        蛇断尾
        '''
        length = len(self.snake)/2
        while length > 0:
            index = len(self.snake) - 1
            self.snake.pop(index)#删除末位
            point = self.__Fission()
            self.snakeDebris.append(point)
            length -= 1

    def SnakeFissionInstantiate(self,dc):
        for debris in self.snakeDebris:
            d = debris +  (self.foodWidth,self.foodWidth)
            dc.DrawRectangle(*d)

    def SnakeMove(self):
        length = len(self.snake)
        self.snake.pop(length-1)#shift
        space = self.snakeSpace
        x = 0
        y = 0
        if self.snakeDire == 317:
            y = space
        elif self.snakeDire == 316:
            x = space
        elif self.snakeDire == 315:
            y = -space
        elif self.snakeDire == 314:
            x = -space
        newhead = (self.snakeHead[0] + x,self.snakeHead[1] + y)
        self.GameOver(newhead)

        self.snake.insert(0,newhead)
        self.snakeHead = newhead
        dc = wx.BufferedDC(wx.ClientDC(self),self.buffer)
        dc.SetPen(self.pen)
        dc.Clear()
        self.SnakeInstantiate(dc)

    def SnakeInstantiate(self,dc):
        '''''
        画出蛇与食物
        '''
        self.foodInstantiate(dc)
        last = self.snake[0]
        length = len(self.snake)
        for s in self.snake[1:length]:
            line = last + s
            dc.DrawLine(*line)
            last = s

        if self.Eat():
            if len(self.snake) > 5:
                self.SnakeFission()
        pen = wx.Pen('red',self.snakeThickness,wx.SOLID)
        dc.SetPen(pen)
        self.SnakeFissionInstantiate(dc)

    def Eat(self):
        if self.snakeHead == self.foodLoc:
            self.snake.insert(0, self.foodLoc)
            self.FoodManufacture()
            return True
        else :
            return False

    def GameOver(self,newhead):
        print newhead
        if newhead in self.snake or newhead in self.snakeDebris:
            self.runtime.Stop()
            print 'autotomy'
            return True
        elif newhead[0] < 0 or newhead[0] > self.area[0] or newhead[1] < 0 or newhead[1] > self.area[1]:
            self.runtime.Stop()
            print 'out'
            return True
        else :
            return False

    def OnTimer(self,event):
        self.SnakeMove()

    def OnKeyUp(self,event):
        code = event.GetKeyCode()
        if code >= 314 and code <=317 and code != self.snakeDire - 2 and code != self.snakeDire + 2:
            self.snakeDire = code
        #self.SnakeMove()

    def OnPaint(self, event):
        dc = wx.BufferedPaintDC(self, self.buffer)#13 处理一个paint（描绘）请求

    def OnLeftUp(self, event):
        dc = wx.BufferedDC(wx.ClientDC(self),self.buffer)
        dc.SetPen(self.pen)
        pos = event.GetPositionTuple()
        pos = pos + (10,10)
        dc.Clear()
        dc.DrawRectangle(*pos)
        print 'drawpoint'

class SnakeFrame(wx.Frame):
    def __init__(self,parent):
        wx.Frame.__init__(self,parent,-1,'title',size=(800,600))

        size = self.__AreaSize(self.GetClientSize())

        panel = wx.Panel(self)
        panel.SetBackgroundColour('#4f5049')

        border = 10

        self.sketch = SnakeWindow(panel,size,2*border)

        box = wx.BoxSizer(wx.VERTICAL)

        box.Add(self.sketch,1,wx.ALIGN_TOP|wx.ALL,border)
        panel.SetSizer(box)

    def __AreaSize(self,size):
        width = self.__AreaMath(size[0])
        height = self.__AreaMath(size[1])
        return (width,height)

    def __AreaMath(self,intparam):
        if intparam%10 < 5:
            return intparam/10 * 10
        else:
            return (intparam/10 + 1)*10

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = SnakeFrame(None)
    frame.Show(True)
    app.MainLoop()
