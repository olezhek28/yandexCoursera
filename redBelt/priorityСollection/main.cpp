#include "testRunner.h"
#include "priorityСollection.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>

class StringNonCopyable : public string
{
public:
	using string::string;  // Позволяет использовать конструкторы строки
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy()
{
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");
	
	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) 
	{
		strings.Promote(red_id);
	}

	strings.Promote(yellow_id);
	
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	/*vector<pair<priority, val>> tmp2;
	set<pair<priority, id>> tmp;

	tmp.insert(make_pair(1, 7));
	tmp.insert(make_pair(4, 2));
	tmp.insert(make_pair(2, 7));
	tmp.insert(make_pair(-3, 3));

	for(auto& t : tmp)
		cout << t.first << ' ' << t.second << endl;*/

	return 0;
}