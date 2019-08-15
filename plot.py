#Ameer Khan
#script to plot/analyze data from csv file and create a report of the data

from scipy import integrate
import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np
import os
import sys
from reportlab.lib import colors
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas
from textwrap import wrap
from datetime import datetime

#create folder for patient
current_directory = os.getcwd()
final_directory = os.path.join(current_directory, str(sys.argv[1]))
if not os.path.exists(final_directory):
   os.makedirs(final_directory)

#ask for patient information
with open (os.path.join(final_directory, 'PatientInfo.txt'), "w") as f:
    f.write("Patient Information");
    f.write("\n");
    f.write("Patient Name:\n" + input('Enter patients name: '));
    f.write("\n");
    f.write("Patient Age:\n" + input('Enter patients age: '));
    f.write("\n");
    f.write("Patient Gender:\n" + input('Enter patients gender: '));
    f.write("\n");
    f.write("Patient Date of Birth:\n" + input('Enter patients date of birth: '));
    f.write("\n");
    f.write("Examiner Name:\n" + input('Enter the examiners name: '));
    
#read in csv file
df = pd.read_csv (sys.argv[2])
row_count = sum(1 for row in csv.reader(open(sys.argv[2])))

#store columns of imu data
t = np.arange(0, (row_count-1)*0.05, 0.05)
Gx = df.rawGx
Gy = df.rawGy
Gz = df.rawGz
Ax = df.rawAx
Ay = df.rawAy
Az = df.rawAz
procGx = df.procGx
procGy = df.procGy
procGz = df.procGz

#store score data
score1 = df.iloc[row_count-11, 13]
score2 = df.iloc[row_count-10, 13]
score3 = df.iloc[row_count-9, 13]
score4 = df.iloc[row_count-8, 13]
score5 = df.iloc[row_count-7, 13]
score6 = df.iloc[row_count-6, 13]
score7 = df.iloc[row_count-5, 13]
score8 = df.iloc[row_count-4, 13]
score9 = df.iloc[row_count-3, 13]
score10 = df.iloc[row_count-2, 13]

#score data analysis
scorecount = df['score'].count()
scoresum = df['score'].sum()
scoremean = df['score'].mean()
scoremedian = df['score'].median()
scorestd = df['score'].std()
scoremin = df['score'].min()
scoremax = df['score'].max()

#store time data
time1 = df.iloc[row_count-11, 12]/1000
time2 = df.iloc[row_count-10, 12]/1000
time3 = df.iloc[row_count-9, 12]/1000
time4 = df.iloc[row_count-8, 12]/1000
time5 = df.iloc[row_count-7, 12]/1000
time6 = df.iloc[row_count-6, 12]/1000
time7 = df.iloc[row_count-5, 12]/1000
time8 = df.iloc[row_count-4, 12]/1000
time9 = df.iloc[row_count-3, 12]/1000
time10 = df.iloc[row_count-2, 12]/1000

#time data analysis
timecount = df['time'].count()
timesum = df['time'].sum()/1000
timemean = df['time'].mean()/1000
timemedian = df['time'].median()/1000
timestd = df['time'].std()/1000
timemin = df['time'].min()/1000
timemax = df['time'].max()/1000

#timestamp of when button was pressed
btime1 = time1
btime2 = time1+time2
btime3 = time1+time2+time3
btime4 = time1+time2+time3+time4
btime5 = time1+time2+time3+time4+time5
btime6 = time1+time2+time3+time4+time5+time6
btime7 = time1+time2+time3+time4+time5+time6+time7
btime8 = time1+time2+time3+time4+time5+time6+time7+time8
btime9 = time1+time2+time3+time4+time5+time6+time7+time8+time9
btime10 = time1+time2+time3+time4+time5+time6+time7+time8+time9+time10
buttonpress = [btime1, btime2, btime3, btime4, btime5, btime6, btime7, btime8, btime9, btime10]

#store prompt data
prompt1 = df.iloc[row_count-11, 14]
prompt2 = df.iloc[row_count-10, 14]
prompt3 = df.iloc[row_count-9, 14]
prompt4 = df.iloc[row_count-8, 14]
prompt5 = df.iloc[row_count-7, 14]
prompt6 = df.iloc[row_count-6, 14]
prompt7 = df.iloc[row_count-5, 14]
prompt8 = df.iloc[row_count-4, 14]
prompt9 = df.iloc[row_count-3, 14]
prompt10 = df.iloc[row_count-2, 14]

#store response data
response1 = df.iloc[row_count-11, 15]
response2 = df.iloc[row_count-10, 15]
response3 = df.iloc[row_count-9, 15]
response4 = df.iloc[row_count-8, 15]
response5 = df.iloc[row_count-7, 15]
response6 = df.iloc[row_count-6, 15]
response7 = df.iloc[row_count-5, 15]
response8 = df.iloc[row_count-4, 15]
response9 = df.iloc[row_count-3, 15]
response10 = df.iloc[row_count-2, 15]

#decode full prompt and response data
def decoder(colorarr, shapearr):
   if colorarr == 'R':
      color = 'Red'
   if colorarr == 'G':
      color = 'Green'
   if colorarr == 'B':
      color = 'Blue'
   if shapearr == 'T':
      shape = 'Triangle'
   if shapearr == 'S':
      shape = 'Square'
   if shapearr == 'C':
      shape = 'Circle'
   return color + " " + shape

p1 = decoder(prompt1[0], prompt1[1])
p2 = decoder(prompt2[0], prompt2[1])
p3 = decoder(prompt3[0], prompt3[1])
p4 = decoder(prompt4[0], prompt4[1])
p5 = decoder(prompt5[0], prompt5[1])
p6 = decoder(prompt6[0], prompt6[1])
p7 = decoder(prompt7[0], prompt7[1])
p8 = decoder(prompt8[0], prompt8[1])
p9 = decoder(prompt9[0], prompt9[1])
p10 = decoder(prompt10[0], prompt10[1])

r1 = decoder(response1[0], response1[1])
r2 = decoder(response2[0], response2[1])
r3 = decoder(response3[0], response3[1])
r4 = decoder(response4[0], response4[1])
r5 = decoder(response5[0], response5[1])
r6 = decoder(response6[0], response6[1])
r7 = decoder(response7[0], response7[1])
r8 = decoder(response8[0], response8[1])
r9 = decoder(response9[0], response9[1])
r10 = decoder(response10[0], response10[1])

