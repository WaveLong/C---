#pragma once
#include <vector>
#include "Account.h"
#include "Date.h"

struct deleter {
	template <class T> void operator () (T* p) { delete p; }
};
class Controller {	//控制器，用来储存账户列表和处理命令
private:
	Date date;					//当前日期
	vector<Account*> accounts;	//账户列表
	bool end;					//用户是否输入了退出命令
public:
	Controller(const Date& date) : date(date), end(false) { }
	~Controller();

	const Date& getDate() const { return date; }
	bool isEnd() const { return end; }
	//执行一条命名，返回该命令是否改变了当前状态（即是否需要保存该命令）
	bool runCommand(const string& cmdLine);
};

