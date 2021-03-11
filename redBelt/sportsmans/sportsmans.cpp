#include "sportsmans.h"

#include <iostream>

void Sportsmans::add(int numberSportsman, int numberNextSportsman)
{
	auto it = std::find(list.begin(), list.end(), numberNextSportsman);

	if (it == list.end())
	{
		list.push_back(numberSportsman);
	}
	else
	{
		list.insert(it , numberSportsman);
	}
}

void Sportsmans::print()
{
	for (auto value : list)
	{
		std::cout << value << '\n';
	}
}