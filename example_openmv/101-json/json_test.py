#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re
import sys
import shutil
import subprocess
import json

obj = [[12,0],[10,12],[22,10],[99,11]]
print(json.dumps(obj))

obj = {
    "number":10,
    "color" :[255,0,0],
    "rate" :0.65
}

#打印生成的json字符串
print(json.dumps(obj))

#打印解析json后的字符串
print(json.loads(json.dumps(obj)))


 