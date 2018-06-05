# Optical Flow Example
#
# Your OpenMV Cam can use optical flow to determine the displacement between
# two images. This allows your OpenMV Cam to track movement like how your laser
# mouse tracks movement. By tacking the difference between successive images
# you can determine instaneous displacement with your OpenMV Cam too!

import sensor, image, time
from pyb import UART
from pyb import LED


sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.B64x64) # or B40x30 or B64x64
clock = time.clock() # Tracks FPS.

red_led   = LED(1)
green_led = LED(2)
blue_led  = LED(3)
ir_led    = LED(4)

def led_control(x):
    if   (x&1)==0: red_led.off()
    elif (x&1)==1: red_led.on()
    if   (x&2)==0: green_led.off()
    elif (x&2)==2: green_led.on()
    if   (x&4)==0: blue_led.off()
    elif (x&4)==4: blue_led.on()
    if   (x&8)==0: ir_led.off()
    elif (x&8)==8: ir_led.on()

# NOTE: The find_displacement function works by taking the 2D FFTs of the old
# and new images and compares them using phase correlation. Your OpenMV Cam
# only has enough memory to work on two 64x64 FFTs (or 128x32, 32x128, or etc).
old = sensor.snapshot()
uart = UART(3, 921600)
sumx = 0.0
sumy = 0.0

while(True):
    for i in range(16):
        led_control(i)

        clock.tick() # Track elapsed milliseconds between snapshots().
        img = sensor.snapshot() # Take a picture and return the image.

        [delta_x, delta_y, response] = old.find_displacement(img)

        old = img.copy()

        sumx += delta_x
        sumy += delta_y
        uart.write("X = %2.3f   Y = %2.3f   \r\n" % (sumx, sumy))

        time.sleep(28)
