#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct date {			//����
	int dd, mm, yy;		//����, �����, ���
};

struct people {			//������ � ����������
	string surname;		//�������
	string position;	//���������
	date birthday;		//���� ��������
	int experiance;		//����(� �����)
	int salary;			//��������
};

date stringToDate(string str) {			//������� ������ � ����
	date x;
	string tmp = str.substr(0, 2);		//����
	x.dd = stoi(tmp);
	tmp = str.substr(3, 2);				//�����
	x.mm = stoi(tmp);
	tmp = str.substr(6, 4);				//���
	x.yy = stoi(tmp);

	return x;
}

vector<people> inFile() {				//���� �� �����
	vector<people> staff;
	people p;
	while (in.peek() != EOF) {
		in >> p.surname;				//�������
		in >> p.position;				//���������
		string tmp; in >> tmp;	
		p.birthday = stringToDate(tmp); //���� ��������
		in >> p.experiance;				//����
		in >> p.salary;					//��������
		staff.push_back(p);
	}

	return staff;
}

void print(people p) {								//����� � ����
	out << setw(15) << left << p.surname;			//�� ������ ����, 15 ������� ��� �������
	out << setw(15) << left << p.position;			//�� ������ ����, 15 ������� ��� ���������
	if (p.birthday.dd < 10)
		out << left << '0' << p.birthday.dd << '.'; //��������� 0, ���� ���� �������� ������ 10
	else
		out << left << p.birthday.dd << '.';
	if (p.birthday.mm < 10)
		out << left << '0' << p.birthday.mm << '.'; //��������� 0, ���� ����� �������� ������ 10
	else
		out << left << p.birthday.mm << '.';
	out << left << setw(6) << p.birthday.yy;		//�� ������ ����, 6 ������� ��� ���� ��������
	out << left << setw(4) << p.experiance;			//�� ������ ����, 4 ������� ��� �����
	out << left << setw(10) << p.salary << '\n';	//�� ������ ����, 10 ������� ��� ��������
}

bool operator < (people first, people second) {		//�������������� �������� <
	if (first.experiance < second.experiance)
		return true;
	return false;
}

bool operator > (people first, people second) {		//�������������� �������� >
	if (first.experiance > second.experiance)
		return true;
	return false;
}

void InsertionSort(vector<people> &staff) {					//���������� ��������
	for (int i = 1; i < staff.size(); i++) {
		int j = i;
		while (j > 0 && staff[j] < staff[j - 1]) {
			swap(staff[j], staff[j - 1]);
			j--;
		}
	}
}

int getMaxExperiance(vector<people> staff) {				//����� ������������� ����� 
	people maxExp = staff[0];								//����������������� ��������

	for (auto p : staff)
		maxExp = p > maxExp ? p : maxExp;					//���������� ������� �������� � ���������

	return maxExp.experiance;
}

int getMinExperiance(vector<people> staff) {				//����� ������������ �����
	people minExp = staff[0];								//����������������� �������

	for (auto p : staff)									//���������� ������� ������� � ���������
		minExp = p < minExp ? p : minExp;

	return minExp.experiance;
}

void BucketSort(vector<people> &staff) {						//������� ����������
	const int P = 5;											//���������� ������
	int maxExperiance = getMaxExperiance(staff);				//������������ ����
	int minExperiance = getMinExperiance(staff);				//����������� ����
	const int m = (maxExperiance - minExperiance) / P;			//����������� m

	vector< vector<people> > segments(5);							//�������-�������

	for (int i = 0; i < staff.size(); i++) {					//������������� ��������� ��������� ������� �� ��������
		int k = (staff[i].experiance - minExperiance) / m;			//����������� ������ �������
		if (k == P)												//���� k ����� ���������� ������, 
			segments[P - 1].push_back(staff[i]);				//�� ���������� ������� � ��������� �������
		else 
			segments[k].push_back(staff[i]);
	}

	for (int i = 0; i < P; i++) {								//� ������ ������� �������� 
		InsertionSort(segments[i]);								//���������� ��������
	}

	staff.clear();												//������� �������� ������
	for (int i = 0; i < P; i++)									//����������
		for (auto p : segments[i])								//��������� � ������ ��������
			staff.push_back(p);
}

int main() {
	vector<people> staff;					//��������� ������ � ����������
	staff = inFile();						//��������� ������

	BucketSort(staff);						//��������� ������ ��������

	for (auto p : staff)					//������� �������� � output.txt
		print(p);

	return 0;
}