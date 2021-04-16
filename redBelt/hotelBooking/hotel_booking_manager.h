#pragma once

#include "booking_info.h"

#include <cstdint>
#include <map>
#include <string>

class HotelBookingManager
{
public:
	void AddBooking(const int64_t time, const std::string& hotel_name, const int client_id, const int room_count);
	int CountClientsForLastDay(const std::string& hotel_name);
	int CountReservedRoomsForLastDay(const std::string& hotel_name);

private:
	std::map<std::string, BookingInfo> database_;
	int64_t last_booking_time_ = 0;
};
