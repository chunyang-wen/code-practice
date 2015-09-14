# tools to change comment
# issue
# pcheck

[ $# -lt 4 ] && echo "error" && echo "Usage: sh comment.sh comment_file comment issue pcheck"

: ${1?"file name not exist"}
: ${2?"comment not exist"}
: ${3?"issue num not exist"}
: ${4?"pcheck num not exist"}

sed -i "1s/.*/$2/" $1
sed -i "s/ISSUE=[0-9]*/ISSUE=$3/" $1
sed -i "s/PCHECK=[0-9]*/PCHECK=$4/" $1
