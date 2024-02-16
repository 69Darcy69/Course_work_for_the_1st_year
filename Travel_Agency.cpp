#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <ctime>
#include <list>

using namespace std;

ofstream fout;
ifstream fin;
ifstream fin0;
fstream flow_tour;
fstream tempor;
fstream flow_passenger;
fstream hot;
fstream old;

void menu();
void delete_space(char*);

//структура хранения даты
struct Date {
	size_t day;
	size_t month;
	size_t year;
	void current_date() {	//получение текущей даты
		time_t now = time(0);
		tm* ltm = localtime(&now);
		DT.day = ltm->tm_mday;
		DT.month = 1 + ltm->tm_mon;
		DT.year = 1900 + ltm->tm_year;
	};
} DT;

size_t number_of_days(size_t month) {	//перевод прошедших месяцов с начала года в дни
	if (month == 1)return 0;
	if (month == 2)return 31;
	if (month == 3)return 59;
	if (month == 4)return 90;
	if (month == 5)return 120;
	if (month == 6)return 151;
	if (month == 7)return 181;
	if (month == 8)return 212;
	if (month == 9)return 243;
	if (month == 10)return 273;
	if (month == 11)return 304;
	if (month == 12)return 334;
};

//структура хранения тура
struct Tour {
	size_t number;
	char name_tour[10];
	struct country {
		char of[14];
		char in[14];
	} C_RY;
	struct town {
		char of[14];
		char in[14];
	} TW;
	char hotel[9];
	char transfer[9];
	struct Begin {
		size_t day;
		size_t month;
		size_t year;
	} BEG;
	struct End {
		size_t day;
		size_t month;
		size_t year;
	} END;
	size_t number_seats;
	size_t tariff;
} TR;
int zTR = sizeof(TR);
list<Tour> tours;

//структура хранения пассажира
struct Passenger {
	char FIO[19];
	char passport[11];
	char gender[9];
	size_t date_birth;
	char address[14];
	char number_phone[12];
	size_t baggage_weight;
	void assemble_fio(const char* last_name, const char* initials) {	//объединение фамилии и инициалов в одну запись
		for (int i = 0; i < strlen(FIO); i++)FIO[i] = ' ';
		delete_space(FIO);
		if (strlen(last_name) >= 14) {
			for (int i = 0; i < 14; i++) {
				FIO[i] = last_name[i];
			};
			FIO[14] = ' ';
			FIO[15] = initials[0];
			FIO[16] = '.';
			FIO[17] = initials[1];
			FIO[18] = '.';
		}
		else {
			for (int j = 0; j < strlen(last_name); j++)FIO[j] = initials[j];
			FIO[strlen(last_name)] = ' ';
			FIO[strlen(last_name) + 1] = initials[0];
			FIO[strlen(last_name) + 2] = '.';
			FIO[strlen(last_name) + 3] = initials[1];
			FIO[strlen(last_name) + 4] = '.';
		};
		delete_space(FIO);
	};
} PS;
int zPS = sizeof(PS);
list<Passenger> passengers;

void filling_list_tour() {	//заполнение листа с турами
	flow_tour.open("Tour.cpp", ios::in | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (124)" << endl;
		system("pause");
		menu();
	};
	while (flow_tour.peek() != EOF) {
		flow_tour.read((char*)&TR, zTR);
		tours.push_back(TR);
	};
	flow_tour.close();
};
void filling_list_passenger() {	//заполнение листа с пассажирами конкретного тура
	flow_passenger.open(string(TR.name_tour) + ".cpp", ios::in | ios::binary);
	if (!flow_passenger) {
		cout << "Ошибка!Возврат в Меню. (137)" << endl;
		system("pause");
		menu();
	};
	while (flow_passenger.peek() != EOF) {
		flow_passenger.read((char*)&PS, zPS);
		passengers.push_back(PS);
	};
	flow_passenger.close();
};

