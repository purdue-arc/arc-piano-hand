def make_graph(fig,line1,data):
    line1.set_ydata(data)
    line1.set_xdata(range(len(data)))
    fig.canvas.draw()
    fig.canvas.flush_events()