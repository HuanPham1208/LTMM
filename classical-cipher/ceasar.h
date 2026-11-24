#ifndef CEASAR_H
#define CEASAR_H

void caesarEncrypt(const char* plain, int key, char* out);
void caesarDecrypt(const char* cipher, int key, char* out);

#endif