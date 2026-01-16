#ifndef BST_TREE_H
#define BST_TREE_H

namespace MyDataStructures {

	template<typename T>
	class bst_tree {
		struct tree_node {
			T val;
			tree_node* right;
			tree_node* left;

			tree_node() = delete;
			tree_node(T val) : val(val), left(nullptr), right(nullptr) {}
			tree_node(T val, tree_node* left, tree_node* right) : val(val), left(left), right(right) {}
		};

		tree_node* head_;
		size_t size_;

		void req_insert(T new_node, tree_node* temp) {
			if (size_ == 0) {
				head_ = new tree_node(new_node);
				++size_;
				return;
			}

			if (temp && new_node == temp->val) {
				return;
			}
			else if (!temp->right && new_node > temp->val) {
				temp->right = new tree_node(new_node);
				++size_;
			}
			else if (!temp->left && new_node < temp->val) {
				temp->left = new tree_node(new_node);
				++size_;
			}
			else if (new_node > temp->val) {
				req_insert(new_node, temp->right);
			}
			else {
				req_insert(new_node, temp->left);
			}
		}

		T* req_find(T val, tree_node* temp) {
			if (!temp) return nullptr;

			if (val > temp->val) {
				return req_find(val, temp->right);
			}
			else if (val < temp->val) {
				return req_find(val, temp->left);
			}
			else {
				return &(temp->val);
			}
		}

		bool req_remove(T val, tree_node* temp, tree_node* par) {
			if (!temp) return false;

			if (val == temp->val) {
				if (!temp->left && !temp->right) {
					if (par->left->val == temp->val) {
						par->left = nullptr;
						delete temp;
						--size_;
					}
					else {
						par->right = nullptr;
						delete temp;
						--size_;
					}
				}
				else if (temp->left && temp->right) {
					tree_node* new_temp = temp->right;
					tree_node* new_par = temp;
					while (new_temp->left) {
						new_par = new_temp;
						new_temp = new_temp->left;
					}
					temp->val = new_temp->val;
					req_remove(val, new_temp, new_par);
				}
				else {
					if (temp->left) {
						if (par->left->val == temp->val) {
							par->left = temp->left;
							delete temp;
							--size_;
						}
						else {
							par->right = temp->left;
							delete temp;
							--size_;
						}
					}
					else {
						if (par->left->val == temp->val) {
							par->left = temp->right;
							delete temp;
							--size_;
						}
						else {
							par->right = temp->right;
							delete temp;
							--size_;
						}
					}
				}
				return true;
			}
			else if (val < temp->val) {
				return req_remove(val, temp->left, temp);
			}
			else {
				return req_remove(val, temp->right, temp);
			}
		}

		void req_clear(tree_node* temp) {
			if (temp) {
				if (temp->left) req_clear(temp->left);
				if (temp->right) req_clear(temp->right);
				delete temp;
			}
		}

	public:
		bst_tree() : size_(0), head_(nullptr) {}
		bst_tree(const bst_tree& other) {
		
		}
		bst_tree(bst_tree&& other) noexcept {
			this->size_ = other.size_;
			other.size_ = 0;
			this->head_ = other.head_;
			other.head_ = nullptr;
		}
		void operator=(const bst_tree& right) {
		
		}
		void operator=(bst_tree&& right) noexcept {
			this->clear();
			this->size_ = right.size_;
			right.size_ = 0;
			this->head_ = right.head_;
			right.head_ = nullptr;
		}

		void insert(T new_node) {
			req_insert(new_node, head_);
		}

		T* find(T val){
			return req_find(val, head_);
		}

		bool contains(T val){
			return find(val) != nullptr;
		}

		bool remove(T val){
			return req_remove(val, head_, nullptr);
		}


		bool empty() {
			return size_ == 0;
		}

		size_t size() {
			return size_;
		}

		void clear(){
			req_clear(head_);
			size_ = 0;
			head_ = nullptr;
		}

		size_t height(){}

		~bst_tree() {
			clear();
		}
	};

}

namespace mds = MyDataStructures;

#endif