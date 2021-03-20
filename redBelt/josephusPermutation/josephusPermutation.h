#pragma once

#include <cstdint>
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size)
{
	list<typename RandomIt::value_type> pool;

	for (auto it = first; it < last; ++it)
	{
		pool.push_back(move(*it));
	}
	
	size_t cur_pos = 0;
	auto f = first;
	
	while (!pool.empty()) 
	{
		auto it = next(pool.begin(), cur_pos);
		*(first++) = move(*it);
		pool.erase(it);
		
		if (pool.empty()) 
		{
			break;
		}
		
		cur_pos = (cur_pos + step_size - 1) % pool.size();
	}
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt
{
	int value;

	NoncopyableInt(int value) : value(value) {}

	NoncopyableInt(const NoncopyableInt&) = delete;
	NoncopyableInt& operator=(const NoncopyableInt&) = delete;

	NoncopyableInt(NoncopyableInt&&) = default;
	NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs)
{
	return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v)
{
	return os << v.value;
}
