import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
try:
    from matplotlib.backends.backend_tkagg import NavigationToolbar2TkAgg
except ImportError:
    from matplotlib.backends.backend_tkagg import NavigationToolbar2Tk as NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style
from matplotlib.collections import LineCollection

import tkinter as tk
from tkinter import StringVar
from tkinter import ttk


LARGE_FONT= ("Verdana", 12)
style.use("ggplot")

#globals that allow tkinter to update
f = Figure(figsize=(10,5), dpi=100)
time_series_plot = f.add_subplot(111)
#heat_plot = f.add_subplot(112)

heat_text_1 = StringVar()
heat_text_2 = StringVar()
heat_text_3 = StringVar()
heat_text_4 = StringVar()
heat_text_5 = StringVar()
heat_text_6 = StringVar()
heat_text_7 = StringVar()
heat_text_8 = StringVar()
heat_text_9 = StringVar()
heat_text_10 = StringVar()
heat_text_11 = StringVar()

imu_x = StringVar()
imu_y = StringVar()
imu_z = StringVar()
baro_pressure = StringVar()
gps_lat = StringVar()
gps_long =  StringVar()
gps_alt = StringVar()

x_values = []
y_values = []


        

def animate(i, multiQueue):
    while not multiQueue.empty():
        new_value = multiQueue.get()
        
        x_values.append(new_value[0])
        y_values.append(new_value[1])
    

    time_series_plot.clear()
    time_series_plot.plot(x_values, y_values)

    #lines = ((0,1),(1,2),(2,2))
    #lc = LineCollection(lines)

    #heat_plot.clear()
    #heat_plot.colorbar(lines)
            

class TelemetryViewer(tk.Tk):

    def __init__(self, *args, **kwargs):
        
        tk.Tk.__init__(self, *args, **kwargs)

        #tk.Tk.iconbitmap(self, default="clienticon.ico")
        tk.Tk.wm_title(self, "Space Cowboys Telemetry Viewer")
        
        
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand = True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        for F in (StartPage,):

            frame = F(container, self)

            self.frames[F] = frame

            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(StartPage)

    def show_frame(self, cont):

        frame = self.frames[cont]
        frame.tkraise()

        
class StartPage(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        label = tk.Label(self, text="Viewer", font=LARGE_FONT)
        label.pack(pady=10,padx=10)

        canvas = FigureCanvasTkAgg(f, self)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True)

        toolbar = NavigationToolbar2TkAgg(canvas, self)
        toolbar.update()
        canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)