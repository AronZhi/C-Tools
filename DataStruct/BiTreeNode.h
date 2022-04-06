#ifndef BITREE_NODE
#define BITREE_NODE

template<class T>
class BiTreeNode
{
public:
	BiTreeNode<T>* _pLeft;
	BiTreeNode<T>* _pRight;
	int32_t _balance;
	T _data;

public:
	BiTreeNode() : _pLeft(nullptr), _pRight(nullptr), _balance(0){}
	BiTreeNode(const BiTreeNode<T>& src) : _pLeft(nullptr), _pRight(nullptr), _balance(0), _data(src._data) {}
	BiTreeNode(const T& data) : _pLeft(nullptr), _pRight(nullptr), _balance(0), _data(data) {}
};

#endif // BITREE_NODE