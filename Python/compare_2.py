#!/usr/bin/env python
import sys
import string
dict={}
SEP='\t'
START=1
def process_file(fin,dic,id):
    item_set=dic.get(id,{})
    for line in fin :
        values = line.strip().split(SEP)
        record = item_set.get(values[0],{})
        for i in range(START,len(values)) :
            record[i] = string.atof(values[i])
        item_set[values[0]] = record
    dic[id] = item_set
def cmp(dic):
    today = dic['t'];
    yestd = dic['y'];
    dif = {}
    for key in today :
        rec = dif.get(key,{})
        for v in range(1,len(today[key])+1):
            if key in yestd:
                if yestd[key][v] == 0:
                    if today[key][v] == 0:
                        rec[v] = "N/A"
                    else :
                        rec[v] = "+100%"
                else:
                    tmp = 100*(today[key][v]/(yestd[key][v])-1)
                    if tmp < 0 :
                        rec[v] = "%.2f" % tmp
                    else :
                        rec[v] = "+%.2f" % tmp
            else:
                rec[v] = "new"
        dif[key] = rec
    for key in yestd :
        if not key in today:
            for v in range(1,len(yestd[key])+1):
                rec[v] = "offline"
            
    return dif
def output(dic,dic2):
    for i in dic:
        today = dic2['t']
        str = "%s\t%.f" % (i,today[i][1])
        for j in range(1,len(dic[i])+1):
            str += "\t%s" % dic[i][j]
        print str
def main():
    fin = open(sys.argv[1], "r")
    process_file(fin,dict,"t")
    fin = open(sys.argv[2], "r")
    process_file(fin,dict,"y")
    output(cmp(dict),dict)
if __name__ == "__main__":
    main()
