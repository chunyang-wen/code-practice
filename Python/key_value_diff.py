#!/bin/env python

# calculate values diff according to key
# only calculate two adjacent values
# if key_odd and key_even not equal, key_odd
# is abondoned.

import sys
import os
import re

IS_DEBUG=False

class Config:
    def __init__(self,file):

######### CONFIGS ###############
# eg
# VALUE_KEY = [1,3,5]
# VALUE_ITEMS = [2,6]

        #self.VALUE_KEY = [0,1]
        #self.VALUE_ITEMS = [3,4,5,6]

        self.VALUE_KEY = []
        self.VALUE_ITEMS = []
        self.read_config(file)

    def read_config(self,file):
        # multiline
        with open(file) as fd:
            ln = 0
            for line in fd:
                if line.startswith("#"):
                    continue
                if line.startswith("$$"):
                    # $$ marks the end
                    break
                nums = line.split(' ')
                for num in nums:
                    num = int(num)
                    if 0 == ln:
                        self.VALUE_KEY.append(num)
                    elif 1 == ln:
                        self.VALUE_ITEMS.append(num)
                ln += 1

######### CONFIGS ###############

def print_key_value(dict):

    for key,value in dict.iteritems():
        line_str = ""
        line_str += (key + '\t')
        n = len(value)

        for i in xrange(n):
            if IS_DEBUG:
                print "value %d is %s" %(i,str(value[i]))

            single_value = str(value[i]) + '\t'
            line_str += single_value

        line_str = line_str.rstrip()
        print line_str


def calculate_diff_key_value(dict1, dict2, prec = 3):
    # only one item
    diff_dict = {}
    DIFF_KEY = "DIFF"

    for key,value_odd in dict1.iteritems():

        n = len(value_odd)
        diff_dict[DIFF_KEY] = [0 for i in xrange(n)]

        value_even = dict2[key]
        for i in xrange(n):
            odd = float(value_odd[i])
            even = float(value_even[i])
            if IS_DEBUG:
                print "ODD: %f EVEN : %f" %(odd,even)
            if odd != 0:
                diff_dict[DIFF_KEY][i] = \
                        "{:.{n}f}%".format((even-odd)*1.0/odd*100, n=prec)

    if IS_DEBUG:
        print "calcluting diff"
    return diff_dict


def diff_key_value(config):

    reserve_key_odd= False
    value_items= len(config.VALUE_ITEMS)
    while True:
        if not reserve_key_odd:
            key_value_odd = {}
            line_odd = sys.stdin.readline()
            if line_odd == "":
                # empty
                return
        
            items = line_odd[:-1].split('\t')
            n = len(items)

            key_odd =""
            for i in config.VALUE_KEY:
                key_odd += items[i]
                key_odd += '\t'
            key_odd = key_odd.rstrip()
            key_value_odd[key_odd] = [0 for i in xrange(n)]

            for i in xrange(value_items):
                # correct misses
                if config.VALUE_ITEMS[i] >= n:
                    continue
                m = re.search(r"[+-]?(\d+)(\.\d+)*",items[config.VALUE_ITEMS[i]])
                if m:
                    key_value_odd[key_odd][i] = float(m.group(0))

        # output key values
        #print_key_value(key_value_odd)
        print line_odd[:-1]
        reserve_key_odd = False

        key_value_even = {}
        line_even = sys.stdin.readline()
        if line_even == "":
            return
        items = line_even[:-1].split('\t')
        n = len(items)
        key_even =""
        for i in config.VALUE_KEY:
            key_even += items[i]
            key_even += '\t'
        key_even = key_even.rstrip()
        key_value_even[key_even] = [0 for i in xrange(n)]

        if IS_DEBUG:
            print "key_odd: %s key_even : %s" %(key_odd,key_even)

        if cmp(key_even, key_odd) != 0:
            # key_even not equal key_odd
            reserve_key_odd = True
        else:
            reserve_key_odd = False

        for i in xrange(value_items):
            # correct misses
            if config.VALUE_ITEMS[i] >= n:
                continue
            key_value_even[key_even][i] = float(items[config.VALUE_ITEMS[i]])

        if reserve_key_odd:
            key_value_odd = key_value_even
            key_odd = key_even.rstrip()
            line_odd = line_even
            if IS_DEBUG:
                print "RESEVE even key_odd changeTo:%s" %(key_odd)
            continue
        else:
            #print_key_value(key_value_even)
            print line_even[:-1]

        diff_dict = calculate_diff_key_value(key_value_odd, key_value_even)
        print_key_value(diff_dict)



def main():

    file = ""
    if len(sys.argv) < 3:
        print "CRAP, RTFS"
        return
    if sys.argv[1] == '-f':
        file = sys.argv[2]
    else:
        print "We know nothing about input args"
        return
    config = Config(file)
    diff_key_value(config)

if __name__ == '__main__':
    main()

