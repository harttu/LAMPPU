#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
port = '/dev/rfcomm0'


ard = serial.Serial(port,9600,timeout=5)

i = 0


ard.write("#1X001000001000001");
#time.sleep(2);
#ard.write("#1R000000000000255");
#time.sleep(2);
ard.write("#1G000000050000255");
time.sleep(2);
#ard.write("#1G000000000000255");
#time.sleep(2);
#ard.write("#1G000000000000255");
#ard.write("#1R0000000000000000");
exit()

for i in range(1,255):
	ard.write("#1"+str(i))
	time.sleep(0.05)
exit()
