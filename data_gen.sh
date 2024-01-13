#!/bin/bash

for i in {1..12}
do
    filename="random_data${i}.txt"
    size=$((2 * 1 * 64 * 4 ** (i - 1)))

    echo "Generating $filename with size $size"
    g++ data_gen.cpp -o data_gen && ./data_gen $filename $size
done
