#include "Date.h"
#include<iostream>
using namespace std;
namespace {
	//存储平年中某个月1日之前有多少天，为便于getMaxDay函数的实现，该数组多出一项
	const int DAYS_BEFORE_MONTH[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
}

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {
	//计算total_days
	if(day > get_max_day())throw runtime_error("Invalid date");

	total_days = year * 365 + year / 4 - year / 100 + year / 400 \
		+ DAYS_BEFORE_MONTH[month - 1] + day;

	if (is_leep_year())total_days++;
}
int Date::get_max_day() {
	if (is_leep_year() && month == 2)return 29;
	return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1];
}

istream& operator >> (std::istream& in, Date& date) {
	int year, month, day;
	char c1, c2;
	in >> year >> c1 >> month >> c2 >> day;
	if (c1 != '-' || c2 != '-')throw runtime_error("Invalid time format");
	date = Date(year, month, day);
	return in;
}
ostream& operator << (std::ostream& out, const Date& date) {
	out << date.get_year() << "-" << date.get_month() << "-" << date.get_day();
	return out;
}