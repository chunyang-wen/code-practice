#!/bin/env python

import sys
import os

class Config:

    def __init__(self,file):
        self.bad_key = []
        self.bad_key_pos = set() 
        self.read_config(file)

    def read_config(self,file):

        with open(file) as fd:
            for line in fd:
                if line.startswith("#"):
                    continue
                keys = line[:-1].split(' ')
                self.bad_key.append(keys[0])
                self.bad_key_pos.add(int(keys[1]))


def deal_with_line(config):

    for line in sys.stdin:
        items = line[:-1].split('\t')
        NOT_EXISTED = True

        for pos in config.bad_key_pos:
            key = items[pos]
            if key in config.bad_key:
                NOT_EXISTED = False
                break

        if NOT_EXISTED:
            print line[:-1]

         
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
    deal_with_line(config)

if __name__ == "__main__":
    main()

