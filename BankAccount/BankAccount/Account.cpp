#include "Account.h"
#include<cstdlib>

using namespace std;

/*****************AccountRecord******************/
AccountRecord::AccountRecord(const Date& date, Account* account, double amount, double balance, const string& desc) : 
	date(date), account(account), amount(amount), balance(balance), desc(desc){}

void AccountRecord::show() const {//打印信息
	cout << date << "\t#" << account->get_id() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
} 

/*****************Account************************/
double Account::total_balance = 0;
RecordMap Account::record_map;
Account::Account(const Date& date, const string& id) : id(id), balance(0) { }

void Account::record(const Date &date, double amount, const string & desc) {
	//改
	balance += amount;
	total_balance += amount;
	//记
	AccountRecord tmp_record(date, this, amount, balance, desc);
	tmp_record.show();
	record_map.insert(make_pair(date, tmp_record));
}

void Account::show(ostream& out) {
	out << id << "\tBalance: " << balance;
}

void Account::query(const Date& begin, const Date& end) {
	for (auto iter = record_map.begin(); iter != record_map.end(); ++iter) {
		iter->second.show();
	}
}

/***************SavingsAccount*******************/
SavingAccount::SavingAccount(Date& date, string& id, double rate) : 
	Account(date, id) , rate(rate), acc(Accumulator(date, 0)){
	cout << date << " create a new saving account #" << id << endl;
}

void SavingAccount::save(Date& date, double amount, const string& desc) {
	record(date, amount, desc);
	acc.change(date, get_balance());
}
void SavingAccount::withdraw(Date& date, double amount, const string& desc) {
	if (amount < get_balance()) {
		record(date, -amount, desc);
		acc.change(date, get_balance());
	}
	else {
		cout << "Not enough money!" << endl;
		exit(0);
	}
	
}
void SavingAccount::settle(const Date& date) {
	if (date.get_month() == 1) { // 每年一月计算利息
		double interest = acc.get_sum(date) * rate / (date - Date(date.get_year() - 1, 1, 1));
		if (interest != 0) {
			record(date, interest, "Interest");
		}
		acc.reset(date, get_balance());
	}
	else {
		cout << "Not at settling time..." << endl;
	}
}

void SavingAccount::show(ostream& out) {
	out << "Saving Account\t";
	Account::show(out);
	out << endl;
}

/***************CreditAccount***********************/
CreditAccount::CreditAccount(Date& date, string id, double rate, double credit, double fee):
	Account(date, id), rate(rate), credit(credit), fee(fee), acc(Accumulator(date, 0)){
	cout << date << " create a new credit account #" << id << endl;
}

void CreditAccount::save(Date& date, double amount, const string& desc) {
	cout << "Balance: " << get_balance() << endl;
	record(date, amount, desc);
	acc.change(date, get_debt());
}
void CreditAccount::withdraw(Date& date, double amount, const string& desc) {
	if (get_balance() + credit < amount) {
		cout << "Your credit is not enough..." << endl;
	}
	else {
		record(date, amount, desc);
		acc.change(date, get_debt());
	}
}
void CreditAccount::settle(const Date& date) {
	double interest = acc.get_sum(date) * rate;
	if (interest != 0)
		record(date, interest, " Interest");
	if (date.get_month() == 1)
		record(date, -fee, " annual fee");
	acc.reset(date, get_debt());
}

void CreditAccount::show(ostream& out) {
	cout << "Credit Account\t";
	Account::show(out);
	out << "\tAvailable credit:" << get_available_credit() << endl;
}
