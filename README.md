Data Generate:

```
g++ data_gen.cpp -o data_gen

./data_gen
```

Openssl Baseline:

```
g++ openssl_aes.cpp -o openssl_aes -W -Wall -std=c++17 -fopenmp -pthread -lssl -lcrypto
```

Openmp:

```
 g++ aes.cpp gmult.cpp main_omp.cpp -o omp_aes -std=c++17 -fopenmp -pthread -O3
 
 ./omp_aes
```

MPI:

```
 mpicxx aes.cpp gmult.cpp main_mpi.cpp -o mpi_aes -std=c++17
 
 mpirun -np xx ./mpi_aes
```

CUDA:

```
nvcc gmult.cu main_cuda.cu -o cuda_aes -O3 -std=c++17

./cuda_aes
```

