#include "event_info.h"

constexpr int kSecondsPerDay = 86400;

void EventInfo::Change(const int64_t time, const int clientId, const int roomCount)
{
	if (uniq_clients_.find(clientId) == uniq_clients_.end())
	{
		uniq_clients_[clientId] = 1;
		++uniq_clients_count_;
	}
	else
	{
		++uniq_clients_[clientId];
	}

	events_.push({time, clientId, roomCount});
	reserved_rooms_count_ += roomCount;
}

void EventInfo::Update(const int64_t time)
{
	while (!events_.empty() && events_.front().time <= (time - kSecondsPerDay))
	{
		reserved_rooms_count_ -= events_.front().room_count;
		--uniq_clients_[events_.front().client_id];

		auto it = uniq_clients_.find(events_.front().client_id);

		if (it->second == 0)
		{
			uniq_clients_.erase(it);
			--uniq_clients_count_;
		}

		events_.pop();
	}
}

int EventInfo::GetUniqClientsCount() const
{
	return uniq_clients_count_;
}

int EventInfo::GetReservedRoomsCount() const
{
	return reserved_rooms_count_;
}