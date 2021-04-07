#pragma once

#include <cstdint>
#include <string>
#include <tuple>

using namespace std;

struct Date
{
	int year, month, day;
};

struct Time
{
	int hours, minutes;
};

struct AirlineTicket
{
	string from;
	string to;
	string airline;
	Date departure_date;
	Time departure_time;
	Date arrival_date;
	Time arrival_time;
	uint64_t price;
};

bool operator < (const Date& date1, const Date& date2)
{
	return std::tie(date1.year, date1.month, date1.day) < std::tie(date2.year, date2.month, date2.day);
}

bool operator == (const Date& date1, const Date& date2)
{
	return std::tie(date1.year, date1.month, date1.day) == std::tie(date2.year, date2.month, date2.day);
}

ostream& operator << (ostream& os, const Date& date)
{
	os << date.year << '-' << date.month << '-' << date.day;
	return os;
}

bool operator < (const Time& time1, const Time& time2)
{
	return std::tie(time1.hours, time1.minutes) < std::tie(time2.hours, time2.minutes);
}

bool operator == (const Time& time1, const Time& time2)
{
	return std::tie(time1.hours, time1.minutes) == std::tie(time2.hours, time2.minutes);
}

ostream& operator << (ostream& os, const Time& time)
{
	os << time.hours << ':' << time.minutes;
	return os;
}

#define SORT_BY(field)\
[](const AirlineTicket& lhs, const AirlineTicket& rhs)  \
{                                                       \
	return lhs.field < rhs.field;                       \
}