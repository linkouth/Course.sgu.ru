#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct date {			//äàòà
	int dd, mm, yy;		//äåíü, ìåñÿö, ãîä
};

struct people {			//äàííûå î ñîòðóäíèêå
	string surname;		//ôàìèëèÿ
	string position;	//äîëæíîñòü
	date birthday;		//äàòà ðîæäåíèÿ
	int experiance;		//ñòàæ(â ãîäàõ)
	int salary;			//çàðïëàòà
};

date stringToDate(string str) {			//ïåðåâîä ñòðîêè â äàòó
	date x;
	string tmp = str.substr(0, 2);		//äåíü
	x.dd = stoi(tmp);
	tmp = str.substr(3, 2);				//ìåñÿö
	x.mm = stoi(tmp);
	tmp = str.substr(6, 4);				//ãîä
	x.yy = stoi(tmp);

	return x;
}

vector<people> inFile() {				//ââîä èç ôàéëà
	vector<people> staff;
	people p;
	while (in.peek() != EOF) {
		in >> p.surname;				//ôàìèëèÿ
		in >> p.position;				//äîëæíîñòü
		string tmp; in >> tmp;	
		p.birthday = stringToDate(tmp); //äàòà ðîæäåíèÿ
		in >> p.experiance;				//ñòàæ
		in >> p.salary;					//çàðïëàòà
		staff.push_back(p);
	}

	return staff;
}

void print(people p) {								//âûâîä â ôàéë
	out << setw(15) << left << p.surname;			//ïî ëåâîìó êðàþ, 15 ïîçèöèé äëÿ ôàìèëèè
	out << setw(15) << left << p.position;			//ïî ëåâîìó êðàþ, 15 ïîçèöèé äëÿ äîëæíîñòè
	if (p.birthday.dd < 10)
		out << left << '0' << p.birthday.dd << '.'; //äîáàâëÿåì 0, åñëè äåíü ðîæäåíèÿ ìåíüøå 10
	else
		out << left << p.birthday.dd << '.';
	if (p.birthday.mm < 10)
		out << left << '0' << p.birthday.mm << '.'; //äîáàâëÿåì 0, åñëè ìåñÿö ðîæäåíèÿ ìåíüøå 10
	else
		out << left << p.birthday.mm << '.';
	out << left << setw(6) << p.birthday.yy;		//ïî ëåâîìó êðàþ, 6 ïîçèöèé äëÿ ãîäà ðîæäåíèÿ
	out << left << setw(4) << p.experiance;			//ïî ëåâîìó êðàþ, 4 ïîçèöèé äëÿ ñòàæà
	out << left << setw(10) << p.salary << '\n';	//ïî ëåâîìó êðàþ, 10 ïîçèöèé äëÿ çàðïëàòû
}

bool operator < (people first, people second) {		//ïåðåîïðåäåëÿåì îïåðàòîð <
	if (first.experiance < second.experiance)
		return true;
	return false;
}

bool operator > (people first, people second) {		//ïåðåîïðåäåëÿåì îïåðàòîð >
	if (first.experiance > second.experiance)
		return true;
	return false;
}

void InsertionSort(vector<people> &staff) {					//ñîðòèðîâêà âñòàâêîé
	for (int i = 1; i < staff.size(); i++) {
		int j = i;
		while (j > 0 && staff[j] < staff[j - 1]) {
			swap(staff[j], staff[j - 1]);
			j--;
		}
	}
}

int getMaxExperiance(vector<people> staff) {				//ïîèñê ìàêñèìàëüíîãî îïûòà 
	people maxExp = staff[0];								//ïðåäïîëîæèòåëüíûé ìàêñèìóì

	for (auto p : staff)
		maxExp = p > maxExp ? p : maxExp;					//ñðàâíèâàåì òåêóùèé ìàêñèìóì ñ ýëåìåíòîì

	return maxExp.experiance;
}

int getMinExperiance(vector<people> staff) {				//ïîèñê ìèíèìàëüíîãî îïûòà
	people minExp = staff[0];								//ïðåäïîëîæèòåëüíûé ìèíèìóì

	for (auto p : staff)									//ñðàâíèâàåì òåêóùèé ìèíèìóì ñ ýëåìåíòîì
		minExp = p < minExp ? p : minExp;

	return minExp.experiance;
}

void BucketSort(vector<people> &staff) {						//áëî÷íàÿ ñîðòèðîâêà
	const int P = 5;											//êîëè÷åñòâî êîðçèí
	int maxExperiance = getMaxExperiance(staff);				//ìàêñèìàëüíûé îïûò
	int minExperiance = getMinExperiance(staff);				//ìèíèìàëüíûé îïûò
	const int m = (maxExperiance - minExperiance) / P;			//êîýôôèöèåíò m

	vector< vector<people> > segments(5);							//îòðåçêè-êîðçèíû

	for (int i = 0; i < staff.size(); i++) {					//ðàñïðåäåëåíèå ýëåìåíòîâ èñõîäíîãî ìàññèâà ïî êîðçèíàì
		int k = (staff[i].experiance - minExperiance) / m;			//îïðåäåëåíèå íîìåðà êîðçèíû
		if (k == P)												//åñëè k ðàâíî êîëè÷åñòâó êîðçèí, 
			segments[P - 1].push_back(staff[i]);				//òî ääîáàâëÿåì ýëåìåíò â ïîñëåäíþþ êîðçèíó
		else 
			segments[k].push_back(staff[i]);
	}

	for (int i = 0; i < P; i++) {								//â êàæäîé êîðçèíå ïðîâîäèì 
		InsertionSort(segments[i]);								//ñîðòèðîâêó âñòàâêîé
	}

	staff.clear();												//î÷èùàåì èñõîäíûé ìàññèâ
	for (int i = 0; i < P; i++)									//ïîêîðçèííî
		for (auto p : segments[i])								//äîáàâëÿåì â ìàññèâ ýëåìåíòû
			staff.push_back(p);
}

int main() {
	vector<people> staff;					//îáúÿâëÿåì âåêòîð ñ ïåðñîíàëîì
	staff = inFile();						//çàïîëíÿåì âåêòîð

	BucketSort(staff);						//ñîðòèðóåì âåêòîð ïîáëî÷íî

	for (auto p : staff)					//âûâîäèì ïåðñîíàë â output.txt
		print(p);

	return 0;
}
