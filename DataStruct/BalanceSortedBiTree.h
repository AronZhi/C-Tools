#ifndef BALANCE_SORTED_BI_TREE
#define BALANCE_SORTED_BI_TREE

#include "BiTree.h"
#include "BiTreeNode.h"

template<class T>
class BalanceSortedBiTree : public BiTree<T>
{
private:
	void _Add(BiTreeNode<T>* node, BiTreeNode<T>*& parent)
	{
		if (parent)
		{
			if (parent->_data > node->_data)
				_Add(node, parent->_pLeft);
			else
				_Add(node, parent->_pRight);
		}
		else
		{
			parent = node;
		}
	}

public:
	void Add(BiTreeNode<T>* node) { if (node) _Add(node, this->_pRoot); }
};

#endif // BALANCE_SORTED_BI_TREE
