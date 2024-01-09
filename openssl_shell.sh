#!/bin/bash

input_file="random_data.txt"
output_file="encrypt_output.txt"
password="1234567890"

start_time=$(date +%s.%N)
openssl enc -aes-256-ecb -pass pass:"$password" -pbkdf2 -iter 14 -p -in "$input_file" -out "$output_file"
#openssl enc -aes-256-cbc -pass pass:"$password" -pbkdf2 -iter 14 -p -in "$input_file" -out "$output_file"
end_time=$(date +%s.%N)

execution_time=$(echo "$end_time - $start_time" | bc)
echo "AES Time: $execution_time 秒"
