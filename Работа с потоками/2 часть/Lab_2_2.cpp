#include <iostream>
#include <windows.h>

using namespace std;

int n = 0;
int k = 5;
string text = "asdhfgjk jsdhf kskskjdwerf";
//float summa = 0;
float* sum = new float[k];

CRITICAL_SECTION cs;

DWORD WINAPI FillingMatrixRows(LPVOID param) // функция для заполнения строк матрицы
{
    int* pNumberOfCol = (int*)param;
    int NumberOfThread = *pNumberOfCol;

    int s = 0;
    int NubmerOfChar = NumberOfThread + k * s;
    while (NubmerOfChar<text.length())
    {
        EnterCriticalSection(&cs);
        //summa += int(text[NubmerOfChar]);
        sum[NumberOfThread] += int(text[NubmerOfChar]);
        LeaveCriticalSection(&cs);

        s++;
        NubmerOfChar = NumberOfThread + k * s;
    }

    return 0;
}


void main()
{
    setlocale(LC_ALL, "RUS");

    n = text.length();
    while (k >= n)
    {
        k--;
    }

    int* number = new int[k];
    for (int i = 0; i < k; i++)
    {
        number[i] = i;
    }

    for (int i = 0; i < k; i++)
    {
        sum[i] = 0;
    }

    HANDLE* FillingThread = new HANDLE[k];
    DWORD* FillingThreadID = new DWORD[k];

    InitializeCriticalSection(&cs);


    for (int i = 0; i < k; i++) // запуск потоков для заполнения строк
    {
        FillingThread[i] = CreateThread(NULL, 0, FillingMatrixRows, &(number[i]), 0, &(FillingThreadID[i]));
        //FillingThread[i] = CreateThread(атрибуты безопасности по умолчанию, размер стека по умолчанию,имя функции, указатель на параметры, флаг создания = 0, адрес переменной для идентификатора)

        if (FillingThread[i] == NULL) // Проверям - создан ли поток
        {
            cout << "Поток №" << i << "не был создан\n" << "Ошибка: " << GetLastError();
        }
    }

    WaitForMultipleObjects(k, FillingThread, true, INFINITE); // Ожидаем завершения потоков

    for (int i = 0; i < k; i++) // закрываем потоки
    {
        CloseHandle(FillingThread[i]);
    }

    //cout << endl << "Сумма элементов: " << summa/256 << endl;

    float g=0;
    for (int i = 0; i < k; i++)
    {
        if (sum[i] != INT_MAX)
        {
            g += sum[i];
        }
    }
    cout << "Сумма элементов по модулю 256: " << g/256 << endl;
    DeleteCriticalSection(&cs);
}