#ifndef BI_TREE
#define BI_TREE

#include <vector>
#include <queue>

#include "BiTreeNode.h"

template<class T>
class BiTree
{
protected:
	BiTreeNode<T>* _pRoot;

	void _ForwardTraverse(BiTreeNode<T>* node, std::vector<BiTreeNode<T>*>& ret)
	{
		if (node)
		{
			ret.push_back(node);
			_ForwardTraverse(node->_pLeft, ret);
			_ForwardTraverse(node->_pRight, ret);
		}
	}

	void _BackTraverse(BiTreeNode<T>* node, std::vector<BiTreeNode<T>*>& ret)
	{
		if (node)
		{
			_BackTraverse(node->_pLeft, ret);
			_BackTraverse(node->_pRight, ret);
			ret.push_back(node);
		}
	}

	void _InorderTraverse(BiTreeNode<T>* node, std::vector<BiTreeNode<T>*>& ret)
	{
		if (node)
		{
			_InorderTraverse(node->_pLeft, ret);
			ret.push_back(node);
			_InorderTraverse(node->_pRight, ret);
		}
	}

	void _LevelTraverse(BiTreeNode<T>* node, std::vector<BiTreeNode<T>*>& ret)
	{
		if (node)
		{
			std::queue<BiTreeNode<T>*> queue;
			queue.push(node);
			while (!queue.empty())
			{
				BiTreeNode<T>* pNode = queue.front();
				ret.push_back(pNode);
				queue.pop();
				if (pNode->_pLeft)
					queue.push(pNode->_pLeft);
				if (pNode->_pRight)
					queue.push(pNode->_pRight);
			}
		}
	}

public:
	BiTree() : _pRoot(nullptr) {}

	virtual void Add(BiTreeNode<T>* node) = 0;
	void ForwardTraverse(std::vector<BiTreeNode<T>*>& ret) { _ForwardTraverse(_pRoot, ret); }
	void BackTraverse(std::vector<BiTreeNode<T>*>& ret) { _BackTraverse(_pRoot, ret); }
	void InorderTraverse(std::vector<BiTreeNode<T>*>& ret) { _InorderTraverse(_pRoot, ret); }
	void LevelTraverse(std::vector<BiTreeNode<T>*>& ret) { _LevelTraverse(_pRoot, ret); }
};

#endif // BI_TREE