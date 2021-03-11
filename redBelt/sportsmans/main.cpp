#include <iostream>
#include "sportsmans.h"

int main()
{
	Sportsmans sportsmans;
	int numSportsmans;

	std::cin >> numSportsmans;

	sportsmans.reserve(numSportsmans);

	while(numSportsmans-- > 0)
	{
		int numberSportsman, numberNextSportsman;

		std::cin >> numberSportsman >> numberNextSportsman;
		sportsmans.add(numberSportsman, numberNextSportsman);
	}

	sportsmans.print();
}