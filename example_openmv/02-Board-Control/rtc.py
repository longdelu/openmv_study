# RTC Example
#
# This example shows how to use the RTC.
import time
from pyb import RTC

rtc = RTC()
rtc.datetime((2018, 5, 28, 2, 0, 0, 0, 0))

while (True):
    print(rtc.datetime())
    time.sleep(1000)
