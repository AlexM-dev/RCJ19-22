import sensor, image, math, pyb
from pyb import UART
uart = UART(3, 115200, timeout_char=1)
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1)
led = pyb.LED(3)
def dot(x, y, color=(255, 0, 0), sz = 5):
    x -= sz / 2
    y -= sz / 2
    for i in range(sz * sz):
        img.set_pixel(int(x) + (i % sz) - 1, int(y) + int(i / sz) - 1, color)
thresholds = [(48, 83, -7, 17, 11, 127),
              (31, 41, -8, 23, -56, -31)]
cX = 165
cY = 90
yX = 0
yY = 0
bX = 0
bY = 0
SMax=0
yAngle = 0
yDist = 0
bAngle = 0
bDist = 0
EXPOSURE_TIME_SCALE = 0
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(True)
#sensor.set_auto_exposure(True)
sensor.set_auto_whitebal(True)
sensor.set_auto_gain(False)
#sensor.set_auto_exposure(False)
sensor.skip_frames(100)
while(True):
    img = sensor.snapshot()
    yS=0
    bS=0
    ySMax=0
    bSMax=0
    #led.on()
    yAngle=0
    yDist=0
    bAngle=0
    bDist=0
    for blob in img.find_blobs(thresholds, pixels_threshold=20, area_threshold=20, merge=True):
        if blob.code() == 1:
            img.draw_rectangle(blob.rect(), color=(255,255,0), fill=1)
            yS=blob.w()*blob.h()
            if yS > ySMax:
                ySMax=yS
                yY = cY - blob.y() - blob.h() / 2
                yX = cX - blob.x() - blob.w() / 2
        if blob.code() == 2:
            img.draw_rectangle(blob.rect(), color=(50,50,255), fill=1)
            bS=blob.w()*blob.h()
            if bS > bSMax:
                bSMax=bS
                bY = cY - blob.y() - blob.h() / 2
                bX = cX - blob.x() - blob.w() / 2
    dot(cX, cY, color = (0,255,0), sz = 10)
    dot(cX - yX, cY - yY)
    dot(cX - bX, cY - bY)
    yAngle = int(math.atan2(yX, yY) / 3.14 * 180)
    yDist = int(math.sqrt(yX*yX + yY*yY))
    bAngle = int(math.atan2(bX, bY) / 3.14 * 180)
    bDist = int(math.sqrt(bX*bX + bY*bY))
    if yAngle < 0:
      yAngle = int(yAngle + 360)
    if bAngle < 0:
      bAngle = int(bAngle + 360)
    if yAngle < 0:
       yAngle = 0
    if bAngle < 0:
       bAngle = 0
    if yDist < 0:
       yDist = 0
    if bDist < 0:
       bDist = 0
    try:
        uart.write("*")
        if(yAngle < 10):
            uart.write(str(0))
            uart.write(str(0))
            uart.write(str(yAngle))
        elif(yAngle < 100):
            uart.write(str(0))
            uart.write(str(yAngle))
        else:
            uart.write(str(yAngle))
        if(yDist < 10):
            uart.write(str(0))
            uart.write(str(0))
            uart.write(str(yDist))
        elif(yDist < 100):
            uart.write(str(0))
            uart.write(str(yDist))
        else:
            uart.write(str(yDist))
        if(bAngle < 10):
            uart.write(str(0))
            uart.write(str(0))
            uart.write(str(bAngle))
        elif(bAngle < 100):
            uart.write(str(0))
            uart.write(str(bAngle))
        else:
            uart.write(str(bAngle))
        if(bDist < 10):
            uart.write(str(0))
            uart.write(str(0))
            uart.write(str(bDist))
        elif(bDist < 100):
            uart.write(str(0))
            uart.write(str(bDist))
        else:
            uart.write(str(bDist))
    except: pass
