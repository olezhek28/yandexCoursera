#pragma once

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection
{
public:
	
	struct Element
	{
		size_t id;
		size_t priority;
		T value;

		bool operator< (const Element& other) const { return priority < other.priority; }

		/*Element(Id id, int priority, T value) : id(id), priority(priority), value(value)
		{}

		bool operator< (const Element& other) const { return id < other.id; }

		bool operator<(const Id& id) { return this->id < id; }
		friend bool operator<(const Id& id, const Element& t) { return id < t.id; }
		friend bool operator<(const Element& t1, const Element& t2) { return t1.id < t2.id; }*/
	};
	
	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	size_t Add(T object);

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin);

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(size_t id) const;

	// Получить объект по идентификатору
	const T& Get(size_t id) const;

	// Увеличить приоритет объекта на 1
	void Promote(size_t id);

	// Получить объект с максимальным приоритетом и его приоритет
	pair<const T&, size_t> GetMax() const;

	// Аналогично GetMax, но удаляет элемент из контейнера
	pair<T, size_t> PopMax();

private:
	vector<Element> objects;
};

template <typename T>
typename size_t PriorityCollection<T>::Add(T object)
{
	objects.push_back(Element
	{
		!objects.empty() ? objects.size() : 0,
		0,
		move(object)
	});

	return !objects.empty() ? objects.size() - 1 : 0;
}

template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
{
	for(auto& it = range_begin; it < range_end; ++it)
	{
		objects.push_back(Element
		{
			!objects.empty() ? objects.size() : 0,
			0,
			move(*it)
		});
		ids_begin++ = objects.size() - 1;
	}
}

template <typename T>
bool PriorityCollection<T>::IsValid(size_t id) const
{
	return true; //return objects.find(id) != objects.end();
}

template <typename T>
const T& PriorityCollection<T>::Get(size_t id) const
{
	return {};// objects[id].second;
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
	return true; //x.second < y.second;
}

template <typename T>
void PriorityCollection<T>::Promote(size_t id)
{
	auto it = find_if(objects.begin(), objects.end(), [id](const Element& elem)
	{
		return elem.id == id;
	});

	++it->priority;
}

template <typename T>
pair<const T&, size_t> PriorityCollection<T>::GetMax() const
{
	auto it = std::max_element(objects.rbegin(), objects.rend());

	return { it->value, it->priority };
}

template <typename T>
pair<T, size_t> PriorityCollection<T>::PopMax()
{
	auto it = std::max_element(objects.rbegin(), objects.rend());

	pair<T, size_t> tmp;
	tmp.first = move(it->value);
	tmp.second = move(it->priority);
	objects.erase(std::next(it).base());
	
	return tmp;
}
