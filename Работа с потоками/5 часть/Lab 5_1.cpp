#include <iostream>
#include <windows.h>

using namespace std;

int n;
int x;
double MaclorenSum;
double stepen;
double factorial;

HANDLE SumThread, SumEvent, StepEvent, FacEvent, mutex;

DWORD WINAPI Stepen(LPVOID param)
{
    int* pcol_num = (int*)param;
    int k = *pcol_num;

    WaitForSingleObject(StepEvent, INFINITE);
    WaitForSingleObject(mutex, INFINITE);

    stepen = x;
    for (int i = 0; i < k; i++)
    {
        stepen *= x;
    }

    ReleaseMutex(mutex);
    ResetEvent(StepEvent);

    SetEvent(FacEvent);

    return 0;
}

DWORD WINAPI Factorial(LPVOID param)
{
    int* pcol_num = (int*)param;
    int k = *pcol_num;

    WaitForSingleObject(FacEvent, INFINITE);
    WaitForSingleObject(mutex, INFINITE);

    factorial = 1;
    for (int i = 0; i < k; i++) 
    {
        factorial *= i+2;
    }

    ReleaseMutex(mutex);
    ResetEvent(FacEvent);

    SetEvent(SumEvent);

    return 0;
}

DWORD WINAPI Macloren(LPVOID param)
{
    int* m = new int[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        m[i] = i + 1;
    }

    MaclorenSum = 1 + x;

    HANDLE StepenThread;
    HANDLE FactorialThread;

    for (int i = 0; i < n-1; i++)
    {
        StepenThread = CreateThread(NULL, 0, Stepen, &(m[i]), 0, NULL);
        FactorialThread = CreateThread(NULL, 0, Factorial, &(m[i]), 0, NULL);

        WaitForSingleObject(StepenThread, INFINITE);
        WaitForSingleObject(FactorialThread, INFINITE);

        WaitForSingleObject(SumEvent, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        MaclorenSum += (stepen / factorial);

        ReleaseMutex(mutex);
        ResetEvent(SumEvent);

        SetEvent(StepEvent);
    }

    cout << "Сумма ряда: " << MaclorenSum << endl;

    return 0;
}

void main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");

    cout << "Введите кол-во элементов в ряду (не считая 1): ";
    cin >> n;

    cout << "Введите значение x: ";
    cin >> x;

    SumEvent = CreateEvent(NULL, true, false, NULL);
    StepEvent = CreateEvent(NULL, true, true, NULL);
    FacEvent = CreateEvent(NULL, true, false, NULL);
    mutex = CreateMutex(NULL, false, NULL);

    SumThread = CreateThread(NULL, 0, Macloren, NULL, 0, NULL);
    WaitForSingleObject(SumThread, INFINITE);
    CloseHandle(SumThread);

}