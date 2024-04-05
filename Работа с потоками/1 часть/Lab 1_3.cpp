#include <iostream>
#include <windows.h>
//#include <map>
//#include <sstream>
//#include <string>

using namespace std;

const int n = 4, m = 8;
int matrix[n][m];// изначальная матрица

HANDLE FillingThread[n];// -- массив из n указателей потоков
DWORD FillingThreadID[n];// -- массив из n идентификаторов потоков
int СountForFilling = 0;


DWORD WINAPI FillingMatrixRows(LPVOID param) // функция для заполнения строк матрицы
{
    srand(time(NULL) + FillingThreadID[::СountForFilling]);

    int* pNumberOfCol = (int*)param;
    int NumberOfCol = *pNumberOfCol;
    for (int i = 0; i < m; i++)
    {
        matrix[NumberOfCol][i] = rand() % 10;
    }
    ::СountForFilling++;
    return 0;
}

int x; // множитель

DWORD WINAPI Multiply(LPVOID param) // функция для умножения строк матрицы на множитель
{
    int* pNumberOfCol = (int*)param;
    int NumberOfCol = *pNumberOfCol;

    for (int i = 0; i < m; i++)
    {
        matrix[NumberOfCol][i] *= x;
    }

    return 0;
}

void main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    int col_number[n];
    for (int i = 0; i < n; i++)
    {
        col_number[i] = i;
    }

    for (int i = 0; i < n; i++) // запуск потоков для заполнения строк
    {
        FillingThread[i] = CreateThread(NULL, 0, FillingMatrixRows, &(col_number[i]), 0, &(FillingThreadID[i]));
        //FillingThread[i] = CreateThread(атрибуты безопасности по умолчанию, размер стека по умолчанию,имя функции, указатель на параметры, флаг создания = 0, адрес переменной для идентификатора)

        if (FillingThread[i] == NULL) // Проверям - создан ли поток
        {
            cout << "Поток для заполнения№" << i << "не был создан\n" << "Ошибка: " << GetLastError();
        }
    }

    WaitForMultipleObjects(n, FillingThread, true, INFINITE); // Ожидаем завершения потоков

    for (int i = 0; i < n; i++) // закрываем потоки
    {
        CloseHandle(FillingThread[i]);
    }

    cout << "Исходная матрица: " << endl;
    for (int i = 0; i < n; i++) // выводим матрицу потоки
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    int x1;
    cout << endl << "Введите множитель, на который необходимо умножить матрицу: ";
    cin >> x1;
    ::x = x1;

    HANDLE MultiplyThread[n];// -- массив из n указателей потоков
    DWORD MultiplyThreadID[n];// -- массив из n идентификаторов потоков

    for (int i = 0; i < n; i++) // запуск потоков для умножения строк на множитель
    {
        MultiplyThread[i] = CreateThread(NULL, 0, Multiply, &(col_number[i]), 0, &(MultiplyThreadID[i]));

        if (MultiplyThread[i] == NULL) // Проверям - создан ли поток
        {
            cout << "Поток умножения №" << i << "не был создан\n" << "Ошибка: " << GetLastError();
        }
    }

    WaitForMultipleObjects(n, MultiplyThread, true, INFINITE); // Ожидаем завершения потоков

    for (int i = 0; i < n; i++) // закрываем потоки
    {
        CloseHandle(MultiplyThread[i]);
    }

    cout << endl << "Матрица после умножения на множитель "<< x << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}