import sys, serial
import numpy as np
import json
from time import sleep
from collections import deque
from matplotlib import pyplot as plt

esp = serial.Serial(port='/dev/cu.usbserial-0001', baudrate=9600, timeout=.1)
j = '{"cmd" : "undefined"}'
json_j = json.loads(j)

def writetoESP(x):
    esp.write(bytes(x, 'utf-8'))

while True:
    print("start / stop")
    i = input() # Taking input from user
    if i == "start" :
        json_j["cmd"] = "start"
    elif i == "stop" :
        json_j["cmd"] = "stop"

    writetoESP(str(json_j))