#ifndef PLAYFAIR_H
#define PLAYFAIR_H

//Ma trận 5x5
void playfairMatrix(const char* key, char matrix[5][5]);


void playfairEncrypt(const char* plain, const char* key, char* out);
void playfairDecrypt(const char* cipher, const char* key, char* out);

#endif