# MAVLink OpticalFlow Script.
#
# This script sends out OpticalFlow detections using the MAVLink protocol to
# an LIGHT/PixHawk UAV controller for position control using your OpenMV Cam.
#
# P4 = TXD 115200,8,N,1


import sensor, image, time, pyb, struct, math

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.B64x64) # or B40x30 or B64x64
clock = time.clock() # Tracks FPS.

old = sensor.snapshot()

uart = pyb.UART(3, 115200, timeout_char = 1000)

def send_optical_flow_packet(x, y, c):
    temp = struct.pack("<bbiii",
                       0xAA,
                       0xAE,
                       int(x * 100000 ), # up sample by 4
                       int(y * 100000 ), # up sample by 4
                       int(c * 100000))
    uart.write(temp)


while(True):
    clock.tick() #
    img = sensor.snapshot() # 获取一帧图像
    '''
    find_displacement 这个功能函数使用是是2D FFT算法获得新旧两张图像的相位移动，由于OPenMV上单片机内存的问题，只能计算
    64x64或者64*32的图片（openmv2），如果使用OPenMV3可以计算128*32或者32*128的图片
    '''
    [delta_x, delta_y, response] = old.find_displacement(img) #获取前面一张图像与刚捕获的图像之间的偏移
    old = img.copy()
    print("%0.6fX   %0.6fY   %0.2fC   %0.2fFPS" % (delta_x, delta_y, response, clock.fps()))
    if (not (math.isnan(delta_x) or math.isnan(delta_y) or math.isnan(response))):
        send_optical_flow_packet(delta_x, delta_y, response)
