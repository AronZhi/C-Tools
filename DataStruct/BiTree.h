#ifndef BI_TREE_H
#define BI_TREE_H

#include <queue>
#include <list>
#include <vector>

#include "TreeNode.h"

template <class T>
class BiTree
{
public:
	TreeNode<T>* _pRoot;

protected:
	void _PreTraverse(std::queue<TreeNode<T>*>& out, TreeNode<T>* pRootNode)
	{
		if (pRootNode)
		{
			out.push(pRootNode);
			_PreTraverse(out, pRootNode->LeftRef());
			_PreTraverse(out, pRootNode->RightRef());
		}
	}

	void _InTraverse(std::queue<TreeNode<T>*>& out, TreeNode<T>* pRootNode)
	{
		if (pRootNode)
		{
			_InTraverse(out, pRootNode->LeftRef());
			out.push(pRootNode);
			_InTraverse(out, pRootNode->RightRef());
		}
	}

	void _BakTraverse(std::queue<TreeNode<T>*>& out, TreeNode<T>* pRootNode)
	{
		if (pRootNode)
		{
			_BakTraverse(out, pRootNode->LeftRef());
			_BakTraverse(out, pRootNode->RightRef());
			out.push(pRootNode);
		}
	}

	void _LevTraverse(std::vector<TreeNode<T>*>& out, TreeNode<T>* pRootNode)
	{
		if (pRootNode)
		{
			std::queue<TreeNode<T>*> tq;
			tq.push(pRootNode);
			out.push_back(pRootNode);
			while (!tq.empty())
			{
				TreeNode<T>* pNode = tq.front();
				TreeNode<T>* tPNode = pNode->LeftRef();
				if (tPNode)
					tq.push(tPNode);
				out.push_back(tPNode);
				tPNode = pNode->RightRef();
				if (tPNode)
					tq.push(tPNode);
				out.push_back(tPNode);
				tq.pop();
			}
		}
	}

public:
	BiTree(): _pRoot(nullptr) {}
	virtual ~BiTree(){}

	virtual void AddNode(TreeNode<T>* node) = 0;
	void PreTraverse(std::queue<TreeNode<T>*>& out) { _PreTraverse(out, _pRoot); }
	void InTraverse(std::queue<TreeNode<T>*>& out) { _InTraverse(out, _pRoot); }
	void BakTraverse(std::queue<TreeNode<T>*>& out) { _BakTraverse(out, _pRoot); }
	void LevTraverse(std::vector<TreeNode<T>*>& out) { _LevTraverse(out, _pRoot); }
};
#endif // BI_TREE_H	