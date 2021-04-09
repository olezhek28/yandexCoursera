#pragma once

#include <map>
#include <set>

using namespace std;

class RouteManager
{
private:
	map<int, set<int>> reachableLists;

public:
	void AddRoute(int start, int finish);

	int FindNearestFinish(int start, int finish) const;
};
