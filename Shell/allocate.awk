#!/bin/env gawk -f

BEGIN{
    FS="\t";
    OFS="\t";
    people_num = 0;
    item_total = 100;
    start_seq = 0;
    cur_people = 0;
    tested_people["sh"] = 0;
}

function get_len(a) {
    j = 0;
    for (i in a) {
        ++j;
    }
    return j;
}

NR==FNR {
    a[people_num] = $1;
    b[$1] = 0;
    people_num++;
    cur_people = int(rand() * people_num);
    #print people_num;
}

NR>FNR {
    people = int(rand() * people_num);
    each_max = item_total / people_num;
    delete tested_people

    if (start_seq > 0) {
        print $1, a[cur_people % people_num]
        ++cur_people;
        next;
    }

    #print "pep: """b[a[people]]
    #print "each_max: """each_max
    #print "people_num: """people_num

    if (b[a[people]] < each_max) {
        print $1,a[people]
        b[a[people]] += 1;
        tested_people[people] = 0;
    } else {
    # try to pick another people
    while(1) {
        people = int(rand() * people_num);
        if (b[a[people]] < each_max) {
            b[a[people]] += 1;
            print $1, a[people];
            break;
        } 
        tested_people[people] = 0;
        if (get_len(tested_people) == people_num) {
            # try to allocate sequentially
            b[a[cur_people % people_num]] += 1;
            print $1, a[cur_people % people_num]
            cur_people++;
            start_seq = 1;
            #print "CRAP all full";
            break;
        }
    }
}
}
