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
			_PreTraverse(out, pRootNode->Left());
			_PreTraverse(out, pRootNode->Right());
		}
	}

	void _InTraverse(std::queue<TreeNode<T>*>& out, TreeNode<T>* pRootNode)
	{
		if (pRootNode)
		{
			_InTraverse(out, pRootNode->Left());
			out.push(pRootNode);
			_InTraverse(out, pRootNode->Right());
		}
	}

	void _BakTraverse(std::queue<TreeNode<T>*>& out, TreeNode<T>* pRootNode)
	{
		if (pRootNode)
		{
			_BakTraverse(out, pRootNode->Left());
			_BakTraverse(out, pRootNode->Right());
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
				TreeNode<T>* tPNode = pNode->Left();
				if (tPNode)
					tq.push(tPNode);
				out.push_back(tPNode);
				tPNode = pNode->Right();
				if (tPNode)
					tq.push(tPNode);
				out.push_back(tPNode);
				tq.pop();
			}
		}
	}

public:
	BiTree(): _pRoot(nullptr) {}
	virtual ~BiTree()
	{
		std::queue<TreeNode<T>*> q;
		BakTraverse(q);
		while (!q.empty())
		{
			TreeNode<T>* pNode = q.front();
			delete pNode;
			q.pop();
		}
		_pRoot = nullptr;
	}

	virtual void AddNode(T data) = 0;
	void PreTraverse(std::queue<TreeNode<T>*>& out) { _PreTraverse(out, _pRoot); }
	void InTraverse(std::queue<TreeNode<T>*>& out) { _InTraverse(out, _pRoot); }
	void BakTraverse(std::queue<TreeNode<T>*>& out) { _BakTraverse(out, _pRoot); }
	void LevTraverse(std::vector<TreeNode<T>*>& out) { _LevTraverse(out, _pRoot); }
};
#endif // BI_TREE_H	