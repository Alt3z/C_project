#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <map>

using namespace std;

HANDLE Start, Event1, Event2, Event3, Event4, Event5, Event6, Next;

bool endProg = false;
bool end1 = false;
int all = 0;

DWORD WINAPI One(LPVOID param)
{
    WaitForSingleObject(Event1, INFINITE);
    if (end1 == false)
    {
        float x1, x2;
        cout << "Введите 2 числа для умножения: " << endl;
        cin >> x1;
        cin >> x2;
        float x3 = x1 * x2;
        cout <<"Произведение: " << x3 << endl << endl;

        end1 = true;
    }
    all++;
    ResetEvent(Event1);

    if (all != 6)
    {
        SetEvent(Event2);
    }

    return 0;
}

DWORD WINAPI Two(LPVOID param)
{
    WaitForSingleObject(Event2, INFINITE);
    if (end1 == false)
    {
        ifstream F1;
        F1.open("float mas in.txt");

        float x;
        float mas[100];
        int count = 0;
        while (F1 >> x)
        {
            mas[count] = x;
            count++;
        }
        F1.close();

        int n = count;
        for (int i = 0; i < n; i++) 
        {
            for (int j = i + 1; j < n;) 
            {
                if (mas[i] == mas[j]) 
                {
                    for (int k = j; k < n - 1; k++) 
                    {
                        mas[k] = mas[k + 1];
                    }
                    n--;
                }
                else 
                {
                    j++;
                }
            }
        }

        ofstream F2;
        F2.open("float mas out.txt");

        for (int i = 0; i < n; i++)
        {
            F2 << mas[i];
            F2 << " ";
        }
        F2.close();

        cout << "Массив записан" << endl << endl;
        end1 = true;
    }
    all++;
    ResetEvent(Event2);

    if (all != 6)
    {
        SetEvent(Event3);
    }

    return 0;
}

DWORD WINAPI Three(LPVOID param)
{
    WaitForSingleObject(Event3, INFINITE);
    if (end1 == false)
    {
        ifstream file;
        file.open("Text for 3 task.txt");

        map<string, int> wordCount; // создание словаря для подсчета слов

        string word;
        while (file >> word) 
        {
            // Исключаем пунктуацию и переводим слова в нижний регистр
            for (char& c : word) 
            {
                if (ispunct(c))
                    c = ' ';
                else
                    c = tolower(c);
            }

            // Обновляем счетчик для каждого слова
            if (!word.empty())
                wordCount[word]++;
        }
        file.close();

        // Находим самое часто встречающееся слово и его количество вхождений
        string mostCommonWord;
        int maxCount = 0;

        for (const auto& pair : wordCount) 
        {
            if (pair.second > maxCount) 
            {
                mostCommonWord = pair.first;
                maxCount = pair.second;
            }
        }

        // Выводим результаты
        cout << "Самое часто встречающееся слово: " << mostCommonWord << endl;
        cout << "Количество вхождений: " << maxCount << endl<<endl;
        
        end1 = true;
    }
    all++;
    ResetEvent(Event3);

    if (all != 6)
    {
        SetEvent(Event4);
    }

    return 0;
}

DWORD WINAPI Four(LPVOID param)
{
    WaitForSingleObject(Event4, INFINITE);
    if (end1 == false)
    {
        srand(time(NULL));

        int n;
        cout << "Введите размерность матрицы: ";
        cin >> n;

        int** matrix = new int* [n];
        for (int i = 0; i < n; i++) 
        {
            matrix[i] = new int[n];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) 
            {
                matrix[i][j] = rand() % 10;
            }
        }

        cout << "Исходная матрица: " << endl;
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        int minElement = matrix[1][0]; // минимальный элемент ниже главной диагонали
        int maxElement = matrix[0][0]; // максимальный элемент выше побочной диагонали

        for (int i = 1; i < n; i++) 
        {
            for (int j = 0; j < i; j++) 
            {
                if (matrix[i][j] < minElement) 
                {
                    minElement = matrix[i][j];
                }
            }
        }

        int count = n;
        for (int i = 0; i < n - 1; i++) 
        {
            for (int j = 0; j < count-1; j++) 
            {
                if (matrix[i][j] > maxElement) 
                {
                    maxElement = matrix[i][j];
                }
            }
            count--;
        }

        cout << "Минимальный элемент ниже главной диагонали: " << minElement << endl;
        cout << "Максимальный элемент выше побочной диагонали: " << maxElement << endl << endl;

        end1 = true;
    }
    all++;
    ResetEvent(Event4);

    if (all != 6)
    {
        SetEvent(Event5);
    }

    return 0;
}

DWORD WINAPI Five(LPVOID param)
{
    WaitForSingleObject(Event5, INFINITE);
    if (end1 == false)
    {
        int n;
        cout << "Введите число n: ";
        cin >> n;
        cout << "Простые числа от 0 до " << n << ": ";

        bool* isPrime = new bool[n];
        for (int i = 0; i <= n; i++) 
        {
            isPrime[i] = true;
        }

        for (int p = 2; p * p <= n; p++) 
        {
            // Если текущее число p простое, то помечаем все его кратные как непростые
            if (isPrime[p] == true) 
            {
                for (int i = p * p; i <= n; i += p)
                    isPrime[i] = false;
            }
        }

        // Выводим все простые числа
        for (int p = 2; p <= n; p++) 
        {
            if (isPrime[p])
                cout << p << " ";
        }
        cout << endl << endl;

        end1 = true;
    }
    all++;
    ResetEvent(Event5);

    if (all != 6)
    {
        SetEvent(Event6);
    }

    return 0;
}

DWORD WINAPI Six(LPVOID param)
{
    WaitForSingleObject(Event6, INFINITE);
    if (end1 == false)
    {
        endProg = true;
        end1 = true;
    }
    all++;
    ResetEvent(Event6);

    if (all != 6)
    {
        SetEvent(Event1);
    }

    return 0;
}

void main()
{
    setlocale(LC_ALL, "RUS");

    Start = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"Start");
    if (Start == NULL)
    {
        cout << "Ожидание запуска программы с меню." << endl;
        while (Start == NULL)
        {
            Start = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"Start");
            Sleep(100);
        }
    }
    Next = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"Next");

    Event1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"1");
    Event2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"2");
    Event3 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"3");
    Event4 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"4");
    Event5 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"5");
    Event6 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (wchar_t*)"6");

    HANDLE thread[6];
    int number;

    while (endProg == false)
    {
        cout << "Ожидание выбора действия в программе с меню." << endl;
        WaitForSingleObject(Start, INFINITE);

        thread[0] = CreateThread(NULL, 0, One, NULL, 0, NULL);
        thread[1] = CreateThread(NULL, 0, Two, NULL, 0, NULL);
        thread[2] = CreateThread(NULL, 0, Three, NULL, 0, NULL);
        thread[3] = CreateThread(NULL, 0, Four, NULL, 0, NULL);
        thread[4] = CreateThread(NULL, 0, Five, NULL, 0, NULL);
        thread[5] = CreateThread(NULL, 0, Six, NULL, 0, NULL);

        WaitForMultipleObjects(6, thread, true, INFINITE);

        end1 = false;
        all = 0;

        ResetEvent(Start);
        
        SetEvent(Next);
    }

    for (int i = 0; i < 6; i++)
    {
        CloseHandle(thread[i]);
    }
}