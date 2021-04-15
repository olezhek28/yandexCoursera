#pragma once
#include <cstdint>
#include <map>
#include <queue>

class EventInfo
{
	struct Event
	{
		int64_t time = 0;
		int client_id = 0;
		int room_count = 0;
	};

public:
	EventInfo() = default;

	void Change(const int64_t time, const int clientId, const int roomCount);
	void Update(const int64_t time);
	int GetUniqClientsCount() const;
	int GetReservedRoomsCount() const;

private:
	int reserved_rooms_count_ = 0;
	int uniq_clients_count_ = 0;
	std::map<int, int> uniq_clients_;
	std::queue<Event> events_;
};
