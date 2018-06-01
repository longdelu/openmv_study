# 疯狂画线例子
#
# 这个例子展示了如何使用OpenMV内置的画线功能。
# 这个例子只是一个原始的测试，但是是一个很好的参考。
# 请把IDE设置为non-JPEG模式来观看最清晰的质量。

import pyb, sensor, image, math#引入例程所依赖的模块

sensor.reset()#openmv初始化
sensor.set_framesize(sensor.QVGA)#设置图像大小

while(True):

    #画一个点（更改某个像素的颜色）
    # Test Set Pixel
    sensor.set_pixformat(sensor.GRAYSCALE)#灰度图
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            #pyb.rng()返回一个随机数，％为取余运算，//为取模运算
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.set_pixel(x, y, 255)#设置(x,y)点的像素值为255，即白色，
            #灰度图颜色范围0～255
    sensor.set_pixformat(sensor.RGB565)#色彩图
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.set_pixel(x, y, (255, 255, 255))
            #设置(x,y)点的颜色为（255，255，255）白色，rgb色彩图的各通道分别
            #代表红绿蓝，值域0～255

    # Test Draw Line画直线
    sensor.set_pixformat(sensor.GRAYSCALE)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x0 = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y0 = (pyb.rng() % (2*img.height())) - (img.height()//2)
            x1 = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y1 = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.draw_line([x0, y0, x1, y1])
            #draw_line((x0, y0, x1, y1), color=White)，从(x0,y0)到(x1,y1)
            #画一条直线，注意[x0, y0, x1, y1]是一个元组，不要漏写括号［ ］或（）。
            #如果是灰度图，color值域为0-255；如果是rgb图，color也为一个元组 color=[255,255,255]，不要少写括号。color默认值为255或［255,255,255］白色。
    sensor.set_pixformat(sensor.RGB565)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x0 = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y0 = (pyb.rng() % (2*img.height())) - (img.height()//2)
            x1 = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y1 = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.draw_line([x0, y0, x1, y1])

    # Test Draw Rectangle画矩形
    sensor.set_pixformat(sensor.GRAYSCALE)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            w = (pyb.rng() % img.width())
            h = (pyb.rng() % img.height())
            img.draw_rectangle([x, y, w, h])
            #draw_rectangle((x,y,w,h), color=White)，以(x,y)为左上角顶点
            #画宽为w高为h的矩形，注意[x,y,w,h]是一个元组，不要漏写括号［ ］或者()。
            #如果是灰度图，color值域为0-255；如果是rgb图，color也为一个元组，#color=[255,255,255]，不要少写括号。color默认值为255或［255,255,255］白色。
    sensor.set_pixformat(sensor.RGB565)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            w = (pyb.rng() % img.width())
            h = (pyb.rng() % img.height())
            img.draw_rectangle([x, y, w, h])

    # Test Draw Circle画圆
    sensor.set_pixformat(sensor.GRAYSCALE)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            r = (pyb.rng() % (img.width() if (img.width() > img.height()) else img.height()))
            img.draw_circle(x, y, r)
            #draw_rectangle(x, y, radius, color=White)，以(x,y)为圆心
            #画半径为r的圆。如果是灰度图，color值域为0-255；如果是rgb图，
            #color也为一个元组，color=[255,255,255]，不要少写括号。color默认值为255或［255,255,255］白色。
    sensor.set_pixformat(sensor.RGB565)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            r = (pyb.rng() % (img.width() if (img.width() > img.height()) else img.height()))
            img.draw_circle(x, y, r)

    # Test Draw String在图像上打印文字
    sensor.set_pixformat(sensor.GRAYSCALE)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.draw_string(x, y, "Hello\nWorld!")
            #draw_string(x, y, text, color=White)，以(x,y)为起点在图像上
            #打印文字text，注意text是字符串格式，要用双引号括起来；\n表示换行，
            #\r表示回车；文字大小默认8x10。如果是灰度图，color值域为0-255；
            #如果是rgb图，color也为一个元组，color=[255,255,255]，不要少写括号。
            #color默认值为255或［255,255,255］白色。
    sensor.set_pixformat(sensor.RGB565)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.draw_string(x, y, "Hello\nWorld!")

    # Test Draw Cross
    sensor.set_pixformat(sensor.GRAYSCALE)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.draw_cross(x, y)
            #draw_cross(x, y, size=5, color=White)，以(x,y)为中心
            #画长度为size的十字形，size默认大小为5。如果是灰度图，color值域
            #为0-255；如果是rgb图，color也为一个元组，color=[255,255,255]，
            #不要少写括号。color默认值为255或［255,255,255］白色。
    sensor.set_pixformat(sensor.RGB565)
    for i in range(10):
        img = sensor.snapshot()
        for j in range(100):
            x = (pyb.rng() % (2*img.width())) - (img.width()//2)
            y = (pyb.rng() % (2*img.height())) - (img.height()//2)
            img.draw_cross(x, y)
