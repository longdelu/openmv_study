#!/usr/bin/env python
# _*_ coding:utf-8 _*_

import os
import sys
sys.path.append("../../../drivers/dht/")

str=('python ../../../drivers/dht/dht.py')   #python命令 + B.py 
p=os.system(str)
print(p)                                    #打印执行结果 0表示 success ， 1表示 fail



#../../../drivers/dht/dht.py