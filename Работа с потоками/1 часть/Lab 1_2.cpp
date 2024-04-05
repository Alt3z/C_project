#include <iostream>
#include <windows.h>
#include <map>
#include <sstream>
//#include <string>

using namespace std;

const int n = 4, m = 8;
float matrix[n][m];// изначальная матрица

HANDLE FillingThread[n];// -- массив из n указателей потоков
DWORD FillingThreadID[n];// -- массив из n идентификаторов потоков
int count = 0;


DWORD WINAPI FillingMatrixRows(LPVOID param) // функция для заполнения строк матрицы
{
    srand(time(NULL) + FillingThreadID[::count]);

    int* pNumberOfCol = (int*)param;
    int NumberOfCol = *pNumberOfCol;
    for (int i = 0; i < m; i++)
    {
        matrix[NumberOfCol][i] = rand() % 10 + rand() % 100 * 0.01;
    }
    ::count++;
    return 0;
}

DWORD WINAPI CountingSort(LPVOID param) // функция для сортировки строк матрицы методом подсчета
{
    int* pNumberOfCol = (int*)param;
    int NumberOfCol = *pNumberOfCol;

    map<string, unsigned> countt;

    for (int i = 0; i < m; i++) // Считаем слолько раз встретилось каждое значение
    {
        stringstream st;
        st << matrix[NumberOfCol][i];
        string s = st.str(); // получаем значение из массива и конвертируем в строку

        if (countt.count(s) != 1) // если значениея нет, то добавляем его
        {
            countt[s] = 1;
        }
        else // если есть, то увеличиваем счетчик вхождений
        {
            countt[s] += 1;
        }
    }

    int index = m-1;
    for (auto it = countt.begin(); it != countt.end(); ++it) // Создаем новый отсортированный массив
    {
        int x = (*it).second; // получаем количество вхождений
        for (int i = 0; i < x; i++)
        {
            string str = (*it).first; // конвертируем ключ в число и записываем в массив
            stringstream ss;
            ss << str;
            float result;
            ss >> result;

            matrix[NumberOfCol][index--] = result;
        }
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

    HANDLE CountingSortThread[n];// -- массив из n указателей потоков
    DWORD CountingSortThreadID[n];// -- массив из n идентификаторов потоков

    for (int i = 0; i < n; i++) // запуск потоков для сортировки строк
    {
        CountingSortThread[i] = CreateThread(NULL, 0, CountingSort, &(col_number[i]), 0, &(CountingSortThreadID[i]));
        //FillingThread[i] = CreateThread(атрибуты безопасности по умолчанию, размер стека по умолчанию,имя функции, указатель на параметры, флаг создания = 0, адрес переменной для идентификатора)

        if (CountingSortThreadID[i] == NULL) // Проверям - создан ли поток
        {
            cout << "Поток для сортировки №" << i << "не был создан\n" << "Ошибка: " << GetLastError();
        }
    }

    WaitForMultipleObjects(n, CountingSortThread, true, INFINITE); // Ожидаем завершения потоков

    for (int i = 0; i < n; i++) // закрываем потоки
    {
        CloseHandle(CountingSortThread[i]);
    }

    cout << endl << "Отсортированная матрица матрица по убыванию: " << endl;
    for (int i = 0; i < n; i++) // выводим матрицу
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}