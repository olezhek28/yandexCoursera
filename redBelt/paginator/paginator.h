#pragma once
#include <algorithm>
#include <vector>

using namespace std;

template <typename It>
class Page
{
public:
	Page() = default;
	Page(It _begin, It _end, size_t _pageSize);
	It begin() const;
	It end() const;
	size_t size() const;

private:
	It first, last;
};

template <typename It>
Page<It>::Page(It _begin, It _end, size_t _pageSize): first(_begin), last(_end)
{
}

template <typename It>
It Page<It>::begin() const
{
	return first;
}

template <typename It>
It Page<It>::end() const
{
	return last;
}

template <typename It>
size_t Page<It>::size() const
{
	return last - first;
}

template <typename Iterator>
class Paginator
{
public:
	Paginator(Iterator _begin, Iterator _end, size_t _pageSize);

	typename vector<Page<Iterator>>::iterator begin() const;
	typename vector<Page<Iterator>>::const_iterator begin();
	typename vector<Page<Iterator>>::iterator end() const;
	typename vector<Page<Iterator>>::const_iterator end();
	size_t size() const;

private:
	size_t pageSize;
	size_t pageCount;
	vector<Page<Iterator>> pages;
};

template <typename Iterator>
Paginator<Iterator>::Paginator(Iterator _begin, Iterator _end, size_t _pageSize): pageSize(_pageSize)
{
	size_t totalSize = _end - _begin;
	pageCount = totalSize % pageSize == 0 ? totalSize / pageSize : totalSize / pageSize + 1;

	pages.reserve(pageCount);

	for (size_t i = 0; i < pageCount; i++)
	{
		pages.push_back(Page(_begin + (i * pageSize),
		                     _begin + (i * pageSize) + min(pageSize, totalSize),
		                     min(pageSize, totalSize)));
		totalSize -= pageSize;
	}
}

template <typename Iterator>
typename vector<Page<Iterator>>::iterator Paginator<Iterator>::begin() const
{
	return !pages.empty() ? pages.begin() : pages.end();
}

template <typename Iterator>
typename vector<Page<Iterator>>::const_iterator Paginator<Iterator>::begin()
{
	return !pages.empty() ? pages.begin() : pages.end();
}

template <typename Iterator>
typename vector<Page<Iterator>>::iterator Paginator<Iterator>::end() const
{
	return pages.end();
}

template <typename Iterator>
typename vector<Page<Iterator>>::const_iterator Paginator<Iterator>::end()
{
	return pages.end();
}

template <typename Iterator>
size_t Paginator<Iterator>::size() const
{
	return pageCount;
}

template <typename C>
auto Paginate(C& c, size_t pageSize)
{
	return Paginator{c.begin(), c.end(), pageSize};
}
