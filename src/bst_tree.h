#ifndef BST_TREE_H
#define BST_TREE_H

template<typename T>
class bst_tree {
	struct tree_node {
		T val;
		tree_node* right;
		tree_node* left;

		tree_node(){}
		tree_node(T val) : this->val(val) {}
		tree_node(T val, tree_node* left, tree_node* right) : this->val(val), this->left(left), this->right(right){}
	};

	tree_node* head_;
	size_t size_;


public:
	bst_tree(){}

	~bst_tree(){}
};






#endif