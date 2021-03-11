#pragma once
#include <vector>

class Sportsmans
{
private:
	std::vector<int> list;

public:
	void add(int numberSportsman, int numberNextSportsman);
	void print();
	void reserve(int size);
};
