#!/bin/env awk -f
BEGIN {
    FS="\t";
    OFS="\t";
    data_items["1pv1"] = 2;
    data_items["2pv2"] = 3;
    data_items["3s1ctr"] = 6;
    data_items["4s2ctr"] = 7;
    data_items["5ctr"] = 8;
    data_items["6s2cpm"] = 9;
    data_items["7cpm"] = 10;
    data_items["8acp"] = 11;
    file_index = 0;
    folder = output_folder; #"data/";
}

ARGIND==1 {
    # domain file
    a[$1] = 0;
}
ARGIND>1 {
    file_index = ARGIND - 1;
    # print index;
    # handle data files
    if ($0 == "" || a[$1] == "") {
        next;
    }
    for (key in data_items) {
        #print $1,key,file_index;
        b[$1,key,file_index] = $data_items[key]
    } 

}
END {
    # print file_index
    len = asorti(data_items, data_items_key);
    for (key in a) {
        #print "key: """key
        for (data_index = 1; data_index <= len; ++data_index) {
            key_data = data_items_key[data_index];
            #print key_data
            line = "";#key_data;
            if (b[key, key_data, 1] == "") {
                break;
            }
            #print "data_key: """key_data
            for (i = 1; i <= file_index; ++i) {
                line = line"""\t"""b[key, key_data, i]
            }

            key_rep = key;
            gsub(/\./, "_", key_rep);
            if (match(key_rep, /^[0-9]+.*/)) {
                key_rep = "X"""key_rep;
            }
            print substr(line, 2)>>folder"""/"""key_rep""".txt"
        }
    }

}
