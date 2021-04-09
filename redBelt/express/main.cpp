#include <iostream>
#include <sstream>

#include "routeManager.h"

using namespace std;

int main()
{
	RouteManager routes;

	int queryCount;
	cin >> queryCount;

	for (int queryId = 0; queryId < queryCount; ++queryId) 
	{
		string queryType;
		cin >> queryType;
		
		int start, finish;
		cin >> start >> finish;

		if (queryType == "ADD") 
		{
			routes.AddRoute(start, finish);
		}
		else if (queryType == "GO") 
		{
			cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}

	return 0;
}