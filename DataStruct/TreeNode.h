#ifndef TREE_NODE_H
#define TREE_NODE_H

template <class T>
class TreeNode
{
private:
	TreeNode<T>* _pRight;
	TreeNode<T>* _pLeft;
	T _data;

public:
	TreeNode() : _pRight(nullptr), _pLeft(nullptr) {}
	TreeNode(T data) : _pRight(nullptr), _pLeft(nullptr), _data(data) {}
	TreeNode(const TreeNode<T>& src) :_pRight(nullptr), _pLeft(nullptr), _data(src._data) {}
	virtual ~TreeNode() {}

	TreeNode<T>*& RightRef() { return _pRight; }
	TreeNode<T>*& LeftRef() { return _pLeft; }
	T& DataRef() { return _data; }

	bool SetLeft(TreeNode<T>* node) { return _pLeft ? false : _pLeft = node, true; }
	bool SetRight(TreeNode<T>* node) { return _pRight ? false : _pRight = node, true; }

	bool LessThan(const TreeNode<T>& other) { return _data < other._data; }
	bool BiggerThan(const TreeNode<T>& other) { return _data > other._data; }
	bool EqualTo(const TreeNode<T>& other) { return _data == other._data; }
};
#endif // TREE_NODE_H