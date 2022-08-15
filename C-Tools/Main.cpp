#include <Windows.h>
#include <iostream>
#include <queue>
#include <vector>

#include "DataStruct/BinaryTree.h"
#include "DataStruct/AvlSortTree.h"
#include "Algorithm/Sort.h"
#include "String/Split.h"
#include "Memory/MemoryPool.h"

void TestBiTree()
{
	AvlSortTree<int> tree;
	tree.insert(1, nullptr);
	tree.insert(2, nullptr);
	tree.insert(3, nullptr);
	std::vector<BinaryTreeNode<int>*> tree_arr;
	tree.levelTraverse(tree.root(), tree_arr);
	for (auto p_node : tree_arr)
		std::cout << p_node->_data << ", ";
	std::cout << std::endl;
}

void TestQuickSort()
{
	std::vector<int> a{ 1, 9, 7, 3, 5, -1, 9, 10, 6};
	//std::vector<int> a{ 5,4,3,2,1};
	QuickSort<int>(a);
	for (auto num : a)
		std::cout << num << " ";
	std::cout << std::endl;
}

void TestMergeSort()
{
	std::vector<int> a{ 1, 9, 7, 3, 5, -1, 9, 10, 6 };
	MergeSort<int>(a);
	for (auto num : a)
		std::cout << num << " ";
	std::cout << std::endl;
}

void Test_Split()
{
	std::string input("1 10 j a");
	std::vector<std::string> res;
	Split(input, " ", res);
	for (auto item : res)
		std::cout << item << std::endl;
}

int main()
{
	TestBiTree();
	char c;
	do
	{
		c = getchar();
	} while (c != 'q');
	return 0;
}