void delete_space(char* str) {	//удаление пробелов в начале и конце массива символов
	int x, x1 = 0, x2 = strlen(str) - 1;
	while (str[x1] == ' ') x1++;
	while (str[x2] == ' ' || str[x2] == '\n') x2--;
	for (x = x1; x <= x2; x++)
		str[x - x1] = str[x];
	str[x - x1] = '\0';
};
char shT[]{ "||Номер||Название   ||Страна отправления->Страна прибытия||Город отправления->Город прибытия ||Отель     ||Транспорт ||Дата начала||Дата окончания||Места||Стоимость||" };
void vivod_tour() {	//вывод информации об одном туре
	cout << "||" << setw(5) << TR.number << "||" << setw(11) << TR.name_tour << "||" << setw(18) << TR.C_RY.of << "->" << setw(15) << TR.C_RY.in << "||" <<
		setw(17) << TR.TW.of << "->" << setw(15) << TR.TW.in << "||" << setw(10) << TR.hotel << "||" << setw(10) << TR.transfer << "||" <<
		setw(2) << TR.BEG.day << "." << setw(2) << TR.BEG.month << "." << setw(5) << TR.BEG.year << "||" <<
		setw(3) << TR.END.day << "." << setw(3) << TR.END.month << "." << setw(6) << TR.END.year << "||" << setw(5) << TR.number_seats << "||" <<
		setw(9) << TR.tariff << "||" << endl;
	fout << "||" << setw(5) << TR.number << "||" << setw(11) << TR.name_tour << "||" << setw(18) << TR.C_RY.of << "->" << setw(15) << TR.C_RY.in << "||" <<
		setw(17) << TR.TW.of << "->" << setw(15) << TR.TW.in << "||" << setw(10) << TR.hotel << "||" << setw(10) << TR.transfer << "||" <<
		setw(2) << TR.BEG.day << "." << setw(2) << TR.BEG.month << "." << setw(5) << TR.BEG.year << "||" <<
		setw(3) << TR.END.day << "." << setw(3) << TR.END.month << "." << setw(6) << TR.END.year << "||" << setw(5) << TR.number_seats << "||" <<
		setw(9) << TR.tariff << "||" << endl;
};
char shP[]{ "||ФИО                 ||Паспорт     ||Пол       ||Год Р.||Адрес           ;Телефон       ||Вес багажа||" };
void vivod_passenger() {	//вывод информации об одном пассажире
	cout << "||" << setw(20) << PS.FIO << "||" << setw(12) << PS.passport << "||" << setw(10) << PS.gender << "||" << setw(6) << PS.date_birth << "||"
		<< setw(15) << PS.address << " ; " << setw(13) << PS.number_phone << "||" << setw(10) << PS.baggage_weight << "||" << endl;
	fout << "||" << setw(20) << PS.FIO << "||" << setw(12) << PS.passport << "||" << setw(10) << PS.gender << "||" << setw(6) << PS.date_birth << "||"
		<< setw(15) << PS.address << " ; " << setw(13) << PS.number_phone << "||" << setw(10) << PS.baggage_weight << "||" << endl;
};

void create_list_passengers() {	//создание бинарного файла пассажиров тура
	fin0.open(string(TR.name_tour) + ".txt");
	if (!fin0) {
		cout << "Ошибка! (180)" << endl;
		system("pause");
		return;
	};
	flow_passenger.open(string(TR.name_tour) + ".cpp", ios::out | ios::binary);
	if (!flow_passenger) {
		cout << "Ошибка! (186)" << endl;
		system("pause");
		return;
	};
	char temp[250];
	while (fin0.peek() != EOF) {
		fin0.get(PS.FIO, 19); delete_space(PS.FIO);
		fin0.get(PS.passport, 11); delete_space(PS.passport);
		fin0.get(PS.gender, 9); delete_space(PS.gender);
		fin0 >> PS.date_birth;
		fin0.get(PS.address, 14); delete_space(PS.address);
		fin0.get(PS.number_phone, 12); delete_space(PS.number_phone);
		fin0 >> PS.baggage_weight;
		fin0.getline(temp, 100);
		passengers.push_back(PS);
	};
	passengers.sort([](Passenger const& a, Passenger const& b) { return string(a.FIO) < string(b.FIO); });
	for (auto PS : passengers)
	{
		flow_passenger.write((char*)&PS, sizeof(PS));
	};
	passengers.clear();
	fin0.close();
	flow_passenger.close();
};
void create_list_tour() {	//создание бинарного файла туров
	fin.open("sozd.txt");
	if (!fin) {
		cout << "Ошибка! (214)" << endl;
		system("pause");
		return;
	};
	flow_tour.open("Tour.cpp", ios::out | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка! (220)" << endl;
		system("pause");
		return;
	};
	char temp[250];
	while (!fin.eof()) {
		fin >> TR.number;
		fin.get(TR.name_tour, 10); delete_space(TR.name_tour);
		fin.get(TR.C_RY.of, 14); delete_space(TR.C_RY.of);
		fin.get(TR.C_RY.in, 14); delete_space(TR.C_RY.in);
		fin.get(TR.TW.of, 14); delete_space(TR.TW.of);
		fin.get(TR.TW.in, 14); delete_space(TR.TW.in);
		fin.get(TR.hotel, 9); delete_space(TR.hotel);
		fin.get(TR.transfer, 9); delete_space(TR.transfer);
		fin >> TR.BEG.day;
		fin >> TR.BEG.month;
		fin >> TR.BEG.year;
		fin >> TR.END.day;
		fin >> TR.END.month;
		fin >> TR.END.year;
		fin >> TR.number_seats;
		fin >> TR.tariff;
		fin.getline(temp, 100);
		create_list_passengers();
		tours.push_back(TR);
	};
	tours.sort([](Tour const& a, Tour const& b)
		{ if (a.BEG.year != b.BEG.year) return a.BEG.year < b.BEG.year;
		else if (a.BEG.month != b.BEG.month) return a.BEG.month < b.BEG.month;
		else return a.BEG.day < b.BEG.day;
		});
	for (auto TR : tours)
	{
		flow_tour.write((char*)&TR, sizeof(TR));
	};
	tours.clear();
	fin.close();
	flow_tour.close();
};

