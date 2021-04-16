#include "hotel_booking_manager.h"

#include <iostream>

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	HotelBookingManager manager;

	int queryCount;
	std::cin >> queryCount;

	for (int queryId = 0; queryId < queryCount; queryId++) 
	{
		std::string hotelName;
		std::string queryType;
		std::cin >> queryType;

		if (queryType == "BOOK") 
		{
			int64_t time;
			std::cin >> time;

			std::cin >> hotelName;

			int clientId;
			std::cin >> clientId;

			int roomCount;
			std::cin >> roomCount;

			manager.AddBooking(time, hotelName, clientId, roomCount);
		}
		else if (queryType == "CLIENTS") 
		{
			std::cin >> hotelName;
			
			std::cout << manager.CountClientsForLastDay(hotelName) << "\n";
		}
		else if (queryType == "ROOMS")
		{
			std::cin >> hotelName;

			std::cout << manager.CountReservedRoomsForLastDay(hotelName) << "\n";
		}
	}

	return 0;
}