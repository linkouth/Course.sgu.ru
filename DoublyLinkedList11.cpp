#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct list {
	int inf;
	list *prev;
	list *next;
};

void push(list *&h, list *&t, int x) {		 //вставка элемента в конец списка
	list *r = new list;						 //создаем новый элемент
	r->inf = x;
	r->next = NULL;							 //всегда последний
	if (!h && !t) {							 //если список пуст
		r->prev = NULL;						 //первый элемент
		h = r;								 //это голова
	}
	else {									 
		t->next = r;						 //r - следующий для хвоста
		r->prev = t;						 //хвост - предыдущий для r
	}

	t = r;									 //r теперь хвост
}

void print(list *&h, list *&t) {			//печать элементов списка
	list *p = h;							//укзатель на голову
	while (p) {								//пока не дошли до конца списка
		cout << p->inf << ' ';
		p = p->next;						//переход к следующему элементу
	}
	delete p;
	cout << '\n';
}

list *find(list *&h, list *&t, int x) {		//печать элементов списка
	list *p = h;							//укзатель на голову
	while (p) {								//пока не дошли до конца списка
		if (p->inf == x)					// если нашли, прекращаем цикл
			break;
		p = p->next;						//переход к следующему элементу
	}
	
	return p;								//возвращаем указатель
}

void insert_after(list *&h, list *&t, list *r, int x) {		//вставляем после r
	list *p = new list;										//создаем новый элемент
	p->inf = x;
	if (r == t) {											//если вставляем после хвоста
		push(h, t, x);										//вставляемый эл-т - последний
	}										
	else {													//вставляем в середину списка
		r->next->prev = p;									//для следующего за r эл-та предыдущий - p
		p->next = r->next;									//следующий за p - следующий за r
		p->prev = r;										//p вставляем после r
		r->next = p;
	}
}

void delete_node(list *&h, list *&t, list *r) {				//удаляем после r
	if (r == h && r == t) {									//единственный элемент списка
		h = t = NULL;
	}
	else if (r == t) {										//удаляем хвост списка
		t = t->prev;										//сдвигаем хвост
		t->next = NULL;
	}
	else if (r == h) {										//удаляем голову списка
		h = h->next;										//сдвигаем голову
		h->prev = NULL;
	}
	else {
		r->next->prev = r->prev;							//для следующего от r предыдущим
		r->prev->next = r->next;							//для предыдущего от r следующим
	}

	delete r;												//удаляем r
}

void delete_list(list *&h, list *&t) {						//удаляем список
	while (h) {												//пока список не пуст
		list *p = h;										//указатель на голову
		h = h->next;										//переносим голову
		h->prev = NULL;										//обнуляем
		delete p;											//удаляем p
	}
}

double average(list *h, list *t) {			//нахождение среднего арифметического от элемента h до t
	int count = 0;							//количество элементов
	int amount = 0;							//сумма элементов

	list *p = h;							//указатель на голову
	while (p) {								//пока не дошли до конца
		count++;							//увеличиваем счетчик на 1
		amount += p->inf;					//суммируем элемент
		p = p->next;						//переходим к следующему элементу
	}
	
	return 1.0 * amount / count;			//возвращаем среднее арифметическое
}

void handler(list *&h, list *&t) {
	list *head = NULL;						//Объявляем новый список-результат
	list *tail = NULL;

	list *p = h;							//указатель на голову
	while (p != t) {						//пока не дошли до хвоста
		double aver = average(p, t);		//подсчитываем среднее
		if (p->inf >= aver) {				//если подходит по условию, то
			push(head, tail, p->inf);		//добавляем элемент в новый список
		}
		p = p->next;						//переходим к следующему элементу
	}
	push(head, tail, p->inf);				//хвост всегда проходит по условию
	h = head;								//переопределяем указатели
	t = tail;
}

int main() {
	cout << "Enter your numbers: ";							//вводим числа
	string input; getline(cin, input);
	stringstream str(input);
	string strNumber;
	int number;

	list *head = NULL;										//инициализируем список
	list *tail = NULL;
	while (str >> strNumber) {								//добавляем числа в список
		number = stoi(strNumber);
		push(head, tail, number);
	}

	handler(head, tail);									//вызываем обработчик

	/*list *p = head;
	while (p) {
		cout << average(p, tail) << ' ';
		p = p->next;
	}*/

	cout << '\n';

	print(head, tail);										//вывод списка

	system("pause");
	return 0;
}
