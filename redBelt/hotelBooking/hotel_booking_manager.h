#pragma once

#include "event_info.h"

#include <cstdint>
#include <map>
#include <string>



class HotelBookingManager
{
public:
	void AddEvent(const int64_t time, const std::string& hotelName, const int clientId, const int roomCount);
	int Clients(const std::string& hotelName);
	int Rooms(const std::string& hotelName);

private:
	std::map<std::string, EventInfo> database_;
	int64_t current_time_ = 0;
};
