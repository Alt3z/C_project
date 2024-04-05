#include <iostream>
#include <windows.h>

using namespace std;

const int m = 10, n = 20;
float mtx[n][m];   	 // изначальная матрица

float col_sums[n];    // массив сумм
int col_numbers[n]; // номера столбцов


HANDLE FillingThread[n];// -- массив из n указателей потоков
DWORD FillingThreadID[n];// -- массив из n идентификаторов потоков
int count = 0;


DWORD WINAPI col_sum(LPVOID param) // Функция потока для подсчета суммы
{
    int* pcol_num = (int*)param;// Получаем значение параметра - номер столбца
    int col_num = *pcol_num;

    col_sums[col_num] = 0; // Находим искомую сумму
    for (int i = 0; i < n; i++)
    {
        col_sums[col_num] += (mtx[i][col_num]);
    }

    return 0;
}

DWORD WINAPI FillingMatrixRows(LPVOID param) // функция для заполнения строк матрицы
{
    srand(time(NULL) + FillingThreadID[::count]);

    int* pNumberOfCol = (int*)param;
    int NumberOfCol = *pNumberOfCol;
    for (int i = 0; i < m; i++)
    {
        mtx[NumberOfCol][i] = rand() % 21 + rand() % 100 * 0.01;
    }
    ::count++;
    return 0;
}


void main()
{
    srand(time(NULL));
    setlocale(LC_ALL,"RUS");

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
            cout << "Поток №" << i << "не был создан\n" << "Ошибка: " << GetLastError();
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
            cout << mtx[i][j] << " ";
        }
        cout << endl;
    }


    HANDLE hThread[n];
    DWORD dwThreadID[n];

    
    for (int i = 0; i < n; i++)
    {
        col_sums[i] = 0;
        col_numbers[i] = i;
    }

    
    for (int i = 0; i < n; i++) //Запуск потоков для подсчета суммы
    {
        hThread[i] = CreateThread(NULL, 0, col_sum, &(col_numbers[i]), 0, &(dwThreadID[i]));

        if (hThread[i] == NULL)// Проверям - создан ли поток
        {
            cout << "Поток № " << i << "не был создан\n" << "Ошибка " << GetLastError();
        }
    }

    WaitForMultipleObjects(n, hThread, true, INFINITE);

    // Находим номер столбца с минимальной суммой
    int num_min = 0;
    float min = col_sums[0];

    for (int i = 1; i < n; i++)
    {
        if (min > col_sums[i])
        {
            min = col_sums[i];
            num_min = i;
        }
    }

    // Вывод результата
    cout << endl <<"Столбец с минимальной суммой: " << num_min << endl;

    
    for (int i = 0; i < n; i++)
    {
        CloseHandle(hThread[i]);
    }
}