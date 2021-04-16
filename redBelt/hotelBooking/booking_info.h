#pragma once

#include <cstdint>
#include <map>
#include <queue>

class BookingInfo
{
	struct Booking
	{
		int64_t time = 0;
		int client_id = 0;
		int room_count = 0;
	};

public:
	BookingInfo() = default;

	void Change(const int64_t time, const int client_id, const int room_count);
	void Update(const int64_t time);
	
	int get_number_of_reserved_rooms() const;
	int get_number_of_unique_clients() const;

private:
	int number_of_reserved_rooms_ = 0;
	int number_of_unique_clients_ = 0;
	std::map<int, int> unique_clients_;
	std::queue<Booking> booking_;
};