#decode color and shape for prompt and response
def decodecolor(colorarr):
   if colorarr == 'R':
      color = 'Red'
   if colorarr == 'G':
      color = 'Green'
   if colorarr == 'B':
      color = 'Blue'
   return color

def decodeshape(shapearr):
   if shapearr == 'T':
      shape = 'Triangle'
   if shapearr == 'S':
      shape = 'Square'
   if shapearr == 'C':
      shape = 'Circle'
   return shape

pcolor1 = decodecolor(prompt1[0])
pcolor2 = decodecolor(prompt2[0])
pcolor3 = decodecolor(prompt3[0])
pcolor4 = decodecolor(prompt4[0])
pcolor5 = decodecolor(prompt5[0])
pcolor6 = decodecolor(prompt6[0])
pcolor7 = decodecolor(prompt7[0])
pcolor8 = decodecolor(prompt8[0])
pcolor9 = decodecolor(prompt9[0])
pcolor10 = decodecolor(prompt10[0])

pshape1 = decodeshape(prompt1[1])
pshape2 = decodeshape(prompt2[1])
pshape3 = decodeshape(prompt3[1])
pshape4 = decodeshape(prompt4[1])
pshape5 = decodeshape(prompt5[1])
pshape6 = decodeshape(prompt6[1])
pshape7 = decodeshape(prompt7[1])
pshape8 = decodeshape(prompt8[1])
pshape9 = decodeshape(prompt9[1])
pshape10 = decodeshape(prompt10[1])

rcolor1 = decodecolor(response1[0])
rcolor2 = decodecolor(response2[0])
rcolor3 = decodecolor(response3[0])
rcolor4 = decodecolor(response4[0])
rcolor5 = decodecolor(response5[0])
rcolor6 = decodecolor(response6[0])
rcolor7 = decodecolor(response7[0])
rcolor8 = decodecolor(response8[0])
rcolor9 = decodecolor(response9[0])
rcolor10 = decodecolor(response10[0])

rshape1 = decodeshape(response1[1])
rshape2 = decodeshape(response2[1])
rshape3 = decodeshape(response3[1])
rshape4 = decodeshape(response4[1])
rshape5 = decodeshape(response5[1])
rshape6 = decodeshape(response6[1])
rshape7 = decodeshape(response7[1])
rshape8 = decodeshape(response8[1])
rshape9 = decodeshape(response9[1])
rshape10 = decodeshape(response10[1])

#variables that keeps track of what answer, color and shape is wrong
wrong = 0
redtracker = 0
greentracker = 0
bluetracker = 0
triangletracker = 0
squaretracker = 0
circletracker = 0

#checks to see which answer, color and shape is wrong
if score1 == 0:
    wrong += 1
    if pcolor1 != rcolor1:
        if pcolor1 == 'Red':
            redtracker += 1
        if pcolor1 == 'Green':
            greentracker += 1
        if pcolor1 == 'Blue':
            bluetracker += 1
    if pshape1 != rshape1:
        if pshape1 == 'Triangle':
            triangletracker += 1
        if pshape1 == 'Square':
            squaretracker += 1
        if pshape1 == 'Circle':
            circletracker += 1
if score2 == 0:
    wrong += 1
    if pcolor2 != rcolor2:
        if pcolor2 == 'Red':
            redtracker += 1
        if pcolor2 == 'Green':
            greentracker += 1
        if pcolor2 == 'Blue':
            bluetracker += 1
    if pshape2 != rshape2:
        if pshape2 == 'Triangle':
            triangletracker += 1
        if pshape2 == 'Square':
            squaretracker += 1
        if pshape2 == 'Circle':
            circletracker += 1
if score3 == 0:
    wrong += 1
    if pcolor3 != rcolor3:
        if pcolor3 == 'Red':
            redtracker += 1
        if pcolor3 == 'Green':
            greentracker += 1
        if pcolor3 == 'Blue':
            bluetracker += 1
    if pshape3 != rshape3:
        if pshape3 == 'Triangle':
            triangletracker += 1
        if pshape3 == 'Square':
            squaretracker += 1
        if pshape3 == 'Circle':
            circletracker += 1
if score4 == 0:
    wrong += 1
    if pcolor4 != rcolor4:
        if pcolor4 == 'Red':
            redtracker += 1
        if pcolor4 == 'Green':
            greentracker += 1
        if pcolor4 == 'Blue':
            bluetracker += 1
    if pshape4 != rshape4:
        if pshape4 == 'Triangle':
            triangletracker += 1
        if pshape4 == 'Square':
            squaretracker += 1
        if pshape4 == 'Circle':
            circletracker += 1
if score5 == 0:
    wrong += 1
    if pcolor5 != rcolor5:
        if pcolor5 == 'Red':
            redtracker += 1
        if pcolor5 == 'Green':
            greentracker += 1
        if pcolor5 == 'Blue':
            bluetracker += 1
    if pshape5 != rshape5:
        if pshape5 == 'Triangle':
            triangletracker += 1
        if pshape5 == 'Square':
            squaretracker += 1
        if pshape5 == 'Circle':
            circletracker += 1
if score6 == 0:
    wrong += 1
    if pcolor6 != rcolor6:
        if pcolor6 == 'Red':
            redtracker += 1
        if pcolor6 == 'Green':
            greentracker += 1
        if pcolor6 == 'Blue':
            bluetracker += 1
    if pshape6 != rshape6:
        if pshape6 == 'Triangle':
            triangletracker += 1
        if pshape6 == 'Square':
            squaretracker += 1
        if pshape6 == 'Circle':
            circletracker += 1
if score7 == 0:
    wrong += 1
    if pcolor7 != rcolor7:
        if pcolor7 == 'Red':
            redtracker += 1
        if pcolor7 == 'Green':
            greentracker += 1
        if pcolor7 == 'Blue':
            bluetracker += 1
    if pshape6 != rshape6:
        if pshape7 == 'Triangle':
            triangletracker += 1
        if pshape7 == 'Square':
            squaretracker += 1
        if pshape7 == 'Circle':
            circletracker += 1
if score8 == 0:
    wrong += 1
    if pcolor8 != rcolor8:
        if pcolor8 == 'Red':
            redtracker += 1
        if pcolor8 == 'Green':
            greentracker += 1
        if pcolor8 == 'Blue':
            bluetracker += 1
    if pshape8 != rshape8:
        if pshape8 == 'Triangle':
            triangletracker += 1
        if pshape8 == 'Square':
            squaretracker += 1
        if pshape8 == 'Circle':
            circletracker += 1
