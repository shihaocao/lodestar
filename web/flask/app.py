from flask import Flask
import threading
import time
import serial

POOL_TIME = 1
altitude = 0

dataLock = threading.Lock()
threadHandler = threading.Thread()

telem = serial.Serial('dev/ttyUSB0')

def interrupt():
    global threadHandler
    threadHandler.cancel()

def doStuff():
    global altitude
    global threadHandler
    with dataLock:
    # Do your stuff with commonDataStruct Here
        altitude += 1
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

@app.route('/altitude')
def get_altitude():
    global dataLock, altitude
    with dataLock:
        return {'altitude': altitude}