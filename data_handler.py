import time
import serial
def handleData(running, multiQueue, startTime):
    a = 1
    ser = serial.Serial('COM3', 19200, timeout=1)
    while (running.value):
        
        while ser.in_waiting:
            
            #print(ser.readline().decode())
            vars = [0 for x in range(24)]
            try:
                vars = list(map(float, ser.readline().decode().split()))
            except ValueError:
                pass
            if len(vars) != 24:
                print("fooey")
                vars = [0 for x in range(24)]
            multiQueue.put([time.time()-startTime] + vars)