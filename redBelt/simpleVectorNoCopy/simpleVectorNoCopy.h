#pragma once
#include <algorithm>
#include <cstdint>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVectorNoCopy
{
public:
	SimpleVectorNoCopy() = default;
	explicit SimpleVectorNoCopy(size_t size);
	~SimpleVectorNoCopy();

	T& operator[](size_t index);
	
	T* begin();
	T* end();

	size_t Size() const;
	size_t Capacity() const;
	void PushBack(T value);

	// При необходимости перегрузите
	// существующие публичные методы

private:
	T* data = nullptr;
	int size = 0;
	int capacity = 0;
};

template <typename T>
SimpleVectorNoCopy<T>::SimpleVectorNoCopy(size_t size) : size(size), capacity(size)
{
	data = new T[capacity];
}

template <typename T>
SimpleVectorNoCopy<T>::~SimpleVectorNoCopy()
{
	delete[] data;
}

template <typename T>
T& SimpleVectorNoCopy<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
T* SimpleVectorNoCopy<T>::begin()
{
	return data;
}

template <typename T>
T* SimpleVectorNoCopy<T>::end()
{
	return data + size;
}

template <typename T>
size_t SimpleVectorNoCopy<T>::Size() const
{
	return size;
}

template <typename T>
size_t SimpleVectorNoCopy<T>::Capacity() const
{
	return capacity;
}

template <typename T>
void SimpleVectorNoCopy<T>::PushBack(T value)
{
	if (size >= capacity)
	{
		capacity = capacity == 0 ? 1 : 2*capacity;
		auto* tmp = new T[capacity];
		std::move(begin(), end(), tmp);

		delete[] data;

		data = tmp;
	}

	data[size++] = move(value);
}
