#!/bin/bash

# files are all single column
# find the all the join files

[ $# -lt 2 ] && echo "Usage sh intersect.sh file-ouput file1-input file2-input **"

TEMPFILE1=`mktemp $$.XXXXXX || echo "Making temp file failed;";exit 0`
TEMPFILE2=`mktemp $$.XXXXXX || echo "Making temp file failed;";exit 0`
OUTPUT=$1

INDEX=1

# remove output file
shift
for file in "$@";
do
    [ ! -e $file ] && continue;
    [ ! -s $file ] && continue;
    [[ $INDEX == 1 ]] && cat $file > $TEMPFILE1
    cat $TEMPFILE1 $file | sort | uniq -d > $TEMPFILE2
    mv $TEMPFILE2 $TEMPFILE1
    let "INDEX++"
done

mv $TEMPFILE1 $OUTPUT

