# Python Homework 4
# -*- coding: utf-8 -*-

import re,os

try:  # import as appropriate for 2.x vs. 3.x
    from tkinter import *
    from tkinter.ttk import *
    import tkinter.messagebox as messagebox
    import tkinter.filedialog as filedialog
except:
    from Tkinter import *
    from Tkinter.ttk import *

class GUI(Frame):#main GUI
    def __init__(self, master=None):
        self.filename="D:\Design_Project\Homework_byBlues\Python\profile.gif"
        self.name = StringVar()
        self.edu = StringVar()
        self.spec = StringVar()
        self.name.set("Blues")
        self.edu.set("本科")
        self.spec.set("集成电路设计")
        Frame.__init__(self, master)
        self.pack()
        self.createMainGUI()

    def createMainGUI(self):#topLabel,mainFrame and last two buttons
        self.topLabel = Label(self, text=self.name.get()+"的个人简历",font="微软雅黑 -24 bold")
        self.topLabel.pack()
        self.mainFrame = Frame(self)
        self.createMainFrame()
        self.mainFrame.pack()
        self.quitFrame = Frame(self)
        self.contactButton = Button(self.quitFrame, text='Contact me', command=self.contact)
        self.quitButton = Button(self.quitFrame, text='Quit', command=self.quit)
        self.contactButton.pack(side='left')
        self.quitButton.pack(side='left')
        self.quitFrame.pack()

    def createMainFrame(self):#initial main frame into left & right frame
        self.subLeftFrame = Frame(self.mainFrame)
        self.createSubLeftFrame()
        self.subLeftFrame.grid(row=0, column=0,ipadx=15,padx=20,ipady=15,pady=20,sticky=N)
        self.subRightFrame = Frame(self.mainFrame)
        self.createSubRightFrame()
        self.subRightFrame.grid(row=0, column=1,ipady=15,pady=20)

    def createSubLeftFrame(self): #initial left sub frame
        #the profile Photo
        self.img = PhotoImage(file=self.filename,height=120,width=120)
        self.profileLabel = Label(self.subLeftFrame, image=self.img)
        self.profileLabel.pack()
        #update button
        self.uploadButton = Button(self.subLeftFrame,text='Upload Profile Photo',command=self.updateFilename)
        self.uploadButton.pack()
        #the last 3 Checkbutton on 专业技能
        Label(self.subLeftFrame, text="专业技能",justify = 'left',anchor = 'w',font="微软雅黑").pack()
        self.skillButton1 =Checkbutton(self.subLeftFrame,text="平面设计",command=self.update)
        self.skillButton2 =Checkbutton(self.subLeftFrame,text="空间设计",command=self.update)
        self.skillButton3 =Checkbutton(self.subLeftFrame,text="工业设计",command=self.update)
        self.skillButton1.pack()
        self.skillButton2.pack()
        self.skillButton3.pack()
    def createSubRightFrame(self):#right sub frame,and it still has some sub frame
        #some basic infomation
        self.basicInfoFrame = Frame(self.subRightFrame)
        Label(self.basicInfoFrame,text='姓名:').grid(row=0, column=0)
        self.nameTextBox = Entry(self.basicInfoFrame,textvariable=self.name,state = 'disabled')
        self.nameTextBox.grid(row=0, column=1)
        Label(self.basicInfoFrame,text='学历:').grid(row=1, column=0)
        self.eduTextBox = Entry(self.basicInfoFrame,textvariable=self.edu,state = 'disabled')
        self.eduTextBox.grid(row=1, column=1)
        Label(self.basicInfoFrame,text='专业:').grid(row=2, column=0)
        self.spcTextBox = Entry(self.basicInfoFrame,textvariable=self.spec,state = 'disabled')
        self.spcTextBox.grid(row=2, column=1)
        self.confirmBasicInfoButton = Button(self.basicInfoFrame,text='修改',command=self.basicInfoEvent)#this button;s state can change between conform and change
        self.confirmBasicInfoButton.grid(row=3, column=0,columnspan=2)
        self.basicInfoFrame.pack()

        Label(self.subRightFrame,text='所获奖励',font="微软雅黑").pack()
        self.rewardTextBox = Text(self.subRightFrame,height=4,width=40, wrap='none',font="微软雅黑")
        self.lineCounter=1
        #add infomation directly
        self.rewardTextBox.insert('1.0',"1.学生会办公室干事")
        self.rewardTextBox.pack()
        #the last part
        Label(self.subRightFrame,text='实习经历',font="微软雅黑").pack()
        self.experienceTextBox = Text(self.subRightFrame,height=4,width=40, wrap='none',font="微软雅黑")
        self.experienceTextBox.pack()
        #need StringVar() to get the info from Entry widgets
        self.experAddFrame = Frame(self.subRightFrame)
        self.experDateAdd = StringVar()
        self.experInfoAdd = StringVar()

        self.experDateAddTextBox = Entry(self.experAddFrame,textvariable=self.experDateAdd,width=10)
        self.experInfoAddTextBox = Entry(self.experAddFrame,textvariable=self.experInfoAdd,width=30)
        self.experAddButton = Button(self.experAddFrame,text='Add', command=self.addExper)
        self.experDelButton = Button(self.experAddFrame,text='Delete', command=self.delExper)
        #use grid to make GUI not so tight
        self.experDateAddTextBox.grid(row=0, column=0,padx=5,pady=15)
        self.experInfoAddTextBox.grid(row=0, column=1,padx=5,pady=15)
        self.experAddButton.grid(row=0, column=2,padx=5,pady=15)
        self.experDelButton.grid(row=0, column=3,padx=5,pady=15)
        self.experAddFrame.pack()
    #Event recall.Include every function for recall
    def basicInfoEvent(self):#disable every entry widgets
        if(self.confirmBasicInfoButton["text"] == '修改'):
            self.confirmBasicInfoButton["text"] = '确认'
            self.nameTextBox["state"]='normal'
            self.eduTextBox["state"]='normal'
            self.spcTextBox["state"]='normal'
        elif(self.confirmBasicInfoButton["text"] == '确认'):
            self.confirmBasicInfoButton["text"] = '修改'
            self.nameTextBox["state"]='disabled'
            self.eduTextBox["state"]='disabled'
            self.spcTextBox["state"]='disabled'
        self.update()
    def update(self):
        self.skillResult=[False,False,False]
        self.topLabel["text"] = self.name.get()+"的个人简历"
    def contact(self):#show the contact infomation
        messagebox.showinfo('Contact me', 'Email:blues.jiang@foxmail.com')
    def addExper(self):#recall for the experience frame
        temp = self.experDateAddTextBox.get()
        temp = temp + '\t' + self.experInfoAddTextBox.get() + '\n'
        self.experienceTextBox.insert(END,temp)
    def delExper(self):
        self.experDateAdd.set("")
        self.experInfoAdd.set("")
    def updateFilename(self):#we can use this to update the file for the image
        self.temp = filedialog.askopenfilename(filetypes=[("Image File","*.bmp;*.gif")])
        if(self.temp != ""):
            self.filename=self.temp
        self.img = PhotoImage(file=self.filename,height=120,width=120)
        self.profileLabel['image'] = self.img

def main():#main function to use the GUI class
    root=Tk()
    root.title("Resume")
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)
    root.maxsize(800, 600)
    root.geometry('800x600')  #设置了主窗口的初始大小960x540

    app = GUI(master=root)
    app.mainloop()
    root.quit()
main();
