#include "Accumulator.h"

Accumulator::Accumulator(Date date, double value) : last_date(date), value(value), sum(0) {}

double Accumulator::get_sum(const Date& date) {
	return sum + value * (date - last_date);
}

void Accumulator::change(const Date& date, double value) {
	last_date = date;
	this->value = value;
}

void Accumulator::reset(const Date& date, double value) {
	last_date = date;
	this->value = value;
	sum = 0;
}