declare -A lis
lis[0,0]=1
lis[0,1]='este_es_el_1'
lis[1,0]=2
lis[1,1]='este_es_el_2'
for i in {0..1}
do
./comands.sh ${lis[$i,0]} result.csv ${lis[$i,1]}
done

