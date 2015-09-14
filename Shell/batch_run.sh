for i in `seq 12 1 20`
do
    date=201506"$i"
    sh -x pre-process.sh $date
done




