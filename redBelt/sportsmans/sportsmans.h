#pragma once
#include <list>

class Sportsmans
{
private:
	std::list<int> list;

public:
	void add(int numberSportsman, int numberNextSportsman);
	void print();
};
