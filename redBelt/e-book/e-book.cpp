#include <iomanip>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <utility>

#include "profile.h"

#include "test_runner.h"

using namespace std;

class ReadingManager
{
public:
	ReadingManager();

	void Read(int user_id, int page_count);
	double Cheer(int user_id) const;

private:
	// —татическое поле не принадлежит какому-то конкретному
	// объекту класса. ѕо сути это глобальна€ переменна€,
	// в данном случае константна€.
	// Ѕудь она публичной, к ней можно было бы обратитьс€ снаружи
	// следующим образом: ReadingManager::MAX_USER_COUNT.
	static const int MAX_USER_COUNT_ = 100'000;
	static const int MAX_PAGES_COUNT_ = 100'000;

	//vector<int> user_page_counts_;
	//vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
	//vector<int> user_positions_; // позиции в векторе sorted_users_

	//vector<pair<int, int>> dbUsers;

	/*vector<list<int>> dbPages;*/
	vector<int> dbUsers;
	
	int GetUserCount() const;
	void AddUser(int user_id);
	void SwapUsers(int lhs_position, int rhs_position);
};

ReadingManager::ReadingManager(): /*user_page_counts_(MAX_USER_COUNT_ + 1, 0),
									sorted_users_(),
									user_positions_(MAX_USER_COUNT_ + 1, -1),*/
									dbUsers(MAX_USER_COUNT_, 0)
{
	//dbPages.resize(MAX_PAGES_COUNT_);
}

void ReadingManager::Read(int user_id, int page_count)
{
	/*if(dbUsers[user_id] != 0)
	{
		auto it = std::find(dbPages[dbUsers[user_id]].begin(), dbPages[dbUsers[user_id]].end(), user_id);
		dbPages[dbUsers[user_id]].erase(it);
	}*/

	//dbPages[page_count].insert(dbPages[page_count].begin(), user_id);
	dbUsers[user_id] = page_count;
	
	/*if (user_page_counts_[user_id] == 0)
	{
		AddUser(user_id);
	}

	user_page_counts_[user_id] = page_count;
	int& position = user_positions_[user_id];

	while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]])
	{
		SwapUsers(position, position - 1);
	}*/
}

double ReadingManager::Cheer(int user_id) const
{
	if(dbUsers[user_id] == 0)
		return 0;

	/*if(dbUsers.size() == 1)
		return 1;*/

	int lessCount = 0;
	int total = 0;

	for (auto user : dbUsers)
	{
		if(user > 0)
		{
			total++;

			if (user < dbUsers[user_id])
				lessCount++;
		}
	}
	
	/*for(int i = 0; i < dbPages.size(); i++)
	{
		if (i < dbUsers[user_id])
			lessCount += dbPages[i].size();

		total += dbPages[i].size();
	}*/

	if(total == 1)
		return 1;

	return static_cast<double>(lessCount) / static_cast<double>(total - 1);
	
	//if (user_page_counts_[user_id] == 0)
	//{
	//	return 0;
	//}

	//const int user_count = GetUserCount();
	//if (user_count == 1)
	//{
	//	return 1;
	//}

	//const int page_count = user_page_counts_[user_id];
	//int position = user_positions_[user_id];

	//while (position < user_count &&
	//	user_page_counts_[sorted_users_[position]] == page_count)
	//{
	//	++position;
	//}

	//if (position == user_count)
	//{
	//	return 0;
	//}
	//// ѕо умолчанию деление целочисленное, поэтому
	//// нужно привести числитель к типу double.
	//// ѕростой способ сделать это Ч умножить его на 1.0.
	//return (user_count - position) * 1.0 / (user_count - 1);
}

//int ReadingManager::GetUserCount() const
//{
//	return sorted_users_.size();
//}
//
//void ReadingManager::AddUser(int user_id)
//{
//	sorted_users_.push_back(user_id);
//	user_positions_[user_id] = sorted_users_.size() - 1;
//}
//
//void ReadingManager::SwapUsers(int lhs_position, int rhs_position)
//{
//	const int lhs_id = sorted_users_[lhs_position];
//	const int rhs_id = sorted_users_[rhs_position];
//	swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
//	swap(user_positions_[lhs_id], user_positions_[rhs_id]);
//}

//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//
//	ReadingManager manager;
//
//	int query_count = 1'000'000;
//
//	{
//		LOG_DURATION("add");
//		
//		for (int query_id = 0; query_id < query_count; ++query_id) 
//		{
//			/*string query_type;
//			cin >> query_type;*/
//			
//			int user_id = rand() % 1'00'000 + 0;
//			int page_count = rand() % 1000 + 0;
//			manager.Read(user_id, page_count);
//		}
//	}
//
//	{
//		LOG_DURATION("find")
//		
//		for (int query_id = 0; query_id < query_count; ++query_id) 
//		{
//			/*string query_type;
//			cin >> query_type;*/
//			
//			int user_id = rand() % 1'00'000 + 0;
//			manager.Cheer(user_id);
//		}
//	}
//
//	return 0;
//}

void test()
{
    //LOG_DURATION("tests ")
    ReadingManager manager;
    ASSERT_EQUAL(manager.Cheer(5), 0);
    manager.Read(1, 10);
    ASSERT_EQUAL(manager.Cheer(1), 1);
    manager.Read(2, 5);
    manager.Read(3, 7);
    ASSERT_EQUAL(manager.Cheer(2), 0);
    ASSERT_EQUAL(manager.Cheer(3), 0.5);
    manager.Read(3, 10);
    ASSERT_EQUAL(manager.Cheer(3), 0.5);
    manager.Read(3, 11);
    ASSERT_EQUAL(manager.Cheer(3), 1);
    ASSERT_EQUAL(manager.Cheer(1), 0.5);
}

int main()
{
	test();
	return 0;
	// ƒл€ ускорени€ чтени€ данных отключаетс€ синхронизаци€
	// cin и cout с stdio,
	// а также выполн€етс€ отв€зка cin от cout
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) 
	{
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") 
		{
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		}
		else if (query_type == "CHEER") 
		{
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}
