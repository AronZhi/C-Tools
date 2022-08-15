#ifndef AVL_NODE
#define AVL_NODE

template <class T>
class AvlNode
{
public:
	short _balance;
	unsigned int _leveal;
	T* _pData;
	AvleNode<T>* _pLeftChild;
	AvleNode<T>* _pRightChild;

	AvlNode(unsigned short level = 0, T* pData = nullptr) : _balance(0), _leave(level), _pData(pData), 
		_pLeftChild(nullptr), _pRightChild(nullptr) {}
	AvlNode(const AvlNodde<T>& src) = delete;
};

#endif // AVL_NODE
