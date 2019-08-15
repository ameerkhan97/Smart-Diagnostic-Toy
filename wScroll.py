import serial
import csv
import numpy as np
from tkinter import*
from tkinter import scrolledtext
myGui = Tk()
myGui.title("IMU_Stream")
myGui.geometry("350x200")
txt = scrolledtext.ScrolledText(myGui,width=400,height=100)
txt.grid(column=1,row=10) 
ser = serial.Serial("/dev/tty.HC-05-DevB")
f = open('output.csv', 'w+')
while(1):
        line = ser.readline().decode('utf-8')[:-1]
        if line:  # If it isn't a blank line
                if "X" in line:
                        print(line)
                else:
                      f.write(line)
                      ##myLabel = Label(myGui, text =line,font=12).pack()
                      txt.insert(INSERT,line)
                      myGui.update_idletasks()
                      txt.delete(1.0,END)
                      myGui.update()
                      
f.close()
  
