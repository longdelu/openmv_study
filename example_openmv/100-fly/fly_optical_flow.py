# MAVLink OpticalFlow Script.
#
# This script sends out OpticalFlow detections using the MAVLink protocol to
# an LIGHT/PixHawk UAV controller for position control using your OpenMV Cam.
#
# P4 = TXD 115200,8,N,1


import sensor, image, time, pyb, struct, math

import optical_flow_uart_observer

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.B64X64) # or B40x30 or B64x64
clock = time.clock() # Tracks FPS.

old = sensor.snapshot()

sumx = 0.0
sumy = 0.0


def filter(buf, total_size, win_size):

    if win_size > total_size:
       return -1

    index = []

    ave = 0

    sum = 0

    offest = (total_size - win_size) // 2

    i = 0
    for i in range((total_size - win_size)):

        index.append(offest + i)

    i = 0
    for i in index:

       sum += buf[i]

    ave = sum / (total_size - win_size)

    return ave

while(True):

    delta_x  = []
    delta_y  = []

    response = []

    delta_x_ave  = 0
    delta_y_ave  = 0
    response_ave = 0

    clock.tick() #
    i = 0;
    for i in range(10):

        img = sensor.snapshot() # 获取一帧图像

        '''
        find_displacement 这个功能函数使用是是2D FFT算法获得新旧两张图像的相位移动，由于OPenMV上单片机内存的问题，只能计算
        64x64或者64*32的图片（openmv2），如果使用OPenMV3可以计算128*32或者32*128的图片
        '''
        displacement_obj  = old.find_displacement(img) #获取前面一张图像与刚捕获的图像之间的偏移

        # 打印原始数据，查看diaplacement对象都有哪些属性
        #print(displacement_obj)

        if (not (math.isnan(displacement_obj.x_translation()) or math.isnan(displacement_obj.y_translation()) or math.isnan(displacement_obj.response()))):

           delta_x.append(displacement_obj.x_translation())
           delta_y.append(displacement_obj.y_translation())
           response.append(displacement_obj.response())

        old = img.copy()


    delta_x_ave  = filter(delta_x, 10, 6)
    delta_y_ave  = filter(delta_y, 10, 6)
    response_ave = filter(response, 10, 6)

    sumx += delta_x_ave
    sumy += delta_y_ave

    print("%0.6fX   %0.6fY   %0.2fC   %0.2fFPS   %0.6fSUMX   %0.6fSUMY" % (delta_x_ave, delta_x_ave, response_ave,  clock.fps(), sumx, sumy))

    optical_flow_uart_observer.send_optical_flow_packet(10, 20, 50, 100)



