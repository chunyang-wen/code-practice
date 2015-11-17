#!/bin/env python
#-*- coding:utf-8 -*-

import sys
import os
reload(sys)
sys.setdefaultencoding( "utf-8" )

prefix = '0000'

for line in sys.stdin:
    line = line[:-1]
    uline = ""
    for c in line:
        uchr = str(hex(ord(c))).replace('0x','')
        if len(uchr) < 4:
            uchr = prefix[0:4-len(uchr)] + uchr
        uline = uline + '\\u' + uchr
    print uline
