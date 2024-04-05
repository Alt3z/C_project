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
		cout << "Ожидание окончания записи в файл... (ожидание открытия мьютекса)" << endl;
	}

	WaitForSingleObject(hMutexOUT, INFINITE); // Захватить мьютекс

	ifstream out;          // поток для записи
	out.open("D:\\7 трим\\VS\\OS defend\\Lab_3_2\\Lab_3_2\\out.txt");      // открываем файл для записи
	if (out.is_open())
	{
		out >> s;
		out.close();
		cout << "Cтрока из файла: " << s << endl;
	}
	else
	{
		cout << "Файла не существет " << s;
	}

	ReleaseMutex(hMutexOUT);// Освободить мьютекс "информация обработана"

	return 0;
}

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");

	hMutexOUT = OpenMutex(MUTEX_ALL_ACCESS, FALSE, (wchar_t*)"MutexForFile"); // открываем мьютекс
	if (hMutexOUT == NULL)
	{
		//cout << "Ошибка открытия мьютекса!" << endl;
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