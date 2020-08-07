#pragma once
#include<iostream>
using namespace std;

class Date {
private:
	int year, month, day;
	int total_days; //从公元元年1月1日计算

public:
	Date(int year = 1, int month = 1, int day = 1);
	int get_year() const { return year; }
	int get_month() const { return month; }
	int get_day() const { return day; }
	int get_max_day(); //获取当前月有多少天

	bool is_leep_year() const { // 是否是闰年
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}

	int operator - (const Date& a) const{
		return total_days - a.total_days;
	}
	bool operator < (const Date& a)const {
		return total_days < a.total_days;
	}
};

std::istream& operator >> (std::istream& in, Date& date);
std::ostream& operator << (std::ostream& out, const Date& date);