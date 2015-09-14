#!/usr/bin/env python
import sys
import string
dict={}
SEP='\t'
START=1
def process_file(fin,dic,t):
    for line in fin :
        values = line.strip().split(SEP)
        domain = values[0]
        record = dic.get(domain,{})
        for i in range(START,len(values)) :
            unit = record.get(i,{})
            unit[t] = string.atof(values[i])
            record[i] = unit
        dic[domain] = record
def cmp(dic):
    dif = {}
    for key in dic :
        record = dic[key]
        for v in range(1,len(record)+1):
            unit = record[v]
            if "t" in unit:
                if  not "y" in unit:
                    unit["d"] = "new";
                    unit["y"] = 0;
                else:
                    if(unit["y"]==0) :
                        tmp = 100
                    else :
                        tmp = 100*(unit["t"]/unit["y"]-1)
                    if tmp < 0 :
                        unit["d"] = "%.2f" % tmp
                    else :
                        unit["d"] = "%.2f" % tmp
            else:
                if  "y" in unit:
                    unit["t"] = 0
                    unit["d"] = "off" 
                else :
                    unit["d"] = "error"
                    unit["t"] = "error"
                    unit["y"] = "error"
            record[v] = unit
    return dic
def output(dic):
    for i in dic:
        record = dic[i]
        str = i
        for j in range(1,len(record)+1):
            unit = record[j]
            value1 = unit["t"]
            value2 = unit["y"]
            str += "\t%s\t%s\t%s" % (unit["t"],(value1 - value2),unit["d"])
        print str
def main():
    fin = open(sys.argv[1], "r")
    process_file(fin,dict,"t")
    fin = open(sys.argv[2], "r")
    process_file(fin,dict,"y")
    output(cmp(dict))
if __name__ == "__main__":
    main()
