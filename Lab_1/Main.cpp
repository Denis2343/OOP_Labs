#include <iostream>
#include "tritset.h"
#include "gtest/gtest.h"

TEST(TritSetTest, SizeOfMemoryUINT)
{
	TritSet set(1000);
	EXPECT_GE(set.capacity(), 1000 * 2 / 8 / sizeof(set.uint_));
}

TEST(TritSetTest, NoMemoryAllocation)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	set[10000] = Unknown;
	EXPECT_EQ(allocLength, set.capacity());

	if (set[20000] == True) {}
	EXPECT_EQ(allocLength, set.capacity());
}

TEST(TritSetTest, MemoryAllocation)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	set[10000] = True;
	EXPECT_LT(allocLength, set.capacity());
}

TEST(TritSetTest, NoMemoryOperations)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	set[10000] = True;
	allocLength = set.capacity();
	set[10000] = Unknown;
	set[9700] = False;
	EXPECT_EQ(allocLength, set.capacity());
}

TEST(TritSetTest, Shrink)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	set[10000] = True;
	allocLength = set.capacity();
	set[10000] = Unknown;
	set[9700] = False;
	set.shrink();
	EXPECT_GT(allocLength, set.capacity());
}

TEST(TritSetTest, TritAnd)
{
	TritSet setA(1000);
	TritSet setB(2000);
	TritSet setC = setA & setB;
	EXPECT_EQ(setC.capacity(), setB.capacity());
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}