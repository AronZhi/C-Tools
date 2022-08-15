#ifndef AVL_SORT_TREE
#define AVL_SORT_TREE

#include "BinaryTree.h"


template <class T>
class AvlSortTree : public BinaryTree<T>
{
public:
	~AvlSortTree()
	{
		std::vector<BinaryTreeNode<T>*> tree_arr;
		levelTraverse(p_node, tree_arr);
		count = tree_arr.size();
		for (int i = count - 1; i >= 0; --i)
		{
			delete tree_arr[i];
			tree_arr[i] = nullptr;
		}
	}

	void relinkChild(BinaryTreeNode<T>* p_node, BinaryTreeNode<T>* p_parent, bool node_is_left_child)
	{
		if (p_parent)
		{
			if (node_is_left_child)
				p_parent->_p_left_child = p_node;
			else
				p_parent->_p_right_child = p_node;
		}
	}

	void rightRotate(BinaryTreeNode<T>* p_node, BinaryTreeNode<T>* p_parent, bool node_is_left_child)
	{
		/*
		*	����ת,A��(˳ʱ��)��ת��ΪB��������B����������ָ��A,Ҫ����A��������ָ��B��������������B��������ָ��A������ᶪʧ��B���������������ڵ㲻�䣬B��Ϊ�µĸ��ڵ㡣
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
		relinkChild(p_node_B, p_parent, node_is_left_child);
	}

	void leftRotate(BinaryTreeNode<T>* p_node, BinaryTreeNode<T>* p_parent, bool node_is_left_child)
	{
		/*
		*	����ת,A��(��ʱ��)��ת��ΪB��������B����������ָ��A��Ҫ����A��������ָ��B��������������B��������ָ��A,����ᶪʧ��B���������������ڵ㲻�䣬B��Ϊ�µĸ��ڵ㡣
		*		A						B
		*		 \					   / \
		*		  B			->		  A   C
		*		   \
		*			C
		*/
		// BinaryTreeNode<T>* p_node_A = p_node;
		BinaryTreeNode<T>* p_node_B = p_node->_p_right_child;
		p_node->_p_right_child = p_node_B->_p_left_child;
		p_node_B->_p_right_child = p_node;
		relinkChild(p_node_B, p_parent, node_is_left_child);
	}

