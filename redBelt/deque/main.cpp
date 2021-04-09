#include "deque.h"
#include "testRunner.h"

void TestAll()
{
	{
		Deque<int> test;

		ASSERT_EQUAL(test.Size(), 0)

		test.PushBack(1);
		test.PushBack(2);

		ASSERT_EQUAL(test.Size(), 2)

		test.PushFront(3);
		test.PushFront(4);

		ASSERT_EQUAL(test.Size(), 4)
		ASSERT_EQUAL(test[0], 4)
		ASSERT_EQUAL(test[1], 3)
		ASSERT_EQUAL(test[3], 2)
		ASSERT_EQUAL(test.Front(), 4)
		ASSERT_EQUAL(test.Back(), 2)
		ASSERT_EQUAL(test.At(3), 2)

		const Deque<int> deque = test;
		
		ASSERT_EQUAL(deque.Size(), 4)
		ASSERT_EQUAL(deque[0], 4)
		ASSERT_EQUAL(deque[1], 3)
	}
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestAll);

	return 0;
}
