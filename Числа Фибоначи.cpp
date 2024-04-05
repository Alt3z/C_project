#include <iostream>
using namespace std;

int Fib(int n) //вызов функции для подсчета числа Фибоначчи
{
	int f = 1;
	if (n <= 2) //условие окончания функции
	{
		f = 1;
		return f;
	}
	else
	{
		f = Fib(n - 1) + Fib(n - 2); //формула для вычисления чила Фибоначчи
		return f;
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");
	int x, N,n=0,f(0);
	cout << "Количество чисел Фибоначчи  N = ";
	cin >> N;
	for (int i = 1; i < N + 1; i++) //цикл для вывода и подсчета цисел Фибоначчи
	{
		n += 1;
		x = Fib(n); //вызов функции
		cout << "f("<<i<<") = "<< x << endl;
	}
}

//Количество чисел Фибоначчи  N = 20
//f(1) = 1
//f(2) = 1
//f(3) = 2
//f(4) = 3
//f(5) = 5
//f(6) = 8
//f(7) = 13
//f(8) = 21
//f(9) = 34
//f(10) = 55
//f(11) = 89
//f(12) = 144
//f(13) = 233
//f(14) = 377
//f(15) = 610
//f(16) = 987
//f(17) = 1597
//f(18) = 2584
//f(19) = 4181
//f(20) = 6765


//1.2

//#include <iostream>
//using namespace std;
//
//int fn;
//
//int Fib(int n) //вызов функции для подсчета числа Фибоначчи
//{
//	fn++; //увеличение чилса вызовов
//	if (n == 0) return 0; //ограничитель функции
//	if (n == 1) return 1; //ограничитель функции
//	cout << "f(" << n - 1 << ") и f(" << n - 2 << ")" << endl;
//	return Fib(n - 1) + Fib(n - 2); //формула вычисления чилса Фибоначчи
//}
//
//void main()
//{
//	setlocale(LC_ALL, "RUS");
//	int x, N,n=0,f(0);
//	cout << "Количество чисел Фибоначчи  N = ";
//	cin >> N;
//	for (int i = 1; i < N + 1; i++) //цикл для вывода и подсчета цисел Фибоначчи
//	{
//		fn = 0;
//		n += 1;
//		x = Fib(n); //вызов функции
//		cout << "f(" << i << ")=" << x << endl;
//		cout << "Количество вызовов функции = " << fn << endl << endl;
//	}
//}

//Количество чисел Фибоначчи  N = 6
//f(1) = 1
//Количество вызовов функции = 1
//
//f(1) и f(0)
//f(2) = 1
//Количество вызовов функции = 3
//
//f(2) и f(1)
//f(1) и f(0)
//f(3) = 2
//Количество вызовов функции = 5
//
//f(3) и f(2)
//f(2) и f(1)
//f(1) и f(0)
//f(1) и f(0)
//f(4) = 3
//Количество вызовов функции = 9
//
//f(4) и f(3)
//f(3) и f(2)
//f(2) и f(1)
//f(1) и f(0)
//f(1) и f(0)
//f(2) и f(1)
//f(1) и f(0)
//f(5) = 5
//Количество вызовов функции = 15
//
//f(5) и f(4)
//f(4) и f(3)
//f(3) и f(2)
//f(2) и f(1)
//f(1) и f(0)
//f(1) и f(0)
//f(2) и f(1)
//f(1) и f(0)
//f(3) и f(2)
//f(2) и f(1)
//f(1) и f(0)
//f(1) и f(0)
//f(6) = 8
//Количество вызовов функции = 25

//2.1

//#include <iostream>
//using namespace std;
//
//int fn; //счетчик вызова функции
//
//int Combin1(int N, int K) //функция для подсчета N по K
//{
//    fn += 1; //увеличиваем счетчик вызова функции
//    if (K == 0 || K == N) // условие, при котором функция заканчивает работу
//    {
//        return 1;
//    }
//    else
//    {
//        return Combin1(N - 1, K) + Combin1(N - 1, K - 1); // формула для вычисления
//    }
//}
//
//void main() //основная функция
//{
//    setlocale(LC_ALL,"RUS");
//    int N, K;
//    fn = 0;
//    cout << "Введите N>0 = ";
//    cin >> N;
//    cout << "Введите  0<=K<=" << N << " = ";
//    cin >> K;
//    int Combin = Combin1(N, K); //вызов функции
//    cout << "Результат работы Функции = " << Combin << endl << "Количество вызовов функции = " << fn;
//}

//Введите N > 0 = 15
//Введите  0 <= K <= 15 = 5
//Результат работы Функции = 3003
//Количество вызовов функции = 6005

//Введите N > 0 = 5
//Введите  0 <= K <= 5 = 2
//Результат работы Функции = 10
//Количество вызовов функции = 19

//Введите N > 0 = 7
//Введите  0 <= K <= 7 = 1
//Результат работы Функции = 7
//Количество вызовов функции = 13
