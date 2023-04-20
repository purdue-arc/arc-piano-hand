from flask import Flask, render_template,request, redirect, url_for
import serial
ser = serial.Serial('COM4', 9800, timeout=1)
app = Flask(__name__)
# we are able to make 2 different requests on our webpage
# GET = we just type in the url
# POST = some sort of form submission like a button
@app.route('/', methods = ['POST','GET'])
def hello_world():
    # variables for template page (templates/index.html)
    # if we make a post request on the webpage aka press button then do stuff
    if request.method == 'POST':
        if request.form['submit'] == 'Press Finger 1':
            speed = request.form['speedSlider']
            delay = request.form['delaySlider']
            print('Finger 1 pressed with speed {} and delay {}'.format(speed, delay))
            reversed = 1 if 'reversed' in request.form else 0
            ser.write(bytes("{},0,{},{}".format(speed,str(int(delay) * 1000),reversed), 'utf-8'))
        elif request.form['submit'] == 'Press Finger 2':
            speed = request.form['speedSlider']
            delay = request.form['delaySlider']
            reversed = 1 if 'reversed' in request.form else 0
            print('Finger 2 pressed with speed {} and delay {}'.format(speed, delay))
            ser.write(bytes("{},1,{},{}".format(speed,str(int(delay) * 1000),reversed), 'utf-8'))
        elif request.form['submit'] == 'Press Finger 3':
            speed = request.form['speedSlider']
            delay = request.form['delaySlider']
            reversed = 1 if 'reversed' in request.form else 0
            print('Finger 3 pressed with speed {} and delay {}'.format(speed, delay))
            ser.write(bytes("{},2,{},{}".format(speed,str(int(delay) * 1000),reversed), 'utf-8'))

    # the default page to display will be our template with our template variables
    return render_template('index.html')
if __name__ == "__main__":
    # lets launch our webpage!
    # do 0.0.0.0 so that we can log into this webpage
    # using another computer on the same network later
    app.run(host='0.0.0.0')

