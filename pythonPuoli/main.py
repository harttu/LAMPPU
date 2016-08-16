#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
port = '/dev/rfcomm0'


ard = serial.Serial(port,9600,timeout=5)

i = 0

for i in range(1,255):
	ard.write("#1"+str(i))
	time.sleep(0.05)
exit()
