#pragma once
/*
定义单个账户，包含的参数：
-id：账户编号
-balance：当前账户余额
-record_map：存取记录
方法：
-save：存
-withdraw：取
-settle：利息结算
-query：查询指定时间内的交易信息
-show：打印账户信息
-get_balance：获取账户余额
*/
#include "Date.h"
#include "Accumulator.h"
#include <iostream>
#include<string>
#include<map>

using namespace std;

class Account; // 前置引用声明

/********************AccountRecord********************/
class AccountRecord {
private:
	Date date; // 交易时间
	Account *account; //交易账户
	double amount; // 交易数额
	double balance; // 交易后账户余额
	string desc; //交易备注
public:
	AccountRecord() = default;
	AccountRecord(const Date& date, Account* account, double amount, double balance, const string& desc);
	void show() const; //打印信息
};

typedef multimap<Date, AccountRecord> RecordMap;

/********************账户基类************************/
class Account {
private:
	string id;
	double balance;
	static double total_balance; //所有账户的资产总和
	static RecordMap record_map; //所有账户的交易记录
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

/********************储蓄账户***********************/
class SavingAccount : public Account{ //储蓄账户
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

/********************信用卡账户*********************/
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
	double get_available_credit() {	//获得可用信用
		if (get_balance() < 0)
			return credit + get_balance();
		else
			return credit;
	}
	double get_debt() {	//获得欠款额
		double balance = get_balance();
		return (balance < 0 ? balance : 0);
	}

	virtual void save(Date& date, double amount, const string& desc);
	virtual void withdraw(Date& date, double amount, const string& desc);
	virtual void settle(const Date& date);
	virtual void show(ostream& out);
};