#include "testRunner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

template <typename T>
class Synchronized
{
public:
	explicit Synchronized(T initial = T()) : value(move(initial))
	{}

	struct Access
	{
		T& refToValue;
		lock_guard<mutex> lck;
	};

	Access GetAccess()
	{
		return Access{value, lock_guard<mutex>(m)};
	}

private:
	T value;
	mutex m;
};

void TestConcurrentUpdate()
{
	Synchronized<string> commonString;

	const size_t addCount = 50000;
	auto updater = [&commonString, addCount]
	{
		for (size_t i = 0; i < addCount; ++i) 
		{
			auto access = commonString.GetAccess();
			access.refToValue += 'a';
		}
	};

	auto f1 = async(updater);
	auto f2 = async(updater);

	f1.get();
	f2.get();

	ASSERT_EQUAL(commonString.GetAccess().refToValue.size(), 2 * addCount);
}

vector<int> Consume(Synchronized<deque<int>>& common_queue)
{
	vector<int> got;

	for (;;) 
	{
		deque<int> q;

		{
			auto access = common_queue.GetAccess();
			q = move(access.refToValue);
		}

		for (int item : q) 
		{
			if (item > 0) 
			{
				got.push_back(item);
			}
			else 
			{
				return got;
			}
		}
	}
}

void TestProducerConsumer()
{
	Synchronized<deque<int>> commonQueue;

	auto consumer = async(Consume, ref(commonQueue));

	const size_t itemCount = 100000;

	for (size_t i = 1; i <= itemCount; ++i) 
	{
		commonQueue.GetAccess().refToValue.push_back(i);
	}
	
	commonQueue.GetAccess().refToValue.push_back(-1);

	vector<int> expected(itemCount);
	iota(begin(expected), end(expected), 1);
	ASSERT_EQUAL(consumer.get(), expected);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestProducerConsumer);
}
