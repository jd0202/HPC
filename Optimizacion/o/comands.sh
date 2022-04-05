echo $3";" >> $2
lis=(150 200 250 500 1000 2000 3000)
for a in ${lis[@]}
do
echo -n $a";" >> $2
done
echo >> $2
for j in {1..10}
do
for i in ${lis[@]}
do
./$1 $i>> $2
done
echo >> $2
done
