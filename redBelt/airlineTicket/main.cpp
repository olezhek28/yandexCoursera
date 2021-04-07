#include <algorithm>
#include <vector>

#include "airlineTicket.h"
#include "test_runner.h"

using namespace std;


void TestSortBy()
{
	std::vector<AirlineTicket> tixs = 
	{
		{"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
		{"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
		{"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
		{"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
		{"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
	};

	sort(begin(tixs), end(tixs), SORT_BY(price));
	ASSERT_EQUAL(tixs.front().price, 1200);
	ASSERT_EQUAL(tixs.back().price, 9000);

	sort(begin(tixs), end(tixs), SORT_BY(from));
	ASSERT_EQUAL(tixs.front().from, "AER");
	ASSERT_EQUAL(tixs.back().from, "VKO");

	sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
	ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
	ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

void TestUpdate()
{
	AirlineTicket t;
	t.price = 0;

	const map<string, string> updates1 = 
	{
		{"departure_date", "2018-2-28"},
		{"departure_time", "17:40"},
	};
	
	
	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);
	UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
	ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
	ASSERT_EQUAL(t.price, 0);

	const map<string, string> updates2 = 
	{
		{"price", "12550"},
		{"arrival_time", "20:33"},
	};
	
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);

	ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
	ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestSortBy);
	RUN_TEST(tr, TestUpdate);

	return 0;
}