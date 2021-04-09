#pragma once

#include <vector>
#include <stdexcept>

template <class T>
class Deque
{
private:
	std::vector<T> front;
	std::vector<T> back;

public:
	Deque() = default;

	bool Empty() const;

	size_t Size() const;

	T& operator[](size_t index);

	const T& operator[](size_t index) const;

	T& At(size_t index);

	const T& At(size_t index) const;

	T& Front();

	const T& Front() const;

	T& Back();

	const T& Back() const;

	void PushFront(const T& item);

	void PushBack(const T& item);
};

template <class T>
bool Deque<T>::Empty() const
{
	return front.empty() && back.empty();
}

template <class T>
size_t Deque<T>::Size() const
{
	return front.size() + back.size();
}

template <class T>
T& Deque<T>::operator[](size_t index)
{
	if (index >= front.size())
		return back[index - front.size()];

	return front[front.size() - 1 - index];
}

template <class T>
const T& Deque<T>::operator[](size_t index) const
{
	if (index >= front.size())
		return back[index - front.size()];

	return front[front.size() - 1 - index];
}

template <class T>
T& Deque<T>::At(size_t index)
{
	if (index >= front.size() + back.size())
		throw std::out_of_range("");

	if (index >= front.size())
		return back[index - front.size()];

	return front[front.size() - 1 - index];
}

template <class T>
const T& Deque<T>::At(size_t index) const
{
	if (index >= front.size() + back.size())
		throw std::out_of_range("");

	if (index >= front.size())
		return back[index - front.size()];

	return front[front.size() - 1 - index];
}

template <class T>
T& Deque<T>::Front()
{
	if (front.empty())
		return back.front();

	return front.back();
}

template <class T>
const T& Deque<T>::Front() const
{
	if (front.empty())
		return back.front();

	return front.back();
}

template <class T>
T& Deque<T>::Back()
{
	if (back.empty())
		return front.front();

	return back.back();
}

template <class T>
const T& Deque<T>::Back() const
{
	if (back.empty())
		return front.front();

	return back.back();
}

template <class T>
void Deque<T>::PushFront(const T& item)
{
	front.push_back(item);
}

template <class T>
void Deque<T>::PushBack(const T& item)
{
	back.push_back(item);
}
