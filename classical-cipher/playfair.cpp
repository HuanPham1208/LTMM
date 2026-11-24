#include "playfair.h"

// Chuyển ký tự về chữ in hoa
static char normalizeLetter(char c)
{
    if (c >= 'a' && c <= 'z')
        c = (char)(c - 'a' + 'A');
    if (c < 'A' || c > 'Z')
        return 0;
    if (c == 'J')
        c = 'I';
    return c;
}

void  playfairMatrix(const char* key, char matrix[5][5])
{
    bool used[26];
    for (int i = 0; i < 26; i++)
        used[i] = false;

    int pos = 0; 

    // Bước 1: điền các chữ cái của khóa 
    for (int i = 0; key[i] != '\0'; i++)
    {
        char c = normalizeLetter(key[i]);
        if (c != 0 && !used[c - 'A'])
        {
            used[c - 'A'] = true;
            matrix[pos / 5][pos % 5] = c;
            pos++;
        }
    }

    // Bước 2: điền các chữ cái còn lại theo thứ tự bảng chữ cái
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J')
            continue;
        if (!used[c - 'A'])
        {
            used[c - 'A'] = true;
            matrix[pos / 5][pos % 5] = c;
            pos++;
        }
    }
}

// Tìm vị trí ký tự c trong ma trận
static void findPosition(char matrix[5][5], char c, int& row, int& col)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == c)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Xử lý một cặp ký tự (a, b). dir = 1: mã hóa, dir = 4: giải mã (tương đương -1 mod 5)
static void processPair(char matrix[5][5], char a, char b, int dir, char& outA, char& outB)
{
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    findPosition(matrix, a, r1, c1);
    findPosition(matrix, b, r2, c2);

    if (r1 == r2)
    {
        // Cùng hàng: lấy ký tự bên phải (mã hóa) / bên trái (giải mã)
        outA = matrix[r1][(c1 + dir) % 5];
        outB = matrix[r2][(c2 + dir) % 5];
    }
    else if (c1 == c2)
    {
        // Cùng cột: lấy ký tự bên dưới (mã hóa) / bên trên (giải mã)
        outA = matrix[(r1 + dir) % 5][c1];
        outB = matrix[(r2 + dir) % 5][c2];
    }
    else
    {
        // Hình chữ nhật: đổi chéo cột
        outA = matrix[r1][c2];
        outB = matrix[r2][c1];
    }
}

void playfairEncrypt(const char* plain, const char* key, char* out)
{
    char matrix[5][5];
     playfairMatrix(key, matrix);

    // Bước 1: lọc chỉ giữ chữ cái, in hoa, J -> I
    char clean[512];
    int n = 0;
    for (int i = 0; plain[i] != '\0' && n < 511; i++)
    {
        char c = normalizeLetter(plain[i]);
        if (c != 0)
            clean[n++] = c;
    }

    // Bước 2: tách thành các cặp; nếu 2 chữ giống nhau thì chèn 'X' ở giữa;
    //         nếu còn lẻ 1 chữ ở cuối thì thêm 'X'
    char text[1024];
    int m = 0;
    int i = 0;
    while (i < n)
    {
        char a = clean[i];
        char b;
        if (i + 1 < n)
            b = clean[i + 1];
        else
            b = 'X';

        if (a == b)
        {
            b = 'X';
            i += 1;
        }
        else
        {
            i += 2;
        }
        text[m++] = a;
        text[m++] = b;
    }

    // Bước 3: mã hóa từng cặp
    for (int k = 0; k < m; k += 2)
        processPair(matrix, text[k], text[k + 1], 1, out[k], out[k + 1]);
    out[m] = '\0';
}

void playfairDecrypt(const char* cipher, const char* key, char* out)
{
    char matrix[5][5];
     playfairMatrix(key, matrix);

    // Lọc chữ cái
    char clean[512];
    int n = 0;
    for (int i = 0; cipher[i] != '\0' && n < 511; i++)
    {
        char c = normalizeLetter(cipher[i]);
        if (c != 0)
            clean[n++] = c;
    }

    // Giải mã từng cặp (bỏ qua ký tự lẻ cuối nếu có)
    int m = 0;
    for (int k = 0; k + 1 < n; k += 2)
    {
        processPair(matrix, clean[k], clean[k + 1], 4, out[m], out[m + 1]);
        m += 2;
    }
    out[m] = '\0';
}