#include <future>

#include "testRunner.h"
#include "profile.h"
#include "paginator.h"

#include <map>
#include <set>
#include <string>
using namespace std;

struct Stats
{
	map<string, int> word_frequences;

	void operator += (const Stats& other)
	{
		for(const auto& word : other.word_frequences)
		{
			word_frequences[word.first] += word.second;
		}
	}
};

Stats ExploreKeyWords(const set<string>& key_words, istream& input)
{
	vector<string> words;

	for (string line; getline(input, line);)
	{
		int startPos = 0;
		
		while(true)
		{
			auto pos = line.find(' ', startPos);
			
			if (pos == std::string::npos)
			{
				words.push_back(line.substr(startPos));
				break;
			}
			
			words.push_back(line.substr(startPos, pos - startPos));
			startPos = pos + 1;
		}
	}

	auto pageSize = words.size() % 4 == 0 ? words.size() / 4 : words.size() / 4 + 1;
	vector<future<Stats>> threadResult;
	threadResult.reserve(words.size() % pageSize == 0 ? words.size() / pageSize : words.size() / pageSize + 1);
	
	for (const auto& page : Paginate(words, pageSize))
	{
		threadResult.push_back(async([key_words, page]
		{
			Stats result;

			for(const auto& word : page)
			{
				if (key_words.find(word) != key_words.end())
					++result.word_frequences[word];
			}
			
			return result;
		}));
	}

	Stats result;
	for(auto& thread : threadResult)
	{
		auto tmpRes = thread.get();

		for (auto& res : tmpRes.word_frequences)
		{
			result.word_frequences[res.first] += res.second;
		}
	}

	return result;
}

void TestBasic()
{
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);

	const map<string, int> expected = 
	{
		{"yangle", 6},
		{"rocks", 2},
		{"sucks", 1}
	};
	
	ASSERT_EQUAL(stats.word_frequences, expected);
}


int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}
