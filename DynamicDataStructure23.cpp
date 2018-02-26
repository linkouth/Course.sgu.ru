#include <iostream>
#include <string>

using namespace std;

struct queue {
	int inf;
	queue* next;
};

void push(queue *&h, queue *&t, int x) {
	queue *r = new queue;
	r->inf = x;
	r->next = NULL;
	if (!h && !t) {
		h = t = r;
	}
	else {
		t->next = r;
		t = r;
	}
}

int pop(queue *&h, queue *&t) {
	int i = h->inf;
	queue *r = h;
	h = h->next;
	if (!h) {
		t = NULL;
	}
	delete r;
	return i;
}

int main() {
	cout << "Enter N = ";
	int N; cin >> N;

	int** Gr = new int* [N + 1];
	for (int i = 0; i < N + 1; i++) {
		Gr[i] = new int[N];
	}

	cout << "Fill the matrix : \n";
	for (int i = 0; i < N + 1; i++, cout << '\n') {
		for (int j = 0; j < N + 1; j++) {
			cout << "Gr[" << i << "][" << j << "] = ";
			cin >> Gr[i][j];
		}
	}

	cout << "Enter x = ";
	int x; cin >> x;

	queue *h = NULL;
	queue *t = NULL;

	int* A = new int[N + 1];
	for (int i = 0; i < N + 1; i++) {
		A[i] = 0;
	}

	A[x] = 1;

	push(h, t, x);

	cout << x << ' ';

	while (h) {
		x = pop(h, t);
		for (int i = 0; i < N + 1; i++) {
			if (A[i] == 0 && Gr[x][i] == 1) {
				int y = i;
				A[y] = 1;
				push(h, t, y);
				cout << y << ' ';
			}
		}
	}

	/*for (int i = 0; i < N + 1; i++, cout << '\n')
		for (int j = 0; j < N + 1; j++) {
			cout << Gr[i][j] << " ";
		}*/

	system("pause");
	return 0;
}
