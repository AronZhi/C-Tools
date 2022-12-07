#ifndef AVL_SORT_TREE
#define AVL_SORT_TREE

#include "BinaryTree.hpp"


template <class T>
class AvlSortTree : public BinaryTree<T>
{
public:
	~AvlSortTree()
	{
		std::vector<BinaryTreeNode<T>*> tree_arr;
		this->levelTraverse(this->root(), tree_arr);
		int count = tree_arr.size();
		for (int i = count - 1; i >= 0; --i)
		{
			delete tree_arr[i];
			tree_arr[i] = nullptr;
		}
	}

	void __relinkChild(BinaryTreeNode<T>* p_node, BinaryTreeNode<T>* p_parent, bool node_is_left_child)
	{
		if (nullptr == p_parent)
		{
			this->_p_root = p_node;	
		}
		else
		{
			if (node_is_left_child)
				p_parent->_p_left_child = p_node;
			else
				p_parent->_p_right_child = p_node;
		}
	}

	void __rightRotate(BinaryTreeNode<T>*& p_node, BinaryTreeNode<T>* p_parent, bool node_is_left_child)
	{
		/*
		*	右旋转,A右(顺时针)旋转成为B的子树。B的右子树将指向A,要先用A的左子树指向B的右子树，再让B的右子树指向A，否则会丢失掉B的右子树，其他节点不变，B成为新的根节点。
		* 
		*			A					B
		*		   /				   / \
		*		  B			->		  C   A
		*		 /
		*		C
		*/
		// BinaryTreeNode<T>* p_node_A = p_node;
		BinaryTreeNode<T>* p_node_B = p_node->_p_left_child;
		p_node->_p_left_child = p_node_B->_p_right_child;
		p_node_B->_p_right_child = p_node;
		__relinkChild(p_node_B, p_parent, node_is_left_child);
	}

	void __leftRotate(BinaryTreeNode<T>*& p_node, BinaryTreeNode<T>* p_parent, bool node_is_left_child)
	{
		/*
		*	左旋转,A左(逆时针)旋转成为B的子树。B的左子树将指向A，要先用A的右子树指向B的左子树，再让B的左子树指向A,否则会丢失掉B的右子树，其他节点不变，B成为新的根节点。
		*		A						B
		*		 \					   / \
		*		  B			->		  A   C
		*		   \
		*			C
		*/
		// BinaryTreeNode<T>* p_node_A = p_node;
		BinaryTreeNode<T>* p_node_B = p_node->_p_right_child;
		p_node->_p_right_child = p_node_B->_p_left_child;
		p_node_B->_p_left_child = p_node;
		__relinkChild(p_node_B, p_parent, node_is_left_child);
	}

