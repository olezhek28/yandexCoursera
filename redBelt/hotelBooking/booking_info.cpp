#include "booking_info.h"

constexpr int kSecondsPerDay = 86400;

void BookingInfo::Change(const int64_t time, const int client_id, const int room_count)
{
	if (unique_clients_.find(client_id) == unique_clients_.end())
	{
		unique_clients_[client_id] = 1;
		++number_of_unique_clients_;
	}
	else
	{
		++unique_clients_[client_id];
	}

	booking_.push({ time, client_id, room_count });
	number_of_reserved_rooms_ += room_count;
}

void BookingInfo::Update(const int64_t time)
{
	while (!booking_.empty() && booking_.front().time <= (time - kSecondsPerDay))
	{
		number_of_reserved_rooms_ -= booking_.front().room_count;
		--unique_clients_[booking_.front().client_id];

		auto it = unique_clients_.find(booking_.front().client_id);

		if (it->second == 0)
		{
			unique_clients_.erase(it);
			--number_of_unique_clients_;
		}

		booking_.pop();
	}
}

int BookingInfo::get_number_of_reserved_rooms() const
{
	return number_of_reserved_rooms_;
}

int BookingInfo::get_number_of_unique_clients() const
{
	return number_of_unique_clients_;
}
