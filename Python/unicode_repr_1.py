#!bin/env python
#-*-coding=utf-8-*-

import sys

for line in sys.stdin:
    line = line[:-1]
    print repr(line.decode('gbk')).replace("u\'","").replace("\'","")
