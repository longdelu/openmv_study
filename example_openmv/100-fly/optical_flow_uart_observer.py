# Optical Flow Example
#
# Your OpenMV Cam can use optical flow to determine the displacement between
# two images. This allows your OpenMV Cam to track movement like how your laser
# mouse tracks movement. By tacking the difference between successive images
# you can determine instaneous displacement with your OpenMV Cam too!

import  pyb

import struct, math

uart = pyb.UART(3, 9600)

def CRC_CHECK(Buf = [],  CRC_CNT = 0):

    #print("crc_check buf and cnt", Buf, CRC_CNT)

    CRC_Temp = 0xffff

    for i in range(CRC_CNT):

        CRC_Temp ^= Buf[i]

        for j in range(8):

            if (CRC_Temp & 0x01):

                CRC_Temp = (CRC_Temp >> 1 ) ^ 0xa001
            else:
                CRC_Temp = CRC_Temp >> 1


    return(CRC_Temp)


def SDS_OutPut_Data(SDS_OutData = []):

    temp1   = [0, 0, 0, 0]
    databuf = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    CRC16   = 0;

    #print("SDS_OutData is ", SDS_OutData)

    for i in range(4):
        temp1[i] = int(SDS_OutData[i])

    #print ("temp1", temp1)

    for i in range(4):

        databuf[i * 2]     = (temp1[i] % 256)
        databuf[i * 2 + 1] = (temp1[i] // 256)


    CRC16 = CRC_CHECK(databuf,8)

    databuf[8] = CRC16 % 256

    databuf[9] = CRC16 // 256


    #print ("databuf", databuf)

    for i in range(10):

        temp = struct.pack("<B",
                           databuf[i])
        uart.write(temp)

        pass

def send_optical_flow_packet(x, y, sum_x, sum_y):

    SDS_OutData = [0.0, 0.0, 0.0, 0.0]

    SDS_OutData[0] = x
    SDS_OutData[1] = y
    SDS_OutData[2] = sum_x
    SDS_OutData[3] = sum_y

    SDS_OutPut_Data(SDS_OutData)

#while True:

     #send_optical_flow_packet(10, 20, 50, 100);


