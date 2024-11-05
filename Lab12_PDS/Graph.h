#pragma once
#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

struct Edge {
	int to;
	int weight;
};

class Graph {
public:
	Graph(int n);
	void addEdge(int from, int to, int weight);
	void djikstra(int from, int to);
	vector<int> djikstra(int from);
	bool loadFromFile(const string& fileName);
	void printWeightMatrix();

	vector<vector<Edge>> adjList;
	void printShortestPath(int from, int to, const vector<int>& parent);
};

Graph::Graph(int n) : adjList(n) {	};

void Graph::addEdge(int from, int to, int weight) {
	adjList[from].push_back({ to, weight });
}

void Graph::djikstra(int from, int to) {
	int n = adjList.size();
	vector<int> dist(n, numeric_limits<int>::max());
	vector<int> parent(n, -1);
	dist[from] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, from });
	
	while (!pq.empty()) {
		int current_dist = pq.top().first;
		int u = pq.top().second;

		pq.pop();

		if (current_dist > dist[u])
			continue;

		for (const Edge& edge : adjList[u]) {
			int v = edge.to;
			int weight = edge.weight;

			if (dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				parent[v] = u;
				pq.push({ dist[v], v });
			}
		}
	}

	if (dist[to] == numeric_limits<int>::max()) {
		cout << "Шляху між вершинами " << (from + 1)
			<< " та " << (to + 1) << " не існує" << endl;
	}
	else {
		cout << "Найкоротша відстань між вершинами " << (from + 1)
			<< " та " << (to + 1) << " = " << dist[to] << endl;
		cout << "Шлях: ";
		printShortestPath(from, to, parent);
		cout << endl;
	}
}

vector<int> Graph::djikstra(int from) {
	int n = adjList.size();
	vector<int> dist(n, numeric_limits<int>::max());
	vector<int> parent(n, -1);
	dist[from] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, from });

	while (!pq.empty()) {
		int current_dist = pq.top().first;
		int u = pq.top().second;

		pq.pop();

		if (current_dist > dist[u])
			continue;

		for (const Edge& edge : adjList[u]) {
			int v = edge.to;
			int weight = edge.weight;

			if (dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				parent[v] = u;
				pq.push({ dist[v], v });
			}
		}
	}

	cout << "Найкоротші відстані від вершини " 
		<< (from + 1) << ":" << endl;

	for (int i = 0; i < n; i++) {
		if (dist[i] == numeric_limits<int>::max()) {
			cout << "Вершина " << (i + 1) << ": "
				<< "недосяжна" << endl;
		}
		else {
			cout << "Вершина " << (i + 1) << ": протяжність шляху "
				<< dist[i] << " [";
			printShortestPath(from, i, parent);
			cout << "]" << endl;
		}
	}
	
	return dist;
}

void Graph::printShortestPath(int from, int to, const vector<int>& parent) {
	stack<int> path;
	for (int v = to; v != -1; v = parent[v]) {
		path.push(v);
	}
	while (!path.empty()) {
		cout << (path.top() + 1);
		path.pop();
		if (!path.empty())
			cout << " -> ";;
	}
}

void Graph::printWeightMatrix() {
	cout << "Матриця ваг графа: " << endl;
	int n = adjList.size();

	vector<vector<int>> weightMatrix(n, vector<int>(n, numeric_limits<int>::max()));

	for (int i = 0; i < n; i++) {
		weightMatrix[i][i] = 0;
		for (const Edge& edge : adjList[i])
			weightMatrix[i][edge.to] = edge.weight;
	}

	for (int i = 0; i < n; i++) {
		cout << setw(0) << "Вершина " << i + 1 << ": ";
		for (int j = 0; j < n; j++) {
			if (weightMatrix[i][j] == numeric_limits<int>::max()) {
				cout << setw(10) << "INF";
			}
			else {
				cout << setw(10) << weightMatrix[i][j];
			}
		}
		cout << endl;
	}
}

bool Graph::loadFromFile(const string& fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cerr << "Не вдалося відкрити файл." << endl;
		return false;
	}

	int n, m;
	file >> n >> m;

	if (n <= 0 || m <= 0) {
		cerr << "Кількість вершин і ребер повинні бути більше нуля." << endl;
		return false;
	}

	adjList.resize(n);

	for (int i = 0; i < m; i++) {
		int from, to, weight;
		if (!(file >> from >> to >> weight)) {
			cerr << "Помилка при зчитуванні ребра." << endl;
			return false;
		}
		if (from < 1 || from > n || to < 1 || to > n) {
			cerr << "Помилка: невірні індекси ребра: "
				<< from << " -> " << to << endl;
			return false;
		}
		if (weight >= 0) {
			addEdge(from - 1, to - 1, weight);
		}
		else {
			cerr << "Від'ємна вага ребра: " << from
				<< " ->" << to << " зі значенням " << weight << endl;
			return false;
		}
	}

	file.close();
	return true;
}