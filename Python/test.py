#-*- coding: utf-8 -*-

"""
Tkconstants.py -- 常量类

tkinter布局

pack 参数说明
fill -- x 横向填充（默认,各组件自上而下）， y竖向填充（各组件自左往右），both都填充
expand -- 1 父外框大小改变时，自动扩充大小，0为false
side -- left right top bottom 停靠在父组件的哪一边上
anchor -- 对齐方式

grid  参数说明
row -- 行号
rowspan -- 合并行
column -- 列号
columnspan -- 合并列
sticky -- 组件紧靠所在单元格的某一边角

grid填充（自动缩放）--同 pack的 expand属性
root.columnconfigure(0, weight=1)
root.rowconfigure(0, weight=1)
frame.grid(row=0, column=0, sticky="nsew")

下面是程序融合了 pack填充（自动缩放）和 grid填充（自动缩放）与及 多组件整合布局
http://blog.csdn.net/xxb2008
"""

import tkinter


class MainFrame(tkinter.Frame):
    def __init__(self, master=None):
        tkinter.Frame.__init__(self, master)
        self.grid(row=0, column=0, sticky="nsew")
        self.createFrame()

    def createFrame(self):
        self.frameTop = tkinter.Frame(self)
        self.frameTop.pack(fill="x")

        self.labelFilePaths = tkinter.Label(self.frameTop, text="文件路径：", width=10)
        self.labelFilePaths.pack(fill="y", expand=0, side=tkinter.LEFT)

        self.textFilePaths = tkinter.Text(self.frameTop, height=10)
        self.textFilePaths.pack(fill="both", expand=1, side=tkinter.LEFT)

        self.frameCenter = tkinter.Frame(self)
        self.frameCenter.pack(fill="x")

        self.frameBottom = tkinter.Frame(self)
        self.frameBottom.pack(fill="x")



        #self.labelFilePaths = tkinter.Label(self, text="文件路径：", width=10)
        #self.labelFilePaths.grid(row=0, column=0, sticky="w")

        #self.textFilePaths = tkinter.Text(self.frame, height=10)
        #self.textFilePaths.pack(fill="both")
        #self.textFilePaths.grid(row=1, column=0, sticky="nsew")


def main():
    root = tkinter.Tk()
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)
    root.geometry('640x360')  #设置了主窗口的初始大小960x540

    app = MainFrame(root)
    app.mainloop()


if __name__ == "__main__":
    main()


            self.quitFrame = Frame(self)

            self.quitFrame.pack()
