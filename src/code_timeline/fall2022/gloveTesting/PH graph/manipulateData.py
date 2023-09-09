import matplotlib.pyplot as plt


# with open('Arduino_Outputs') as f:
#     lines = f.readlines()
def analyze_data(data):
    keyPressed = []
    for i in range(len(data)):
        keyPressed.append(analyze_value(data[i]) * 100)
    return keyPressed

def analyze_value(value):
    return value > 80
    
def analyze_last_20(data):
    last_20 = data[-20:]
    return analyze_data(last_20)

# Make a graph using the values
def make_graph(fingerArray, fig, lineArray):
    #timelist = range(0, len(converted_readings))
    # timelist = [time/3 for time in timelist]
    #keyPressed = analyze_data(converted_readings)
    #line2.set_ydata(keyPressed)
    plt.legend(loc="lower left")
    plt.xlabel("Time")
    plt.ylabel("Finger values")
    for i in range(len(fingerArray)):
        lineArray[i].set_ydata(fingerArray[i][-20:])
    fig.canvas.flush_events()
    fig.canvas.draw()
    # plt.plot(timelist, converted_readings)
    # #Graph of converted values vs. time
    # converted_readings = converted_readings[-20:]
    # timelist = timelist[-20:]
    # ax.clear()
    # ax.plot(converted_readings,timelist)
    
    # plt.xlabel("time")
    # plt.ylabel("converted values")
    # plt.title('time vs. converted values')
    # # plt.legend()
    # #plt.legend(["Finger 1","Finger 2","Finger 3","Finger 4","Finger 5",])
    # plt.show()