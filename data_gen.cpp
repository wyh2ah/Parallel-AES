#include <iostream>
#include <fstream>
#include <random>
#include <cstdint>
#include <iomanip>

int main(int argc, const char * argv[]) {
    std::string outputFileName = argv[1];
    std::size_t dataSize = atoi(argv[2]);
    // const std::size_t dataSize = 512 * 1024 * 1024; // 1G
    // const std::size_t dataSize = 2 * 1 * 64;
    std::size_t seedValue = 42;


    std::ofstream outputFile(outputFileName, std::ios::binary);

    std::mt19937 gen(seedValue);
    std::uniform_int_distribution<uint8_t> dis(0x00, 0xff);

    for (std::size_t i = 0; i < dataSize; ++i) {
        uint8_t randomByte = dis(gen);
        outputFile << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(randomByte);
    }

    outputFile.close();

    std::cout << "Random data generated and written to " << outputFileName << std::endl;

    return 0;
}