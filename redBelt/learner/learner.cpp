#include "learner.h"


int Learner::Learn(const vector<string>& words)
{
	size_t oldSize = dict.size();
	for (const auto& word : words)
	{
		dict.insert(word);
	}
	return dict.size() - oldSize;
}

vector<string> Learner::KnownWords()
{
	return {dict.begin(), dict.end()};
}
