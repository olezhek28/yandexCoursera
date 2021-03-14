#include "translator.h"
#include "testRunner.h"

void TestSimple()
{
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}