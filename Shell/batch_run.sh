for i in `seq -w 01 1 25`
do
    date=201506"$i"
    sh -x gen_data_mobile.sh $date
done




