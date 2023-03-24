import time

def handleData(running, multiQueue, startTime):
    a = 1
    while (running.value):
        multiQueue.put([time.time()-startTime, a])
        a *= -1.005
        time.sleep(.001)