void read_tour() {	//вывод туров
	flow_tour.open("Tour.cpp", ios::in | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (263)" << endl;
		system("pause");
		menu();
	};
	cout << shT << endl;
	fout << shT << endl;
	while (flow_tour.peek() != -1) {
		flow_tour.read((char*)&TR, zTR);
		vivod_tour();
	};
	flow_tour.close();
	system("pause");
};

void addition_tour_fail() {	//дополнение списка туров из файла
	char temp[200];
	filling_list_tour();
	fin.open("AdditionTour.txt");
	if (!fin) {
		cout << "Ошибка!Возврат в Меню. (282)" << endl;
		system("pause");
		menu();
	};
	flow_tour.open("Tour.cpp", ios::out | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (288)" << endl;
		system("pause");
		menu();
	};
	while (!fin.eof()) {
		fin >> TR.number;
		fin.get(TR.name_tour, 10); delete_space(TR.name_tour);
		fin.get(TR.C_RY.of, 14); delete_space(TR.C_RY.of);
		fin.get(TR.C_RY.in, 14); delete_space(TR.C_RY.in);
		fin.get(TR.TW.of, 14); delete_space(TR.TW.of);
		fin.get(TR.TW.in, 14); delete_space(TR.TW.in);
		fin.get(TR.hotel, 9); delete_space(TR.hotel);
		fin.get(TR.transfer, 9); delete_space(TR.transfer);
		fin >> TR.BEG.day;
		fin >> TR.BEG.month;
		fin >> TR.BEG.year;
		fin >> TR.END.day;
		fin >> TR.END.month;
		fin >> TR.END.year;
		fin >> TR.number_seats;
		fin >> TR.tariff;
		fin.getline(temp, 100);
		tours.push_back(TR);
		cout << shT << endl;
		fout << shT << endl;
		vivod_tour();
		flow_passenger.open(string(TR.name_tour) + ".cpp", ios::out | ios::binary);
		if (!flow_passenger) {
			cout << "Ошибка! (316)" << endl;
			system("pause");
			return;
		};
		flow_passenger.close();
		cout << "Тур успешно добавлен" << endl;
	};
	tours.sort([](Tour const& a, Tour const& b)
		{ if (a.BEG.year != b.BEG.year) return a.BEG.year < b.BEG.year;
		else if (a.BEG.month != b.BEG.month) return a.BEG.month < b.BEG.month;
		else return a.BEG.day < b.BEG.day;
		});
	for (auto TR : tours)
	{
		flow_tour.write((char*)&TR, sizeof(TR));
	};
	tours.clear();
	flow_tour.close();
	fin.close();
	cout << "Дополнение выполнено успешно" << endl;
	cout << "Для возврата в Меню нажмите любую клавишу" << endl;
	system("pause");
	menu();
};
void addition_tour_keyboard() {
	filling_list_tour();
	flow_tour.open("Tour.cpp", ios::out | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (344)" << endl;
		system("pause");
		menu();
	};
	cout << "Введите номер тура" << endl;
	cin >> TR.number;
	cout << "Введите название тура(max: 10 символов)" << endl;
	cin >> TR.name_tour; delete_space(TR.name_tour);
	cout << "Введите страну отправления(max: 14 символов)" << endl;
	cin >> TR.C_RY.of; delete_space(TR.C_RY.of);
	cout << "Введите страну прибытия(max: 14 символов)" << endl;
	cin >> TR.C_RY.in; delete_space(TR.C_RY.in);
	cout << "Введите город отправляния(max: 14 символов)" << endl;
	cin >> TR.TW.of; delete_space(TR.TW.of);
	cout << "Введите город прибытия(max: 14 символов)" << endl;
	cin >> TR.TW.in, 14; delete_space(TR.TW.in);
	cout << "Введите отель(max: 9 символов)" << endl;
	cin >> TR.hotel, 9; delete_space(TR.hotel);
	cout << "Введите транспорт(max: 9 символов)" << endl;
	cin >> TR.transfer, 9; delete_space(TR.transfer);
	cout << "Введите день отправления" << endl;
	cin >> TR.BEG.day;
	cout << "Введите месяц отправления" << endl;
	cin >> TR.BEG.month;
	cout << "Введите год отправления" << endl;
	cin >> TR.BEG.year;
	cout << "Введите день окончания тура" << endl;
	cin >> TR.END.day;
	cout << "Введите месяц окончания тура" << endl;
	cin >> TR.END.month;
	cout << "Введите год окончания тура" << endl;
	cin >> TR.END.year;
	cout << "Введите количество доступных мест" << endl;
	cin >> TR.number_seats;
	cout << "Ввведите стоимость тура" << endl;
	cin >> TR.tariff;
	fout << shT << endl;
	fout << "||" << setw(5) << TR.number << "||" << setw(11) << TR.name_tour << "||" << setw(18) << TR.C_RY.of << "->" << setw(15) << TR.C_RY.in << "||" <<
		setw(17) << TR.TW.of << "->" << setw(15) << TR.TW.in << "||" << setw(10) << TR.hotel << "||" << setw(10) << TR.transfer << "||" <<
		setw(2) << TR.BEG.day << "." << setw(2) << TR.BEG.month << "." << setw(5) << TR.BEG.year << "||" <<
		setw(3) << TR.END.day << "." << setw(3) << TR.END.month << "." << setw(6) << TR.END.year << "||" << setw(5) << TR.number_seats << "||" <<
		setw(9) << TR.tariff << "||" << endl;
	tours.push_back(TR);
	flow_passenger.open(string(TR.name_tour) + ".cpp", ios::out | ios::binary);
	if (!flow_passenger) {
		cout << "Ошибка! (389)" << endl;
		system("pause");
		return;
	};
	flow_passenger.close();
	cout << "Тур успешно добавлен" << endl;
	tours.sort([](Tour const& a, Tour const& b)
		{ if (a.BEG.year != b.BEG.year) return a.BEG.year < b.BEG.year;
		else if (a.BEG.month != b.BEG.month) return a.BEG.month < b.BEG.month;
		else return a.BEG.day < b.BEG.day;
		});
	for (auto TR : tours)
	{
		flow_tour.write((char*)&TR, sizeof(TR));
	};
	tours.clear();
	flow_tour.close();
	cout << "Дополнение выполнено успешно" << endl;
	cout << "Для возврата в Меню нажмите любую клавишу" << endl;
	system("pause");
	menu();

};

