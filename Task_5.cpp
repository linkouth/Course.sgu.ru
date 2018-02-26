#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct list {				// ��������� ����������� ������
	int inf;				// �������������� ����
	list *prev;				// ���� � ������� �� ���������� �������
	list *next;				// ���� � ������� �� ��������� �������
};

void push(list *&h, list *&t, int x) {		//������� �������� � ����� ������
	list *r = new list;						//������� ����� �������
	r->inf = x;
	r->next = NULL;							//������ ���������
	if (!h && !t) {							//���� ������ ����
		r->prev = NULL;						//������ �������
		h = r;								//��� ������
	}
	else {
		t->next = r;						//r - ��������� ��� ������
		t->prev = t;						//����� - ���������� ��� r
	}
	t = r;									//r ������ �����
}

void print(list *h, list *t) {				//������ ��������� ������
	list *p = h;							//�������� �� ������
	while (p) {								//���� �� ����� �� ����� ������
		cout << p->inf << ' ';				
		p = p->next;						//������� � ���������� ��������
	}
}

list *find(list *h, list *t, int x) {		//����� �������� ������
	list *p = h;							//�������� �� ������
	while (p) {								//���� �� ����� �� ����� ������
		if (p->inf == x)					// ���� �����, ���������� ����
			break;
		p = p->next;						//������� � ���������� ��������
	}

	return p;								//���������� ���������
}

void insert_after(list *&h, list *&t, list *r, int x) {			//������� ����� r
	list *p = new list;											//������� ����� �������
	p->inf = x;

	if (r == t) {												//���� ��������� ����� ������
		p->next = NULL;											//����������� ��-� - ���������
		p->prev = r;											//��������� ����� r
		r->next = p;
		t = p;													//������ ����� - p
	}
	else {														//��������� � �������� ������
		r->next->prev = p;										//��� ���������� �� r ��-�� ���������� - p
		p->next = r->next;										//��������� �� p - ��������� �� r
		p->prev = r;											//p ��������� ����� r
		r->next = p;
	}
}

void del_node(list *&h, list *&t, list *r) {					//������� ����� r
	if (r == h && t == r)										//������������ ������� ������
		h = t = NULL;
	else if (r == h) {											//������� ������ ������		
		h = h->next;											//�������� ������
		h->prev = NULL;
	}
	else if (r == t) {											//������� ����� ������
		t = t->prev;											//�������� �����
		t->next = NULL;
	} 
	else {
		r->next->prev = r->prev;								//��� ���������� �� r ����������
		r->prev->next = r->next;								//��� ����������� �� r ���������
	}
	delete r;													//������� r
}

void del_list(list *&h, list *&t) {								//������� ������
	while (h) {													//���� ������ �� ����
		list *p = h;											//��������� �� ������
		h = h->next;											//��������� ������
		h->prev = NULL;											//��������
		delete p;												//������� p
	}
}

void handler(list *&h, list *&t, int x) {						//�������-����������
	list *p = h;												//�������� �� ������
	while (p) {													//���� �� ����� �� ����� ������
		if (p->inf / 1000 == 0 && p->inf / 100 > 0) {			//���� ����� �����������, �� ��������� ����� �������
			insert_after(h, t, p, x);
		}
		p = p->next;											//������� � ���������� ��������
	}
}

int main() {
	cout << "Enter your numbers: ";
	string input; getline(cin, input);							//��������� �����
	stringstream str(input);

	list *head = NULL;											//��������� ������
	list *tail = NULL;

	string snumber;												//��������� ����� � ������
	while (str >> snumber) {
		int number = stoi(snumber);
		push(head, tail, number);
	}

	cout << "Enter your number to insert: ";					//������ ����� ��� �������
	int x; cin >> x;
	//print(head, tail);											//������� ������

	handler(head, tail, x);										//��������� ������

	print(head, tail);											//������� ���������� ������
	cout << "\nSuccess!\n";
	system("pause");
	return 0;
}


	

