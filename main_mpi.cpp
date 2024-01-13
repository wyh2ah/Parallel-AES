#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include "aes.hpp"
#include "mpi.h"

using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const std::string inputFileName = argv[1];
    const std::string outputFileName = "encrypt_output.txt";

    std::ifstream inputFile(inputFileName, std::ios::binary);

    inputFile.seekg(0, std::ios::end);
    std::size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    std::vector<uint8_t> inputData(fileSize);
    inputFile.read(reinterpret_cast<char*>(inputData.data()), fileSize);

    inputFile.close();

    const std::size_t blockSize = 16;

    uint8_t key[] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13,
        0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b,
        0x1c, 0x1d, 0x1e, 0x1f};

    uint8_t *w = aes_init(sizeof(key));

    auto begin_time = high_resolution_clock::now();

	aes_key_expansion(key, w);

    MPI_Bcast(w, sizeof(w), MPI_BYTE, 0, MPI_COMM_WORLD);

    std::size_t blocks_per_process = fileSize / blockSize;
    std::size_t local_block_size = blocks_per_process / size;

    std::vector<uint8_t> local_inputData(local_block_size * blockSize);
    std::vector<uint8_t> local_encryptedData(local_block_size * blockSize);

    MPI_Scatter(inputData.data(), local_block_size * blockSize, MPI_BYTE,
                local_inputData.data(), local_block_size * blockSize, MPI_BYTE,
                0, MPI_COMM_WORLD);

    for (std::size_t i = 0; i < local_block_size; ++i) {
        uint8_t in[blockSize];
        uint8_t out[blockSize];

        std::copy(local_inputData.begin() + i * blockSize,
                  local_inputData.begin() + (i + 1) * blockSize, in);

        aes_cipher(in /* in */, out /* out */, w /* expanded key */);

        std::copy(out, out + blockSize,
                  local_encryptedData.begin() + i * blockSize);
    }

    MPI_Gather(local_encryptedData.data(), local_block_size * blockSize, MPI_BYTE,
               inputData.data(), local_block_size * blockSize, MPI_BYTE,
               0, MPI_COMM_WORLD);


    if (rank == 0) {
        

        std::ofstream outputFile(outputFileName, std::ios::binary);

        auto end_time = high_resolution_clock::now();
        auto dur_time = duration_cast<duration<double>>(end_time - begin_time);
        std::cout << "AES Time: " << dur_time.count() << std::endl;
        
        outputFile.write(reinterpret_cast<const char*>(inputData.data()), fileSize);
        outputFile.close();

        std::cout << "Encrypted data written to: " << outputFileName << std::endl;
    }

    MPI_Finalize();

    return 0;
}
