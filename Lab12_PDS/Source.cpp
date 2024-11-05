#include"Graph.h"
#include<Windows.h>
#include<string>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filePath;
	cout << "Введіть шлях з назвою файлу графа: ";
	getline(cin, filePath);

	Graph graph(0);

	if (!graph.loadFromFile(filePath)) {
		cerr << "Помилка при зчитуванні графа з файлу." << endl;
		return 1;
	}
	graph.printWeightMatrix();

	unsigned int start, end;

	cout << "Пошук найкоротшої відстані з початкової до кінцевої вершини." << endl;
	cout << "Введіть початкову вершину: ";
	cin >> start;
	if (cin.fail()) {
		cout << "Початкова вершина неправильно введена." << endl;
		return -2;
	}

	cout << "Введіть кіцеву вершину: ";
	cin >> end;
	if (cin.fail()) {
		cout << "Кінцеву вершину неправильно введено." << endl;
		return -3;
	}

	if (start < 1 || start > graph.adjList.size()
		|| end < 1 || end > graph.adjList.size()
		) {
		cout << "Початкова або кінцева вершина для"
			<< "пошуку виходить за межі дозволених границь графу." << endl;
		return -4;
	}
	graph.djikstra(start - 1, end - 1);

	unsigned int startAll;

	cout << "Пошук найкоротшої відстані з початкової до всіх вершин." << endl;
	cout << "Введіть початкову вершину: ";
	cin >> startAll;
	if (cin.fail()) {
		cout << "Початкова вершина неправильно введена." << endl;
		return -5;
	}


	if (startAll < 1 || startAll > graph.adjList.size()) {
		cout << "Початкова вершина для"
			<< "пошуку виходить за межі дозволених границь графу." << endl;
		return -6;
	}
	graph.djikstra(startAll - 1);

	return false;
}