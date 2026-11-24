#include <iostream>
#include "ceasar.h"
#include "playfair.h"

using namespace std;

void inShowMatrix(const char* key)
{
    char matrix[5][5];
    playfairMatrix(key, matrix);
    cout << "Ma tran khoa Playfair:" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

void runCaesar()
{
    char text[256];
    char result[256];
    int key, mode;

    cout << "1. Ma hoa\n2. Giai ma\nChon: ";
    cin >> mode;
    cout << "Nhap khoa (so nguyen): ";
    cin >> key;
    cin.ignore(1000, '\n');
    cout << "Nhap van ban: ";
    cin.getline(text, 256);

    if (mode == 1)
    {
        caesarEncrypt(text, key, result);
        cout << "Ban ma: " << result << endl;
    }
    else
    {
        caesarDecrypt(text, key, result);
        cout << "Ban ro: " << result << endl;
    }
}

void runPlayfair()
{
    char text[256];
    char key[256];
    char result[1024];
    int mode;

    cout << "1. Ma hoa\n2. Giai ma\nChon: ";
    cin >> mode;
    cin.ignore(1000, '\n');
    cout << "Nhap khoa (chuoi chu cai): ";
    cin.getline(key, 256);
    cout << "Nhap van ban: ";
    cin.getline(text, 256);

    inShowMatrix(key);

    if (mode == 1)
    {
        playfairEncrypt(text, key, result);
        cout << "Ban ma: " << result << endl;
    }
    else
    {
        playfairDecrypt(text, key, result);
        cout << "Ban ro (co the chua ky tu X them vao): " << result << endl;
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Mat ma Caesar" << endl;
        cout << "2. Mat ma Playfair" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon: ";
        cin >> choice;

        if (choice == 1)
            runCaesar();
        else if (choice == 2)
            runPlayfair();
    } while (choice != 0);

    return 0;
}
