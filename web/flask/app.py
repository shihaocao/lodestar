from flask import Flask
from flask import jsonify
import threading
import time
import serial

POOL_TIME = 0.001
altitude = 0
incr = 0
ccno = 0
dataLock = threading.Lock()
threadHandler = threading.Thread()

telem = serial.Serial('/dev/ttyACM0')

def str_to_val(field):
    '''
    Automatically detects floats, ints and bools

    Returns a float, int or bool
    '''
    if 'nan' in field:
        return float("NAN")
    elif '.' in field:
        return float(field)
    elif field == 'true':
        return True
    elif field == 'false':
        return False
    else:
        return int(field)

def listgen(input_string):
    ret = input_string.split(",")
    ret = [x for x in ret if x != '']
    ret = [str_to_val(x) for x in ret]
    return ret


def interrupt():
    global threadHandler
    threadHandler.cancel()

def doStuff():
    global altitude
    global threadHandler
    global incr
    global ccno
    with dataLock:
    # Do your stuff with commonDataStruct Here
        telem_data = listgen(telem.readline().strip().decode("utf-8"))
        # print(telem_data)
        ccno = telem_data[0]
        # print(ccno)
        altitude = telem_data[1]
        incr += 1
    # Set the next thread to happen
    threadHandler = threading.Timer(POOL_TIME, doStuff, ())
    threadHandler.start()   

def doStuffStart():
    # Do initialisation stuff here
    global threadHandler
    # Create your thread
    threadHandler = threading.Timer(POOL_TIME, doStuff, ())
    threadHandler.start()

doStuffStart()

app = Flask(__name__)

@app.route('/query', methods = ['POST'])
def get_query_from_react():
    return "Flask Server Yeet."

@app.route('/time')
def get_current_time():
    return {'time': time.time()}

@app.route('/ccno')
def get_ccno():
    global ccno
    with dataLock:
        return {'ccno': ccno}

@app.route('/altitude')
def get_altitude():
    global dataLock, altitude, incr
    with dataLock:
        return {'altitude': altitude}

@app.route('/altitudes')
def get_altitudes():
    global dataLock, altitude, ccno
    with dataLock:
        return jsonify(cc=ccno,alt = altitude)