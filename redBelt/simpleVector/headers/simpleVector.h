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
	data = new T[size];
	_end = data + size;
	this->size = Capacity();
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
	return _end - data;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value)
{
	if (Capacity() == 0)
	{
		data = new T[1];
		_end = data + 1;
	}
	
	if (size == Capacity())
	{
		T* tmp = new T[2*size];
		std::copy(data, _end, tmp);

		delete[] data;

		data = tmp;
	}

	data[size] = value;
	size++;
	_end = data + size;
}
