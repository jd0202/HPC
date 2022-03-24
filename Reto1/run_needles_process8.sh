for j in {1..10}
do
for i in 150 200 250 500 1000 2000 3000 20000 100000 500000 1000000 50000000
do
echo $i >> times_needles_process_8.txt
./needles_process_8 $i >> times_needles_process_8.txt
done
done
python3 crear.py times_needles_process_8.txt