void read_passengers() {	//вывод пассажиров одного тура
	cout << "Введите название тура, для которого хотите вывести список пассажиров(max: 10 символов)" << endl;
	char name_tour_local[10];
	cin >> name_tour_local;
	delete_space(name_tour_local);
	cout << "Список участников:" << endl;
	fout << "Список участников " << name_tour_local << " :" << endl;
	flow_passenger.open(string(name_tour_local) + ".cpp", ios::in | ios::binary);
	if (!flow_passenger) {
		cout << "Ошибка!Возврат в Меню. (422)" << endl;
		system("pause");
		menu();
	};
	cout << shP << endl;
	fout << shP << endl;
	while (flow_passenger.peek() != -1) {
		flow_passenger.read((char*)&PS, zPS);
		vivod_passenger();
	};
	flow_passenger.close();
	cout << "Для возврата в Меню нажмите любую клавишу" << endl;
	system("pause");
	menu();
};

void hot_tour() {	//создание бинарного файла горящих (2 дня до начала) туров
	flow_tour.open("Tour.cpp", ios::in | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка! (441)" << endl;
		system("pause");
		return;
	};
	hot.open("Hot.cpp", ios::out | ios::binary);
	if (!hot) {
		cout << "Ошибка! (447)" << endl;
		system("pause");
		return;
	};
	while (flow_tour.peek() != EOF) {
		flow_tour.read((char*)&TR, zTR);
		if ((number_of_days(TR.BEG.month) + TR.BEG.day + (TR.BEG.year - 1) * 365) - (number_of_days(DT.month) + DT.day + (DT.year - 1) * 365) <= 2) {
			TR.tariff = TR.tariff - (TR.tariff / 10);
			hot.write((char*)&TR, zTR);
		};
	};
	flow_tour.close();
	hot.close();
};

