#include <iostream>
#include <list>
#include <vector>

using namespace std;

vector< list<int> > graph = {
	{ 1 },			// a 0
	{ 2, 4, 5 },	// b 1
	{ 3, 6 },		// c 2
	{ 2, 7 },		// d 3
	{ 5, 0},		// e 4
	{ 6 },			// f 5
	{ 5 },			// g 6
	{ 3, 6 }		// h 7
};

vector< list <int> > TransGraph(const vector< list <int> >& graph) {
	vector< list <int> > result(graph.size());

	for (size_t i = 0; i < graph.size(); ++i) {
		for (const auto& el : graph[i]) {
			result[el].push_back(i);
		}
	}
}

vector< list <int> > graphTrans = TransGraph(graph);
vector<bool> used(graph.size());
vector <int> order, component;

void dfs(int v) {
	used[v] = true;
	for (auto l : graph[v]) {
		int to = l;
		if (!used[to]) {
			dfs(to);
		}
	}
	order.push_back(v);
}

void topologicalSort() {
	for (size_t i = 0; i < graph.size(); ++i) {
		used[i] = false;
	}
	order.clear();
	for (size_t i = 0; i < graph.size(); ++i) {
		if (!used[i]) {
			dfs(i);
		}
	}
	reverse(begin(order), end(order));
}

int i_element(const list<int>& lst, const int i) {
	int res, j = 0;
	
}

void dfs2(int v) {
	used[v] = true;
	component.push_back(v);
	for (auto i = begin(graphTrans[v]); i != end(graphTrans[v]); i++) {
		if (!used[graphTrans[v][i]])
			dfs2(graphTrans[v][i]);
	}
}

int main() {
	topologicalSort();

	used.assign(graph.size(), false);
	for (size_t i = 0; i < graph.size(); ++i) {
		int v = order[graph.size() - 1 - i];
		if (!used[v]) {

		}
	}


	cout << endl;

	system("pause");
	return 0;
}
