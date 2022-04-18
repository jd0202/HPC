for i in 1 2 3 4 5 6 7 8 9 10
do
    echo "Try $i \n">>result.txt
    gcc matrices_open.c -o output -fopenmp 
    for j in 16 200 400 600
    do
        echo "Matrix's size $j x $j: ">>result.txt
        ./output $j
    done
    echo "\n">>result.txt
done