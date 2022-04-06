#ifndef AVL_SORTED_TREE
#define AVL_SORTED_TREE

#include "BiTree.h"
#include "BiTreeNode.h"

template<class T>
class AvlSortedTree : public BiTree<T>
{
protected:
	int32_t _node_count;

	void _LlRotate(BiTreeNode<T>*& node)
	{
		/* right rotate */
		if (node)
		{
			BiTreeNode<T>* grand = node;
			BiTreeNode<T>* child = grand->_pLeft;
			grand->_pLeft = child->_pRight;
			child->_pRight = grand;
			grand->_balance = 0;
			child->_balance = 0;
			node = child;
		}
	}
	void _RrRotate(BiTreeNode<T>*& node)
	{
		/* left rotate */
		if (node)
		{
			BiTreeNode<T>* grand = node;
			BiTreeNode<T>* child = grand->_pRight;
			grand->_pRight = child->_pLeft;
			child->_pLeft = grand;
			grand->_balance = 0;
			child->_balance = 0;
			node = child;
		}
	}

	void _LrRotate(BiTreeNode<T>*& node)
	{
		if (node)
		{
			_RrRotate(node->_pLeft);
			_LlRotate(node);

		}
	}

	void _RlRotate(BiTreeNode<T>*& node)
	{
		if (node)
		{
			_LlRotate(node->_pRight);
			_RrRotate(node);
		}
	}

	void _Add(BiTreeNode<T>* node, BiTreeNode<T>*& parent, int32_t depth)
	{
		if (parent)
		{
			if (parent->_data > node->_data)
			{
				parent->_balance += 1;
				_Add(node, parent->_pLeft, depth);
			}
			else
			{
				parent->_balance -= 1;
				_Add(node, parent->_pRight, depth);
			}

			if (parent->_balance >= 2)
			{
				if (parent->_pLeft->_balance == 1)
					_LlRotate(parent);
				else
					_LrRotate(parent);
			}
			else if (parent->_balance <= -2)
			{
				if (parent->_pRight->_balance > 0)
					_RlRotate(parent);
				else
					_RrRotate(parent);
			}
		}
		else
		{
			parent = node;
			_node_count += 1;
		}
	}

public:
	void Add(BiTreeNode<T>* node) { if (node) _Add(node, this->_pRoot, 0); }
	int32_t GetNodeCount() { return _node_count; }
};

#endif //AVL_SORTED_TREE
