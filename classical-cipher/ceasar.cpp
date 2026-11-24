#include "ceasar.h"


static int normalizeKey(int key)
{
    key = key % 26;
    if (key < 0)
        key = key + 26;
    return key;
}

// Dịch chuyển một ký tự 
static char shiftChar(char c, int shift)
{
    if (c >= 'A' && c <= 'Z')
        return (char)('A' + (c - 'A' + shift) % 26);
    if (c >= 'a' && c <= 'z')
        return (char)('a' + (c - 'a' + shift) % 26);
    return c; 
}

void caesarEncrypt(const char* plain, int key, char* out)
{
    int k = normalizeKey(key);
    int i = 0;
    while (plain[i] != '\0')
    {
        out[i] = shiftChar(plain[i], k);
        i++;
    }
    out[i] = '\0';
}

void caesarDecrypt(const char* cipher, int key, char* out)
{
    int k = 26 - normalizeKey(key);
    int i = 0;
    while (cipher[i] != '\0')
    {
        out[i] = shiftChar(cipher[i], k);
        i++;
    }
    out[i] = '\0';
}