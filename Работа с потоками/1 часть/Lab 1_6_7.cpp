#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int n, k;
int BlocksCount = 0;

string key;
string CryptedText, unCryptedText;
string* CryptedBlocks = new string[1000];
string* UnCryptedBlocks = new string[1000];


DWORD WINAPI coding(LPVOID param)
{
    string* pcol_num = (string*)param;
    string block = *pcol_num;

    char num1 = block[0];
    int num2 = num1 - '0';
    block = block.substr(1, block.length());
    string a = block;

    reverse(block.begin(), block.end());
    block += key;
    string CryptedBlock = "";
    for (int i = 0; i < a.length(); i++)
    {
        CryptedBlock += a[i] ^ key[i];
    }

    block += CryptedBlock;
    CryptedBlocks[num2] = block;

    return 0;
}

DWORD WINAPI DecoderBlock(LPVOID param)
{
    string* pcol_num = (string*)param;
    string block = *pcol_num;

    char num1 = block[0];
    int num2 = num1 - '0';
    block = block.substr(1, block.length());
    string first = "";

    if (block.length() == k * 3)
    {
        for (int i = 0; i < k; i++)
        {
            first += block[i];
        }
    }
    else
    {
        int kForDecoder = (block.length() - k) / 2;
        for (int i = 0; i < kForDecoder; i++)
        {
            first += block[i];
        }
    }

    reverse(first.begin(), first.end());
    UnCryptedBlocks[num2] = first;

    return 0;
}

void main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    //string text = "qwe rtyu wr";
    //cout << "Введите текст для шифрования: " << text << endl;
    //n = text.length();
    string text;
    cout << "Введите текст для шифрования: ";
    getline(cin, text);
    n = text.length();

    //string key2 = "12r ";
    //cout << "Введите ключ: " << key2 << endl;
    //k = key2.length();
    //key = key2;
    string key2;
    cout << "Введите ключ: ";
    getline(cin, key2);
    k = key2.length();
    key = key2;

    BlocksCount = ceil(n / k);
    if (n % k != 0)
    {
        BlocksCount += 1;
    }
    string* blocks = new string[BlocksCount];
    int countBlock = 0;

    int p = 0;
    for (int j = 0; j < BlocksCount; j++)
    {
        string s2 = to_string(j);
        for (p; p < n; p++)
        {
            if (countBlock != k)
            {
                s2 += text[p];
                countBlock++;
            }
            else
            {
                countBlock = 0;
                break;
            }
        }
        if (p <= n)
        {
            blocks[j] = s2;
            if (p == n)
            {
                p++;
            }
        }
    }

    HANDLE* CodingThread = new HANDLE[BlocksCount];
    DWORD* CodingThreadID = new DWORD[BlocksCount];

    for (int i = 0; i < BlocksCount; i++)
    {
        CodingThread[i] = CreateThread(NULL, 0, coding, &(blocks[i]), 0, &(CodingThreadID[i]));
        if (CodingThread[i] == NULL)
        {
            cout << "Поток № " << i << "не был создан\n" << "Ошибка " << GetLastError();
        }
    }

    WaitForMultipleObjects(BlocksCount, CodingThread, true, INFINITE);

    for (int i = 0; i < BlocksCount; i++)
    {
        CloseHandle(CodingThread[i]);
    }

    for (int i = 0; i < BlocksCount; i++)
    {
        CryptedText += CryptedBlocks[i];
    }
    cout << "Зашифрованный текст: " << CryptedText << endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    string* blocksForDecoder = new string[BlocksCount];
    p = 0;
    countBlock = 0;
    for (int j = 0; j < BlocksCount; j++)
    {
        string s2 = to_string(j);
        for (p; p < CryptedText.length(); p++)
        {
            if (countBlock != k * 3)
            {
                s2 += CryptedText[p];
                countBlock++;
            }
            else
            {
                countBlock = 0;
                break;
            }
        }
        if (p <= CryptedText.length())
        {
            blocksForDecoder[j] = s2;
            if (p == CryptedText.length())
            {
                p++;
            }
        }
    }

    for (int i = 0; i < BlocksCount; i++)
    {
        CodingThread[i] = CreateThread(NULL, 0, DecoderBlock, &(blocksForDecoder[i]), 0, &(CodingThreadID[i]));

        if (CodingThread[i] == NULL)
        {
            cout << "Поток № " << i << "не был создан\n" << "Ошибка " << GetLastError();
        }
    }

    WaitForMultipleObjects(BlocksCount, CodingThread, true, INFINITE);

    for (int i = 0; i < BlocksCount; i++)
    {
        CloseHandle(CodingThread[i]);
    }

    for (int i = 0; i < BlocksCount; i++)
    {
        unCryptedText += UnCryptedBlocks[i];
    }
    cout << "Расшифрованный текст: " << unCryptedText << endl;

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] != unCryptedText[i])
        {
            cout << "Дешифровка или кодирова не верная!";
        }
    }
}