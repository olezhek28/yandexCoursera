#pragma once
#include <queue>
#include <set>

using namespace std;

template <class T>
class ObjectPool
{
public:
	ObjectPool() = default;
	T* Allocate();
	T* TryAllocate();
	void Deallocate(T* object);
	~ObjectPool();

private:
	set<T*> busy;
	queue<T*> free;
};

template <class T>
T* ObjectPool<T>::Allocate()
{
	T* it = nullptr;

	if (free.empty())
	{
		it = new T();
		busy.insert(it);
	}
	else
	{
		it = free.front();
		busy.insert(it);
		free.pop();
	}

	return it;
}

template <class T>
T* ObjectPool<T>::TryAllocate()
{
	if (free.empty())
		return nullptr;

	return Allocate();
}

template <class T>
void ObjectPool<T>::Deallocate(T* object)
{
	auto it = busy.find(object);

	if (it != busy.end())
	{
		free.push(object);
		busy.erase(it);
	}
	else
	{
		throw invalid_argument("err");
	}
}

template <class T>
ObjectPool<T>::~ObjectPool()
{
	for (auto& b : busy)
		delete b;

	while (!free.empty())
	{
		delete free.front();
		free.pop();
	}
}
