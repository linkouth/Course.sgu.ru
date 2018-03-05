#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct date {			//дата
	int dd, mm, yy;		//день, месяц, год
};

struct people {			//данные о сотруднике
	string surname;		//фамилия
	string position;	//должность
	date birthday;		//дата рождения
	int experiance;		//стаж(в годах)
	int salary;			//зарплата
};

date stringToDate(string str) {			//перевод строки в дату
	date x;
	string tmp = str.substr(0, 2);		//день
	x.dd = stoi(tmp);
	tmp = str.substr(3, 2);				//месяц
	x.mm = stoi(tmp);
	tmp = str.substr(6, 4);				//год
	x.yy = stoi(tmp);

	return x;
}

vector<people> inFile() {				//ввод из файла
	vector<people> staff;
	people p;
	while (in.peek() != EOF) {
		in >> p.surname;				//фамилия
		in >> p.position;				//должность
		string tmp; in >> tmp;
		p.birthday = stringToDate(tmp); //дата рождения
		in >> p.experiance;				//стаж
		in >> p.salary;					//зарплата
		staff.push_back(p);
	}

	return staff;
}

void print(people p) {								//вывод в файл
	out << setw(15) << left << p.surname;			//по левому краю, 15 позиций для фамилии
	out << setw(15) << left << p.position;			//по левому краю, 15 позиций для должности
	if (p.birthday.dd < 10)
		out << left << '0' << p.birthday.dd << '.'; //добавляем 0, если день рождения меньше 10
	else
		out << left << p.birthday.dd << '.';
	if (p.birthday.mm < 10)
		out << left << '0' << p.birthday.mm << '.'; //добавляем 0, если месяц рождения меньше 10
	else
		out << left << p.birthday.mm << '.';
	out << left << setw(6) << p.birthday.yy;		//по левому краю, 6 позиций для года рождения
	out << left << setw(4) << p.experiance;			//по левому краю, 4 позиций для стажа
	out << left << setw(10) << p.salary << '\n';	//по левому краю, 10 позиций для зарплаты
}

bool operator < (people first, people second) {		//переопределяем оператор <
	if (first.salary < second.salary)
		return true;
	if (first.salary == second.salary && first.birthday.dd < second.birthday.dd)
		return true;
	return false;
}

bool operator > (people first, people second) {		//переопределяем оператор >
	if (first.experiance > second.experiance)
		return true;
	return false;
}

void InsertionSort(vector<people> &staff) {					//сортировка вставкой
	for (int i = 1; i < staff.size(); i++) {
		int j = i;
		while (j > 0 && staff[j] < staff[j - 1]) {
			swap(staff[j], staff[j - 1]);
			j--;
		}
	}
}

int getMaxExperiance(vector<people> staff) {				//поиск максимального опыта 
	people maxExp = staff[0];								//предположительный максимум

	for (auto p : staff)
		maxExp = p > maxExp ? p : maxExp;					//сравниваем текущий максимум с элементом

	return maxExp.experiance;
}

int getMinExperiance(vector<people> staff) {				//поиск минимального опыта
	people minExp = staff[0];								//предположительный минимум

	for (auto p : staff)									//сравниваем текущий минимум с элементом
		minExp = p < minExp ? p : minExp;

	return minExp.experiance;
}

void BucketSort(vector<people> &staff) {						//блочная сортировка
	const int P = 5;											//количество корзин
	int maxExperiance = getMaxExperiance(staff);				//максимальный опыт
	int minExperiance = getMinExperiance(staff);				//минимальный опыт
	const int m = (maxExperiance - minExperiance) / P;			//коэффициент m

	vector< vector<people> > segments(5);							//отрезки-корзины

	for (int i = 0; i < staff.size(); i++) {					//распределение элементов исходного массива по корзинам
		int k = (staff[i].experiance - minExperiance) / m;			//определение номера корзины
		if (k == P)												//если k равно количеству корзин, 
			segments[P - 1].push_back(staff[i]);				//то ддобавляем элемент в последнюю корзину
		else
			segments[k].push_back(staff[i]);
	}

	for (int i = 0; i < P; i++) {								//в каждой корзине проводим 
		InsertionSort(segments[i]);								//сортировку вставкой
	}

	staff.clear();												//очищаем исходный массив
	for (int i = 0; i < P; i++)									//покорзинно
		for (auto p : segments[i])								//добавляем в массив элементы
			staff.push_back(p);
}

void merge(vector<people> &ar, int left, int right, int middle) {
	if (left >= right && middle < left && middle > right) {
		return;
	}
	if (right == left + 1){
		if (ar[left] > ar[right]) 
		   swap(ar[left], ar[right]);
		return;
	}

	vector<people> buf(right - left + 1);
	int cur = 0, i = left, j = middle + 1;
	while (right - left + 1 != cur) {
		if (i > middle) {
			for (int k = j; k <= right; k++)
				buf[cur++] = ar[k];
		}
		else if (j > right) {
			for (int k = i; k <= middle; k++) {
				buf[cur++] = ar[k];
			}
		}
		else if (ar[i] > ar[j]) {
			buf[cur++] = ar[j++];
		}
		else {
			buf[cur++] = ar[i++];
		}
	}

	for (int k = 0; k < buf.size(); k++)
		ar[k + left] = buf[k];
}

void MergeSort(vector<people> &ar, int left, int right) {
	if (left >= right)
		return;

	int middle = (left + right) / 2;
	MergeSort(ar, left, middle);
	MergeSort(ar, middle + 1, right);
	merge(ar, left, right, middle);
}

void BubbleSort(vector<people> &staff) {
	for (int i = 0; i < staff.size(); i++) {
		for (int j = staff.size() - 1; j > i; j--) {
			if (staff[j - 1] > staff[j])
				swap(staff[j - 1], staff[j]);
		}
	}
}

int main() {
	vector<people> staff;					//объявляем вектор с персоналом
	staff = inFile();						//заполняем вектор

	MergeSort(staff, 0, staff.size()-1);		//сортируем вектор слиянием

	for (auto p : staff)					//выводим персонал в output.txt
		print(p);

	return 0;
}
