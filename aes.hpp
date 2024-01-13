#ifndef AES_HPP
#define AES_HPP

#include <stdint.h>
#include <stdlib.h>

#define gmult(a,b) gmult_aes[256*a + b]

uint8_t *aes_init(size_t key_size);

void aes_key_expansion(uint8_t *key, uint8_t *w);

void aes_cipher(uint8_t *in, uint8_t *out, uint8_t *w);

#endif