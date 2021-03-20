#include "testRunner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
using Key = String;

template <typename String>
Key<String> GenerateKey(const String& word)
{
	String tmpStr = word;

	std::sort(tmpStr.begin(), tmpStr.end());
	tmpStr.erase(std::unique(tmpStr.begin(), tmpStr.end()), tmpStr.end());

	return tmpStr;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings)
{
	map<Key<String>, Group<String>> uniqMap;
	vector<Group<String>> group;
	
	for (auto& word : strings)
	{
		uniqMap[GenerateKey(word)].push_back(move(word));
	}

	group.reserve(uniqMap.size());
	for(auto& val : uniqMap)
	{
		group.push_back(move(val.second));
	}

	return group;
}


void TestGroupingABC()
{
	vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
	ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal()
{
	vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
	ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
	ASSERT_EQUAL(groups[2], vector<string>({"port"}));
	ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);
	return 0;
}
