# -*- coding: utf-8 -*-


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import serial
import time



brain_exercise = 50 #Make sure the this number is equal the arduino's brain_exercise value.
angles_raw = []
result = []
servo1_list = []
servo2_list = []
hcsr04_list = []

ser=serial.Serial('COM6', 9600, timeout=1)
time.sleep(1)
print('Is port open?', ser.is_open)
time.sleep(10)


if ser.is_open == True:
     if ser.inWaiting() > 0 :
        
        for i in range(brain_exercise):
             time.sleep(5)
             arduino_data = ser.read(12)
             angles_raw.append(arduino_data)
             print('Data',i,'=',arduino_data)
             servo1 = int(angles_raw[i][0:3])
             servo2 = int(angles_raw[i][4:7])
             hcsr04  = int(angles_raw[i][8:11])
             servo1_list.append(servo1)
             servo2_list.append(servo2)
             hcsr04_list.append(hcsr04)
        
        servo1_df = pd.DataFrame(data = servo1_list, index = range(brain_exercise),columns = ['Servo-1'])
        servo2_df = pd.DataFrame(data = servo2_list, index = range(brain_exercise),columns = ['Servo-2'])
        hcsr04_df = pd.DataFrame(data = hcsr04_list, index = range(brain_exercise),columns = ['Distance'])
        all_data_df = pd.concat([servo1_df,servo2_df,hcsr04_df],axis=1)
        all_data_df = all_data_df.sort_values(by = 'Distance')
        all_data_df.to_csv('brain_data.csv', encoding='utf-8', index=False)





time.sleep(1)
ser.close()