void read_hot() {	//вывод горящих (2 дня до начала) туров
	hot.open("Hot.cpp", ios::in | ios::binary);
	if (!hot) {
		cout << "Ошибка!Возврат в Меню. (465)" << endl;
		system("pause");
		menu();
	};
	cout << shT << endl;
	fout << shT << endl;
	while (hot.peek() != -1) {
		hot.read((char*)&TR, zTR);
		vivod_tour();
	};
	hot.close();
	system("pause");
};

void delete_tour(char* tour_deleted) {	//удаление одного тура
	flow_tour.open("Tour.cpp", ios::in | ios::binary);
	tempor.open("Tempor.cpp", ios::out | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (483)" << endl;
		system("pause");
		menu();
	};
	if (!tempor) {
		cout << "Ошибка!Возврат в Меню. (488)" << endl;
		system("pause");
		menu();
	};
	while (flow_tour.peek() != EOF) {
		flow_tour.read((char*)&TR, zTR);
		if (!strcmp(TR.name_tour, tour_deleted)) {
			remove((string(TR.name_tour) + ".cpp").c_str());
		}
		else tempor.write((char*)&TR, zTR);
	};
	flow_tour.close();
	tempor.close();
	flow_tour.open("Tour.cpp", ios::out | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (503)" << endl;
		system("pause");
		menu();
	};
	tempor.open("Tempor.cpp", ios::in | ios::binary);
	if (!tempor) {
		cout << "Ошибка!Возврат в Меню. (509)" << endl;
		system("pause");
		menu();
	};
	while (tempor.peek() != EOF) {
		tempor.read((char*)&TR, zTR);
		flow_tour.write((char*)&TR, zTR);
	};
	flow_tour.close();
	tempor.close();
	cout << "Тур успешно удалён" << endl;
	cout << "Для возврата в Меню нажмите любую клавишу" << endl;
	system("pause");
	menu();
};

void restart_tour() {	//создание бинарного файла с прошедшими турами (срок хранения 1 год)
	flow_tour.open("Tour.cpp", ios::in | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка! (528)" << endl;
		system("pause");
		return;
	};
	old.open("OldTour.cpp", ios::app | ios::binary);
	if (!old) {
		cout << "Ошибка! (534)" << endl;
		system("pause");
		return;
	};
	tempor.open("Tempor.cpp", ios::out | ios::binary);
	if (!tempor) {
		cout << "Ошибка! (540)" << endl;
		system("pause");
		return;
	};
	while (flow_tour.peek() != EOF) {
		flow_tour.read((char*)&TR, zTR);
		if (((number_of_days(TR.BEG.month) + TR.BEG.day + (TR.BEG.year - 1) * 365) < (number_of_days(DT.month) + DT.day + (DT.year - 1) * 365)) &&
			(((number_of_days(DT.month) + DT.day + (DT.year - 1) * 365) - (number_of_days(TR.BEG.month) + TR.BEG.day + (TR.BEG.year - 1) * 365)) <= 365)) {
			old.write((char*)&TR, zTR);
		}
		else if ((number_of_days(TR.BEG.month) + TR.BEG.day + (TR.BEG.year - 1) * 365) >= (number_of_days(DT.month) + DT.day + (DT.year - 1) * 365)) tempor.write((char*)&TR, zTR);
		else remove((string(TR.name_tour) + ".cpp").c_str());
	};
	flow_tour.close();
	old.close();
	tempor.close();
	flow_tour.open("Tour.cpp", ios::out | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка! (558)" << endl;
		system("pause");
		return;
	};
	tempor.open("Tempor.cpp", ios::in | ios::binary);
	if (!tempor) {
		cout << "Ошибка! (564)" << endl;
		system("pause");
		return;
	};
	while (tempor.peek() != EOF) {
		tempor.read((char*)&TR, zTR);
		flow_tour.write((char*)&TR, zTR);
	};
	flow_tour.close();
	tempor.close();
};

