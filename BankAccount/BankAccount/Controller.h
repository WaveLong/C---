#pragma once
#include <vector>
#include "Account.h"
#include "Date.h"

struct deleter {
	template <class T> void operator () (T* p) { delete p; }
};
class Controller {	//�����������������˻��б�ʹ�������
private:
	Date date;					//��ǰ����
	vector<Account*> accounts;	//�˻��б�
	bool end;					//�û��Ƿ��������˳�����
public:
	Controller(const Date& date) : date(date), end(false) { }
	~Controller();

	const Date& getDate() const { return date; }
	bool isEnd() const { return end; }
	//ִ��һ�����������ظ������Ƿ�ı��˵�ǰ״̬�����Ƿ���Ҫ��������
	bool runCommand(const string& cmdLine);
};

