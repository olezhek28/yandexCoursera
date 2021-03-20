#include "testRunner.h"
#include "profile.h"
#include "paginator.h"

#include <future>
#include <vector>
using namespace std;

template <typename ContainerOfVectors>
int64_t CalculateVectorSum(const ContainerOfVectors& matrix)
{
	int64_t sum = 0;

	for(const auto& page : matrix)
	{
		for(auto& elem : page)
		{
			sum += elem;
		}
	}
	
	return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix)
{
	vector<future<int64_t>> resThreads;

	int sizePage = matrix.size() % 4 == 0 ? matrix.size() / 4 : (matrix.size() / 4) + 1;
	
	for (auto page : Paginate(matrix, sizePage))
	{
		resThreads.push_back(async([=] { return CalculateVectorSum(page); }));
	}

	int64_t sum = 0;

	for(auto& res : resThreads)
	{
		sum += res.get();
	}

	return sum;
}

void TestCalculateMatrixSum()
{
	const vector<vector<int>> matrix = 
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void TestCalculateBigMatrixSum()
{
	vector<vector<int>> matrix;

	for (int i = 0; i < 9000; i++)
	{
		matrix.emplace_back();

		for (int j = 0; j < 10; j++)
		{
			matrix[i].push_back(i*11 + j);
		}
	}

	{
		LOG_DURATION("TestCalculateBigMatrixSum")

		cout << CalculateMatrixSum(matrix) << endl;
	}
	
	//ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
	RUN_TEST(tr, TestCalculateBigMatrixSum);
}
