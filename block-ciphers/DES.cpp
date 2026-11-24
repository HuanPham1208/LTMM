#include "des.h"

uint64_t IP_function(uint64_t plaintext) {
    uint64_t result = 0;
    for (int i = 0; i < 64; ++i) {
        result <<= 1;
        result |= (plaintext >> (64 - IP[i])) & 1ULL;
    }
    return result;
}

uint64_t IP_inverse_function(uint64_t input) {
    uint64_t result = 0;
    for (int i = 0; i < 64; ++i) {
        result <<= 1;
        result |= (input >> (64 - IP_INV[i])) & 1ULL;
    }
    return result;
}

uint32_t P_function(uint32_t input) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result <<= 1;
        result |= (input >> (32 - P[i])) & 1U;
    }
    return result;
}