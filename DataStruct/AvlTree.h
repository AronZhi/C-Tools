#ifndef AVL_TREE
#define AVL_TREE

#include "AvlNode.h"

class AvlTree
{
protected:
	AvlNode<T>* _pRoot;

public:
	AvlTree(): _pRoot(nullptr) {}
};

#endif // AVL_TREE