if score9 == 0:
    wrong += 1
    if pcolor9 != rcolor9:
        if pcolor9 == 'Red':
            redtracker += 1
        if pcolor9 == 'Green':
            greentracker += 1
        if pcolor9 == 'Blue':
            bluetracker += 1
    if pshape9 != rshape9:
        if pshape9 == 'Triangle':
            triangletracker += 1
        if pshape9 == 'Square':
            squaretracker += 1
        if pshape9 == 'Circle':
            circletracker += 1 
if score10 == 0:
    wrong += 1
    if pcolor10 != rcolor10:
        if pcolor10 == 'Red':
            redtracker += 1
        if pcolor10 == 'Green':
            greentracker += 1
        if pcolor10 == 'Blue':
            bluetracker += 1
    if pshape10 != rshape10:
        if pshape10 == 'Triangle':
            triangletracker += 1
        if pshape10 == 'Square':
            squaretracker += 1
        if pshape10 == 'Circle':
            circletracker += 1
            
#variables that keeps track of the total time to find each color and shape
redtime = 0
greentime = 0
bluetime = 0
triangletime = 0
squaretime = 0
circletime = 0

#variables that keep track of the total amount of each color and shape
totalred = 0
totalgreen = 0
totalblue = 0
totaltriangle = 0
totalsquare = 0
totalcircle = 0

#checks the total time taken to find each color and total amount of each color
if pcolor1 == 'Red':
   redtime += time1
   totalred += 1
if pcolor1 == 'Green':
   greentime += time1
   totalgreen += 1
if pcolor1 == 'Blue':
   bluetime += time1
   totalblue += 1
   
if pcolor2 == 'Red':
   redtime += time2
   totalred += 1
if pcolor2 == 'Green':
   greentime += time2
   totalgreen += 1
if pcolor2 == 'Blue':
   bluetime += time2
   totalblue += 1

if pcolor3 == 'Red':
   redtime += time3
   totalred += 1
if pcolor3 == 'Green':
   greentime += time3
   totalgreen += 1
if pcolor3 == 'Blue':
   bluetime += time3
   totalblue += 1

if pcolor4 == 'Red':
   redtime += time4
   totalred += 1
if pcolor4 == 'Green':
   greentime += time4
   totalgreen += 1
if pcolor4 == 'Blue':
   bluetime += time4
   totalblue += 1
   
if pcolor5 == 'Red':
   redtime += time5
   totalred += 1
if pcolor5 == 'Green':
   greentime += time5
   totalgreen += 1
if pcolor5 == 'Blue':
   bluetime += time5
   totalblue += 1

if pcolor6 == 'Red':
   redtime += time6
   totalred += 1
if pcolor6 == 'Green':
   greentime += time6
   totalgreen += 1
if pcolor6 == 'Blue':
   bluetime += time6
   totalblue += 1

if pcolor7 == 'Red':
   redtime += time7
   totalred += 1
if pcolor7 == 'Green':
   greentime += time7
   totalgreen += 1
if pcolor7 == 'Blue':
   bluetime += time7
   totalblue += 1
   
if pcolor8 == 'Red':
   redtime += time8
   totalred += 1
if pcolor8 == 'Green':
   greentime += time8
   totalgreen += 1
if pcolor8 == 'Blue':
   bluetime += time8
   totalblue += 1

if pcolor9 == 'Red':
   redtime += time9
   totalred += 1
if pcolor9 == 'Green':
   greentime += time9
   totalgreen += 1
if pcolor9 == 'Blue':
   bluetime += time9
   totalblue += 1

if pcolor10 == 'Red':
   redtime += time10
   totalred += 1
if pcolor10 == 'Green':
   greentime += time10
   totalgreen += 1
if pcolor10 == 'Blue':
   bluetime += time10
   totalblue += 1

#checks the total time taken to find each shape and total amount of each shape
if pshape1 == 'Triangle':
   triangletime += time1
   totaltriangle += 1
if pshape1 == 'Square':
   squaretime += time1
   totalsquare += 1
if pshape1 == 'Circle':
   circletime += time1
   totalcircle += 1
   
if pshape2 == 'Triangle':
   triangletime += time2
   totaltriangle += 1
if pshape2 == 'Square':
   squaretime += time2
   totalsquare += 1
if pshape2 == 'Circle':
   circletime += time2
   totalcircle += 1

if pshape3 == 'Triangle':
   triangletime += time3
   totaltriangle += 1
if pshape3 == 'Square':
   squaretime += time3
   totalsquare += 1
if pshape3 == 'Circle':
   circletime += time3
   totalcircle += 1

if pshape4 == 'Triangle':
   triangletime += time4
   totaltriangle += 1
if pshape4 == 'Square':
   squaretime += time4
   totalsquare += 1
if pshape4 == 'Circle':
   circletime += time4
   totalcircle += 1
   
if pshape5 == 'Triangle':
   triangletime += time5
   totaltriangle += 1
if pshape5 == 'Square':
   squaretime += time5
   totalsquare += 1
if pshape5 == 'Circle':
   circletime += time5
   totalcircle += 1

if pshape6 == 'Triangle':
   triangletime += time6
   totaltriangle += 1
if pshape6 == 'Square':
   squaretime += time6
   totalsquare += 1
if pshape6 == 'Circle':
   circletime += time6
   totalcircle += 1

if pshape7 == 'Triangle':
   triangletime += time7
   totaltriangle += 1
if pshape7 == 'Square':
   squaretime += time7
   totalsquare += 1
if pshape7 == 'Circle':
   circletime += time7
   totalcircle += 1
   
if pshape8 == 'Triangle':
   triangletime += time8
   totaltriangle += 1
if pshape8 == 'Square':
   squaretime += time8
   totalsquare += 1
if pshape8 == 'Circle':
   circletime += time8
   totalcircle += 1

if pshape9 == 'Triangle':
   triangletime += time9
   totaltriangle += 1
if pshape9 == 'Square':
   squaretime += time9
   totalsquare += 1
if pshape9 == 'Circle':
   circletime += time9
   totalcircle += 1

if pshape10 == 'Triangle':
   triangletime += time10
   totaltriangle += 1
if pshape10 == 'Square':
   squaretime += time10
   totalsquare += 1
if pshape10 == 'Circle':
   circletime += time10
   totalcircle += 1

#calculate average time taken for each color and shape
avgred = 0
avggreen = 0
avgblue = 0
avgtriangle = 0
avgsquare = 0
avgcircle = 0

if totalred > 0:
   avgred = redtime/totalred
if totalgreen > 0:
   avggreen = greentime/totalgreen
