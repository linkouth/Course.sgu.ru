#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct list {				// Структура двухсвяного списка
	int inf;				// Информационное поле
	list *prev;				// Поле с ссылкой на предыдущий элемент
	list *next;				// Поле с ссылкой на следующий элемент
};

void push(list *&h, list *&t, int x) {		//вставка элемента в конец списка
	list *r = new list;						//создаем новый элемент
	r->inf = x;
	r->next = NULL;							//всегда последний
	if (!h && !t) {							//если список пуст
		r->prev = NULL;						//первый элемент
		h = r;								//это голова
	}
	else {
		t->next = r;						//r - следующий для хвоста
		t->prev = t;						//хвост - предыдущий для r
	}
	t = r;									//r теперь хвост
}

void print(list *h, list *t) {				//печать элементов списка
	list *p = h;							//укзатель на голову
	while (p) {								//пока не дошли до конца списка
		cout << p->inf << ' ';				
		p = p->next;						//переход к следующему элементу
	}
}

list *find(list *h, list *t, int x) {		//поиск элемента списка
	list *p = h;							//укзатель на голову
	while (p) {								//пока не дошли до конца списка
		if (p->inf == x)					// если нашли, прекращаем цикл
			break;
		p = p->next;						//переход к следующему элементу
	}

	return p;								//возвращаем указатель
}

void insert_after(list *&h, list *&t, list *r, int x) {			//вставка после r
	list *p = new list;											//создаем новый элемент
	p->inf = x;

	if (r == t) {												//если вставляем после хвоста
		p->next = NULL;											//вставляемый эл-т - последний
		p->prev = r;											//вставляем после r
		r->next = p;
		t = p;													//теперь хвост - p
	}
	else {														//вставляем в середину списка
		r->next->prev = p;										//для следующего за r эл-та предыдущий - p
		p->next = r->next;										//следующий за p - следующий за r
		p->prev = r;											//p вставляем после r
		r->next = p;
	}
}

void del_node(list *&h, list *&t, list *r) {					//удаляем после r
	if (r == h && t == r)										//единственный элемент списка
		h = t = NULL;
	else if (r == h) {											//удаляем голову списка		
		h = h->next;											//сдвигаем голову
		h->prev = NULL;
	}
	else if (r == t) {											//удаляем хвост списка
		t = t->prev;											//сдвигаем хвост
		t->next = NULL;
	} 
	else {
		r->next->prev = r->prev;								//для следующего от r предыдущим
		r->prev->next = r->next;								//для предыдущего от r следующим
	}
	delete r;													//удаляем r
}

void del_list(list *&h, list *&t) {								//удаляем список
	while (h) {													//пока список не пуст
		list *p = h;											//указатель на голову
		h = h->next;											//переносим голову
		h->prev = NULL;											//обнуляем
		delete p;												//удаляем p
	}
}

void handler(list *&h, list *&t, int x) {						//функция-обработчик
	list *p = h;												//укзатель на голову
	while (p) {													//пока не дошли до конца списка
		if (p->inf / 1000 == 0 && p->inf / 100 > 0) {			//если число трехзначное, то вставляем новый элемент
			insert_after(h, t, p, x);
		}
		p = p->next;											//переход к следующему элементу
	}
}

int main() {
	cout << "Enter your numbers: ";
	string input; getline(cin, input);							//считываем числа
	stringstream str(input);

	list *head = NULL;											//объявляем список
	list *tail = NULL;

	string snumber;												//добавляем числа в список
	while (str >> snumber) {
		int number = stoi(snumber);
		push(head, tail, number);
	}

	cout << "Enter your number to insert: ";					//вводим число для вставки
	int x; cin >> x;
	//print(head, tail);											//выводим список

	handler(head, tail, x);										//обработка списка

	print(head, tail);											//выводим измененный список
	cout << "\nSuccess!\n";
	system("pause");
	return 0;
}


	

