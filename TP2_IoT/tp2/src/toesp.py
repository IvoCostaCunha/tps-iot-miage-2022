import sys, serial
import numpy as np
import json
from time import sleep
from collections import deque
from matplotlib import pyplot as plt

esp = serial.Serial(port='/dev/cu.usbserial-0001', baudrate=9600, timeout=.1)

def write_read(x):
    esp.write(bytes(x, 'utf-8'))

while True:
    print("G for green led / R for red led \n")
    c = input() # Taking input from user
    value = write_read(c)