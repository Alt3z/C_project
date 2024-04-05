#include <iostream> // библиотека для ввода/вывода
#include <fstream> // библиотека для записи в файл
#include <vector> // библиотека для использования векторов
#include <queue> // библиотека для использования очередей
#include <ctime> // библиотека для замера времени
#include <string> // библиотека для использования строк

using namespace std;

void main()
{
    int time; //время выполнения программы

    setlocale(LC_ALL, "RUS");

    ifstream f;
    f.open("input.txt");

    string s;
    int strok = -2, k, p, count=0;
    bool strok1 = true;
    while (getline(f, s))
    {
        k = s.length();
        p = 0;
        count = 0;
        while (p < k)
        {
            if (s[p] != ' ' && (s[p + 1] == ' ' || s[p + 1] == '\0'))
            {
                count++;
            }
            p++;
        }
        if (strok == -2)
        {
            if (count != 2)
            {
                strok1 = false;
            }
        }
        if (count != 0 && (count == 3 || count == 2))
        {
            strok++;
        }
    }
    if (count != 2)
    {
        strok1 = false;
    }

    f.close();

    f.open("input.txt");

    int n, m; //m - кол-во вершин, n - кол-во ребер
    f >> m;
    f >> n;
    cout << "Количисечество вершин: " << m << endl << "Количисечество ребер: " << n << endl;

    if (strok == n && strok1 == true)
    {
        vector<vector<int>>matrsmej(m, vector<int>(m, 0)); //создаем двумерный вектор matrsmej и заполняем его 0
        bool negative = false;
        int a, b, c; // a - откуда идем, b-куда идем, c-длина
        for (int i = 0; i < n; i++) // заполняем вектор из файла
        {
            f >> a;
            f >> b;
            f >> c;
            if (c <= 0)
            {
                negative = true;
            }
            matrsmej[a - 1][b - 1] = matrsmej[b - 1][a - 1] = c; // показывает, что по ребру можно двигаться в обе стороны и задает длину ребра (получается матрица смежности)
        }

        if (negative == false)
        {
            int vSTART, vEND;
            f >> vSTART;
            f >> vEND;

            f.close();

            bool* visite = new bool[m]; // указывает, была ли посещена вершина
            int* dist = new int[m]; //будет показывать дистанцию (например, от вершины 1 до вершины 3)

            for (int i = 0; i < m; i++) // заполняем оба массива
            {
                if (i == vSTART - 1)
                {
                    dist[i] = 0;
                    visite[i] = true;
                }
                else
                {
                    dist[i] = INT_MAX; // значения INT_MAX, так как изначально всем вершинам присваивается бесконечность
                    visite[i] = false; // значения false, так как мы не посещали вершины
                }
            }

            queue<int>o; // инициализируем очередь o
            o.push(vSTART); // изначальную вершину добавляем в очередь

            while (!o.empty()) // пока очередь не опустеет, то:
            {
                int ver = o.front() - 1; // присваиваем переменной вершину из очереди
                o.pop();//удаляем эту вершину из очереди

                for (int j = 0; j < m; j++) // проходим по всем вершинам
                {
                    if (visite[j] == 0 && matrsmej[ver][j] && matrsmej[ver][j] + dist[ver] < dist[j]) // 1.если вершина не посещена 2.У вершины есть ребра 3.если дистанция меньше чем была
                    {
                        dist[j] = matrsmej[ver][j] + dist[ver];//обновляем дистанцию
                        o.push(j + 1);//добавляем эту вершину в очередь
                    }
                }
            }

            int* way = new int[m];
            way[0] = vEND; // начальный элемент - конечная вершина
            int end = vEND - 1; // индекс конечной вершины
            int IND = 1; // индекс предыдущей вершины
            int weight = dist[end]; // вес конечной вершины

            while (end != vSTART - 1) // пока не дошли до начальной вершины
            {
                for (int i = 0; i < m; i++) // просматриваем все вершины
                {
                    if (matrsmej[i][end] != 0)   // если связь, то:
                    {
                        int temp = weight - matrsmej[i][end]; // определяем вес пути из предыдущей вершины
                        if (temp == dist[i]) // если вес равен тому, который был найден раннее, то значит из найденной вершины мы пришли в итоговую
                        {
                            weight = temp; // сохраняем новый вес
                            end = i;       // сохраняем предыдущую вершину
                            way[IND] = i + 1; // и записываем ее в массив
                            IND++;
                        }
                    }
                }
            }

            cout << endl << "Путь из вершины " << vSTART << " в вершину " << vEND << " равен = " << dist[vEND - 1] << endl;

            ofstream file;
            file.open("output.txt");

            file << dist[vEND - 1] << endl;

            cout << endl << "Путь: ";
            for (int i = m - 1; i >= 0; i--)
            {
                if (way[i] > 0 && way[i] < n + 1)
                {
                    cout << way[i] << " ";
                    if (i != 0)
                    {
                        file << way[i] << " ";
                    }
                    else
                    {
                        file << way[i];
                    }
                }
            }

            file.close();

            time = clock();
            cout << endl << endl << "Время выполнения: " << time << "мс" << endl;
        }
        else
        {
            cout << "Некоректный ввод";
        }
    }
    else
    {
        cout << "Некоректный ввод";
    }
}