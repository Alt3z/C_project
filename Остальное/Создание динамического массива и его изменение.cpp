#include <iostream>

using namespace std;

void main()
{
	setlocale(LC_ALL, "RUS");
	double *MAS;
	int n;
	cout << "Введите количество элементов массива = ";
	cin >> n;
	MAS = new double[n];
	int count = 0;
	cout << "MAS = ";
	for (int i = 0; i < n-1; i++)
	{
		MAS[i] = rand()%10;
		cout <<MAS[i] << " ";
	}
	cout << endl;
	int min = MAS[0];
	int poz=0;
	for (int j = 0; j < n-1; j++)
	{
		if (MAS[j] <= min)
		{
			count += 1;
			min = MAS[j];
			poz = j;
		}
	}
	for (int i = n-1; i != poz-1; i--)
	{
		MAS[i+1] = MAS[i];
	}
	int k8;
	cout << "Введите новое значение = ";
	cin >> k8;
	MAS[poz] = k8;
	cout << "Измененный массив = ";
	for (int z = 0; z < n; z++)
	{
		cout << MAS[z]<<" ";
	}
}

//Введите количество элементов массива = 7
//MAS = 1 7 4 0 9 4
//Введите новое значение = 11
//Измененный массив = 1 7 4 11 0 9 4