if totalblue > 0:
   avgblue = bluetime/totalblue
if totaltriangle > 0:
   avgtriangle = triangletime/totaltriangle
if totalsquare > 0:
   avgsquare = squaretime/totalsquare
if totalcircle > 0:
   avgcircle = circletime/totalcircle

'''
These are the plots
comparing the
integrated gyroscope
'''

#integratedGx plot
plt.figure(1)
Gx_int = integrate.cumtrapz(Gx, t, initial=0)
plt.plot(t, Gx_int, label='integrated gyrox')
Gx_slope = np.diff(Gx_int)/np.diff(t)
Gx_sign = np.where(np.diff(np.signbit(Gx_slope)))[0]
Gx_time = []
freq = []
pt = 5
hold = 5
for i in Gx_sign:
   if i >= pt:
      if (Gx_int[i+pt] - Gx_int[i+1]) > hold or (Gx_int[i+pt] - Gx_int[i+1]) < -hold or (Gx_int[i+1] - Gx_int[i-pt]) > hold or (Gx_int[i+1] - Gx_int[i-pt]) < -hold:
         plt.plot(t[i+1], Gx_int[i+1], '-o', color='black')
         Gx_timesign = t[i+1]
         Gx_time.append(Gx_timesign)
         freq.append(Gx_timesign)

#integratedGx data summary
Gxdata = pd.DataFrame(Gx_int)
Gxcount = Gxdata.count().values
Gxsum = Gxdata.sum().values
Gxmean = Gxdata.mean().values
Gxmedian = Gxdata.median().values
Gxstd = Gxdata.std().values
Gxmin = Gxdata.min().values
Gxmax = Gxdata.max().values

#integratedGy plot
Gy_int = integrate.cumtrapz(Gy, t, initial=0)
plt.plot(t, Gy_int, label='integrated gyroy')
Gy_slope = np.diff(Gy_int)/np.diff(t)
Gy_sign = np.where(np.diff(np.signbit(Gy_slope)))[0]
Gy_time = []
for i in Gy_sign:
   if i >= pt:
      if (Gy_int[i+pt] - Gy_int[i+1]) > hold or (Gy_int[i+pt] - Gy_int[i+1]) < -hold or (Gy_int[i+1] - Gy_int[i-pt]) > hold or (Gy_int[i+1] - Gy_int[i-pt]) < -hold:
         plt.plot(t[i+1], Gy_int[i+1], '-o', color='black')
         Gy_timesign = t[i+1]
         Gy_time.append(Gy_timesign)
         freq.append(Gy_timesign)

#integratedGy data summary
Gydata = pd.DataFrame(Gy_int)
Gycount = Gydata.count().values
Gysum = Gydata.sum().values
Gymean = Gydata.mean().values
Gymedian = Gydata.median().values
Gystd = Gydata.std().values
Gymin = Gydata.min().values
Gymax = Gydata.max().values

#integratedGz plot
Gz_int = integrate.cumtrapz(Gz, t, initial=0)
plt.plot(t, Gz_int, label='integrated gyroz')
plt.xlabel('Time (s)')
plt.ylabel('Angular Position (Degrees)')
plt.title('Integrated Gyroscope Data')
plt.legend()
Gz_slope = np.diff(Gz_int)/np.diff(t)
Gz_sign = np.where(np.diff(np.signbit(Gz_slope)))[0]
Gz_time = []
for i in Gz_sign:
   if i >= pt:
      if (Gz_int[i+pt] - Gz_int[i+1]) > hold or (Gz_int[i+pt] - Gz_int[i+1]) < -hold or (Gz_int[i+1] - Gz_int[i-pt]) > hold or (Gz_int[i+1] - Gz_int[i-pt]) < -hold:
         plt.plot(t[i+1], Gz_int[i+1], '-o', color='black')
         Gz_timesign = t[i+1]
         Gz_time.append(Gz_timesign)
         freq.append(Gz_timesign)
for i in buttonpress:
   plt.axvline(x=i, ls='--', color='k')
plt.savefig(os.path.join(final_directory, 'Integrated Gyroscope Plot.png'), dpi=75)

#integratedGz data summary
Gzdata = pd.DataFrame(Gz_int)
Gzcount = Gzdata.count().values
Gzsum = Gzdata.sum().values
Gzmean = Gzdata.mean().values
Gzmedian = Gzdata.median().values
Gzstd = Gzdata.std().values
Gzmin = Gzdata.min().values
Gzmax = Gzdata.max().values

#calculating the number of inflection points between each button press
rot1 = 0
rot2 = 0
rot3 = 0
rot4 = 0
rot5 = 0
rot6 = 0
rot7 = 0
rot8 = 0
rot9 = 0
rot10 = 0

for i in freq:
   if i < btime1:
      rot1 += 1
   elif i >= btime1 and i < btime2:
      rot2 += 1
   elif i >= btime2 and i < btime3:
      rot3 += 1
   elif i >= btime3 and i < btime4:
      rot4 += 1
   elif i >= btime4 and i < btime5:
      rot5 += 1
   elif i >= btime5 and i < btime6:
      rot6 += 1
   elif i >= btime6 and i < btime7:
      rot7 += 1
   elif i >= btime7 and i < btime8:
      rot8 += 1
   elif i >= btime8 and i < btime9:
      rot9 += 1
   elif i >= btime9 and i < btime10:
      rot10 += 1

totalrot = rot1+rot2+rot3+rot4+rot5+rot6+rot7+rot8+rot9+rot10
avgrot = totalrot/10

'''
This is the plot for
the fourier transform
of the integrated data
'''

plt.figure(2)
rawX_list = []
rawY_list = []
rawZ_list = []
with open(sys.argv[2], newline="\n") as csv_file:
    reader = csv.reader(csv_file,delimiter=',')
    for idx,row in enumerate(reader):

        if(idx == 0):
            continue

        rawX = row[0]
        if(rawX is ''): 
            continue 
        else:
            rawX_list.append(int(rawX))
   
        rawY = row[1]
        if(rawY is ''): 
            continue 
        else:
            rawY_list.append(int(rawY))

        rawZ = row[2]
        if(rawZ is ''): 
            continue 
        else:
            rawZ_list.append(int(rawZ))

fftxtime = np.arange(0, len(rawX_list)*0.05, 0.05)
fftytime = np.arange(0, len(rawY_list)*0.05, 0.05)
fftztime = np.arange(0, len(rawZ_list)*0.05, 0.05)

