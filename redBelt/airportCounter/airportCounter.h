#pragma once
#include <utility>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

// TAirport should be enum with sequential items and last item TAirport::Last_
template <typename TAirport>
class AirportCounter
{
public:
	AirportCounter() = default;

	template <typename TIterator>
	AirportCounter(TIterator begin, TIterator end);

	size_t Get(TAirport airport) const;
	void Insert(TAirport airport);
	void EraseOne(TAirport airport);
	void EraseAll(TAirport airport);

	using Item = pair<TAirport, size_t>;
	using Items = array<Item, static_cast<uint32_t>(TAirport::Last_)>;

	Items GetItems() const
	{
		Items stats;

		for (size_t i = 0; i < departureStatistics.size(); i++)
		{
			stats[i].first = static_cast<TAirport>(i);
			stats[i].second = departureStatistics[i];
		}
		
		return stats;
	}

private:
	array<size_t, static_cast<uint32_t>(TAirport::Last_)> departureStatistics;
};

template <typename TAirport>
template <typename TIterator>
AirportCounter<TAirport>::AirportCounter(TIterator begin, TIterator end)
{
	for (size_t i = 0; i < departureStatistics.size(); ++i)
	{
		departureStatistics[i] = 0;
	}
	
	for (auto& it = begin; it < end; ++it)
	{
		++departureStatistics[static_cast<uint32_t>(*it)];
	}
}

template <typename TAirport>
size_t AirportCounter<TAirport>::Get(TAirport airport) const
{
	return departureStatistics[static_cast<uint32_t>(airport)];
}

template <typename TAirport>
void AirportCounter<TAirport>::Insert(TAirport airport)
{
	++departureStatistics[static_cast<uint32_t>(airport)];
}

template <typename TAirport>
void AirportCounter<TAirport>::EraseOne(TAirport airport)
{
	--departureStatistics[static_cast<uint32_t>(airport)];
}

template <typename TAirport>
void AirportCounter<TAirport>::EraseAll(TAirport airport)
{
	departureStatistics[static_cast<uint32_t>(airport)] = 0;
}
