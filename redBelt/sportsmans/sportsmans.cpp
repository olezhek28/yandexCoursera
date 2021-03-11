#include "sportsmans.h"

#include <iostream>
#include <algorithm>

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

void Sportsmans::reserve(int size)
{
	list.reserve(size);
}