X_list = integrate.cumtrapz(rawX_list, fftxtime, initial=0)
Y_list = integrate.cumtrapz(rawY_list, fftytime, initial=0)
Z_list = integrate.cumtrapz(rawZ_list, fftztime, initial=0)

#plot fourier transform for integratedGx
dt = 0.05
sample_rate = 1/dt
n = len(X_list)
mag  = np.fft.fft(X_list, n=n)
freq = np.fft.fftfreq(n,d=dt); # Compute frequency bins given sample time 

# To get energy at each frequency we take the magnitude of the
# real and imaginary components
mag = mag.real*mag.real + mag.imag*mag.imag
mag = np.sqrt(mag)

# Normalize data to [0,1]
hi = 1
lo = 0
magMax = max(mag.real)
magMin = min(mag.real)
scaled_mag = []
for data in mag.real:
    newData = (hi-lo)* (data - magMin)/(magMax-magMin) + lo
    scaled_mag.append(newData)

plt.plot(freq, scaled_mag, label='integrated gyrox freq')
plt.xlim(left=0, right=1.5)
plt.xticks(np.arange(0,2,step=0.5))

#plot fourier transform for integratedGy
dt = 0.05
sample_rate = 1/dt
n = len(Y_list)
mag  = np.fft.fft(Y_list, n=n)
freq = np.fft.fftfreq(n,d=dt); # Compute frequency bins given sample time 

# To get energy at each frequency we take the magnitude of the
# real and imaginary components
mag = mag.real*mag.real + mag.imag*mag.imag
mag = np.sqrt(mag)

# Normalize data to [0,1]
hi = 1
lo = 0
magMax = max(mag.real)
magMin = min(mag.real)
scaled_mag = []
for data in mag.real:
    newData = (hi-lo)* (data - magMin)/(magMax-magMin) + lo
    scaled_mag.append(newData)

plt.plot(freq, scaled_mag, label='integrated gyroy freq')
plt.xlim(left=0, right=1.5)
plt.xticks(np.arange(0,2,step=0.5))

#plot fourier transform for integratedGz
dt = 0.05
sample_rate = 1/dt
n = len(Z_list)
mag  = np.fft.fft(Z_list, n=n)
freq = np.fft.fftfreq(n,d=dt); # Compute frequency bins given sample time 

# To get energy at each frequency we take the magnitude of the
# real and imaginary components
mag = mag.real*mag.real + mag.imag*mag.imag
mag = np.sqrt(mag)

# Normalize data to [0,1]
hi = 1
lo = 0
magMax = max(mag.real)
magMin = min(mag.real)
scaled_mag = []
for data in mag.real:
    newData = (hi-lo)* (data - magMin)/(magMax-magMin) + lo
    scaled_mag.append(newData)

plt.plot(freq, scaled_mag, label='integrated gyroz freq')
plt.xlim(left=0, right=1.5)
plt.xticks(np.arange(0,2,step=0.5))
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude')
plt.title('Fourier Transform of Integrated Gyroscope Data')
plt.legend()
plt.savefig(os.path.join(final_directory, 'Fourier Transform of Integrated Gyroscope Plot.png'), dpi=75)

'''
These are the plots
comparing the
integrated accelerometer
'''

#integratedAx plot
plt.figure(3)
Ax_int = integrate.cumtrapz(Ax, t, initial=0)
Ax_int2 = integrate.cumtrapz(Ax_int, t, initial=0)
plt.plot(t, Ax_int2, label='integrated accelx')

#integratedAx data summary
Axdata = pd.DataFrame(Ax_int2)
Axcount = Axdata.count().values
Axsum = Axdata.sum().values
Axmean = Axdata.mean().values
Axmedian = Axdata.median().values
Axstd = Axdata.std().values
Axmin = Axdata.min().values
Axmax = Axdata.max().values

#integratedAy plot
Ay_int = integrate.cumtrapz(Ay, t, initial=0)
Ay_int2 = integrate.cumtrapz(Ay_int, t, initial=0)
plt.plot(t, Ay_int2, label='integrated accely')

#integratedAy data summary
Aydata = pd.DataFrame(Ay_int2)
Aycount = Aydata.count().values
Aysum = Aydata.sum().values
Aymean = Aydata.mean().values
Aymedian = Aydata.median().values
Aystd = Aydata.std().values
Aymin = Aydata.min().values
Aymax = Aydata.max().values

#integratedAz plot
Az_int = integrate.cumtrapz(Az, t, initial=0)
Az_int2 = integrate.cumtrapz(Az_int, t, initial=0)
plt.plot(t, Az_int2, label='integrated accelz')
plt.xlabel('Time (s)')
plt.ylabel('Acceleration')
plt.title('Integrated Accelerometer Data')
plt.legend()
plt.savefig(os.path.join(final_directory, 'Integrated Accelerometer Plot.png'), dpi=75)

#integratedAz data summary
Azdata = pd.DataFrame(Az_int2)
Azcount = Azdata.count().values
Azsum = Azdata.sum().values
Azmean = Azdata.mean().values
Azmedian = Azdata.median().values
Azstd = Azdata.std().values
Azmin = Azdata.min().values
Azmax = Azdata.max().values

'''
This is the bar graph for
the game data involving
score, time,
color/shape prompt and response
'''

#plot bar graph for wrong answers of the game data
plt.figure(4)
objects = ('Total', 'Red', 'Green', 'Blue', 'Triangle', 'Square', 'Circle')
y_pos = np.arange(len(objects))
x_values = [wrong, redtracker, greentracker, bluetracker, triangletracker, squaretracker, circletracker]
plt.bar(y_pos, x_values, align='center', alpha=0.5, color=['black', 'red', 'green', 'blue', 'cyan', 'magenta', 'yellow'], edgecolor='black')
plt.xticks(y_pos, objects)
for a,b in zip(x_values, y_pos):
    plt.text(b, a, str(a), horizontalalignment='center', verticalalignment='bottom', fontsize=8, color='blue', fontweight='bold')
plt.ylabel('Total Amount')
plt.title('Incorrect Answers')
plt.savefig(os.path.join(final_directory, 'Incorrect Answers Graph.png'), dpi=75)

#plot bar graph for the time data
plt.figure(5)
objects = ('Total', 'Avg', 'Max', 'Min', 'Q1', 'Q2', 'Q3', 'Q4', 'Q5', 'Q6', 'Q7', 'Q8', 'Q9', 'Q10')
y_pos = np.arange(len(objects))
x_values = [np.around(timesum, 2), np.around(timemean, 2), np.around(timemax, 2), np.around(timemin, 2),
            np.around(time1, 2), np.around(time2, 2), np.around(time3, 2), np.around(time4, 2), np.around(time5, 2),
            np.around(time6, 2), np.around(time7, 2), np.around(time8, 2), np.around(time9, 2), np.around(time10, 2)]
