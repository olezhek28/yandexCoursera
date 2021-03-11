#pragma once

#include <algorithm>

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
	size_t size = 0;
	size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector() : data(nullptr) { }

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) : capacity(size), size(size)
{
	data = new T[capacity];
}

template <typename T>
SimpleVector<T>::~SimpleVector()
{
	delete[] data;
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
	return data + size;
}

template <typename T>
const T* SimpleVector<T>::begin() const
{
	return data;
}

template <typename T>
const T* SimpleVector<T>::end() const
{
	return data + size;
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
	if (size >= capacity)
	{
		capacity = capacity == 0 ? 1 : 2*capacity;
		T* tmp = new T[capacity];
		std::copy(begin(), end(), tmp);

		delete[] data;

		data = tmp;
	}

	data[size++] = value;
}
