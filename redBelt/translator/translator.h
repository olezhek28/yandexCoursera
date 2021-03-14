#pragma once

#include <set>
#include <map>
#include <string_view>

using namespace std;

class Translator
{
public:
	Translator() = default;
	void Add(string_view source, string_view target);
	string_view TranslateForward(string_view source) const;
	string_view TranslateBackward(string_view target) const;

private:

	string_view GetElement(string_view word);
	static string_view Translate(const map<string_view, string_view>& dict, string_view word);
	
	set<string> words;
	map<string_view, string_view> dictionaryForward;
	map<string_view, string_view> dictionaryBackward;
};
