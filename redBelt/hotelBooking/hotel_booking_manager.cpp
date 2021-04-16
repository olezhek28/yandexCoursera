#include "hotel_booking_manager.h"

void HotelBookingManager::AddBooking(const int64_t time, const std::string& hotel_name, const int client_id, const int room_count)
{
	database_[hotel_name].Change(time, client_id, room_count);
	last_booking_time_ = time;
}

int HotelBookingManager::CountClientsForLastDay(const std::string& hotel_name)
{
	if (database_.find(hotel_name) == database_.end())
		return 0;

	database_[hotel_name].Update(last_booking_time_);
	return database_[hotel_name].get_number_of_unique_clients();
}

int HotelBookingManager::CountReservedRoomsForLastDay(const std::string& hotel_name)
{
	if (database_.find(hotel_name) == database_.end())
		return 0;

	database_[hotel_name].Update(last_booking_time_);
	return database_[hotel_name].get_number_of_reserved_rooms();
}
