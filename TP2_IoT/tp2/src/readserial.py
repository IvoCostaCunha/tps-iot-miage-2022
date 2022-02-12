#Fichier readserial.py
import time
import serial

ser = serial.Serial(
 port='/dev/cu.usbserial-0001',
 baudrate = 9600,
 parity=serial.PARITY_NONE,
 stopbits=serial.STOPBITS_ONE,
 bytesize=serial.EIGHTBITS,
 timeout=1 #https://pythonhosted.org/pyserial/shortintro.html#readline
)

while True:
 try:
  x = ser.readline() # read a '\n' terminated line
  x = x.rstrip()
  try :
     x = x.decode("utf-8")
  except UnicodeError: 
    continue
  #x = x.decode("utf-8")
  
  print ("Valeur : {}".format(x))

 except KeyboardInterrupt:
  print('exiting')
  break
 
 #On ecrit 
 #ser.write('1') ;ser.flush()
 
# close serial
ser.flush()
ser.close()
    
