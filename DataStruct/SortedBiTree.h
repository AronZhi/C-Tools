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
				if (parent->DataRef() > node->DataRef())
					_AddNode(node, parent->LeftRef());
				else
					_AddNode(node, parent->RightRef());
			}
			else
			{
				parent = node;
			}
		}
	}

public:
	SortedBiTree() {}

	void AddNode(TreeNode<T>* node)
	{
		if (node)
			_AddNode(node, this->_pRoot);
	}
};

#endif // SORTED_BI_TREE
