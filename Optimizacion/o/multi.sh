declare -A lis
lis[0,0]=m2
lis[0,1]='O2'
lis[1,0]=m3
lis[1,1]='O3'
for i in {0..1}
do
./comands.sh ${lis[$i,0]} result.csv ${lis[$i,1]}
done

