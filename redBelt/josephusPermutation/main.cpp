//#include "josephusPermutation.h"
//#include "testRunner.h"
//
//#include <numeric>
//#include <vector>
//
//
//
//void TestAvoidsCopying()
//{
//	vector<NoncopyableInt> numbers;
//	numbers.emplace_back(1);
//	numbers.emplace_back(2);
//	numbers.emplace_back(3);
//	numbers.emplace_back(4);
//	numbers.emplace_back(5);
//
//	MakeJosephusPermutation(begin(numbers), end(numbers), 2);
//
//	vector<NoncopyableInt> expected;
//	expected.emplace_back(1);
//	expected.emplace_back(3);
//	expected.emplace_back(5);
//	expected.emplace_back(4);
//	expected.emplace_back(2);
//
//	ASSERT_EQUAL(numbers, expected);
//}
//
//vector<int> MakeTestVector()
//{
//	vector<int> numbers(10);
//	iota(begin(numbers), end(numbers), 0);
//	return numbers;
//}
//
//void TestIntVector()
//{
//	const vector<int> numbers = MakeTestVector();
//	
//	{
//		vector<int> numbers_copy = numbers;
//		MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
//		ASSERT_EQUAL(numbers_copy, numbers);
//	}
//	
//	{
//		vector<int> numbers_copy = numbers;
//		MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
//		ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
//	}
//}

#include <iostream>

int main()
{
	/*TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	RUN_TEST(tr, TestAvoidsCopying);*/

	int a[] = {1, 2, 3, 4, 5, 6};
    std::cout << (1 + 3)[a] - a[0] + (a + 1)[2];

	return 0;
}