	void handleLeftLeftUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* �ڵ�����Ϊ�½ڵ������������������������ʧ�⡣
		* ����ʧ��ڵ�һ�μ��ɴ���
		*		A							B
		*	   / \						   / \
		*     B   E					      C   A
		*    / \			->			 /   / \
		*   C   D						F   D   E
		*  /
		* F
		* F������C����߻����ұߣ�����������
		*/
		rightRotate(p_unbalance_node, p_parent, p_unbalance_node == p_parent->_p_left_child);
	}

	void handleRightRightUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* �ڵ�����Ϊ�½ڵ������������������������ʧ�⡣
		* ����ʧ��ڵ�һ�μ��ɴ���
		*		A							B
		*	   / \						   / \
		*     E   B						  A   C
		*        / \		->			 / \   \
		*       D   C					E   D   F
		*			 \
		*			  F
		* F������C����߻����ұߣ�����������
		*/
		leftRotate(p_unbalance_node, p_parent, p_unbalance_node == p_parent->_p_left_child);
	}

	void handleLeftRightUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* �ڵ�����Ϊ�½ڵ������������������������ʧ�⡣
		* ������Bʹ֮��Ϊһ��LLʧ�����,Ȼ������A��
		* 
		*		A							A							D
		*	   / \						   / \						   / \
		*	  B	  F						  D	  F						  B	  A
		*	 / \			->			 /				->			 / \   \
		*	C   D						B							C   E	F
		*	   /					   / \	 
		*	  E						  C	  E  
		*/
		leftRotate(p_unbalance_node->_p_left_child, p_unbalance_node, true);
		rightRotate(p_unbalance_node, p_parent, p_unbalance_node == p_parent->_p_left_child);
	}

	void handleRightLeftUnbalance(BinaryTreeNode<T>* p_unbalance_node, BinaryTreeNode<T>* p_parent)
	{
		/*
		* �ڵ�����Ϊ�½ڵ������������������������ʧ�⡣
		* ������B��ʹ֮��ΪRRʧ�������������A���ɡ�
		*			A						A							C
		*		   / \					   / \						   / \
		*		  F	  B					  F   C						  A	  B
		*			 / \	->				 / \		->			 / \   \
		*			C	D					E	B					F	E	D
		*		   /						     \
		*		  E								  D
		*/
		rightRotate(p_unbalance_node->_p_right_child, p_unbalance_node, false);
		leftRotate(p_unbalance_node, p_parent, p_unbalance_node == p_parent->_p_left_child);
	}

	void handleUnBalance(BinaryTreeNode<T>* p_tree)
	{
		std::vector<BinaryTreeNode<T>*> tree_arr;
		levelTraverse(p_node, tree_arr);
		count = tree_arr.size();
		for (int i = count - 1; i >= 0; --i)
		{
			BinaryTreeNode<T>* p_node = tree_arr[i];
			if (height(p_node->_p_left_child) - height(p_node->_p_right_child) > 1)
			{
				/* ��ΪAVL���Ǹ߶����1���ڵĶ���������������Ϊʧ��ڵ㲻���ܻ���Ҷ�ӽڵ㣬
				����ʧ��ڵ���˵��������˳��洢�ķ���������丸�ڵ� */
				if (height(p_node->_p_left_child->_p_left_child) > height(p_node->_p_left_child->_p_right_child))
					handleLeftLeftUnbalance(p_node, tree_arr[(i - 1) / 2]);
				else
					handleLeftRightUnbalance(p_node, tree_arr[(i - 1) / 2]);
				break;
			}
			else if (height(p_node->_p_left_child) - height(p_node->_p_right_child) < -1)
			{
				if (height(p_node->_p_right_child->_p_left_child) > height(p_node->_p_right_child->_p_right_child))
					handleRightLeftUnbalance(p_node, tree_arr[(i - 1) / 2]);
				else
					handleRightRightUnbalance(p_node, tree_arr[(i - 1) / 2]);
				break;
			}
		}
		updateHeight(p_tree);
	}

	int __addNode(T data, BinaryTreeNode<T>* p_tree)
	{
		if (p_tree)
		{
			if (data > p_tree->data)
				addNode(data, p_tree->_p_right_child);
			else if (data < p_tree->data)
				addNode(data, p_tree->_p_left_child);
			else
				return -1;
		}
		else
		{
			p_tree = new BinaryTreeNode<T>(data);
		}
		return 0;
	}

	int insert(T data, BinaryTreeNode<T>* p_tree)
	{
		__addNode(data, p_tree);
		updateHeight(p_tree);
		handleUnBalance(p_tree);
		return 0;
	}

	int __delNode(T data, BinaryTreeNode<T>* p_tree, BinaryTreeNode<T>* p_parent)
	{
		if (p_tree)
		{
			if (p_tree->_data == data)
			{
				if (nullptr == p_tree->_p_left_child && nullptr == p_tree->_p_right_child)
				{
					/* pass */
				}
				else if (nullptr == p_tree->_p_left_child)
				{
					relinkChild(p_tree->_p_left_child, p_parent, p_tree == p_parent->_p_left_child);
					
				}
				else if (nullptr == p_tree->_p_right_child)
				{
					relinkChild(p_tree->_p_right_child, p_parent, p_tree == p_parent->_p_left_child);
				}
				else
				{
					BinaryTreeNode<T>* p_tmp_1 = p_tree;
					BinaryTreeNode<T>* p_tmp_2 = p_tree->_p_left_child;
					while (p_tmp_2->_p_right_child)
					{
						p_tmp_1 = p_tmp_2;
						p_tmp_2 = p_tmp_2->_p_right_child;
					}
					p_tmp_1->_p_right_child = nullptr;
					p_tmp_2->_p_left_child = p_tree->_p_left_child;
					p_tree->_p_left_child = nullptr;
					relinkChild(p_tmp_2, p_parent, p_tree == p_parent->_p_left_child);
				}
				delete p_tree;
				p_tree = nullptr;
				return 0;

			}
			else if (data > p_tree->_data)
				delNode(data, p_tree->_p_right_child, p_tree);
			else
				dleNode(data, p_tree->_p_left_child, p_tree);
		}
		return -1;
	}

	int remove(T data, BinaryTreeNode<T>* p_tree)
	{
		int ret = __delNode(data, p_tree, p_tree);
		if (0 == ret)
		{
			updateHeight(p_tree);
			handleUnBalance(p_tree);
		}
		return ret;
	}
};

#endif // AVL_SORT_TREE
