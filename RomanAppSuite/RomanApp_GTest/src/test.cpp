#include "pch.h"

#include "Dec2Roman.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST( DecRoman_TestSuite, ChainTest )
{
	bool result = Decimal_2_Roman_Chain_UnitTest();

	// NonFatal assertion
	EXPECT_EQ( result, true ) << "All decimals 1..3999 should pass and vice versa";

	// Fatal assertion
	ASSERT_EQ( result, true ) << "All decimals 1..3999 should pass and vice versa";
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



