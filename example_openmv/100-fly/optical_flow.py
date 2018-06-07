# Optical Flow Example
#
# Your OpenMV Cam can use optical flow to determine the displacement between
# two images. This allows your OpenMV Cam to track movement like how your laser
# mouse tracks movement. By tacking the difference between successive images
# you can determine instaneous displacement with your OpenMV Cam too!

import sensor, image, time, math

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.B64X64) # or B40x30 or B64x64
clock = time.clock() # Tracks FPS.

# NOTE: The find_displacement function works by taking the 2D FFTs of the old
# and new images and compares them using phase correlation. Your OpenMV Cam
# only has enough memory to work on two 64x64 FFTs (or 128x32, 32x128, or etc).
old = sensor.snapshot()
sumx = 0
sumy = 0
while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # Take a picture and return the image.

    displacement_obj  = old.find_displacement(img) #获取前面一张图像与刚捕获的图像之间的偏移

    # 打印原始数据，查看diaplacement对象都有哪些属性
    #print(displacement_obj)

    delta_x = displacement_obj.x_translation()
    delta_y = displacement_obj.y_translation()
    response = displacement_obj.response()

    old = img.copy()

    sumx += delta_x
    sumy += delta_y

    print("%0.6fX   %0.6fY   %0.2fC   %0.2fFPS   %0.6fSUMX   %0.6fSUMY" % (delta_x, delta_y, response,  clock.fps(), sumx, sumy))

    if (not (math.isnan(delta_x) or math.isnan(delta_y) or math.isnan(response))):
        #optical_flow_uart_observer.send_optical_flow_packet(delta_x, delta_y, sumx, sumy)
        pass
