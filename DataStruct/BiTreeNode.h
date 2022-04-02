#ifndef BITREE_NODE
#define BITREE_NODE

template<class T>
class BiTreeNode
{
public:
	BiTreeNode<T>* _pLeft;
	BiTreeNode<T>* _pRight;
	T _data;

public:
	BiTreeNode() : _pLeft(nullptr), _pRight(nullptr) {}
	BiTreeNode(const BiTreeNode<T>& src) : _pLeft(nullptr), _pRight(nullptr), _data(src._data) {}
	BiTreeNode(const T& data) : _pLeft(nullptr), _pRight(nullptr), _data(data) {}
};

#endif // BITREE_NODE