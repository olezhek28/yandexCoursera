#include "hotel_booking_manager.h"

void HotelBookingManager::AddEvent(const int64_t time, const std::string& hotelName, const int clientId, const int roomCount)
{
	database_[hotelName].Change(time, clientId, roomCount);
	current_time_ = time;
}

int HotelBookingManager::Clients(const std::string& hotelName)
{
	if (database_.find(hotelName) == database_.end())
		return 0;

	database_[hotelName].Update(current_time_);
	return database_[hotelName].GetUniqClientsCount();
}

int HotelBookingManager::Rooms(const std::string& hotelName)
{
	if (database_.find(hotelName) == database_.end())
		return 0;

	database_[hotelName].Update(current_time_);
	return database_[hotelName].GetReservedRoomsCount();
}
