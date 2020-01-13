import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

import serial

telem = serial.Serial('COM3')

timecnt = 100
totallen = 100
xar = [x for x in range(totallen)]
alt = [5 for x in range(totallen)]



def listgen(input_string):
    ret = input_string.split(",")
    return ret

# while(len(alt)!=10):
#     xar += [timecnt]
#     alt += [listgen(telem.readline().strip().decode("utf-8"))[0]]
#     timecnt += 1

def animate(i):
    # pullData = open("sampleText.txt","r").read()
    # dataArray = pullData.split('\n')
    # xar = []
    # yar = []
    # for eachLine in dataArray:
    #     if len(eachLine)>1:
    #         x,y = eachLine.split(',')
    #         xar.append(int(x))
    #         yar.append(int(y))
    global timecnt, alt, xar

    xar = xar[1:] + [timecnt]
    timecnt += 1

    alt = alt[1:] + [listgen(telem.readline().strip().decode("utf-8"))[0]]

    ax1.clear()
    ax1.plot(xar,alt)
    
plt.ylim(-41,-40)
fig = plt.figure()

ax1 = fig.add_subplot(1,1,1)


ani = animation.FuncAnimation(fig, animate, interval=100)
plt.show()
