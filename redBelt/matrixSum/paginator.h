#pragma once

#include <algorithm>
#include <vector>

using namespace std;

template <typename It>
class Page
{
private:
	It first, last;

public:
	Page() = default;
	
	Page(It _begin, It _end, size_t _pageSize) : first(_begin), last(_end)
	{
		
	}

	It begin() const
	{
		return first;
	}

	It end() const
	{
		return last;
	}

	size_t size() const
	{
		return last - first;
	}
};

template <typename Iterator>
class Paginator
{
private:
	size_t pageSize;
	size_t pageCount;
	vector<Page<Iterator>> pages;

public:
	Paginator(Iterator _begin, Iterator _end, size_t _pageSize) : pageSize(_pageSize)
	{
		size_t totalSize = _end - _begin;
		pageCount = totalSize % pageSize == 0 ? 
					totalSize / pageSize :
					totalSize / pageSize + 1;

		pages.reserve(pageCount);
		
		for(size_t i = 0; i < pageCount; i++)
		{
			pages.push_back(Page(_begin + (i * pageSize), 
								_begin + (i * pageSize) + min(pageSize, totalSize), 
								min(pageSize, totalSize)));
			totalSize -= pageSize;
		}
	}

	typename vector<Page<Iterator>>::iterator begin() const
	{
		return !pages.empty() ? pages.begin() : pages.end();
	}

	typename vector<Page<Iterator>>::const_iterator begin()
	{
		return !pages.empty() ? pages.begin() : pages.end();
	}

	typename vector<Page<Iterator>>::iterator end() const
	{
		return pages.end();
	}

	typename vector<Page<Iterator>>::const_iterator end()
	{
		return pages.end();
	}

	size_t size() const
	{
		return pageCount;
	}
};

template <typename C>
auto Paginate(C& c, size_t pageSize)
{
	return Paginator{c.begin(), c.end(), pageSize};
}