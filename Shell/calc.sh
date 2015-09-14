#!/bin/bash
awk -F '\t' 'BEGIN{
    OFS="\t";
}{
    k=$1;
    pv1[k]+=$2;
    pv2[k]+=$3;
    click[k]+=$4;
    gain[k]+=$5;
}END{
    for(i in pv1){
        if(pv1[i]>1000){
            print i,\
            pv1[i],\
            pv2[i],\
            click[i],\
            gain[i]/100,\
            1000*pv2[i]/pv1[i],
            1000*click[i]/(pv2[i]+1),\
            1000*click[i]/pv1[i],\
            10*gain[i]/pv1[i],
            (gain[i]/100)/(click[i]+1);
        }else{
            oth_pv1 += pv1[i];
            oth_pv2 += pv2[i];
            oth_click += click[i];
            oth_gain += gain[i];
        }
    }
    print "∆‰À˚’æµ„",\
           oth_pv1,\
           oth_pv2,\
           oth_click,\
           oth_gain/100,\
           1000*oth_pv2/(oth_pv1+1),\
           1000*oth_click/(oth_pv2+1),\
           1000*oth_click/(oth_pv1+1),\
           10*oth_gain/(oth_pv1+1),\
           (oth_gain/100)/(oth_click+1);
}'
