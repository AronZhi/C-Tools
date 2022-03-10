#ifndef SORTED_BI_TREE
#define SORTED_BI_TREE

#include "TreeNode.h"
#include "BiTree.h"

template <class T>
class SortedBiTree : public BiTree<T>
{
protected:
	void _AddNode(TreeNode<T>* node, TreeNode<T>*& parent)
	{
		if (node)
		{
			if (parent)
			{
				if (parent->Data() > node->Data())
					_AddNode(node, parent->Left());
				else
					_AddNode(node, parent->Right());
			}
			else
			{
				parent = node;
			}
		}
	}

public:
	SortedBiTree() {}

	void AddNode(T data)
	{
		TreeNode<T>* node = new TreeNode<T>(data);
		_AddNode(node, this->_pRoot);
	}
};

#endif // SORTED_BI_TREE
