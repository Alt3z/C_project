#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int n = 6; // объем пула печати
string s;
string sD;

char* pull = new char[n]; // пул печати
char* pull2 = new char[n]; // пул печати
int cur_pos; // Текущая позиция записи в пул
int cur_s_pos; // Текущая позиция в тексте
int cur_pos2; // Текущая позиция записи в пул
int cur_s_pos2; // Текущая позиция в тексте

HANDLE SemFull, SemEmpty, SemFull2, Mutex;
HANDLE SemFullD, SemEmptyD, SemFull2D, MutexD;


int n2;

DWORD WINAPI coding(LPVOID param)
{
    int* pcol_num = (int*)param;
    int k = *pcol_num;

    WaitForSingleObject(SemFull, INFINITE);
    WaitForSingleObject(Mutex, INFINITE);

    for (int i = 0; i < k; i++)
    {
        int poz = i;

        if (pull[poz] != '`' && pull[poz] != ' ')
        {
            int x;

            if (int(pull[poz]) >= 97 || 122 <= int(pull[poz]))
            {
                x = (int(pull[poz]) - 32);
                pull[poz] = char(x);
            }
            else if (int(pull[poz]) >= 65 || 90 <= int(pull[poz]))
            {
                x = (int(pull[poz]) + 32);
                pull[poz] = char(x);
            }

            if (int(pull[poz]) != 90 && int(pull[poz]) != 122)
            {
                x = (int(pull[poz]) + 1);
                pull[poz] = char(x);
            }
            else
            {
                if (int(pull[poz]) == 90)
                {
                    x = 65;
                    pull[poz] = char(x);
                }
                else
                {
                    x = 97;
                    pull[poz] = char(x);
                }
            }
        }
    }
    ReleaseMutex(Mutex);
    ReleaseSemaphore(SemFull2, 1, NULL);

    return 0;
}

DWORD WINAPI ReadText1(LPVOID param)
{
    int k = n;

    for (int i = 0; i < n2; i++)
    {
        WaitForSingleObject(SemEmpty, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);

        if (i == n2 - 1)
        {
            if (s.length() % n != 0)
            {
                k = s.length() % n;
            }
        }
        for (int j = 0; j < k; j++)
        {
            pull[j] = s[cur_s_pos];
            cur_s_pos++;
        }

        ReleaseMutex(Mutex);
        ReleaseSemaphore(SemFull, 1, NULL);

    }

    return 0;
}

DWORD WINAPI WriteCodingTextFromPull(LPVOID param)
{
    int k = n;
    ofstream File("output.txt");

    for (int i = 0; i < n2; i++)
    {
        WaitForSingleObject(SemFull2, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);

        if (i == n2 - 1)
        {
            if (s.length() % n != 0)
            {
                k = s.length() % n;
            }
        }
        for (int j = 0; j < k; j++)
        {
            File << pull[j];
        }

        cur_pos = 0;
        ReleaseMutex(Mutex);
        ReleaseSemaphore(SemEmpty, 1, NULL);

    }
    File.close();

    return 0;
}

DWORD WINAPI ReadText2(LPVOID param)
{
    int k = n;

    for (int i = 0; i < n2; i++)
    {
        WaitForSingleObject(SemEmptyD, INFINITE);
        WaitForSingleObject(MutexD, INFINITE);

        if (i == n2 - 1)
        {
            if (sD.length() % n != 0)
            {
                k = sD.length() % n;
            }
        }
        for (int j = 0; j < k; j++)
        {
            pull2[j] = sD[cur_s_pos2];
            cur_s_pos2++;
        }

        ReleaseMutex(MutexD);
        ReleaseSemaphore(SemFullD, 1, NULL);

    }

    return 0;
}

DWORD WINAPI DecodingText(LPVOID param)
{
    int* pcol_num = (int*)param;
    int k = *pcol_num;

    WaitForSingleObject(SemFullD, INFINITE);
    WaitForSingleObject(MutexD, INFINITE);

    for (int i = 0; i < k; i++)
    {
        int poz = i;

        if (pull2[poz] != '`' && pull2[poz] != ' ')
        {
            int x;

            if (int(pull2[poz]) != 65 && int(pull2[poz]) != 97)
            {
                x = (int(pull2[poz]) - 1);
                pull2[poz] = char(x);
            }
            else
            {
                if (int(pull2[poz]) == 65)
                {
                    x = 90;
                    pull2[poz] = char(x);
                }
                else
                {
                    x = 122;
                    pull2[poz] = char(x);
                }
            }

            if (int(pull2[poz]) >= 97 || 122 <= int(pull2[poz]))
            {
                x = (int(pull2[poz]) - 32);
                pull2[poz] = char(x);
            }
            else if (int(pull2[poz]) >= 65 || 90 <= int(pull2[poz]))
            {
                x = (int(pull2[poz]) + 32);
                pull2[poz] = char(x);
            }
        }
    }
    ReleaseMutex(MutexD);
    ReleaseSemaphore(SemFull2D, 1, NULL);

    return 0;
}

