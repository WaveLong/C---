#pragma once
#include "Date.h"

class Accumulator {
private:
	Date last_date; //上一次计算的日期
	double value; //基数
	double sum; //利息
public:
	Accumulator() = default;
	Accumulator(Date date, double value);
	double get_sum(const Date& date);//获取累积的利息，结利时使用
	void change(const Date& date, double value);//修改账户总金额，账户余额变动时使用
	void reset(const Date& date, double value);//重置，结利之后使用
};