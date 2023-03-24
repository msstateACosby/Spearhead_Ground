from multiprocessing import Process, Queue, Value
import viewer
import data_handler

import time



if __name__ == '__main__':
    multiQueue = Queue()
    running = Value('i', 1)
    startTime = time.time()
    p = Process(target=data_handler.handleData, args=(running, multiQueue, startTime))
    p.start()
    app = viewer.TelemetryViewer()
    ani = viewer.animation.FuncAnimation(viewer.f, viewer.animate, fargs = (multiQueue,), interval=1000)
    app.mainloop()
    
    running.value = 0