#include"Graph.h"
#include<Windows.h>
#include<string>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filePath;
	cout << "������ ���� � ������ ����� �����: ";
	getline(cin, filePath);

	Graph graph(0);

	if (!graph.loadFromFile(filePath)) {
		cerr << "������� ��� ��������� ����� � �����." << endl;
		return 1;
	}
	graph.printWeightMatrix();

	unsigned int start, end;

	cout << "����� ���������� ������ � ��������� �� ������ �������." << endl;
	cout << "������ ��������� �������: ";
	cin >> start;
	if (cin.fail()) {
		cout << "��������� ������� ����������� �������." << endl;
		return -2;
	}

	cout << "������ ����� �������: ";
	cin >> end;
	if (cin.fail()) {
		cout << "ʳ����� ������� ����������� �������." << endl;
		return -3;
	}

	if (start < 1 || start > graph.adjList.size()
		|| end < 1 || end > graph.adjList.size()
		) {
		cout << "��������� ��� ������ ������� ���"
			<< "������ �������� �� ��� ���������� ������� �����." << endl;
		return -4;
	}
	graph.djikstra(start - 1, end - 1);

	unsigned int startAll;

	cout << "����� ���������� ������ � ��������� �� ��� ������." << endl;
	cout << "������ ��������� �������: ";
	cin >> startAll;
	if (cin.fail()) {
		cout << "��������� ������� ����������� �������." << endl;
		return -5;
	}


	if (startAll < 1 || startAll > graph.adjList.size()) {
		cout << "��������� ������� ���"
			<< "������ �������� �� ��� ���������� ������� �����." << endl;
		return -6;
	}
	graph.djikstra(startAll - 1);

	return false;
}