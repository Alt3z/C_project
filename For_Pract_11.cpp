#include <iostream>
#include <string>

using namespace std;

void main()
{
    setlocale(LC_ALL, "RUS");
    
    cout << "Введите строку: "; // а роза упала на лапу азора
    
    string str;
    str = "";
    getline(cin, str);
    cout << endl;
    
    
    //1 способ
    
    cout << "Первый способ:" << endl; 
    int d = str.length();
    int r = 0; 
    for (int i = 0; i < d; i++)
    {
        if (str[i] == ' ')
        {
            if (str[i + 1] == ' ')
            {
                break;
            }
            else
            {
                r++;
            }
        }
    }
    cout << "Кол-во слов = " << (r = r + 1)<<endl<<endl;


    //2 способ
    
    cout << "Второй способ:" << endl;
    int j = 0,j1=0, r1 = 0; // j - позиция пробела
    while (j >= 0)
    {
        j = str.find(" ", 0);
        j1== str.find(" ", j);
        if (j != j1)
        {
            r1++;
            str.erase(0, j + 1);
        }
        else
        {
            break;
        }
    }
    cout << "Кол-во слов = " << r1<<endl<<endl;

    
    //палиндром

    string s;
    s = "";
    cout << "Введите строку на проверку палиндрома: "; 
    getline(cin, s);

    while (s.find(" ", 0) != string::npos) //удалем пробелы
    {
        s.erase(s.find(" ", 0), 1);
    }

    int len = s.length();

    for (int i = 0; i < len / 2; i++)
    {
        if (s[i] != s[len - i - 1])
        {
            cout << "Не палиндром";
            return;
        }
    }
    cout << "Палиндром";


    //while (str.find(" ", 0) != string::npos) //удалем пробелы
    //{
    //    str.erase(str.find(" ", 0), 1);
    //}

    //int len = str.length();

    //for (int i = 0; i < len / 2; i++)
    //{
    //    if (str[i] != str[len - i - 1])
    //    {
    //        cout << "Не палиндром";
    //        return;
    //    }
    //}
    //cout << "Палиндром";
}

//Введите строку : иду на поляну
//
//Первый способ :
//Кол - во слов = 3
//
//Второй способ :
//Кол - во слов = 3
//
//Введите строку на проверку палиндрома : а роза упала на лапу азора
//Палиндром


//Введите строку : подсчет слов
//
//Первый способ :
//Кол - во слов = 2
//
//Второй способ :
//Кол - во слов = 2
//
//Введите строку на проверку палиндрома : иди иду
//Не палиндром