#include <iostream>
#include <windows.h>

using namespace std;

float summa = 0;
const int n = 10;
const int m = 10;
const float a = 0, b = 10;

CRITICAL_SECTION cs;

struct Node 
{
    int number_n;
    int number_m;
    float size_block;
    float size_thread;
};

DWORD WINAPI Sum(LPVOID param)
{
    Node* pcol_num = (Node*)param;
    Node mas = *pcol_num;

    float StartX = (mas.number_n * mas.size_block) + (mas.number_m * mas.size_thread) + a;
    float EndX = (mas.number_n * mas.size_block) + (mas.number_m * mas.size_thread) + a + mas.size_thread;

    int height = 4;
    float StartY = StartX + height;
    float EndY = EndX + height;

    float max = EndY;
    if (StartY > EndY)
    {
        max = StartY;
    }

    EnterCriticalSection(&cs);
    summa += max * mas.size_thread;
    LeaveCriticalSection(&cs);

    return 0;
}

int main()
{
    setlocale(LC_ALL, "RUS");

    
    HANDLE hThread[m];
    DWORD dwThreadID[m];

    InitializeCriticalSection(&cs);

    float size = b - a; //длина отрезка
    float size_block = size / (float)n; // длина кусков отрезока
    float size_thread = size_block / (float)m;

    Node* mas { new Node[m * n] };

    for (int i = 0; i < m; i++) 
    {
        mas[i].number_m = i;
        mas[i].size_block = size_block;
        mas[i].size_thread = size_thread;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            mas[j].number_n = i;
            hThread[j] = CreateThread(NULL, 0, Sum, &(mas[j]), 0, &(dwThreadID[j]));

            if (hThread[j] == NULL)
            {
                cout << "Поток № " << i << "не был создан\n" << "Ошибка " << GetLastError();
            }
        }

        WaitForMultipleObjects(m, hThread, true, INFINITE);
    }

    for (int i = 0; i < m; i++) // закрываем потоки
    {
        CloseHandle(hThread[i]);
    }

    cout <<"Площадь: " << summa << endl;
}