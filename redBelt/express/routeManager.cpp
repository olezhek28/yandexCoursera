#include <algorithm>

#include "routeManager.h"

void RouteManager::AddRoute(int start, int finish)
{
	reachableLists[start].insert(finish);
	reachableLists[finish].insert(start);
}

int RouteManager::FindNearestFinish(int start, int finish) const
{
	int result = abs(start - finish);

	if (reachableLists.count(start) < 1)
	{
		return result;
	}

	const set<int>& reachableStations = reachableLists.at(start);

	if (!reachableStations.empty())
	{
		auto finishIt = reachableStations.lower_bound(finish);

		if (finishIt != reachableStations.end())
		{
			result = min(result, abs(finish - *finishIt));
		}

		if (finishIt != reachableStations.begin())
		{
			result = min(result, abs(finish - *prev(finishIt)));
		}
	}

	return result;
}
