#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Room
{
	int clientId;
	int roomCount;
	int time;
};

class HotelBooking
{
	map<string, vector<Room>> db;
	int currentTime = 0;
	
public:
	void Book(int time, const string& hotelName, int clientId, int roomCount)
	{
		db[hotelName].push_back({clientId, roomCount, time});
		currentTime = time;
	}

	int Clients(const string& hotelName)
	{
		return db[hotelName].size();
	}

	int Rooms(const string& hotelName)
	{
		int count = 0;
		
		for(auto room : db[hotelName])
		{
			if((currentTime - room.time) < 86400)
				count++;
		}

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
			int time;
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