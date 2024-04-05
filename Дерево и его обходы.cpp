#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

void ZapolnFile()
{
	ofstream f;
	f.open("input.txt");

	for (int i = 0; i < 50; i++)
	{
		int x = rand() % 100;
		f << x << endl;
	}
	f.close();
}

struct tree
{
	int D; //Поле данных
	tree* Left; //УКАЗАТЕЛЬ на левую ветку
	tree* Right; //УКАЗАТЕЛЬ на правую ветку
};
tree* tr;
tree* pnew;

void nRoot(tree*& Root, int x) // инициализация корня дерева
{
	Root = new tree;
	(*Root).D = x;
	(*Root).Left = NULL;
	(*Root).Right = NULL;
}

void Del_Tree(tree* tr) // удаление дерева
{
	if (!tr) // Вершины нет
	{
		return;
	}
	Del_Tree((*tr).Left); // обход потомка - левое поддерево
	Del_Tree((*tr).Right); // обход потомка - правое поддерево
	delete tr;
	return;
}

void Print_BinaryTree(tree* tr, int l) // функция для вывода дерева в консоль
{
	int i;
	if (tr != NULL)
	{
		Print_BinaryTree((*tr).Right, l + 1);
		for (i = 0; i < l; i++)
		{
			cout << "    ";
		}
		cout << "     " << (*tr).D;
		Print_BinaryTree((*tr).Left, l + 1);
	}
	else
	{
		cout << endl;
	}
}

void Straight(tree* tr) //Прямой обход; указатель на корень дерева или поддерева, обход которого производится 

{
	if (!tr)
	{
		return; //Если отсутствует ветка дерева, то выходим из функции 

	}// ЕСЛИ присутствует ветка дерева, то:
	cout << (*tr).D << " "; //Вывод данных этой ветки	
	Straight((*tr).Left); //поддерево слева
	Straight((*tr).Right);//поддерево  справа
	return;
}

void Back(tree* tr) // Обратный обход
{
	if (!tr)
	{
		return;
	}
	Back((*tr).Left);
	Back((*tr).Right);
	cout << (*tr).D << " ";
}

void Symytr(tree* tr)  // симметричный обход
{
	if (!tr)
	{
		return;
	}
	Symytr((*tr).Left);
	cout << (*tr).D << " ";
	Symytr((*tr).Right);
}

tree* search_insert(tree* Root, int x) // метод поиска с включением
{
	tree* pv = Root;
	tree* prev = NULL;
	bool f = 0;//Переменная отвечающая за то что нашли  элемент или нет
	while (pv && (f == 0))
	{
		prev = pv; //получаем адрес элемента от которого строим дерево
		if (x == (*pv).D)
		{
			f = 1;
		}
		else
		{
			if (x < (*pv).D)  pv = (*pv).Left;
			else pv = (*pv).Right;
		}
		//Выход из цикла осуществляется, тогда когда нашли свободный адрес : ссылку для вставки нового узла 
	}

	/*Если совпало значение элемента со значением элемента который хотим вставить то выходим из функции, возвращая адрес элемента с которым совпало значение */
	bool on = true;
	if (f == 1)
	{
		if (on == true)
		{
			cout << "Элемент: " << x << " не будет включен" << endl;
		}
		return pv;
	}
	//Создание нового узла
	pnew = new tree;
	(*pnew).D = x;
	(*pnew).Left = 0;
	(*pnew).Right = 0;

	if (x < (*prev).D)//Присоединение к левому поддереву предка
	{
		(*prev).Left = pnew;
	}
	else//присоединяем к правому поддереву предка
	{
		(*prev).Right = pnew;
	}
	if (on == true)
	{
		cout << "Элемент: " << x << " будет включен" << endl;
	}

	return pnew;
}


void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	//ZapolnFile();

	int n = 10;
	cout << "Количество элементов: ";
	cin >> n;
	cout << endl;

	tree* Root = NULL;

	int x;
	ifstream f;
	f.open("input.txt");
	f >> x;
	cout << "Корень: " << x << endl;
	nRoot(Root, x);

	for (int i = 0; i < n - 1; i++)
	{
		f >> x;
		search_insert(Root, x); // вызываем метод поиска с включением
	}

	cout << "Дерево: " << endl;
	Print_BinaryTree(Root, 0); // вызываем функцию для вывода дерева
	cout << endl;

	cout << "Прямой обход: ";
	Straight(Root);
	cout << endl;

	cout << "Обратный обход: ";
	Back(Root);
	cout << endl;

	cout << "Симметричный обход: ";
	Symytr(Root);
	cout << endl << endl;

	Del_Tree(Root);
	f.close();
}
