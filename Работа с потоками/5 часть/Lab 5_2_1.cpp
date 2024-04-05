#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

void main()
{
	setlocale(LC_ALL, "RUS");

    bool end = false;
    int x;

    HANDLE Start, Event1, Event2, Event3, Event4, Event5, Event6, Next;

    Next = CreateEvent(NULL, true, true, (wchar_t*)"Next");
    Start = CreateEvent(NULL, true, false, (wchar_t*)"Start");
    Event1 = CreateEvent(NULL, true, false, (wchar_t*)"1");
    Event2 = CreateEvent(NULL, true, false, (wchar_t*)"2");
    Event3 = CreateEvent(NULL, true, false, (wchar_t*)"3");
    Event4 = CreateEvent(NULL, true, false, (wchar_t*)"4");
    Event5 = CreateEvent(NULL, true, false, (wchar_t*)"5");
    Event6 = CreateEvent(NULL, true, false, (wchar_t*)"6");

    while (end == false)
    {
        WaitForSingleObject(Next, INFINITE);

        cout << "Меню действий:" << endl;
        cout << "1.Перемножить 2 числа." << endl;
        cout << "2.Удалить повторяющиеся числа в массиве." << endl;
        cout << "3.Вывести самое часто встречающиеся слово в файле." << endl;
        cout << "4.Вывести минимальный и максимальный элементы квадратной матрицы." << endl;
        cout << "5.Вывести все простые числа от 0 до n." << endl;
        cout << "6.Закончить выполнение программы." << endl;
        cout << "Выбранный вариант: ";
        cin >> x;

        switch (x)
        {
        case 1:
            SetEvent(Event1);
            break;
        case 2:
            SetEvent(Event2);
            break;
        case 3:
            SetEvent(Event3);
            break;
        case 4:
            SetEvent(Event4);
            break;
        case 5:
            SetEvent(Event5);
            break;
        case 6:
            SetEvent(Event6);
            end = true;
            break;
        }
        ResetEvent(Next);
        cout << "Ожидание завершения 2 программы." << endl << endl;

        SetEvent(Start);
    }

    CloseHandle(Start);
    CloseHandle(Next);
}