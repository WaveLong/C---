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
命令：
-创建新账户： [N]ew type id rate [credit, fee]
type：账户类型，[s]avings/[c]redit
rate：利率
credit：信用卡账户额度
fee：信用卡用户年费
-存款：[D]eposite id amount description
-取款：[W]ithdraw id amount description
-查询各个账户信息：[S]how
-查询某段时间的账目：[Q]uery date1 date2

-当前日期：[T]ime
-改变日期：[C]hange
-进入下一个月：[M]onth
-退出：[q]uit
*/
bool Controller::runCommand(const string& cmd_line) {
	istringstream out(cmd_line);
	char operation_type;
	//创建账户的参数
	char type;
	string id;
	double rate, credit, fee;
	//存取款参数
	int index;
	double amount;
	string desc;
	//查询参数
	Date date1, date2;
	//修改日期参数
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
