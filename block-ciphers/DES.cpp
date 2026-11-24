#include "des.h"

//Hàm hoán vị IP và IP^-1
uint64_t IP_function(uint64_t plaintext) {
    uint64_t result = 0;
    for (int i = 0; i < 64; ++i) {
        result <<= 1;
        result |= (plaintext >> (64 - IP[i])) & 1 ;
    }
    return result;
}
uint64_t IP_inverse_function(uint64_t input) {
    uint64_t result = 0;
    for (int i = 0; i < 64; ++i) {
        result <<= 1;
        result |= (input >> (64 - IP_INV[i])) & 1 ;
    }
    return result;
}


//Hàm hoán vị P
uint32_t P_function(uint32_t input) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result <<= 1;
        result |= (input >> (32 - P[i])) & 1U;
    }
    return result;
}
//Hàm mở rộng E
uint64_t E_function(uint32_t input) {
    uint64_t result = 0;
    for (int i = 0; i < 48; ++i) {
        result <<= 1;
        result |= (static_cast<uint64_t>(input) >> (32 - E[i])) & 1 ;
    }
    return result;
}
uint32_t f_function(uint32_t R, uint64_t ki) {
    uint64_t expanded = E_function(R) ^ ki; // Mở rộng R từ 32 -> 48 bit rồi xor với key

    //// 2. Xu ly 8 khoi 6 bit qua 8 bang S-Box
    uint32_t sboxOutput = 0;
    for (int box = 0; box < 8; ++box) {
        uint8_t sixBits = static_cast<uint8_t>((expanded >> (42 - 6 * box)) & 0x3F);
        int row = ((sixBits & 0x20) >> 4) | (sixBits & 0x01);
        int column = (sixBits >> 1) & 0x0F;
        sboxOutput = (sboxOutput << 4) | SBOX[box][row][column];
    }

    return P_function(sboxOutput);
}

//Hàm hoán vị PC1 và PC2
uint64_t PC1_function(uint64_t key) {
    uint64_t result = 0;
    for (int i = 0; i < 56; ++i) {
        result <<= 1;
        result |= (key >> (64 - PC1[i])) & 1 ;
    }
    return result;
}

uint64_t PC2_function(uint64_t input) {
    uint64_t result = 0;
    for (int i = 0; i < 48; ++i) {
        result <<= 1;
        result |= (input >> (56 - PC2[i])) & 1 ;
    }
    return result;
}
//Hàm dịch vòng trái
uint64_t left_shift(uint64_t input, int s) {
    input &= 0x0FFFFFFF ;
    return ((input << s) | (input >> (28 - s))) & 0x0FFFFFFF;
}
//Hàm tạo khoá con
void gen_subkey(uint64_t key, uint64_t k[16]) {
    uint64_t  V = PC1_function(key);
    uint64_t C = ( V >> 28) & 0x0FFFFFFF;
    uint64_t D =  V & 0x0FFFFFFF;

    for (int  i = 0;  i < 16; ++ i) {
        C = left_shift(C, SHIFTS[ i]);
        D = left_shift(D, SHIFTS[ i]);
        k[i] = PC2_function((C << 28) | D);
    }
}