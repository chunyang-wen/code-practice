#!/bin/env python

import sys
import os
import re

IS_DEBUG=False

############ CONFIGS ###############
class Config():

    def __init__(self,file):

    # eg
    # VALUE_KEY = [1,3,5]
    # relative to VALUE_KEY
    # VALUE_ITEMS = [3,4,5,6]
    ### PV1 PV2 CLICK GAIN
    # VALUE_APPEND_ITEMS = [
    #         lambda x:float(x[4])/float(x[3]), # pv2/pv1
    #         lambda x:float(x[5])/float(x[4]), # pv2/click
    #         lambda x:float(x[5])/float(x[3]), # click/pv1
    #         lambda x:float(x[6])/float(x[4]), # gain/pv2
    #         lambda x:float(x[6])/float(x[3]), # gain/pv1
    #         ] 
    #

    #    self.VALUE_APPEND_ITEMS_FORMATER = [
    #           self.format_data(2, "%"),
    #           self.format_data(2, "%"),
    #           self.format_data(2, "%"),
    #           self.format_data(2,""),
    #           self.format_data(2,""),
    #           ]
        self.VALUE_APPEND_ITEMS = []
        self.VALUE_APPEND_ITEMS_FORMATER = []
        self.read_config(file)

        #if IS_DEBUG:
            #aa=[1,2,3,4,5]
            #print self.VALUE_APPEND_ITEMS
            #for i in self.VALUE_APPEND_ITEMS:
            #    print "READING: %f" %(i(aa))

    # Support format float or int data
    # Any other data can be appended to output
    # by using append variable
    # Function wrapper
    def format_data(self,precision=2, append=""):
        
        def inner_format(data):
            str = "{:.{n}f}".format(data,n=precision)
            str += append
            return str
        return inner_format

    def read_config(self,file):

        is_data_or_format = True
        # data
        # format
        #####EXAMPLE####
        # $1+$2
        # 2 %
        #####EXAMPLE####
        with open(file) as fd:
            for line in fd:
                if line.startswith("#"):
                    continue
                if line.startswith("$$"):
                    # $$ marks the end
                    break
                # read syntax
                expression = line[:-1]
                if IS_DEBUG:
                    print "Expression: %s" %(expression)
                # replace $n with with, x[n]
                if is_data_or_format:
                    expression = re.sub(r"\$(\d)", r"float(x[\1])",expression)
                    if IS_DEBUG:
                        print "Expression after replaced: %s" %(expression)
                    func = eval("lambda x: %s" %(expression))
                    self.VALUE_APPEND_ITEMS.append(func)
                    is_data_or_format = not is_data_or_format
                else:
                    # Even having no append, 
                    # an additional space is required
                    items=expression.split(' ')
                    precision = int(items[0])
                    append = items[1]
                    func = self.format_data(precision,append)
                    self.VALUE_APPEND_ITEMS_FORMATER.append(func)
                    is_data_or_format = not is_data_or_format


############# CONFIGS ###############


def line_key_value(config):

    for line in sys.stdin:

        if IS_DEBUG:
            print "Cur line is: %s" %(line[:-1])

        items = line[:-1].split('\t')
        n = len(items)
        line_str = line[:-1] + '\t'

        append_value_items= len(config.VALUE_APPEND_ITEMS)

        for i in xrange(append_value_items):
            data = ""
            try:
                data = config.VALUE_APPEND_ITEMS[i](items)
            except:
                data = 0
            if IS_DEBUG:
                print "data : %f" %(data)
                print items
            data_str = config.VALUE_APPEND_ITEMS_FORMATER[i](data)
            line_str += data_str
            #line_str += str(config.VALUE_APPEND_ITEMS[i](items))
            line_str += '\t'
        line_str = line_str.rstrip()
        print line_str

# "{:.2f}%".format((value[i]*100.0/value_total[key_total][i]))

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
    line_key_value(config)

if __name__ == '__main__':
    main()