DWORD WINAPI WriteCodingTextFromPull2(LPVOID param)
{
    int k = n;
    ofstream File("output2.txt");

    for (int i = 0; i < n2; i++)
    {
        WaitForSingleObject(SemFull2D, INFINITE);
        WaitForSingleObject(MutexD, INFINITE);

        if (i == n2 - 1)
        {
            if (sD.length() % n != 0)
            {
                k = sD.length() % n;
            }
        }
        for (int j = 0; j < k; j++)
        {
            File << pull2[j];
        }

        cur_pos2 = 0;
        ReleaseMutex(MutexD);
        ReleaseSemaphore(SemEmptyD, 1, NULL);

    }
    File.close();

    return 0;
}



void main()
{
    setlocale(LC_ALL, "RUS");

    cur_pos = 0;
    cur_s_pos = 0;

    ifstream Fin("in.txt");
    string s1;
    while (getline(Fin, s1))
    {
        s += s1;
    }
    Fin.close();

    for (int i = 0; i < n; i++)
    {
        pull[i] = '`';
    }


    HANDLE ReadFromFile;
    HANDLE* Coding = new HANDLE[n];
    HANDLE WriteCodingText;

    SemEmpty = CreateSemaphore(NULL, 1, 1, NULL);
    SemFull = CreateSemaphore(NULL, 0, 1, NULL);
    SemFull2 = CreateSemaphore(NULL, 0, 1, NULL);
    Mutex = CreateMutex(NULL, false, NULL);

    n2 = s.length() / n;
    if (s.length() % n != 0)
    {
        n2 += 1;
        //poz[n-1] = s.length() % n;
    }
    int* poz = new int[n2];
    for (int i = 0; i < n2; i++)
    {
        poz[i] = n;
        if (i == n2 - 1)
        {
            if (s.length() % n != 0)
            {
                poz[i] = s.length() % n;
            }
        }
    }

    ReadFromFile = CreateThread(NULL, 0, ReadText1, NULL, 0, NULL);
    for (int i = 0; i < n2; i++)
    {
        Coding[i] = CreateThread(NULL, 0, coding, &poz[i], 0, NULL);
    }
    WriteCodingText = CreateThread(NULL, 0, WriteCodingTextFromPull, NULL, 0, NULL);

    WaitForSingleObject(ReadFromFile, INFINITE);
    WaitForMultipleObjects(n2, Coding, true, INFINITE);
    WaitForSingleObject(WriteCodingText, INFINITE);

    CloseHandle(ReadFromFile);
    for (int i = 0; i < n2; i++)
    {
        CloseHandle(Coding[i]);
    }
    CloseHandle(WriteCodingText);
    CloseHandle(SemFull);
    CloseHandle(SemFull2);
    CloseHandle(SemEmpty);
    CloseHandle(Mutex);

    /////////////////////////////////////////////////////////////////////// декодер ////////////////////////////

    cout << "Введите любое число, чтобы начать декодирование: ";
    int q;
    cin >> q;

    cur_pos2 = 0;
    cur_s_pos2 = 0;

    ifstream FileForDecoder("output.txt");
    string s2;
    while (getline(FileForDecoder, s2))
    {
        sD += s2;
    }
    Fin.close();

    for (int i = 0; i < n; i++)
    {
        pull2[i] = '`';
    }

    HANDLE ReadFromFile2;
    HANDLE* DeCoding = new HANDLE[n];
    HANDLE WriteCodingText2;

    SemEmptyD = CreateSemaphore(NULL, 1, 1, NULL);
    SemFullD = CreateSemaphore(NULL, 0, 1, NULL);
    SemFull2D = CreateSemaphore(NULL, 0, 1, NULL);
    MutexD = CreateMutex(NULL, false, NULL);

    n2 = sD.length() / n;
    if (sD.length() % n != 0)
    {
        n2 += 1;
    }

    int* poz2 = new int[n2];
    for (int i = 0; i < n2; i++)
    {
        poz2[i] = n;
        if (i == n2 - 1)
        {
            if (sD.length() % n != 0)
            {
                poz2[i] = sD.length() % n;
            }
        }
    }

    ReadFromFile2 = CreateThread(NULL, 0, ReadText2, NULL, 0, NULL);
    for (int i = 0; i < n2; i++)
    {
        DeCoding[i] = CreateThread(NULL, 0, DecodingText, &poz2[i], 0, NULL);
    }
    WriteCodingText2 = CreateThread(NULL, 0, WriteCodingTextFromPull2, NULL, 0, NULL);

    WaitForSingleObject(ReadFromFile2, INFINITE);
    WaitForMultipleObjects(n2, DeCoding, true, INFINITE);
    WaitForSingleObject(WriteCodingText2, INFINITE);

    CloseHandle(ReadFromFile2);
    for (int i = 0; i < n2; i++)
    {
        CloseHandle(DeCoding[i]);
    }
    CloseHandle(WriteCodingText2);
    CloseHandle(SemFullD);
    CloseHandle(SemFull2D);
    CloseHandle(SemEmptyD);
    CloseHandle(MutexD);
}