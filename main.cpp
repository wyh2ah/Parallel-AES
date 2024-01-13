#include <iostream>
#include <chrono>
#include "aes.hpp"

using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;

int main() {
	uint8_t i;
	uint8_t key[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,
		0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,
		0x1c, 0x1d, 0x1e, 0x1f};

	uint8_t in[] = {
		0x00, 0x11, 0x22, 0x33,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee, 0xff};
	
	uint8_t out[16]; 

	uint8_t *w; // expanded key

	auto begin_pin = high_resolution_clock::now();

	w = aes_init(sizeof(key));

	aes_key_expansion(key, w);

	printf("Plaintext message:\n");
	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", in[4*i+0], in[4*i+1], in[4*i+2], in[4*i+3]);
	}

	printf("\n");

	aes_cipher(in /* in */, out /* out */, w /* expanded key */);

	auto end_pin = high_resolution_clock::now();
    auto dur_time = duration_cast<duration<double>>(end_pin - begin_pin);
    std::cout << "AES Time: " << dur_time.count() << std::endl; 

	printf("Ciphered message:\n");
	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", out[4*i+0], out[4*i+1], out[4*i+2], out[4*i+3]);
	}

	printf("\n");

	free(w);

	return 0;
}
