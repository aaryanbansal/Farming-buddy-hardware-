import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random
from tkinter import *
import serial
from serial.tools import list_ports
from tkinter import messagebox
import matplotlib.pyplot as plt
import numpy as np
import time
from tkinter import *
import numpy as np
import smtplib
from email.message import EmailMessage
import serial
from serial.tools import list_ports
from tkinter import simpledialog



ser=serial.Serial('/dev/ttyACM0',9600,timeout=1)
ser.flush()

def SerialCommRead():
    global ser
    ser.flush()
    if ser.in_waiting>0:
        Val=ser.readline().decode("ascii").rstrip()
        return Val

def ReceiveSerialData():
    Val=str(SerialCommRead())
    Info='None'
    if Val != 'None':
        Loc1=Val.find('C')
        Loc2=Val.find('M')
        CO=Val[Loc1+2:Loc2-1].strip()
        Loc1=Val.find('M')
        Loc2=Val.find('L')
        Moisture=Val[Loc1+2:Loc2-1].strip()
        Loc1=Val.find('L')
        Loc2=Val.find('F')
        Light=Val[Loc1+2:Loc2-1].strip()
        Loc1=Val.find('F')
        Fire=Val[Loc1+2:].strip()
        ser.flush()
        Info=[CO,Moisture,Light,Fire]
    return Info




fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []
yr = []
yt = []

flag1=0
flag2=0
def animate(i, xs, ys,yr,yt,TH):
    global flag1,flag2
    num1 = i 
    Info=ReceiveSerialData()
    print(Info)
    # Info=[random.randint(0,100),random.randint(0,100),random.randint(0,100),random.randint(0,1)]
    r1.config(text="CO2(PPM): " + str(Info[0]))
    r2.config(text="Moisture(%): " + str(Info[1]))
    r3.config(text="Light(%): " + str(Info[2]))
    ThLabl.config(text=str(TH))
    
    if Info[3]=='1':
        Firel.config(text="Fire Detected")
    else:
        Firel.config(text="No Fire")  
    num2=(Info[0]) 
    
    if num2 is not None:
        xs.append(num1)
        ys.append((Info[0])) 
        yr.append((Info[1])) 
        yt.append((Info[2])) 

    xs = xs[-20:]
    ys = ys[-20:] 
    yr = yr[-20:] 
    yt = yt[-20:] 


    ax.clear()
    ax.plot(xs, ys, '-o', label="Co2")
    ax.plot(xs, yr, '-*', label="Moisture")
    ax.plot(xs, yt, '-s', label="Light")
    ax.legend(loc="lower left")
    ax.set_ylabel('Sensor Value')
    ax.set_xlabel('No of Samples')

    if int(Info[1]) < int(TH):
        SerialWrite(str(1))
        if flag1 == 0:
            SendEmail(": Pump is Turn On")
            flag1 = 1
    else:
        flag1=0
        
    if int(Info[1])>int(TH):
        SerialWrite(str(0))
        if flag2==0:
            SendEmail(": Pump is Turn Off")
            flag2=1
    else:
        flag2=0


def SendEmail(text):
    Sender_Email = "mehakbeniwal2003@gmail.com"
    Reciever_Email = "mehakbeniwal2003@gmail.com"
    Password = "ylzfcslyptgrocxn"

    newMessage = EmailMessage()
    newMessage['Subject'] = "Water Pump Monitoring"
    newMessage['From'] = Sender_Email
    newMessage['To'] = Reciever_Email
    newMessage.set_content('Water Pump Status'+text)

    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp:

        smtp.login(Sender_Email, Password)
        smtp.send_message(newMessage)


def SerialWrite(num):
    ser.write(num.encode('utf-8'))

flag1=0
flag2=0

ROOT = Tk()
ROOT.withdraw()
TH = simpledialog.askstring(title="Input 2",
                                  prompt="Enter Threshold for Pump :  ")

root=Tk()
root.geometry("580x200")
root.config(bg="mint cream")
cntrl_lbl=Label(root,text="Monitoring Sensors",bg="mint cream" ,font="TIMES 13 underline bold")
cntrl_lbl.grid(row=3,column=0)

r1=Label(root,text="1. CO2(PPM)",bg="mint cream",fg="Blue",font=("Times new roman",13,"bold"))
r1.grid(row=4,column=0,padx=15,sticky=W)
r2=Label(root,text="2. Moisture(%)",bg="mint cream",fg="Orange",font=("Times new roman",13,"bold"))
r2.grid(row=4,column=1,padx=30,sticky=W)
r3=Label(root,text="3. Light(%)",bg="mint cream",fg="Green",font=("Times new roman",13,"bold"))
r3.grid(row=4,column=2,padx=50,sticky=W)

title_label = Label(
    root,
    text="Pump Threshold :",
    bg="mint cream",
    font=("TIMES NEW ROMAN", 13, "bold"))
title_label.grid(row=6, column=0, sticky=W, padx=20)   

ThLabl = Label(
    root,
    text="  ",
    bg="mint cream",
    font=("TIMES NEW ROMAN", 13, "bold"))
ThLabl.grid(row=6,column=1,pady=20,padx=30,sticky=W)

Firel = Label(
    root,
    text="No Fire",
    bg="mint cream",width=15,fg="orange",
    font=("TIMES NEW ROMAN", 13, "bold"))
Firel.grid(row=6, column=2, sticky=W, padx=20) 

ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys,yr,yt,TH), interval=1)
plt.show()  

root.mainloop()      