void read_old() {	//вывод прошедших туров
	old.open("OldTour.cpp", ios::in | ios::binary);
	if (!old) {
		cout << "Ошибка!Возврат в Меню. (579)" << endl;
		system("pause");
		menu();
	};
	cout << shT << endl;
	fout << shT << endl;
	while (old.peek() != -1) {
		old.read((char*)&TR, zTR);
		vivod_tour();
	};
	old.close();
	system("pause");
};

void return_ticket() {	//возврат билета на тур
	cout << "Введите номер тура, билет на который хотите вернуть" << endl;
	size_t number;
	cin >> number;
	flow_tour.open("Tour.cpp", ios::in | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (599)" << endl;
		system("pause");
		menu();
	};
	while (flow_tour.peek() != EOF) {
		flow_tour.read((char*)&TR, zTR);
		if (TR.number == number)goto m;
	};
	cout << "Такого тура нет. Возврат в Меню" << endl;
	flow_tour.close();
	system("pause");
	menu();
m:
	flow_tour.close();
	cout << "Введите паспортные данные пассажира, билет которого возвращается(max: 10 символов)" << endl;
	char deleted_passport[10];
	cin >> deleted_passport; delete_space(deleted_passport);
	flow_passenger.open(string(TR.name_tour) + ".cpp", ios::in | ios::binary);
	if (!flow_passenger) {
		cout << "Ошибка!Возврат в Меню. (618)" << endl;
		system("pause");
		menu();
	};
	tempor.open("Tempor.cpp", ios::out | ios::binary);
	if (!tempor) {
		cout << "Ошибка!Возврат в Меню. (624)" << endl;
		system("pause");
		menu();
	};
	size_t count = 0;
	while (flow_passenger.peek() != EOF) {
		flow_passenger.read((char*)&PS, zPS);
		if (!strcmp(PS.passport, deleted_passport)) {
			count++;
			fout << "||" << setw(20) << PS.FIO << "||" << setw(12) << PS.passport << "||" << setw(10) << PS.gender << "||" << setw(6) << PS.date_birth << "||"
				<< setw(15) << PS.address << " ; " << setw(13) << PS.number_phone << "||" << setw(5) << PS.baggage_weight << "||" << endl;
		}
		else tempor.write((char*)&PS, zPS);
	};
	flow_passenger.close();
	tempor.close();
	if (count != 0) {
		flow_passenger.open(string(TR.name_tour) + ".cpp", ios::out | ios::binary);
		if (!flow_passenger) {
			cout << "Ошибка!Возврат в Меню. (643)" << endl;
			system("pause");
			menu();
		};
		tempor.open("Tempor.cpp", ios::in | ios::binary);
		if (!tempor) {
			cout << "Ошибка!Возврат в Меню. (649)" << endl;
			system("pause");
			menu();
		};
		while (tempor.peek() != EOF) {
			tempor.read((char*)&PS, zPS);
			flow_passenger.write((char*)&PS, zPS);
		};
		flow_passenger.close();
		tempor.close();
		flow_tour.open("Tour.cpp", ios::in | ios::out | ios::binary);
		if (!flow_tour) {
			cout << "Ошибка!Возврат в Меню. (661)" << endl;
			system("pause");
			menu();
		};
		while (flow_tour.peek() != EOF) {
			flow_tour.read((char*)&TR, zTR);
			if (TR.number == number) {
				TR.number_seats++;
				flow_tour.seekp(-zTR, ios::cur);
				flow_tour.write((char*)&TR, zTR);
				cout << shT << endl;
				fout << shT << endl;
				vivod_tour();
				flow_tour.close();
				cout << "Билет был возвращён" << endl;
				cout << "Для возврата в Меню нажмите любую клавишу" << endl;
				system("pause");
				menu();
			};
		};
	};
	flow_tour.close();
	cout << "Такого пассажира нет. Возврат в Меню" << endl;
	system("pause");
	menu();
};

