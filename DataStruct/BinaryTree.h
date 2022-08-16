#ifndef BINARY_TREE
#define BINARY_TREE

#include <vector>
#include <queue>
#include <assert.h>
#include <math.h>

template <class T>
class BinaryTreeNode
{
public:
	T _data;
	int _n_height;
	BinaryTreeNode<T>* _p_left_child;
	BinaryTreeNode<T>* _p_right_child;

	BinaryTreeNode(T data) : _data(data), _n_height(0), _p_left_child(nullptr), _p_right_child(nullptr) {}
};


template <class T>
class BinaryTree {
protected:
	BinaryTreeNode<T>* _p_root;

public:
	BinaryTree(): _p_root(nullptr) {}

	virtual ~BinaryTree()
	{
	}

	void forwardTraverse(BinaryTreeNode<T>* p_node, std::vector<BinaryTreeNode<T>*>& ret)
	{
		if (p_node)
		{
			ret.push_back(p_node);
			forwardTraverse(p_node->_p_left_child);
			forwardTraverse(p_node->_p_right_child);
		}
		return;
	}

	void backTraverse(BinaryTreeNode<T>* p_node, std::vector<BinaryTreeNode<T>*>& ret)
	{
		if (p_node)
		{
			backTraverse(p_node->_p_left_child);
			backTraverse(p_node->_p_right_child);
			ret.push_back(p_node);
		}
		return;
	}

	void inorderTraverse(BinaryTreeNode<T>* p_node, std::vector<BinaryTreeNode<T>*>& ret)
	{
		if (p_node)
		{
			inorderTraverse(p_node->_p_left_child);
			ret.push_back(p_node);
			inorderTraverse(p_node->_p_right_child);
		}
		return;
	}

	void levelTraverse(BinaryTreeNode<T>* p_node, std::vector<BinaryTreeNode<T>*>& ret)
	{
		if (p_node)
		{
			std::queue<BinaryTreeNode<T>*> queue;
			queue.push(p_node);
			while (!queue.empty())
			{
				BinaryTreeNode<T>* node = queue.front();
				ret.push_back(node);
				queue.pop();
				if (node->_p_left_child)
					queue.push(node->_p_left_child);
				if (node->_p_right_child)
					queue.push(node->_p_right_child);
			}
		}
	}

	int __updateHeight(BinaryTreeNode<T>*& p_node)
	{
		std::vector<BinaryTreeNode<int>*> p_node_arr;
		levelTraverse(p_node, p_node_arr);
		int count = p_node_arr.size();
		for (int i = count - 1; i >= 0; --i)
		{
			if (nullptr == p_node_arr[i]->_p_left_child && nullptr == p_node_arr[i]->_p_right_child)
				p_node_arr[i]->_n_height = 0;
			else
				p_node_arr[i]->_n_height = max(height(p_node_arr[i]->_p_left_child), height(p_node_arr[i]->_p_right_child)) + 1;
		}
		return p_node->_n_height;
	}

	int height(BinaryTreeNode<T>* p_node)
	{
		return p_node == nullptr ? -1 : p_node->_n_height;
	}

	BinaryTreeNode<T>* root() 
	{ 
		return _p_root; 
	}

	virtual int insert(T data) = 0;

	virtual int remove(T data) = 0;
};


#endif // BINARY_TREE
