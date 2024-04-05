#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

HANDLE hMutexReady,	// Мьютекс "умножение"
hMutex;		// Мьютекс доступа к переменной

int n;
int* vec1 = new int[n];
int* vec2 = new int[n];
int* vec3 = new int[n];


DWORD WINAPI Multipl(LPVOID param)
{
	int* pNumberOfCol = (int*)param;
	int NumberOfCol = *pNumberOfCol;

	WaitForSingleObject(hMutexReady, INFINITE); // Захватить мьютекс
	WaitForSingleObject(hMutex, INFINITE);// Обратиться к критической секции и сгенерировать выражение

	vec3[NumberOfCol] = vec1[NumberOfCol] * vec2[NumberOfCol];

	ReleaseMutex(hMutex);// Освободить критическую секцию
	ReleaseMutex(hMutexReady);// Освободить мьютекс "информация обработана"

	return 0;
}

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");

	hMutexReady = CreateMutex(NULL, false, NULL);// Создаем мьютексы со значениями по умолчанию
	hMutex = CreateMutex(NULL, false, NULL); // все мьютексы созданы в состоянии "открыт"

	cout << "Ведите количество значений векторов: ";
	cin >> n;
	cout << "Введите элементы 1 вектора:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> vec1[i];
	}
	cout << endl << "Введите элементы 2 вектора:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> vec2[i];
	}

	int* col_number = new int[n];
	for (int i = 0; i < n; i++)
	{
		col_number[i] = i;
	}

	HANDLE* thread = new HANDLE[n];
	for (int i = 0; i < n; i++)
	{
		thread[i] = CreateThread(NULL, 0, Multipl, &col_number[i], 0, NULL);
	}

	WaitForMultipleObjects(n, thread, true, INFINITE);

	for (int i = 0; i < n; i++)
	{
		CloseHandle(thread[i]);
	}

	cout << endl << "3 вектор: ";
	for (int i = 0; i < n; i++)
	{
		cout << vec3[i] << " ";
	}
}