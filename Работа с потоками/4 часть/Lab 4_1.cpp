#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int n = 6; // объем пула печати

string* pull = new string[n]; // пул печати
int cur_pos = 0;
int cur_pos2 = 0;

HANDLE SemFull, SemEmpty, Mutex, control;

DWORD WINAPI inpull(LPVOID param)
{
    string* pcol_num = (string*)param;
    string s = *pcol_num;

    WaitForSingleObject(control, INFINITE);
    for (int i = 0; i < s.length(); i++)
    {
        // Дождаться освобождения ячеек
        WaitForSingleObject(SemEmpty, INFINITE);
        // Захватить критический ресурс и сформировать новую операцию
        WaitForSingleObject(Mutex, INFINITE);
        
        pull[cur_pos] = s[i]; // записать в пул
        cur_pos++;

        ReleaseMutex(Mutex);// Освободить критический ресурс
        if (cur_pos == n || i == s.length()-1)
        {
            cur_pos2 = 0;
            ReleaseSemaphore(SemFull, 1, NULL);
        }
    }
    ReleaseMutex(control);
    return 0;
}

DWORD WINAPI outpull(LPVOID param)
{
    while (true)
    {
        setlocale(LC_ALL, "RUS");
        ofstream Fout("out.txt", ios::app);
        WaitForSingleObject(SemFull, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);
        while (pull[cur_pos2] != "`" && cur_pos2!=n)
        {
            
            Fout << pull[cur_pos2]; // записать из пула в файл
            cout << pull[cur_pos2];

            pull[cur_pos2] = "`";
            cur_pos2 += 1;
            
            ReleaseSemaphore(SemEmpty, 1, NULL);
        }
        //cout << endl;
        cur_pos = 0;
        ReleaseMutex(Mutex);
        //Fout << " ";
        Fout.close();
    }
    return 0;
}

void main()
{
    setlocale(LC_ALL, "RUS");

    string s[5];

    ifstream Fin("in.txt");
    string s1;
    int CountLine = 0;
    while (getline(Fin, s1))
    {
        s[CountLine] = s1;
        CountLine += 1;
    }
    
    Fin.close();

    for (int i = 0; i < n; i++)
    {
        pull[i] = "`";
    }

    SemFull = CreateSemaphore(NULL, 0, 1, NULL); // семафор заполненных ячеек создаем закрытым
    SemEmpty = CreateSemaphore(NULL, n, n, NULL); // семафор пустых ячеек создаем открытым
    Mutex = CreateMutex(NULL, false, NULL);
    control = CreateMutex(NULL, false, NULL);

    HANDLE* InPull = new HANDLE[CountLine];
    HANDLE OutPull;

    for (int i=0;i<CountLine;i++)
    {
        InPull[i] = CreateThread(NULL, 0, inpull, &s[i], 0, NULL);
    }
    OutPull = CreateThread(NULL, 0, outpull, NULL, 0, NULL);

    WaitForMultipleObjects(CountLine, InPull, true, INFINITE);
    WaitForSingleObject(OutPull, INFINITE);

    for (int i = 0; i < CountLine; i++)
    {
        CloseHandle(InPull[i]);
    }

    CloseHandle(OutPull);
    CloseHandle(SemFull);
    CloseHandle(SemEmpty);
    CloseHandle(Mutex);
    CloseHandle(control);
}