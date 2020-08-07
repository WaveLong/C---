#pragma once
/*
���嵥���˻��������Ĳ�����
-id���˻����
-balance����ǰ�˻����
-record_map����ȡ��¼
������
-save����
-withdraw��ȡ
-settle����Ϣ����
-query����ѯָ��ʱ���ڵĽ�����Ϣ
-show����ӡ�˻���Ϣ
-get_balance����ȡ�˻����
*/
#include "Date.h"
#include "Accumulator.h"
#include <iostream>
#include<string>
#include<map>

using namespace std;

class Account; // ǰ����������

/********************AccountRecord********************/
class AccountRecord {
private:
	Date date; // ����ʱ��
	Account *account; //�����˻�
	double amount; // ��������
	double balance; // ���׺��˻����
	string desc; //���ױ�ע
public:
	AccountRecord() = default;
	AccountRecord(const Date& date, Account* account, double amount, double balance, const string& desc);
	void show() const; //��ӡ��Ϣ
};

typedef multimap<Date, AccountRecord> RecordMap;

/********************�˻�����************************/
class Account {
private:
	string id;
	double balance;
	static double total_balance; //�����˻����ʲ��ܺ�
	static RecordMap record_map; //�����˻��Ľ��׼�¼
protected:
	void record(const Date& date, double amount, const string& desc);
public:
	Account() = default;
	Account(const Date &date, const string& id);

	string get_id() { return id; }
	double get_balance() { return balance; }
	double get_total() { return total_balance; }

	virtual void save(Date &date, double amount, const string &desc) = 0;
	virtual void withdraw(Date& date, double amount, const string& desc) = 0;
	virtual void settle(const Date& date) = 0;

	virtual void show(ostream &out);
	static void query(const Date& begin, const Date& end);
};

inline std::ostream& operator << (std::ostream& out, Account& account) {
	account.show(out);
	return out;
}

/********************�����˻�***********************/
class SavingAccount : public Account{ //�����˻�
private:
	Accumulator acc;
	double rate;
public:
	SavingAccount() = default;
	SavingAccount(Date& date, string& id, double rate);

	double get_rate() { return rate; }
	virtual void save(Date& date, double amount, const string& desc);
	virtual void withdraw(Date& date, double amount, const string& desc);
	virtual void settle(const Date& date);
	virtual void show(ostream &out);
};

/********************���ÿ��˻�*********************/
class CreditAccount : public Account {
private:
	Accumulator acc;
	double rate, fee, credit;
public:
	CreditAccount() = default;
	CreditAccount(Date& date, string id, double rate, double credit, double fee);
	double get_rate() { return rate; }
	double get_credit() { return credit; }
	double get_fee() { return fee; }
	double get_available_credit() {	//��ÿ�������
		if (get_balance() < 0)
			return credit + get_balance();
		else
			return credit;
	}
	double get_debt() {	//���Ƿ���
		double balance = get_balance();
		return (balance < 0 ? balance : 0);
	}

	virtual void save(Date& date, double amount, const string& desc);
	virtual void withdraw(Date& date, double amount, const string& desc);
	virtual void settle(const Date& date);
	virtual void show(ostream& out);
};