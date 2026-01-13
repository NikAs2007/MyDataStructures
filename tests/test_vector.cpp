#include <gtest/gtest.h>
#include "../src/vector.h"

using namespace mds;

TEST(Vector, AllFunctions) {
	vector<int> v1;
	EXPECT_EQ(v1.size(), 0) << "vector() err" << std::endl;
	v1.push_back(5);
	EXPECT_EQ(v1.size(), 1) << "push_back() err" << std::endl;
	EXPECT_EQ(v1[0], 5) << "push_back() err" << std::endl;
	for (int i = 0; i < 10; ++i) {
		v1.push_back(i);
		EXPECT_EQ(v1[i + 1], i) << "push_back() err" << std::endl;
	}
	EXPECT_EQ(v1.size(), 11) << "size() err" << std::endl;
	v1.pop_back();
	EXPECT_EQ(v1[9], 8) << "pop_back() err" << std::endl;
	EXPECT_EQ(v1.size(), 10) << "pop_back() err" << std::endl;

	vector<int> v2(v1);
	EXPECT_EQ(v1.size(), v2.size()) << "vector(const&) err" << std::endl;
	EXPECT_EQ(v1[0], v2[0]) << "vector(const&) err" << std::endl;
	EXPECT_EQ(v1[9], v2[9]) << "vector(const&) err" << std::endl;

	v1.clear();
	EXPECT_EQ(v1.size(), 0) << "clear() err" << std::endl;
	v1 = v2;
	EXPECT_EQ(v1.size(), 10) << "=(const&) err" << std::endl;
	vector<int> v3(std::move(v2));
	EXPECT_EQ(v3.size(), 10) << "vector(&&) err" << std::endl;
	EXPECT_EQ(v2.size(), 0) << "vector(&&) err" << std::endl;
	v2 = std::move(v1);
	EXPECT_EQ(v2.size(), 10) << "=(&&) err" << std::endl;
	EXPECT_EQ(v1.size(), 0) << "=(&&) err" << std::endl;
}