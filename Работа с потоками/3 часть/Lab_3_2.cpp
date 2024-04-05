#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

HANDLE hMutexOUT;

string s;

bool x = false;

DWORD WINAPI Writing(LPVOID param)
{
	if (x == false) 
	{
		cout << "Ожидание окончания чтения из файла... (ожидание открытия мьютекса)" << endl;
	}

	WaitForSingleObject(hMutexOUT, INFINITE); // Захватить мьютекс

	cout << "Введите строку для записи: ";
	getline(cin, s);

	ofstream out;          // поток для записи
	out.open("out.txt");      // открываем файл для записи
	if (out.is_open())
	{
		out << s;
	}
	cout <<endl<< "Строка записана."<<endl;
	out.close();

	ReleaseMutex(hMutexOUT); // Освободить мьютекс

	return 0;
}

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");

	hMutexOUT = OpenMutex(MUTEX_ALL_ACCESS, FALSE, (wchar_t*)"MutexForFile");
	if (hMutexOUT == NULL)
	{
		//cout << "Ошибка открытия мьютекса для записи!" << endl;

		x = true;
		hMutexOUT = CreateMutex(NULL, false, (wchar_t*)"MutexForFile"); // создаем мьютекс
		if (hMutexOUT == NULL)
		{
			cout << "Ошибка открытия мьютекса!" << endl;
		}
	}

	HANDLE thread = CreateThread(NULL, 0, Writing, NULL, 0, NULL);

	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
}