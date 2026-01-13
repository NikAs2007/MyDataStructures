#include <gtest/gtest.h>
#include "../src/list.h"
#include <utility>

using namespace mds;
//using namespace std;

TEST(List, AllFunctions) {
	list<int> l1;
	EXPECT_EQ(l1.size(), 0) << "list() err" << std::endl;
	l1.push_back(5);
	EXPECT_EQ(l1[0], 5) << "push_back() err" << std::endl;
	for (int i = 0; i < 10; ++i) {
		l1.push_back(i);
		EXPECT_EQ(l1[i+1], i) << "push_back() err" << std::endl;
	}
	EXPECT_EQ(l1.size(), 11) << "size() err" << std::endl;
	l1.pop_back();
	EXPECT_EQ(l1[9], 8) << "pop_back() err" << std::endl;
	EXPECT_EQ(l1.size(), 10) << "pop() err" << std::endl;
	l1.pop_front();
	EXPECT_EQ(l1[0], 0) << "pop_front() err" << std::endl;
	EXPECT_EQ(l1.size(), 9) << "pop_front() err" << std::endl;
	l1.push_front(13);
	EXPECT_EQ(l1[0], 13) << "push_front() err" << std::endl;
	EXPECT_EQ(l1.size(), 10) << "push_front() err" << std::endl;
	
	list<int> l2(l1);
	EXPECT_EQ(l1.size(), l2.size()) << "list(const&) err" << std::endl;
	EXPECT_EQ(l1[0], l2[0]) << "list(const&) err" << std::endl;
	EXPECT_EQ(l1[9], l2[9]) << "list(const&) err" << std::endl;

	l1.clear();
	EXPECT_EQ(l1.size(), 0) << "clear() err" << std::endl;
	l1 = l2;
	EXPECT_EQ(l1.size(), 10) << "=(const&) err" << std::endl;
	list<int> l3(std::move(l2));
	EXPECT_EQ(l3.size(), 10) << "list(&&) err" << std::endl;
	EXPECT_EQ(l2.size(), 0) << "list(&&) err" << std::endl;
	l2 = std::move(l1);
	EXPECT_EQ(l2.size(), 10) << "=(&&) err" << std::endl;
	EXPECT_EQ(l1.size(), 0) << "=(&&) err" << std::endl;
}