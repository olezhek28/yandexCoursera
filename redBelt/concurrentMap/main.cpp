#include "testRunner.h"
#include "profile.h"

#include <algorithm>
#include <future>
#include <mutex>
#include <map>
#include <numeric>
#include <vector>
#include <string>
#include <random>

using namespace std;

template <typename K, typename V>
class ConcurrentMap
{
public:
	static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

	struct Bucket
	{
		mutex mt;
		map<K, V> data;
	};
	
	struct Access
	{
		lock_guard<mutex> lck;
		V& refToValue;

		Access(const K& key, Bucket& bucket) : lck(bucket.mt), refToValue(bucket.data[key])
		{
		}
	};

	explicit ConcurrentMap(size_t bucketCount) : dict(bucketCount), bucketCount(bucketCount)
	{
	}

	Access operator[](const K& key);

	map<K, V> BuildOrdinaryMap();

	

private:
	vector<Bucket> dict;
	size_t bucketCount;
};

template <typename K, typename V>
typename ConcurrentMap<K, V>::Access ConcurrentMap<K, V>::operator[](const K& key)
{
	int id = key % bucketCount;
	return Access{ key, dict[id] };
}

template <typename K, typename V>
map<K, V> ConcurrentMap<K, V>::BuildOrdinaryMap()
{
	map<K, V> result;

	for(int i = 0; i < bucketCount; i++)
	{
		auto m = lock_guard(dict[i].mt);
		result.insert(dict[i].data.begin(), dict[i].data.end());
	}

	return result;
}

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t threadCount, int keyCount)
{
	auto kernel = [&cm, keyCount](int seed)
	{
		vector<int> updates(keyCount);
		iota(begin(updates), end(updates), -keyCount / 2);
		shuffle(begin(updates), end(updates), default_random_engine(seed));

		for (int i = 0; i < 2; ++i) 
		{
			for (auto key : updates) 
			{
				cm[key].refToValue++;
			}
		}
	};

	vector<future<void>> futures;
	for (size_t i = 0; i < threadCount; ++i) 
	{
		futures.push_back(async(kernel, i));
	}
}

void TestConcurrentUpdate()
{
	const size_t threadCount = 3;
	const size_t keyCount = 50000;

	ConcurrentMap<int, int> cm(threadCount);
	RunConcurrentUpdates(cm, threadCount, keyCount);

	const auto result = cm.BuildOrdinaryMap();
	ASSERT_EQUAL(result.size(), keyCount);
	for (auto& [k, v] : result) 
	{
		AssertEqual(v, 6, "Key = " + to_string(k));
	}
}

void TestReadAndWrite()
{
	ConcurrentMap<size_t, string> cm(5);

	auto updater = [&cm]
	{
		for (size_t i = 0; i < 50000; ++i) 
		{
			cm[i].refToValue += 'a';
		}
	};
	
	auto reader = [&cm]
	{
		vector<string> result(50000);
		for (size_t i = 0; i < result.size(); ++i) 
		{
			result[i] = cm[i].refToValue;
		}
		return result;
	};

	auto u1 = async(updater);
	auto r1 = async(reader);
	auto u2 = async(updater);
	auto r2 = async(reader);

	u1.get();
	u2.get();

	for (auto* f : {&r1, &r2}) 
	{
		auto result = f->get();
		ASSERT(all_of(result.begin(), result.end(), [](const string& s) 
		{
			return s.empty() || s == "a" || s == "aa";
		}));
	}
}

void TestSpeedup()
{
	{
		ConcurrentMap<int, int> singleLock(1);

		LOG_DURATION("Single lock");
		RunConcurrentUpdates(singleLock, 4, 50000);
	}
	
	{
		ConcurrentMap<int, int> manyLocks(100);

		LOG_DURATION("100 locks");
		RunConcurrentUpdates(manyLocks, 4, 50000);
	}
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestReadAndWrite);
	RUN_TEST(tr, TestSpeedup);
}
