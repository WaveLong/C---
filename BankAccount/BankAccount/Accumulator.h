#pragma once
#include "Date.h"

class Accumulator {
private:
	Date last_date; //��һ�μ��������
	double value; //����
	double sum; //��Ϣ
public:
	Accumulator() = default;
	Accumulator(Date date, double value);
	double get_sum(const Date& date);//��ȡ�ۻ�����Ϣ������ʱʹ��
	void change(const Date& date, double value);//�޸��˻��ܽ��˻����䶯ʱʹ��
	void reset(const Date& date, double value);//���ã�����֮��ʹ��
};