void buy_ticket() {	//покупка билета на тур
	cout << "Выберите тур для покупки и введите его номер" << endl;
	size_t number;
	cin >> number;
	flow_tour.open("Tour.cpp", ios::in | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (694)" << endl;
		system("pause");
		menu();
	};
	while (flow_tour.peek() != EOF) {
		flow_tour.read((char*)&TR, zTR);
		if (TR.number == number)goto m;
	};
	cout << "Такого тура нет. Возврат в Меню" << endl;
	flow_tour.close();
	system("pause");
	menu();
m:
	if (TR.number_seats == 0) {
		cout << "Места на данный рейс отсутствуют. Возврат в Меню" << endl;
		flow_tour.close();
		system("pause");
		menu();
	};
	flow_tour.close();
	filling_list_passenger();
	char last_name[13]; char initials[2];
	cout << "Введите фамилию пассажира: " << endl;
	cin >> last_name; delete_space(last_name);
	cout << "Введите иннициалы пассажира без любых разделяющих символов" << endl;
	cin >> initials; delete_space(initials);
	PS.assemble_fio(last_name, initials);
	cout << "Введите паспортные данные слитно: серию и номер(10 цифр)" << endl;
	cin >> PS.passport; delete_space(PS.passport);
	cout << "Введите пол пассажира: Мужской/Женский" << endl;
	cin >> PS.gender; delete_space(PS.gender);
	cout << "Введите год рождения пассажира(4 цифры)" << endl;
	cin >> PS.date_birth;
	cout << "Введите контактный адрес" << endl;
	cin >> PS.address; delete_space(PS.address);
	cout << "Введите контактный номер телефона" << endl;
	cin >> PS.number_phone, 12; delete_space(PS.number_phone);
n:
	cout << "Введите вес багажа(максимальный вес составляет 20 кг)" << endl;
	cin >> PS.baggage_weight;
	if (PS.baggage_weight > 20) {
		cout << "Введённый вес превышает допустимый - 20 кг" << endl;
		goto n;
	};
	fout << shP << endl;
	fout << "||" << setw(20) << PS.FIO << "||" << setw(12) << PS.passport << "||" << setw(10) << PS.gender << "||" << setw(6) << PS.date_birth << "||"
		<< setw(15) << PS.address << " ; " << setw(13) << PS.number_phone << "||" << setw(5) << PS.baggage_weight << "||" << endl;
	passengers.push_back(PS);
	passengers.sort([](Passenger const& a, Passenger const& b) { return string(a.FIO) < string(b.FIO); });
	flow_passenger.open(string(TR.name_tour) + ".cpp", ios::out | ios::binary);
	if (!flow_passenger) {
		cout << "Ошибка!Возврат в Меню. (745)" << endl;
		system("pause");
		menu();
	};
	for (auto PS : passengers)
	{
		flow_passenger.write((char*)&PS, sizeof(PS));
	};
	passengers.clear();
	flow_passenger.close();
	flow_tour.open("Tour.cpp", ios::in | ios::out | ios::binary);
	if (!flow_tour) {
		cout << "Ошибка!Возврат в Меню. (757)" << endl;
		system("pause");
		menu();
	};
	while (flow_tour.peek() != EOF) {
		flow_tour.read((char*)&TR, zTR);
		if (TR.number == number) {
			TR.number_seats--;
			flow_tour.seekp(-zTR, ios::cur);
			flow_tour.write((char*)&TR, zTR);
			cout << "Нажмите клавишу для произведения оплаты" << endl;
			system("pause");
			cout << "Оплата произведена успешно. Билет куплен" << endl;
			cout << shT << endl;
			fout << shT << endl;
			vivod_tour();
			flow_tour.close();
			cout << "Для возврата в Меню нажмите любую клавишу" << endl;
			system("pause");
			menu();
		};
	};
};

