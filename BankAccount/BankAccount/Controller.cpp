#include "Controller.h"
#include<iostream>
#include<sstream>
#include<string>
#include <algorithm>
#include<cstdlib>
using namespace std;
Controller::~Controller() {
	for_each(accounts.begin(), accounts.end(), deleter());
}

/*
���
-�������˻��� [N]ew type id rate [credit, fee]
type���˻����ͣ�[s]avings/[c]redit
rate������
credit�����ÿ��˻����
fee�����ÿ��û����
-��[D]eposite id amount description
-ȡ�[W]ithdraw id amount description
-��ѯ�����˻���Ϣ��[S]how
-��ѯĳ��ʱ�����Ŀ��[Q]uery date1 date2

-��ǰ���ڣ�[T]ime
-�ı����ڣ�[C]hange
-������һ���£�[M]onth
-�˳���[q]uit
*/
bool Controller::runCommand(const string& cmd_line) {
	istringstream out(cmd_line);
	char operation_type;
	//�����˻��Ĳ���
	char type;
	string id;
	double rate, credit, fee;
	//��ȡ�����
	int index;
	double amount;
	string desc;
	//��ѯ����
	Date date1, date2;
	//�޸����ڲ���
	int day;

	out >> operation_type;
	switch(operation_type) {
	// N s C11234 0.5
	// N c S442i9 0.5 3000 50
	case 'N':
		out >> type;
		if (type == 's') {
			out >> id >> rate;
			SavingAccount *p = new SavingAccount(date, id, rate);
			accounts.push_back(p);
		}
		else {
			out >> id >> rate >> credit >> fee;
			CreditAccount *p = new CreditAccount(date, id, rate, credit, fee);
			accounts.push_back(p);
		}
		return true;
	// D id amount description
	case 'D':
		out >> index >> amount >> desc;
		accounts[index]->save(date, amount, desc);
		return true;
	// W id amount description
	case 'W':
		out >> index >> amount >> desc;
		accounts[index]->withdraw(date, amount, desc);
		return true;
	// S 
	case 'S':
		for (int i = 0; i < accounts.size(); ++i) {
			cout << "[" << i << "] " << *accounts[i] << endl;
		}
		return true;
	// Q date1 date2
	case 'Q':
		out >> date1 >> date2;
		if (!(date1 < date2)) {
			cout << "Invalid date interval..." << endl;
			return false;
		}
		Account::query(date1, date2);
		return true;
	case 'T':
		cout <<"Current date: "<< date << endl;
		return true;
	case 'C':
		out >> day;
		if (day > date.get_max_day()) {
			cout << "Invalid day..." << endl;
			return false;
		}
		else if(day < date.get_day()){
			cout << "You cannot specify a previous day" << endl;
			return false;
		}
		date = Date(date.get_year(), date.get_month(), day);
		cout << "Current date: " << date << endl;
		return true;
	case 'M':
		if (date.get_month() == 12) {
			date = Date(date.get_year() + 1, 1, 1);
		}
		else {
			date = Date(date.get_year(), date.get_month() + 1, 1);
		}
		for (int i = 0; i < accounts.size(); ++i) accounts[i]->settle(date);
		cout << "Current date: " << date << endl;
		return true;
	case 'q':
		end = true;
		return true;
	}
	return false;
}
