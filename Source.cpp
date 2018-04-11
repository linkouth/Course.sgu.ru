#include <iostream>
#include <list>
#include <vector>

using namespace std;

vector< list<int> > graph = {
	{ 1, 2, 5, 6 },
	{ 0 },
	{ 0 },
	{ 4, 5 },
	{ 3, 5, 6 },
	{ 0, 3, 4 },
	{ 0, 4 },
	{ 8 },{ 7 },
	{ 10, 11, 12 },
	{ 9 },
	{ 9, 12 },
	{ 9, 11 } };

vector<bool> used(graph.size());
vector <int> result;

void dfs(int v) {
	used[v] = true;
	for (auto l : graph[v]) {
		int to = l;
		if (!used[to]) {
			dfs(to);
		}
	}
	result.push_back(v);
}

void topologicalSort() {
	for (size_t i = 0; i < graph.size(); ++i) {
		used[i] = false;
	}
	result.clear();
	for (size_t i = 0; i < graph.size(); ++i) {
		if (!used[i]) {
			dfs(i);
		}
	}
	reverse(begin(result), end(result));
}

int main() {
	topologicalSort();
	for (auto v : result) {
		cout << v << ' ';
	}

	cout << endl;

	system("pause");
	return 0;
}