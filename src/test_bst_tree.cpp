#include <gtest/gtest.h>
#include "../src/bst_tree.h"
#include <utility>

using namespace mds;


TEST(Bst_tree, AllFunctions) {
	bst_tree<int> tr;
	tr.insert(1);
	tr.insert(2);
	tr.insert(0);
	tr.insert(1);
	tr.insert(2);
	tr.insert(0);
	EXPECT_EQ(tr.contains(0), true);
	EXPECT_EQ(*tr.find(0), 0);
	tr.insert(5);
	tr.insert(7);
	EXPECT_EQ(tr.contains(8), false);
	EXPECT_EQ(tr.find(8), nullptr);
	tr.insert(6);
	tr.insert(-5);
	tr.insert(-2);
	EXPECT_EQ(tr.contains(2), true);
	EXPECT_EQ(*tr.find(2), 2);
	EXPECT_EQ(tr.size(), 8);
	tr.remove(2);
	EXPECT_EQ(tr.size(), 7);
	EXPECT_EQ(tr.contains(2), false);
	EXPECT_EQ(tr.contains(1), true);
	EXPECT_EQ(tr.contains(0), true);
	EXPECT_EQ(tr.contains(5), true);
	EXPECT_EQ(tr.contains(7), true);
	EXPECT_EQ(tr.contains(6), true);
	EXPECT_EQ(tr.contains(-5), true);
	EXPECT_EQ(tr.contains(-2), true);
	bst_tree<int> tr1(std::move(tr));
	EXPECT_EQ(tr1.size(), 7);
	EXPECT_EQ(tr.size(), 0);
	tr = std::move(tr1);
	EXPECT_EQ(tr1.size(), 0);
	EXPECT_EQ(tr.size(), 7);

	tr.clear();
	EXPECT_EQ(tr.size(), 0);

}