#include <iostream>
#include "des.h"
using namespace std;

void print_binary64(uint64_t value) {
    for (int i = 63; i >= 0; --i) {
        cout << ((value >> i) & 1);
    }
    cout << '\n';
}

uint64_t Nhap_plaintext() {
    uint64_t plaintext = 0;
    cout << "Nhap plaintext (hex): ";
    cin >> hex >> plaintext;
    return plaintext;
}

uint64_t Nhap_key() {
    uint64_t key = 0;
    cout << "Nhap key (hex): ";
    cin >> hex >> key;
    return key;
}

int main() {
    uint64_t plaintext = Nhap_plaintext();
    uint64_t key = Nhap_key();

    // Mã hóa
    uint64_t ciphertext = encrypt(plaintext, key);
    cout << "\nCiphertext (hex)   : " << hex << ciphertext << '\n';
    cout << "Ciphertext (binary): ";
    print_binary64(ciphertext);

    // Giải mã
    uint64_t decrypted = decrypt(ciphertext, key);
    cout << "\nDecrypted (hex)    : " << hex << decrypted << '\n';
    cout << "Decrypted (binary) : ";
    print_binary64(decrypted);

    return 0;
}