#!/bin/env python

# add all the value
# pv1\t pv2\tclick\tgain\tlp_click\tl1_ctr\tl2_ctr\tl1_cpm\tl2_cpm

import sys


if len(sys.argv) < 2:
    print "error in agrv"
filename = sys.argv[1] # "res_lu.20align0309"

res_dict = {}
def sum():
    fd = open(filename, "rt")
    pv1 = 0.0
    pv2 = 0.0
    click = 0.0
    gain = 0.0
    lp_click = 0.0
    t_jump = 0.0
    t_cqpro = 0.0
    l1_ctr = 0.0
    l2_ctr = 0.0
    l2_cpm = 0.0
    l1_cpm = 0.0
    # domain^tempalte^tu
    kk = "ute"
    items=[kk,"pv1","pv2","click","gain(yuan)","l2_ctr(%)","l1_ctr(%)","l2_cpm(yuan)","l1_cpm(yuan)"]
    l_pv1 = 0.0
    l_pv2 = 0.0
    l_click = 0.0
    l_gain = 0.0
    l_lp_click = 0.0
    l_t_jump = 0.0
    l_t_cqpro = 0.0
    l_l1_ctr = 0.0
    l_l2_ctr = 0.0
    l_l2_cpm = 0.0
    l_l1_cpm = 0.0

    align = 10
    out_str = ""
    for i in items:
        out_str += ('{:<{n}}'.format(i, n=align) + '\t')
    out_str += "\n"
    out_str1 = out_str

    for line in fd:
        str1 = line.split('\t')
        if int(str1[1]) == 0 or int(str1[2]) == 0:
            continue
        l_pv1 = float(str1[1])
        l_pv2 = float(str1[2])
        pv1 += l_pv1
        pv2 += l_pv2
        l_click = float(str1[3])
        l_gain  = float(str1[4])
        click += l_click
        gain  += l_gain

        l_l1_ctr = l_click / l_pv1
        l_l2_ctr = l_click / l_pv2
        
        l_gain /= 100
        l_l1_cpm = l_gain / l_pv1 * 1000.0 # change to yuan
        l_l2_cpm = l_gain / l_pv2 * 1000.0 # chagne to yuan 
        
        l_l1_ctr = '{:.3f}%'.format(l_l1_ctr * 100)
        l_l2_ctr = '{:.3f}%'.format(l_l2_ctr * 100)
        l_l1_cpm = '{:.3f}'.format(l_l1_cpm)
        l_l2_cpm = '{:.3f}'.format(l_l2_cpm)

        values = [l_pv1, l_pv2, l_click, l_gain, l_l2_ctr, l_l1_ctr, l_l2_cpm, l_l1_cpm]
        #key =(str1[0].split('^')[0]) + "^" + (str1[0].split('^')[1])
        key = (str1[0].split('^')[0])
        #out_str +=('{:<{n}}'.format(str1[0].split('^')[0]+'^'+str1[0].split('^')[2]+'\t', n=align+5))
        out_str +=('{:<{n}}'.format(str1[0].split('^')[0]+'\t', n=align+5))

        if key not in res_dict:
            res_dict[key] = values
        else:
            for i in xrange(len(values)):
                res_dict[key][i] += values[i]
        
        for i in values:
            out_str += ('{:<{n}}'.format(str(i)+'\t', n=align))
        out_str += "\n"
        


    # output reslut
    l2_ctr = pv2/pv1
    l1_ctr = click/pv1
    l1_cpm = gain/pv1*1000
    l2_cpm = gain/pv2*1000
    l1_ctr = '{:.3f}%'.format(l1_ctr * 100)
    l2_ctr = '{:.3f}%'.format(l2_ctr * 100)
    l1_cpm = '{:.3f}'.format(l1_cpm)
    l2_cpm = '{:.3f}'.format(l2_cpm)

    

    values=[pv1,pv2,click,gain,l2_ctr,l1_ctr,l2_cpm,l1_cpm]

    out_str +=  "sum:\t"
    sys.stdout.softspace=0
    for i in xrange(len(values)):
        out_str += (str(values[i])[0:8]+'\t')
    out_str += '\n'
    #print out_str

    # update ctr and cpm
    for i in res_dict:
        # update ctr
        res_dict[i][5] = '{:.3f}%'.format(res_dict[i][1]/res_dict[i][0] * 100)
        res_dict[i][4] = '{:.3f}%'.format(res_dict[i][2]/res_dict[i][1] * 100)
        # res_dict[i][5] = res_dict[i][2]/res_dict[i][1]
        # update cpm
        res_dict[i][7] = '{:.3f}'.format(res_dict[i][3]/res_dict[i][0] * 1000)
        res_dict[i][6] = '{:.3f}'.format(res_dict[i][3]/res_dict[i][1] * 1000)
        # res_dict[i][7] = res_dict[i][3]/res_dict[i][1] * 10
    keys = res_dict.keys()
    keys.sort()
    for i in keys:
        # out_str1 += (str(i) + '\t')
        out_str1 += ('{:<{n}}'.format(str(i),n=align) + '\t')
        for j in res_dict[i]:
            out_str1 += ('{:<{n}}'.format(str(j),n=align) + '\t')
        out_str1 += '\n'
    
    out_str1 +=  ('{:<{n}}'.format("sum:", n=align) + "\t")
    for i in xrange(len(values)):
        out_str1 += ('{:<{n}}'.format(str(values[i]),n=align)+'\t')
    out_str1 += '\n'
    print out_str1

    
sum()
















