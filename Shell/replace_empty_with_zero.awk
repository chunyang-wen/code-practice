#!/bin/awk -f

BEGIN{
    FS = "\t";
    OFS = "\t";
}
{
    for (i = 1; i <= NF; ++i) {
        if ($i == "") {
            $i = 0;
        }
    }
    print $0;
}