	void __handleLeftLeftUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* 节点是因为新节点插入了其左子树的左子树而失衡。
		* 右旋失衡节点一次即可处理。
		*		A							B
		*	   / \						   / \
		*     B   E					      C   A
		*    / \			->			 /   / \
		*   C   D						F   D   E
		*  /
		* F
		* F无论在C的左边还是右边，都这样处理
		*/
		__rightRotate(p_unbalance_node, p_parent, p_parent ? p_unbalance_node == p_parent->_p_left_child : false);
	}

	void __handleRightRightUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* 节点是因为新节点插入了其右子树的右子树而失衡。
		* 左旋失衡节点一次即可处理。
		*		A							B
		*	   / \						   / \
		*     E   B						  A   C
		*        / \		->			 / \   \
		*       D   C					E   D   F
		*			 \
		*			  F
		* F无论在C的左边还是右边，都这样处理
		*/
		__leftRotate(p_unbalance_node, p_parent, p_parent ? p_unbalance_node == p_parent->_p_left_child : false);
	}

	void __handleLeftRightUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* 节点是因为新节点插入了其左子树的右子树而失衡。
		* 先左旋B使之成为一个LL失衡的树,然后右旋A。
		* 
		*		A							A							D
		*	   / \						   / \						   / \
		*	  B	  F						  D	  F						  B	  A
		*	 / \			->			 /				->			 / \   \
		*	C   D						B							C   E	F
		*	   /					   / \	 
		*	  E						  C	  E  
		*/
		__leftRotate(p_unbalance_node->_p_left_child, p_unbalance_node, true);
		__rightRotate(p_unbalance_node, p_parent, p_parent ? p_unbalance_node == p_parent->_p_left_child : false);
	}

	void __handleRightLeftUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* 节点是因为新节点插入了其右子树的左子树而失衡。
		* 先右旋B，使之成为RR失衡的树，再左旋A即可。
		*			A						A							C
		*		   / \					   / \						   / \
		*		  F	  B					  F   C						  A	  B
		*			 / \	->				 / \		->			 / \   \
		*			C	D					E	B					F	E	D
		*		   /						     \
		*		  E								  D
		*/
		__rightRotate(p_unbalance_node->_p_right_child, p_unbalance_node, false);
		__leftRotate(p_unbalance_node, p_parent, p_unbalance_node == p_parent->_p_left_child);
	}

	void handleUnBalance(BinaryTreeNode<T>*& p_tree)
	{
		std::vector<BinaryTreeNode<T>*> tree_arr;
		this->levelTraverse(p_tree, tree_arr);
		int count = tree_arr.size();
		for (int i = count - 1; i >= 0; --i)
		{
			BinaryTreeNode<T>* p_node = tree_arr[i];
			if (this->height(p_node->_p_left_child) - this->height(p_node->_p_right_child) > 1)
			{
				/* 因为AVL树是高度相差1以内的二叉搜索树，又因为失衡节点不可能会是叶子节点，
				对于失衡节点来说，可以用顺序存储的方法计算出其父节点 */
				BinaryTreeNode<T>* p_parent = i > 0 ? tree_arr[(i - 1) / 2] : nullptr;
				if (this->height(p_node->_p_left_child->_p_left_child) > this->height(p_node->_p_left_child->_p_right_child))
					__handleLeftLeftUnbalance(p_node, p_parent);
				else
					__handleLeftRightUnbalance(p_node, p_parent);
				this->__updateHeight(p_tree);
				break;
			}
			else if (this->height(p_node->_p_left_child) - this->height(p_node->_p_right_child) < -1)
			{
				BinaryTreeNode<T>* p_parent = i > 0 ? tree_arr[(i - 1) / 2] : nullptr;
				if (this->height(p_node->_p_right_child->_p_left_child) > this->height(p_node->_p_right_child->_p_right_child))
					__handleRightLeftUnbalance(p_node, p_parent);
				else
					__handleRightRightUnbalance(p_node, p_parent);
				this->__updateHeight(p_tree);
				break;
			}
		}
	}

	int __addNode(T data, BinaryTreeNode<T>*& p_tree)
	{
		if (p_tree)
		{
			if (data > p_tree->_data)
				return __addNode(data, p_tree->_p_right_child);
			else if (data < p_tree->_data)
				return __addNode(data, p_tree->_p_left_child);
			else
				return -1;
		}
		else
		{
			p_tree = new BinaryTreeNode<T>(data);
		}
		return 0;
	}

	int insert(T data)
	{
		int ret = __addNode(data, this->_p_root);
		if (0 == ret)
		{
			this->__updateHeight(this->_p_root);
			handleUnBalance(this->_p_root);
		}
		return ret;
	}

	int __delNode(T data, BinaryTreeNode<T>* p_tree, BinaryTreeNode<T>* p_parent)
	{
		if (p_tree)
		{
			if (p_tree->_data == data)
			{
				bool is_left_child = p_parent ? p_tree == p_parent->_p_left_child : false;
				if (p_tree->_p_left_child && p_tree->_p_right_child)
				{
					/* 如果只左右子树都有, 找到左子树的最右节点，替换掉删除节点 */
					BinaryTreeNode<T>* p_tmp_1 = p_tree;
					BinaryTreeNode<T>* p_tmp_2 = p_tree->_p_left_child;
					while (p_tmp_2->_p_right_child)
					{
						p_tmp_1 = p_tmp_2;
						p_tmp_2 = p_tmp_2->_p_right_child;
					}
					p_tmp_2->_p_left_child = p_tree->_p_left_child == p_tmp_2 ? nullptr : p_tree->_p_left_child;
					p_tmp_2->_p_right_child = p_tree->_p_right_child;
					p_tmp_1->_p_right_child = nullptr;
					__relinkChild(p_tmp_2, p_parent, is_left_child);
				}
				else if (nullptr == p_tree->_p_left_child && nullptr == p_tree->_p_right_child)
				{
					/* 如果是叶子节点, 删除既可 */
					__relinkChild(nullptr, p_parent, is_left_child);
				}
				else if (nullptr == p_tree->_p_left_child)
				{
					/* 如果只有左子树, 将左子树替换掉删除节点即可 */
					__relinkChild(p_tree->_p_left_child, p_parent, is_left_child);
				}
				else
				{
					/* 如果只有右子树, 将左子树替换掉删除节点即可 */
					__relinkChild(p_tree->_p_right_child, p_parent, is_left_child);
				}
				p_tree->_p_left_child = nullptr;
				p_tree->_p_right_child = nullptr;
				delete p_tree;
				p_tree = nullptr;
				return 0;

			}
			else if (data > p_tree->_data)
				return __delNode(data, p_tree->_p_right_child, p_tree);
			else
				return __delNode(data, p_tree->_p_left_child, p_tree);
		}
		return -1;
	}

	int remove(T data)
	{
		int ret = __delNode(data, this->_p_root, this->_p_root);
		if (0 == ret)
		{
			this->__updateHeight(this->_p_root);
			handleUnBalance(this->_p_root);
		}
		return ret;
	}
};

#endif // AVL_SORT_TREE