plt.bar(y_pos, x_values, align='center', alpha=0.5, color=['black', 'red', 'green', 'blue', 'cyan', 'magenta', 'yellow'], edgecolor='black')
plt.xticks(y_pos, objects)
for a,b in zip(x_values, y_pos):
    plt.text(b, a, str(a), horizontalalignment='center', verticalalignment='bottom', fontsize=8, color='blue', fontweight='bold')
plt.ylabel('Time (s)')
plt.title('Time Data Summary')
plt.savefig(os.path.join(final_directory, 'Time Data Summary Graph.png'), dpi=75)

#plot bar graph for the average time data of each color and shape
plt.figure(6)
objects = ('Red', 'Green', 'Blue', 'Triangle', 'Square', 'Circle')
y_pos = np.arange(len(objects))
x_values = [np.around(avgred, 2), np.around(avggreen, 2), np.around(avgblue, 2),
            np.around(avgtriangle, 2), np.around(avgsquare, 2), np.around(avgcircle, 2)]
plt.bar(y_pos, x_values, align='center', alpha=0.5, color=['red', 'green', 'blue', 'cyan', 'magenta', 'yellow'], edgecolor='black')
plt.xticks(y_pos, objects)
for a,b in zip(x_values, y_pos):
    plt.text(b, a, str(a), horizontalalignment='center', verticalalignment='bottom', fontsize=8, color='blue', fontweight='bold')
plt.ylabel('Average Time (s)')
plt.title('Color and Shape Time Data')
plt.savefig(os.path.join(final_directory, 'Color and Shape Time Data Graph.png'), dpi=75)

'''
This is the table with
the game data
'''

#add game data to table
plt.figure(7)
col_labels = ['Score', 'Time (s)', 'Prompt', 'Response']
row_labels = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'Total']
table_vals = [[score1, np.around(time1, 2), p1, r1],
              [score2, np.around(time2, 2), p2, r2],
              [score3, np.around(time3, 2), p3, r3],
              [score4, np.around(time4, 2), p4, r4],
              [score5, np.around(time5, 2), p5, r5],
              [score6, np.around(time6, 2), p6, r6],
              [score7, np.around(time7, 2), p7, r7],
              [score8, np.around(time8, 2), p8, r8],
              [score9, np.around(time9, 2), p9, r9],
              [score10, np.around(time10, 2), p10, r10],
              [scoresum, np.around(timesum, 2), '-', '-']]

#create table
the_table = plt.table(cellText=table_vals,
                      colWidths=[0.1] * 6,
                      rowLabels=row_labels,
                      colLabels=col_labels,
                      loc='center')
the_table.auto_set_font_size(False)
the_table.set_fontsize(12)
the_table.scale(4, 2)

#removes ticks and spines to get only a table
plt.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
plt.tick_params(axis='y', which='both', right=False, left=False, labelleft=False)
for pos in ['right','top','bottom','left']:
    plt.gca().spines[pos].set_visible(False)
plt.savefig(os.path.join(final_directory, 'Game Data.png'), bbox_inches='tight', pad_inches=0.05, dpi=50)

'''
These are the tables with
the analysis of the gyroscope
and accelerometer data
'''

#add integrated gyroscope analysis to table
plt.figure(8)
col_labels = ['Gx', 'Gy', 'Gz']
row_labels = ['Data Points', 'Sum', 'Mean', 'Median', 'Standard Deviation', 'Minimum', 'Maximum']
table_vals = [[np.around(Gxcount, 2), np.around(Gycount, 2), np.around(Gzcount, 2)],
              [np.around(Gxsum, 2), np.around(Gysum, 2), np.around(Gzsum, 2)],
              [np.around(Gxmean, 2), np.around(Gymean, 2), np.around(Gzmean, 2)],
              [np.around(Gxmedian, 2), np.around(Gymedian, 2), np.around(Gzmedian, 2)],
              [np.around(Gxstd, 2), np.around(Gystd, 2), np.around(Gzstd, 2)],
              [np.around(Gxmin, 2), np.around(Gymin, 2), np.around(Gzmin, 2)],
              [np.around(Gxmax, 2), np.around(Gymax, 2), np.around(Gzmax, 2)]]

#create table
the_table = plt.table(cellText=table_vals,
                      colWidths=[0.1] * 6,
                      rowLabels=row_labels,
                      colLabels=col_labels,
                      loc='center')
the_table.auto_set_font_size(False)
the_table.set_fontsize(12)
the_table.scale(6, 2)

#removes ticks and spines to get only a table
plt.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
plt.tick_params(axis='y', which='both', right=False, left=False, labelleft=False)
for pos in ['right','top','bottom','left']:
    plt.gca().spines[pos].set_visible(False)
plt.savefig(os.path.join(final_directory, 'Integrated Gyroscope Analysis.png'), bbox_inches='tight', pad_inches=0.05, dpi=50)

#add integrated accelerometer analysis to table
plt.figure(9)
col_labels = ['Ax', 'Ay', 'Az']
row_labels = ['Data Points', 'Sum', 'Mean', 'Median', 'Standard Deviation', 'Minimum', 'Maximum']
table_vals = [[np.around(Axcount, 2), np.around(Aycount, 2), np.around(Azcount, 2)],
              [np.around(Axsum, 2), np.around(Aysum, 2), np.around(Azsum, 2)],
              [np.around(Axmean, 2), np.around(Aymean, 2), np.around(Azmean, 2)],
              [np.around(Axmedian, 2), np.around(Aymedian, 2), np.around(Azmedian, 2)],
              [np.around(Axstd, 2), np.around(Aystd, 2), np.around(Azstd, 2)],
              [np.around(Axmin, 2), np.around(Aymin, 2), np.around(Azmin, 2)],
              [np.around(Axmax, 2), np.around(Aymax, 2), np.around(Azmax, 2)]]

#create table
the_table = plt.table(cellText=table_vals,
                      colWidths=[0.1] * 6,
                      rowLabels=row_labels,
                      colLabels=col_labels,
                      loc='center')
the_table.auto_set_font_size(False)
the_table.set_fontsize(12)
the_table.scale(6, 2)

