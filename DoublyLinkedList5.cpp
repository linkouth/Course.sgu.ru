#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct list {				// Ñòðóêòóðà äâóõñâÿíîãî ñïèñêà
	int inf;				// Èíôîðìàöèîííîå ïîëå
	list *prev;				// Ïîëå ñ ññûëêîé íà ïðåäûäóùèé ýëåìåíò
	list *next;				// Ïîëå ñ ññûëêîé íà ñëåäóþùèé ýëåìåíò
};

void push(list *&h, list *&t, int x) {		//âñòàâêà ýëåìåíòà â êîíåö ñïèñêà
	list *r = new list;						//ñîçäàåì íîâûé ýëåìåíò
	r->inf = x;
	r->next = NULL;							//âñåãäà ïîñëåäíèé
	if (!h && !t) {							//åñëè ñïèñîê ïóñò
		r->prev = NULL;						//ïåðâûé ýëåìåíò
		h = r;								//ýòî ãîëîâà

	}
	else {
		t->next = r;						//r - ñëåäóþùèé äëÿ õâîñòà
		t->prev = t;						//õâîñò - ïðåäûäóùèé äëÿ r
	}
	t = r;									//r òåïåðü õâîñò
}

void print(list *h, list *t) {				//ïå÷àòü ýëåìåíòîâ ñïèñêà
	list *p = h;							//óêçàòåëü íà ãîëîâó
	while (p) {								//ïîêà íå äîøëè äî êîíöà ñïèñêà
		cout << p->inf << ' ';				
		p = p->next;						//ïåðåõîä ê ñëåäóþùåìó ýëåìåíòó
	}
}

list *find(list *h, list *t, int x) {		//ïîèñê ýëåìåíòà ñïèñêà
	list *p = h;							//óêçàòåëü íà ãîëîâó
	while (p) {								//ïîêà íå äîøëè äî êîíöà ñïèñêà
		if (p->inf == x)					// åñëè íàøëè, ïðåêðàùàåì öèêë
			break;
		p = p->next;						//ïåðåõîä ê ñëåäóþùåìó ýëåìåíòó
	}

	return p;								//âîçâðàùàåì óêàçàòåëü
}

void insert_after(list *&h, list *&t, list *r, int x) {			//âñòàâêà ïîñëå r
	list *p = new list;											//ñîçäàåì íîâûé ýëåìåíò
	p->inf = x;

	if (r == t) {												//åñëè âñòàâëÿåì ïîñëå õâîñòà
		p->next = NULL;											//âñòàâëÿåìûé ýë-ò - ïîñëåäíèé
		p->prev = r;											//âñòàâëÿåì ïîñëå r
		r->next = p;
		t = p;													//òåïåðü õâîñò - p
	}
	else {														//âñòàâëÿåì â ñåðåäèíó ñïèñêà
		r->next->prev = p;										//äëÿ ñëåäóþùåãî çà r ýë-òà ïðåäûäóùèé - p
		p->next = r->next;										//ñëåäóþùèé çà p - ñëåäóþùèé çà r
		p->prev = r;											//p âñòàâëÿåì ïîñëå r
		r->next = p;
	}
}

void del_node(list *&h, list *&t, list *r) {					//óäàëÿåì ïîñëå r
	if (r == h && t == r)										//åäèíñòâåííûé ýëåìåíò ñïèñêà
		h = t = NULL;
	else if (r == h) {											//óäàëÿåì ãîëîâó ñïèñêà		
		h = h->next;											//ñäâèãàåì ãîëîâó
		h->prev = NULL;
	}
	else if (r == t) {											//óäàëÿåì õâîñò ñïèñêà
		t = t->prev;											//ñäâèãàåì õâîñò
		t->next = NULL;
	} 
	else {
		r->next->prev = r->prev;								//äëÿ ñëåäóþùåãî îò r ïðåäûäóùèì
		r->prev->next = r->next;								//äëÿ ïðåäûäóùåãî îò r ñëåäóþùèì
	}
	delete r;													//óäàëÿåì r
}

void del_list(list *&h, list *&t) {								//óäàëÿåì ñïèñîê
	while (h) {													//ïîêà ñïèñîê íå ïóñò
		list *p = h;											//óêàçàòåëü íà ãîëîâó
		h = h->next;											//ïåðåíîñèì ãîëîâó
		h->prev = NULL;											//îáíóëÿåì
		delete p;												//óäàëÿåì p
	}
}

void handler(list *&h, list *&t, int x) {						//ôóíêöèÿ-îáðàáîò÷èê
	list *p = h;												//óêçàòåëü íà ãîëîâó
	while (p) {													//ïîêà íå äîøëè äî êîíöà ñïèñêà
		if (p->inf / 1000 == 0 && p->inf / 100 > 0) {			//åñëè ÷èñëî òðåõçíà÷íîå, òî âñòàâëÿåì íîâûé ýëåìåíò
			insert_after(h, t, p, x);
		}
		p = p->next;											//ïåðåõîä ê ñëåäóþùåìó ýëåìåíòó
	}
}

int main() {
	cout << "Enter your numbers: ";
	string input; getline(cin, input);							//ñ÷èòûâàåì ÷èñëà
	stringstream str(input);

	list *head = NULL;											//îáúÿâëÿåì ñïèñîê
	list *tail = NULL;

	string snumber;												//äîáàâëÿåì ÷èñëà â ñïèñîê
	while (str >> snumber) {
		int number = stoi(snumber);
		push(head, tail, number);
	}

	cout << "Enter your number to insert: ";					//ââîäèì ÷èñëî äëÿ âñòàâêè
	int x; cin >> x;
	//print(head, tail);											//âûâîäèì ñïèñîê

	handler(head, tail, x);										//îáðàáîòêà ñïèñêà

	print(head, tail);											//âûâîäèì èçìåíåííûé ñïèñîê
	cout << "\nSuccess!\n";
	system("pause");
	return 0;
}


	


