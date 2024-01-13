#!/bin/bash

g++ aes.cpp gmult.cpp main_omp.cpp -o omp_aes -std=c++17 -fopenmp -pthread -O3
g++ openssl_aes.cpp -o openssl_aes -W -Wall -std=c++17 -fopenmp -pthread -lssl -lcrypto

if [ $? -eq 0 ]; then
    echo "Compilation successful."

    output_result="sequential_results.txt"
    
    echo "File Size: 256B, 1KB, 4KB, 16KB, 64KB, 256KB, 1MB, 4MB, 16MB, 64MB, 256MB, 1GB" > ${output_result}
    echo "omp_aes Time: " >> ${output_result}
    echo "openssl_aes Time: " >> ${output_result}

    for i in {1..12}
    do
        input_file="random_data${i}.txt"

        echo "Running encryption for ${input_file}..."

        dur_time_omp=$(./omp_aes ${input_file} | grep "AES Time:" | cut -d ' ' -f 3)

        dur_time_openssl=$(./openssl_aes ${input_file} | grep "AES Time:" | cut -d ' ' -f 3)

        echo -n "${dur_time_omp}, " >> ${output_result}
        echo "${dur_time_openssl}" >> ${output_result}

        echo "Encryption completed for ${input_file}."
        echo ""
    done

    echo "Results written to: ${output_result}"

else
    echo "Compilation failed. Please fix the compilation errors before running the script."
fi