#removes ticks and spines to get only a table
plt.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
plt.tick_params(axis='y', which='both', right=False, left=False, labelleft=False)
for pos in ['right','top','bottom','left']:
    plt.gca().spines[pos].set_visible(False)
plt.savefig(os.path.join(final_directory, 'Integrated Accelerometer Analysis.png'), bbox_inches='tight', pad_inches=0.05, dpi=50)

'''
These are tables with some
more advanced analysis
of the gyroscope data
'''

#add time data where slope changes of the gyroscope to table
plt.figure(10)
col_labels = ['Inflection Point Times (s)']
row_labels = ['Gx', 'Gy', 'Gz']
table_vals = [[np.around(Gx_time, 2)],
              [np.around(Gy_time, 2)],
              [np.around(Gz_time, 2)]]

#create table
the_table = plt.table(cellText=table_vals,
                      colWidths=[0.1] * 6,
                      rowLabels=row_labels,
                      colLabels=col_labels,
                      loc='center')
the_table.auto_set_font_size(False)
the_table.set_fontsize(11)
the_table.scale(18, 20)

#removes ticks and spines to get only a table
plt.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
plt.tick_params(axis='y', which='both', right=False, left=False, labelleft=False)
for pos in ['right','top','bottom','left']:
    plt.gca().spines[pos].set_visible(False)
plt.savefig(os.path.join(final_directory, 'Gyroscope Inflection Points.png'), bbox_inches='tight', pad_inches=0.05, dpi=50)

#add time of when button was pressed and number of inflection points to table
plt.figure(11)
col_labels = ['Button Press Time (s)', 'Number of Inflection Points']
row_labels = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'Total', 'Avg']
table_vals = [[np.around(btime1, 2), rot1],
              [np.around(btime2, 2), rot2],
              [np.around(btime3, 2), rot3],
              [np.around(btime4, 2), rot4],
              [np.around(btime5, 2), rot5],
              [np.around(btime6, 2), rot6],
              [np.around(btime7, 2), rot7],
              [np.around(btime8, 2), rot8],
              [np.around(btime9, 2), rot9],
              [np.around(btime10, 2), rot10],
              [np.around(timesum, 2), totalrot],
              [np.around(timemean, 2), np.around(avgrot, 2)]]

#create table
the_table = plt.table(cellText=table_vals,
                      colWidths=[0.1] * 6,
                      rowLabels=row_labels,
                      colLabels=col_labels,
                      loc='center')
the_table.auto_set_font_size(False)
the_table.set_fontsize(12)
the_table.scale(6, 2)

#removes ticks and spines to get only a table
plt.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
plt.tick_params(axis='y', which='both', right=False, left=False, labelleft=False)
for pos in ['right','top','bottom','left']:
    plt.gca().spines[pos].set_visible(False)
plt.savefig(os.path.join(final_directory, 'Button Press Times and Number of Inflection Points.png'), bbox_inches='tight', pad_inches=0.05, dpi=50)

'''
This is the table with
a rating system of the
collected data
'''

#add rating sytem to table
plt.figure(12)
col_labels = ['Rating', 'Total Score', 'Total Time (s)', 'Avg Inflection Points']
table_vals = [[0, 0, '>55', '>70'],
              [1, 1, '50 - 55', '63 - 70'],
              [2, 2, '45 - 50', '56 - 63'],
              [3, 3, '40 - 45', '49 - 56'],
              [4, 4, '35 - 40', '42 - 49'],
              [5, 5, '30 - 35', '35 - 42'],
              [6, 6, '25 - 30', '28 - 35'],
              [7, 7, '20 - 25', '21 - 28'],
              [8, 8, '15 - 20', '14 - 21'],
              [9, 9, '10 - 15', '7 - 14'],
              [10, 10, '0 - 10', '0 - 7']]

#create table
the_table = plt.table(cellText=table_vals,
                      colWidths=[0.1] * 6,
                      colLabels=col_labels,
                      loc='center')
the_table.auto_set_font_size(False)
the_table.set_fontsize(12)
the_table.scale(4, 2)

#removes ticks and spines to get only a table
plt.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)
plt.tick_params(axis='y', which='both', right=False, left=False, labelleft=False)
for pos in ['right','top','bottom','left']:
    plt.gca().spines[pos].set_visible(False)
plt.savefig(os.path.join(final_directory, 'Rating System.png'), bbox_inches='tight', pad_inches=0.05, dpi=50)

'''
This is the plot
comparing the processed
gyroscope data
'''

#processedGx plot
plt.figure(13)
plt.plot(t, procGx, label='processed gyrox')
Gx_slope = np.diff(procGx)/np.diff(t)
Gx_sign = np.where(np.diff(np.signbit(Gx_slope)))[0]
Gx_time = []
freq = []
pt = 5
hold = 5
for i in Gx_sign:
   if i >= pt:
      if (procGx[i+pt] - procGx[i+1]) > hold or (procGx[i+pt] - procGx[i+1]) < -hold or (procGx[i+1] - procGx[i-pt]) > hold or (procGx[i+1] - procGx[i-pt]) < -hold:
         plt.plot(t[i+1], procGx[i+1], '-o', color='black')
         Gx_timesign = t[i+1]
         Gx_time.append(Gx_timesign)
         freq.append(Gx_timesign)

#processedGy plot
plt.plot(t, procGy, label='processed gyroy')
Gy_slope = np.diff(procGy)/np.diff(t)
Gy_sign = np.where(np.diff(np.signbit(Gy_slope)))[0]
Gy_time = []
for i in Gy_sign:
   if i >= pt:
      if (procGy[i+pt] - procGy[i+1]) > hold or (procGy[i+pt] - procGy[i+1]) < -hold or (procGy[i+1] - procGy[i-pt]) > hold or (procGy[i+1] - procGy[i-pt]) < -hold:
         plt.plot(t[i+1], procGy[i+1], '-o', color='black')
         Gy_timesign = t[i+1]
         Gy_time.append(Gy_timesign)
         freq.append(Gy_timesign)

#processedGz plot
plt.plot(t, procGz, label='processed gyroz')
plt.xlabel('Time (s)')
plt.ylabel('Angular Position (Degrees)')
plt.title('Processed Gyroscope Data')
plt.legend()
Gz_slope = np.diff(procGz)/np.diff(t)
Gz_sign = np.where(np.diff(np.signbit(Gz_slope)))[0]
Gz_time = []
for i in Gz_sign:
   if i >= pt:
      if (procGz[i+pt] - procGz[i+1]) > hold or (procGz[i+pt] - procGz[i+1]) < -hold or (procGz[i+1] - procGz[i-pt]) > hold or (procGz[i+1] - procGz[i-pt]) < -hold:
         plt.plot(t[i+1], procGz[i+1], '-o', color='black')
         Gz_timesign = t[i+1]
         Gz_time.append(Gz_timesign)
         freq.append(Gz_timesign)
