#include "hotel_booking_manager.h"

#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	HotelBookingManager manager;

	int queryCount;
	cin >> queryCount;

	for (int queryId = 0; queryId < queryCount; queryId++) 
	{
		string hotelName;
		string queryType;
		cin >> queryType;

		if (queryType == "BOOK") 
		{
			int64_t time;
			cin >> time;

			cin >> hotelName;

			int clientId;
			cin >> clientId;

			int roomCount;
			cin >> roomCount;

			manager.AddEvent(time, hotelName, clientId, roomCount);
		}
		else if (queryType == "CLIENTS") 
		{
			cin >> hotelName;
			
			cout << manager.Clients(hotelName) << "\n";
		}
		else if (queryType == "ROOMS")
		{
			cin >> hotelName;

			cout << manager.Rooms(hotelName) << "\n";
		}
	}

	return 0;
}