void menu() {	//меню
	system("cls");
	size_t N;
	cout << "|" << "-----------------------------------------------------------------------------------------------------" << "|" << endl;
	cout << "|" << setw(101) << "                                  Вас приветсвует экран Меню" << "|" << endl;
	cout << "|" << "-----------------------------------------------------------------------------------------------------" << "|" << endl;
	cout << "Дата: " << DT.day << "." << DT.month << "." << DT.year << endl;
	cout << "|" << "-----------------------------------------------------------------------------------------------------" << "|" << endl;
	cout << "|" << setw(5) << "Номер" << "|" << setw(95) << "                                      Вариант обработки" << "|" << endl;
	cout << "|" << "-----------------------------------------------------------------------------------------------------" << "|" << endl;
	cout << "|" << setw(5) << "  1  " << "|" << setw(95) << "Просмотреть список Туров" << "|" << endl;
	cout << "|" << setw(5) << "  2  " << "|" << setw(95) << "Просмотреть список Горящих туров" << "|" << endl;
	cout << "|" << setw(5) << "  3  " << "|" << setw(95) << "Просмотреть список Прошедших туров(до 1 года)" << "|" << endl;
	cout << "|" << setw(5) << "  4  " << "|" << setw(95) << "Дополнить список туров с клавиатуры" << "|" << endl;
	cout << "|" << setw(5) << "  5  " << "|" << setw(95) << "Дополнить список туров из файла" << "|" << endl;
	cout << "|" << setw(5) << "  6  " << "|" << setw(95) << "Исключить тур из системы(информация об участниках будет удалена)" << "|" << endl;
	cout << "|" << setw(5) << "  7  " << "|" << setw(95) << "Просмотреть список участников тура" << "|" << endl;
	cout << "|" << setw(5) << "  8  " << "|" << setw(95) << "Купить Билет на тур" << "|" << endl;
	cout << "|" << setw(5) << "  9  " << "|" << setw(95) << "Вернуть Билет на тур" << "|" << endl;
	cout << "|" << setw(5) << "  0  " << "|" << setw(95) << "Завершить работу" << "|" << endl;
	cout << "|" << "-----------------------------------------------------------------------------------------------------" << "|" << endl << endl;
	cout << "Введите номер выбранного варианта обработки: "; cin >> N;
	if (N == 1) {
		system("cls");
		cout << "Список туров:" << endl;
		fout << "Список туров:" << endl;
		read_tour();
		menu();
	}
	else if (N == 2) {
		system("cls");
		cout << "Список горящих туров:" << endl;
		fout << "Список горящих туров:" << endl;
		read_hot();
		menu();
	}
	else if (N == 3) {
		system("cls");
		cout << "Список прошедших туров:" << endl;
		fout << "Список прошедших туров:" << endl;
		read_old();
		menu();
	}
	else if (N == 4) {
		system("cls");
		cout << "Дополнение списка туров с клавиатуры" << endl;
		addition_tour_keyboard();
	}
	else if (N == 5) {
		system("cls");
		cout << "Дополнение списка туров из файла" << endl;
		fout << "Дополнение списка туров из файла" << endl;
		addition_tour_fail();
	}
	else if (N == 6) {
		system("cls");
		char tour_deleted[10];
		read_tour();
		cout << "Введите название тура, который хотите удалить(max: 10 символов)" << endl;
		cin >> tour_deleted;
		delete_space(tour_deleted);
		delete_tour(tour_deleted);
	}
	else if (N == 7) {
		system("cls");
		read_tour();
		read_passengers();
	}
	else if (N == 8) {
		system("cls");
		cout << "Список туров:" << endl;
		fout << "Список туров:" << endl;
		read_tour();
		cout << "Покупка билетов:" << endl;
		fout << "Покупка билетов:" << endl;
		buy_ticket();
	}
	else if (N == 9) {
		system("cls");
		cout << "Список туров:" << endl;
		fout << "Список туров:" << endl;
		read_tour();
		cout << "Возврат билетов:" << endl;
		fout << "Возврат билетов:" << endl;
		return_ticket();
	}
	else if (N == 0) {
		system("cls");
		remove("Tempor.cpp");
		old.open("OldTour.cpp", ios::in | ios::binary);
		while (!old.eof()) {
			old.read((char*)&TR, zTR);
			remove((string(TR.name_tour) + ".cpp").c_str());
		};
		old.close();
		remove("OldTour.cpp");
		remove("Hot.cpp");
		flow_tour.open("Tour.cpp", ios::in | ios::binary);
		while (!flow_tour.eof()) {
			flow_tour.read((char*)&TR, zTR);
			remove((string(TR.name_tour) + ".cpp").c_str());
		};
		flow_tour.close();
		remove("Tour.cpp");
		fout.close();
		cout << "До скорых встреч!" << endl << "Завершение работы..." << endl;
		exit(0);
	}
	else {
		cout << "Такого варианта обработки не существует, повторите попытку!" << endl;
		system("pause");
		menu();
	};
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fout.open("Proto.res");
	if (!fout) {
		cout << "Ошибка открытия файл протокола" << endl;
		exit(0);
	};
	cout << left;
	fout << left;
	DT.current_date();
	create_list_tour();
	restart_tour();
	hot_tour();
	menu();
	return 0;
}