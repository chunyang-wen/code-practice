#!/bin/env python

# sum values according to key

import sys
import os

IS_DEBUG=False

key_value_dict = {}
value_total = {}

class Config:
    def __init__(self,file):

######### CONFIGS ###############
# eg
# VALUE_KEY = [1,3,5]
# relative to VALUE_KEY
# VALUE_TOTLA_KEY = [0,1]
# VALUE_ITEMS = [2,6]

        #self.VALUE_KEY = [0,1]
        #self.VALUE_KEY_TOTAL = [1] # !!relative to VALUE_KEY!!
        #self.VALUE_ITEMS = [3,4,5,6]
        #self.VALUE_ITEMS_TOTAL = [0,1]

        self.VALUE_KEY = []
        self.VALUE_KEY_TOTAL = [] # !!relative to VALUE_KEY!!
        self.VALUE_ITEMS = []
        self.VALUE_ITEMS_TOTAL = []

        self.PRINT_SINGLE_VALUE = True
        self.PRINT_SUM_VALUE = False
        self.PRINT_PERCENT = True

        self.read_config(file)

        self.VALUE_ITEMS_REAL = []
        for i in self.VALUE_ITEMS_TOTAL:
            self.VALUE_ITEMS_REAL.append(self.VALUE_ITEMS[i])
        if IS_DEBUG:
            print "VALUE_ITEMS_REAL: %s" %(self.VALUE_ITEMS_REAL)

# outformat
# key \t [value1] \t  [total_value] \t [percent]
        #self.PRINT_SINGLE_VALUE = True
        #self.PRINT_SUM_VALUE = False
        #self.PRINT_PERCENT = True

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
                        self.VALUE_KEY_TOTAL.append(num)
                    elif 2 == ln:
                        self.VALUE_ITEMS.append(num)
                    elif 3 == ln:
                        self.VALUE_ITEMS_TOTAL.append(num)
                    elif 4 == ln:
                        self.PRINT_SINGLE_VALUE = num > 0
                    elif 5 == ln:
                        self.PRINT_SUM_VALUE = num > 0
                    elif 6 == ln:
                        self.PRINT_PERCENT = num > 0
                ln += 1
        if IS_DEBUG:
            print "MM",self.PRINT_SUM_VALUE, self.PRINT_PERCENT, self.PRINT_SINGLE_VALUE


######### CONFIGS ###############

def sum_key_value(config):

    global value_total

    for line in sys.stdin:

        items = line[:-1].split('\t')
        n = len(items)

        value_items= len(config.VALUE_ITEMS)

        key =""
        for i in config.VALUE_KEY:#xrange(key_items):
            key += items[i]
            key += '\t'
        key = key.rstrip()
        if key not in key_value_dict:
            key_value_dict[key] = [0 for i in xrange(value_items)]

        key_total = ""
        for i in config.VALUE_KEY_TOTAL:#xrange(key_items):
            key_total += items[config.VALUE_KEY[i]]
            key_total += '\t'
        key_total = key_total.rstrip()

        if key_total not in value_total:
            value_total[key_total] = [0 for i in xrange(value_items)]


        for i in xrange(value_items):
            # correct misses
            if config.VALUE_ITEMS[i] >= n:
                continue
            key_value_dict[key][i] += int(float(items[config.VALUE_ITEMS[i]]))
            # only need required totals @TODO
            if config.VALUE_ITEMS[i] in config.VALUE_ITEMS_REAL:
                if IS_DEBUG:
                    print "Suming for %d" %(config.VALUE_ITEMS[i])
                value_total[key_total][i] += int(float(items[config.VALUE_ITEMS[i]]))


def print_key_value(config):

    p_p = config.PRINT_PERCENT
    p_s_v = config.PRINT_SUM_VALUE
    p_si_v = config.PRINT_SINGLE_VALUE

    for key,value in key_value_dict.iteritems():
        line_str = ""
        line_str += (key + '\t')
        n = len(value)

        key_total = ""
        keys = key.split('\t')
        for i in config.VALUE_KEY_TOTAL:
            key_total += keys[i]
            key_total += '\t'
        key_total = key_total.rstrip()
                
        for i in xrange(n):
            config.PRINT_PERCENT = p_p  
            config.PRINT_SUM_VALUE = p_s_v
            config.PRINT_SINGLE_VALUE = p_si_v
            if IS_DEBUG:
                print "value %d is %d" %(i,value[i])
                print "total is %d" %(value_total[key_total][i])
                print "OO",config.PRINT_SUM_VALUE, config.PRINT_PERCENT, config.PRINT_SINGLE_VALUE

            # @TODO only calculate specified percent
            if value_total[key_total][i] != 0:
                percent = "{:.2f}%".format((value[i]*100.0/value_total[key_total][i]))
                if IS_DEBUG:
                    print "percent is %s" %(percent)
            else:
                percent = 0
            if config.VALUE_ITEMS[i] not in config.VALUE_ITEMS_REAL:
                # we do not need it
                config.PRINT_PERCENT = False
                config.PRINT_SUM_VALUE = False
                if IS_DEBUG:
                    print "VALUE_ITEMS is :%s" %(config.VALUE_ITEMS[i])
                    print "VALUE_ITEMS_REAL is :%s" %(config.VALUE_ITEMS_REAL)

            single_value = str(value[i]) + '\t'
            total_value = str(value_total[key_total][i]) + '\t'
            percent_str = str(percent) + '\t'
            if IS_DEBUG:
                print "NN",config.PRINT_SUM_VALUE, config.PRINT_PERCENT, config.PRINT_SINGLE_VALUE
            if config.PRINT_SINGLE_VALUE:
                line_str += single_value
            if config.PRINT_SUM_VALUE:
                line_str += total_value
            if config.PRINT_PERCENT:
                line_str += percent_str

        line_str = line_str.rstrip()
        print line_str

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
    sum_key_value(config)
    print_key_value(config)

if __name__ == '__main__':
    main()

