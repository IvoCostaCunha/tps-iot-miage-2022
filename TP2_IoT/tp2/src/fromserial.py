"""
Graph from ESP32 Serial link
Run photoresitor sketch in same time !

Author : G.MENEZ

"""
import sys, serial
import numpy as np
import json
from time import sleep
from collections import deque
from matplotlib import pyplot as plt
import drawnow

#=============================================

class AnalogData:
    
    def __init__(self, maxLen=100):
        """ Ring Buffer de maxLen samples """        
        self.x = []
        self.y = []
        self.maxLen = maxLen

    def add(self, x, y):
        """ Add a sample in the  ring buffer """
        if len(self.x) == self.maxLen:
            self.x.pop(0)
            self.y.pop(0)
                        
        self.x.append(x)
        self.y.append(y)
    
#=============================================

class AnalogPlot:
    """ Plotting Figure """
    def __init__(self, analogData):
        plt.ion()                 # set plot to "animated"
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        self.axline, = self.ax.plot(analogData.x, analogData.y,
                                    'r.-', label="light")

        plt.xlabel('# mesure')
        plt.ylabel('lm value')
        #plt.xlim([0, 100])
        #plt.ylim([0, 4000])
        self.decoration("Photo-sensor mesures")
        
    def updateplot(self, analogData):
        """  update plot """
        self.axline.set_xdata(analogData.x)
        self.axline.set_ydata(analogData.y)

        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
        #        self.ax.autoscale()
        self.ax.relim()            # reset intern limits of the current axes
        self.ax.autoscale_view()   # reset axes limits 
    
    def decoration(self, title):
        plt.title(title)
        plt.grid(True)
        plt.legend()

#----------------  Main function -----------------

def main():
    # Ring buffer of last samples 
    analogData = AnalogData()
    # plotting canvas
    analogPlot = AnalogPlot(analogData)    
    
    # open serial port
    ser = serial.Serial(
        port='/dev/cu.usbserial-0001',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

    counter=0
    readingJson = False;

    string_json = ""
    temp = ""
    light = ""
    data = []

    while True:
        try:
            # Read 
            v = ser.readline()
            v = v.rstrip()
            try :
                v = v.decode("utf-8")
            except UnicodeError: 
                continue
            #v = v.decode("utf-8")
            # A partie de la problematique
            #v = int(v)
            #print ("Valeur : {}".format(v))

            if v == "{":
                readingJson = True
                
            if readingJson:
                string_json = string_json + v

            if v == "}":
                readingJson = False
                #print(string_json)
                json_data = json.loads(string_json)
                
                remove_chars = ['C','l','m']

                temp_str = str(json_data["temperature"])
                light_str = str(json_data["light"])

                f=filter(lambda i: i not in remove_chars,temp_str) 
                for i in f: 
                    temp+=i 

                f=filter(lambda i: i not in remove_chars,light_str) 
                for i in f: 
                    light+=i 

                temp_f = float(temp)
                light_i = int(light)
                print(temp_f, light_i)

                # reset string_json since one object is complete
                string_json = ""
                temp = "";
                light = "";


                print("\n")

                # Plot
                analogData.add(counter, light_i)
                analogPlot.updateplot(analogData)
                print('plotting new data...')
                counter += 1
                            
        except KeyboardInterrupt:
            print('exiting')
            break
    
    # close serial
    ser.flush()
    ser.close()
    
#------------------ call main -----------------------

if __name__ == '__main__':
    main()
