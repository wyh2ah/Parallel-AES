Data Generate:

```
# Generate specific file size
g++ data_gen.cpp -o data_gen && ./data_gen $filename $filesize

# auto script
./data_gen.sh
```

Openssl Baseline:

```
g++ openssl_aes.cpp -o openssl_aes -W -Wall -std=c++17 -fopenmp -pthread -lssl -lcrypto

./openssl_aes $input_file $threadnum
```

Openmp:

```
 g++ aes.cpp gmult.cpp main_omp.cpp -o omp_aes -std=c++17 -fopenmp -pthread -O3
 
 ./omp_aes $input_file $threadnum
```

MPI:

```
 mpicxx aes.cpp gmult.cpp main_mpi.cpp -o mpi_aes -std=c++17
 
 mpirun -np xx ./mpi_aes $input_file
```

CUDA:

```
nvcc gmult.cu main_cuda.cu -o cuda_aes -O3 -std=c++17

./cuda_aes $input_file
```

Fix_thread Test:
```
./fix_thread.sh
```

Other Scripts:
```
# OpenMP scalability
./omp_scala.sh

# MPI scalability
./mpi_scala.sh

# Openssl CLI Benchmark
./openssl_shell.sh

# Serial run
./sequential.sh

```

