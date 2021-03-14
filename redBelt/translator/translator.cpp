#include "translator.h"

void Translator::Add(string_view source, string_view target)
{
	const string_view sourceTmp = GetElement(source);
	const string_view targetTmp = GetElement(target);

	dictionaryForward[sourceTmp] = targetTmp;
	dictionaryBackward[targetTmp] = sourceTmp;
}

string_view Translator::TranslateForward(string_view source) const
{
	return Translate(dictionaryForward, source);
}

string_view Translator::TranslateBackward(string_view target) const
{
	return Translate(dictionaryBackward, target);
}

string_view Translator::GetElement(string_view word)
{
	return *words.emplace(word).first;
}

string_view Translator::Translate(const map<string_view, string_view>& dict, string_view word)
{
	auto it = dict.find(word);

	if (it == dict.end())
		return {};

	return it->second;
}
