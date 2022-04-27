#include "gtest/gtest.h"

TEST(AlienLandTest, CPP20_CompileCheck)
{
	struct A
	{
		int a;
		int b;
	};
	std::vector<A> aa;
	aa.emplace_back(42, 42);
	EXPECT_TRUE(true);
}
