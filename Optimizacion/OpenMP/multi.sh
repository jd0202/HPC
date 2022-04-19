declare -A lis
lis[0,0]=m
lis[0,1]='Sin_modificar'
lis[1,0]=mo
lis[1,1]='OpenMP'
for i in {0..1}
do
./comands.sh ${lis[$i,0]} result.csv ${lis[$i,1]}
done

