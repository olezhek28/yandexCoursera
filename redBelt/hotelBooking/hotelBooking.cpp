#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <list>
#include <string>

using namespace std;

struct Room
{
	int clientId;
	int roomCount;
	int64_t time;
};

bool operator<(const Room& lhs, const Room& rhs)
{
	return tie(lhs.clientId, lhs.roomCount, lhs.time) < tie(rhs.clientId, rhs.roomCount, rhs.time);
}

class HotelBooking
{
	map<string, queue<Room>> db;
	map<string, map<int, int64_t>> uniqClients;

	map<string, deque<Room>> events;
	map<string, int> reserveRooms;
	
	int64_t currentTime = 0;
	
public:
	void Book(int64_t time, const string& hotelName, int clientId, int roomCount)
	{
		events[hotelName].push_back({clientId, roomCount, time});
		reserveRooms[hotelName] += roomCount;

		currentTime = time;
		checkEvents();
	}

	void checkEvents()
	{
		for (auto& event : events)
		{
			vector<int> deleteNumbers;
			deleteNumbers.reserve(event.second.size());
			
			for(int i = 0; i < event.second.size(); i++)
			{
				if(llabs(currentTime - event.second[i].time) >= 86400)
				{
					deleteNumbers.push_back(i);
				}
			}

			for(auto& num : deleteNumbers)
			{
				reserveRooms[event.first] -= event.second[num].roomCount;
				event.second.erase(event.second.begin() + num);
			}
		}
	}

	int Clients(const string& hotelName)
	{
		return reserveRooms[hotelName];
	}

	int Rooms(const string& hotelName)
	{
		int count = 0;
		
		for(auto& reservation : events[hotelName])
		{
			if(llabs(currentTime - reservation.time) < 86400)
			{
				count += reservation.roomCount;
			}
		}

		if (count == 0)
			events.erase(hotelName);

		return count;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	HotelBooking manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) 
	{
		string query_type;
		cin >> query_type;

		if (query_type == "BOOK") 
		{
			int64_t time;
			cin >> time;

			string hotelName;
			cin >> hotelName;

			int clientId;
			cin >> clientId;

			int roomCount;
			cin >> roomCount;

			manager.Book(time, hotelName, clientId, roomCount);
		}
		else if (query_type == "CLIENTS") 
		{
			string hotelName;
			cin >> hotelName;
			
			cout << manager.Clients(hotelName) << "\n";
		}
		else if (query_type == "ROOMS")
		{
			string hotelName;
			cin >> hotelName;

			cout << manager.Rooms(hotelName) << "\n";
		}
	}

	return 0;
}