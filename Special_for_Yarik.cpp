#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
	vector< list<int> > graph = {						// ãðàô
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

	vector<int> result(graph.size());					// ðåçóëüòàò
	
	for (size_t i = 0; i < graph.size(); ++i) {			// ñòåïåíü ïîëóèñõîäà
		result[i] = graph[i].size();
	}

	for (size_t i = 0; i < result.size(); ++i) {		// âûâîä ðåçóëüòàòà
		cout << i << " : " << result[i] << endl;
	}
	
	system("pause");
	return 0;
}
