#pragma once

#include <algorithm>
#include <cstdlib>

template <typename T>
class SimpleVector
{
public:
	SimpleVector();
	explicit SimpleVector(size_t size);
	~SimpleVector();

	T& operator[](size_t index);

	T* begin();
	T* end();

	const T* begin() const;
	const T* end() const;

	size_t Size() const;
	size_t Capacity() const;
	void PushBack(const T& value);

private:
	T* data;
	T* _end;
	size_t size = 0;
	size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector()
{
	data = nullptr;
	_end = nullptr;
}

template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
{
	this->capacity = 2*size;
	data = new T[capacity];
	_end = data + size;
	this->size = size;
}

template <typename T>
SimpleVector<T>::~SimpleVector()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
T* SimpleVector<T>::begin()
{
	return data;
}

template <typename T>
T* SimpleVector<T>::end()
{
	return _end;
}

template <typename T>
const T* SimpleVector<T>::begin() const
{
	return data;
}

template <typename T>
const T* SimpleVector<T>::end() const
{
	return _end;
}

template <typename T>
size_t SimpleVector<T>::Size() const
{
	return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const
{
	return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value)
{
	if (capacity == 0)
	{
		capacity = 2;
		data = new T[capacity];
		//_end = data + capacity;
	}
	
	if (size == capacity)
	{
		capacity = 2*size;
		T* tmp = new T[capacity];
		std::copy(data, _end, tmp);

		delete[] data;

		data = tmp;
	}

	data[size] = value;
	size++;
	_end = data + size;
}
