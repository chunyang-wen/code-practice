#!/bin/env python

# sum values according to key
# input format:
# key \t value1 \t value2 ...
import sys
import os


key_value_dict = {}
value_total = {}

def sum_key_value():

    global value_total

    for line in sys.stdin:

        items = line[:-1].split('\t')
        n = len(items)

        key_items=3

        key =""
        for i in xrange(key_items):
            key += items[i]
            key += '\t'
        key.rstrip()
        if key not in key_value_dict:
            key_value_dict[key] = [0 for i in xrange(n-key_items)]

        value_key = '\t'.join(key.split('\t')[0:2])
        if value_key not in value_total:
            value_total[value_key] = [0 for i in xrange(n-key_items)]

        for i in xrange(n-key_items):
            key_value_dict[key][i] += int(items[i+key_items])
            value_total[value_key][i] += int(items[i+key_items])


def print_key_value():

    for key,value in key_value_dict.iteritems():
        line_str = ""
        line_str += (key + '\t')
        n = len(value)
        for i in xrange(n):
            value_key = '\t'.join(key.split('\t')[0:2])
            if value_total[value_key][i] != 0:
                percent = "{:.2f}%".format((value[i]*100.0/value_total[value_key][i]))
            else:
                percent = 0
            percent_str = str(percent) + '\t'
            line_str += (str(value[i]) + '\t' + percent_str)

        line_str.rstrip()
        print line_str


def main():
    sum_key_value()
    print_key_value()



if __name__ == '__main__':
    main()

