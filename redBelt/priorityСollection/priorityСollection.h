#pragma once

#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection
{
public:
	using Id = int;

	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	Id Add(T object);

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin);

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(Id id) const;

	// Получить объект по идентификатору
	const T& Get(Id id) const;

	// Увеличить приоритет объекта на 1
	void Promote(Id id);

	// Получить объект с максимальным приоритетом и его приоритет
	pair<const T&, int> GetMax() const;

	// Аналогично GetMax, но удаляет элемент из контейнера
	pair<T, int> PopMax();

private:
	vector<pair<int, T>> objects;
	set<pair<int, Id>, greater<int>> objectsSortByPriority;
	//vector<pair<priority, val>> tmp2;
	//set<pair<priority, id>> tmp;
};

template <typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object)
{
	objects.push_back(make_pair(0, move(object)));
	objectsSortByPriority.insert(make_pair(0, objects.size() - 1));
	return objects.size() - 1;
}

template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
{
	for(auto& it = range_begin; it < range_end; ++it)
	{
		objects.push_back(make_pair(0, move(*it)));
		objectsSortByPriority.insert(make_pair(0, objects.size() - 1));
		ids_begin++ = objects.size() - 1;
	}
}

template <typename T>
bool PriorityCollection<T>::IsValid(Id id) const
{
	return objects.size() > id;
}

template <typename T>
const T& PriorityCollection<T>::Get(Id id) const
{
	return objects[id].second;
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.second < y.second;
}

template <typename T>
void PriorityCollection<T>::Promote(Id id)
{
	++objects[id].first;

	auto it = find(objectsSortByPriority.begin(), objectsSortByPriority.end(), 
		[id](const pair<int, Id>& element)
		{
		   return element.second == id;
		});

	//it->first++;
}

template <typename T>
pair<const T&, int> PriorityCollection<T>::GetMax() const
{
	return make_pair(objects[objectsSortByPriority.begin()->second].second, objectsSortByPriority.begin()->first);
}

template <typename T>
pair<T, int> PriorityCollection<T>::PopMax()
{
	auto maxElementByPriority = move(*objectsSortByPriority.begin());
	auto maxElement = move(objects[maxElementByPriority.second].second);
	objectsSortByPriority.erase(objectsSortByPriority.begin());
	objects.erase(objects.begin() + maxElementByPriority.second);
	
	return make_pair(maxElement, maxElementByPriority.first);
}