for i in buttonpress:
   plt.axvline(x=i, ls='--', color='k')
plt.savefig(os.path.join(final_directory, 'Processed Gyroscope Plot.png'), dpi=75)

'''
This is the pdf
report that is created
for analysis
'''

def report_template():
    file = open(final_directory+'/'+'PatientInfo.txt',"r")
    patientinfo = file.readlines()
    examinee = patientinfo[2].rstrip()
    age = patientinfo[4].rstrip()
    gender = patientinfo[6].rstrip()
    birth = patientinfo[8].rstrip()
    examiner = patientinfo[10].rstrip()
    date = datetime.today().strftime('%B %d, %Y').replace('X0', ' ')

    my_canvas = canvas.Canvas(os.path.join(final_directory, 'Report.pdf'),
                              pagesize=letter)

    width, height = letter
    # Create textobject
    textobject = my_canvas.beginText()

    #Set font for title, center title
    my_canvas.setFont("Times-Bold", 20)
    my_canvas.drawCentredString((width / 2), height - 70, "Smart Toy Diagnosis Report")

    # Set font face and size for patient info
    textobject.setFont('Times-Roman', 12)
    my_canvas.setFont("Times-Roman", 12)

    # Set text location for patient info
    textobject.setTextOrigin(70, height-100)

    # Write patient info
    textobject.textLine(text='EXAMINEE:')
    my_canvas.drawString(200, height-100, examinee)
    textobject.textLine(text='AGE:')
    my_canvas.drawString(200, height - 115, age)
    textobject.textLine(text='GENDER:')
    my_canvas.drawString(200, height - 130, gender)
    textobject.textLine(text='DATE OF BIRTH:')
    my_canvas.drawString(200, height - 145, birth)
    textobject.textLine()
    textobject.textLine(text='EXAMINER:')
    my_canvas.drawString(200, height - 170, examiner)
    textobject.textLine(text='REPORT DATE:')
    my_canvas.drawString(200, height - 185, date)


    # Title About the Smart Toy
    textobject.textLine()
    my_canvas.setFont("Times-Bold", 20)
    my_canvas.drawString(70, height - 230, "About the Smart Toy")

    # Set text location for  info
    textobject.setTextOrigin(70, height-260)
    textobject.setHorizScale(100)



    my_text = "Your child was just tested using the Smart Diagnostic Toy, Version 1." \
              "This device is a game in the form of a cube. Each face of the toy contains a triangle, circle, or " \
              "square along with an LED that lights up to different colors and a button that records user input. In " \
              "each 10 round game your child was prompted to press the button corresponding to a particular shape and " \
              "color combination. The accuracy and timing of your child's responses were recorded along with the motion " \
              "of the cube."

    wraped_text = "\n".join(wrap(my_text, 100))

    for line in wraped_text.splitlines(False):
        textobject.textLine(line.rstrip())

    # Title: What is Being Monitored
    textobject.textLine()
    my_canvas.setFont("Times-Bold", 20)
    my_canvas.drawString(70, height - 360, "What is Being Monitored")

    # Set text location for What is Being Monitored Section
    textobject.setTextOrigin(70, height-390)
    my_text2 = "The Smart Toy monitors a child's receptive communication skills, expressive communication skills, " \
               "and fine motor skills."
    wraped_text2 = "\n".join(wrap(my_text2, 100))
    for line in wraped_text2.splitlines(False):
        textobject.textLine(line.rstrip())

    textobject.textLine()

    my_text3 = "Receptive communication is the process of recognizing or understanding spoken words and directions. " \
               "The examiner verbally prompts the child to do a particular task (in this case to press the button " \
               "corresponding to a particular shape and color). The child is expected to understand the directions given " \
               "and show that understanding by completing the task."
    wraped_text3 = "\n".join(wrap(my_text3, 100))
    for line in wraped_text3.splitlines(False):
        textobject.textLine(line.rstrip())

    textobject.textLine()

    my_text4 = "Expressive communication is the process of sending a message across or making something happen. The act " \
               "of pressing any button on the cube or having any kind of response to the prompts is monitored."
    wraped_text4 = "\n".join(wrap(my_text4, 100))
    for line in wraped_text4.splitlines(False):
        textobject.textLine(line.rstrip())

    my_text5 = "Fine motor skills refer to the movement or coordination of smaller muscles such as hands and fingers. " \
               "The act of holding the cube, moving it around, and pressing its buttons are all activities that help " \
               "give an insight into the child's fine motor skills."
    wraped_text5 = "\n".join(wrap(my_text5, 100))
    for line in wraped_text5.splitlines(False):
        textobject.textLine(line.rstrip())

    # Title: What is Being Monitored
    textobject.textLine()
    my_canvas.setFont("Times-Bold", 20)
    my_canvas.drawString(70, height - 605, "Child's Results")

    # Write text to the canvas
    my_canvas.drawText(textobject)
    my_canvas.showPage()
    my_canvas.drawImage(final_directory+'/'+'Integrated Gyroscope Plot.png', 70, height/1.8)
    my_canvas.drawImage(final_directory+'/'+'Fourier Transform of Integrated Gyroscope Plot.png', 70, height/10)
    my_canvas.showPage()
    my_canvas.drawImage(final_directory+'/'+'Incorrect Answers Graph.png', 70, height/1.8)
    my_canvas.drawImage(final_directory+'/'+'Time Data Summary Graph.png', 70, height/10)
    my_canvas.showPage()
    my_canvas.drawImage(final_directory+'/'+'Color and Shape Time Data Graph.png', 70, height/1.8)
    my_canvas.drawImage(final_directory+'/'+'Game Data.png', 105, height/4)
    my_canvas.showPage()
    my_canvas.drawImage(final_directory+'/'+'Gyroscope Inflection Points.png', 90, height/8)
    my_canvas.showPage()
    my_canvas.drawImage(final_directory+'/'+'Button Press Times and Number of Inflection Points.png', width/4, height/1.5)
    my_canvas.drawImage(final_directory+'/'+'Integrated Gyroscope Analysis.png', 35, height/2.5)
    my_canvas.drawImage(final_directory+'/'+'Rating System.png', 105, height/8)
    my_canvas.save()
    file.close()

if __name__ == '__main__':
    report_template()
