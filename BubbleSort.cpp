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
	if (first.position < second.position)
		return true;
	if (first.position == second.position && first.experiance < second.experiance)
		return true;
	if (first.position == second.position &&
		first.experiance == second.experiance &&
		first.salary < second.salary)
		return true;
	return false;
}

bool operator > (people first, people second) {		//переопределяем оператор >
	if (first.position > second.position)
		return true;
	if (first.position == second.position && first.experiance > second.experiance)
		return true;
	if (first.position == second.position &&
		first.experiance == second.experiance &&
		first.salary > second.salary)
		return true;
	return false;
}

void BubbleSort(vector<people> &staff) {				//сортировка пузырьком
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

	BubbleSort(staff);		//сортируем вектор слиянием

	for (auto p : staff)					//выводим персонал в output.txt
		print(p);

	return 0;
}
