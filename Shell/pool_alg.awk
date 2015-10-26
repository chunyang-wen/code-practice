#!/bin/awk -f

# pool alg

BEGIN {
    FS="\t";
    OFS="\t";
    m = 500; # need 500 samples
    cur_ind = 0;
}
{
    if (cur_ind < 500) {
        a[cur_ind] = $1;
    } else {
        # rand swap curent value
        val = int(rand() * cur_ind);
        if (val <= m) {
            a[val] = $1;
        }
    }
    ++cur_ind;
}
END {
    for (key in a) {
        print a[key];
    }
}
