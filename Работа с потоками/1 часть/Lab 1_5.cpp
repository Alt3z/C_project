#include <windows.h>
#include <iostream>
using namespace std;

int sum;

struct tree
{
    int data;
    tree* left;
    tree* right;
};

void print(tree* tr, int n)
{
    if (tr != NULL)
    {
        print(tr->right, n + 5);
        for (int i = 0; i <= n; i++)
        {
            printf(" ");
        } 
        printf("%d\n", tr->data);
        print(tr->left, n + 5);
    }
}

void add(int X, tree*& tr)//добавление элементов в дерево
{
    if (!tr) //если нет узла, то создаем
    {
        tr = new tree;
        (*tr).data = X;
        (*tr).left = NULL;
        (*tr).right = NULL;
    }
    else
    {
        if ((*tr).data > X)//если следующий элемент меньше предыдущего, то добавляем его в левое поддерево
        {
            add(X, (*tr).left);
        }    
        else //иначе в правое
        {
            add(X, (*tr).right);
        }
    }
}

DWORD WINAPI summa(LPVOID param) //функция для подсчета суммы элементов дерева
{
    tree* tr = (tree*)param;
    if (!tr) return 0; //нет ветки
    if (tr->left)
    {
        HANDLE RootThreadLeft;
        RootThreadLeft = CreateThread(NULL, 0, summa, tr->left, 0, NULL);
        if (RootThreadLeft == NULL)
        {
            cout << "Поток № " << "не был создан\n" << "Ошибка " << GetLastError();
        }
        WaitForSingleObject(RootThreadLeft, INFINITE);
        CloseHandle(RootThreadLeft);
    }
    if (tr->right)
    {
        HANDLE RootThreadRight;
        RootThreadRight = CreateThread(NULL, 0, summa, tr->right, 0, NULL);
        if (RootThreadRight == NULL)
        {
            cout << "Поток № " << "не был создан\n" << "Ошибка " << GetLastError();
        }
        WaitForSingleObject(RootThreadRight, INFINITE);
        CloseHandle(RootThreadRight);
    }
    sum += (*tr).data;

    return 0;
}

void generate_root(tree* tr, int n)
{ 
    srand(time(NULL) + GetCurrentThreadId());

    tree* root = NULL;
    tr = new tree;

    (*tr).data = rand() % 10;
    (*tr).left = NULL;
    (*tr).right = NULL;
    root = tr;

    for (int i = 1; i < n; i++)//создание дерева
    {
        (*tr).data = rand() % 10;
        add((*tr).data, root);
    }
    
    cout << endl << endl;
    print(root, 0);
    cout << endl;

    HANDLE RootThread;
    RootThread = CreateThread(NULL, 0, summa, root, 0, NULL);
    if (RootThread == NULL)
    {
        cout << "Поток № " << "не был создан\n" << "Ошибка " << GetLastError();
    }
    WaitForSingleObject(RootThread, INFINITE);
    CloseHandle(RootThread);
}

void main()
{
    setlocale(LC_ALL, "RUS");

    tree* root = NULL;

    int n;
    cout << "Введи кол-во элементов дерева: ";
    cin >> n;

    generate_root(root, n);

    cout << endl;
    cout << "Сумма: " << sum << endl;
    cout << "Среднее значение: " << sum / n << endl;
}