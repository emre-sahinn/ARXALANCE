# -*- coding: utf-8 -*-

#Libraries
import pandas as pd
import matplotlib.pyplot as plt
import time

#Data upload
arx_data = pd.read_csv('brain_data.csv')

#For Ignoring Missing Values
from sklearn.preprocessing import Imputer
imputer = Imputer(missing_values=0, strategy='mean', axis=0)


#Separating Servo Motors
x=arx_data.iloc[:,0:2]
y=arx_data.iloc[:,2:3]

#Distance which we want
distance = 9

#DataFrame To Integer Conversion
X=x.values
Y=y.values

imputer=imputer.fit(Y[:,0:]) #Applying Imputer
Y[:,0:] = imputer.transform(Y[:,0:])


from sklearn.cross_validation import train_test_split
x_train,x_test,y_train,y_test = train_test_split(y,x,test_size=1,random_state=1)#If you know better way to do this please tell me :)

x_test = pd.DataFrame(data = [distance], index = range(1),columns = ['Distance'])


#Linear Regression
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(x_train,y_train)
y_pred=regressor.predict(x_test)


#Polynomial Regression
from sklearn.preprocessing import PolynomialFeatures
poly_reg=PolynomialFeatures(degree=8)
x_poly=poly_reg.fit_transform(x_train)
lin_reg=LinearRegression()
lin_reg.fit(x_poly,y_train)
y_pred = lin_reg.predict(poly_reg.fit_transform(distance)) #Ideal height for standing

'''
#KNN 	algorithm for who wants to try KNN
from sklearn.neighbors import KNeighborsClassifier
neigh = KNeighborsClassifier(n_neighbors=10,metric="minkowski")#
neigh.fit(X_train, y_train)#Ölçme birimi ise minkowski metodu
y_pred=neigh.predict(X_test)
'''

#Preparing data for aduino motors
ardu_data1_int = int(round(y_pred[0][1]))
ardu_data2_int = int(round(y_pred[0][0]))
ardu_data1 = chr(ardu_data1_int).encode()
ardu_data2 = chr(ardu_data2_int).encode()


#Sending data to arduino
import serial
ser=serial.Serial('COM6', 9600, timeout=1)
time.sleep(1)
print('Is port open?', ser.is_open)
time.sleep(2)
zero = 0
sent_text = ''
if ser.is_open == True:
    
    for i in range(1): 
        #Data-1
        if (ardu_data1_int % 10) != ardu_data1_int:
            if (ardu_data1_int % 100) != ardu_data1_int:
                ser.write(str(ardu_data1_int).encode())
            else:
                zero = 1
        else : 
            zero = 2
            
        if (ardu_data1_int < 100):
            if (zero == 2):
                sent_text = '00'
            elif (zero == 1):
                sent_text = '0'
                ser.write(str(sent_text + str(ardu_data1_int)).encode())
        
        time.sleep(1)
        print("/"*20)  
        sent_text = ''
        
        #Data-2
        if (ardu_data2_int % 10) != ardu_data2_int:
            if (ardu_data2_int % 100) != ardu_data2_int:
                ser.write(str(ardu_data2_int).encode())
            else:
                zero = 1
        else : 
            zero = 2
        
        if (ardu_data2_int < 100):
            if (zero == 2):
                sent_text = '00'
            elif (zero == 1):
                sent_text = '0'
                ser.write(str(sent_text + str(ardu_data2_int)).encode())
        time.sleep(3)

for i in range(10):
    print(ser.readline())
ser.close()


