# ifndef TREE_H
# define TREE_H

# include "student.h"

template<typename Type>
Type max (Type a, Type b) {
	return (a > b ? a : b);
}

template<typename Type>
Type abs (Type a) {
	return (a > 0 ? a : -a);
}

class tree;

class tree_node : public student {
	private:
		tree_node *left;
		tree_node *right;
	public:
		tree_node () = default;
		tree_node (const tree_node& x) = delete;
		tree_node (tree_node&& x) : student ((student&&)x) {
			erase_links();
			x.erase_links();
		}
		~tree_node () {
			erase_links();
		}
		tree_node& operator= (const tree_node& x) = delete;
		tree_node& operator= (tree_node&& x) {
			if(this == &x)
				return *this;
			(student&&) *this = (student&&) x;
			erase_links();
			x.erase_links();
			return *this;
		}
		friend class tree;
	private:
		void erase_links () {
			left = nullptr; right = nullptr;
		}
} ;

class tree {
	private:
		tree_node *root = nullptr;
	public:
		tree () = default;
		tree (const tree& x) = delete;
		tree (tree&& x) {
			root = x.root; x.root = nullptr;
		}
		~tree () {
			delete_subtree(root);
			root = nullptr;
		}
		tree& operator= (const tree& x) = delete;
		tree& operator= (tree&& x) {
			if(this == &x)
				return *this;
			delete_subtree(root);
			root = x.root; x.root = nullptr;
			return *this;
		}
		void print (unsigned int r = 10, FILE *fp = stdout) const {
			print_subtree(root, 0, r, fp);
		}
		io_status read (FILE *fp = stdin, unsigned int max_read = -1) {
			tree_node x;
			unsigned int count = 0;
			while(x.read(fp) == io_status::success && count < max_read) {
				tree_node *curr = new tree_node((tree_node&&)x);
				if(curr == nullptr)
					return io_status::memory;
				if(root == nullptr)
					root = curr;
				else
					add_node_subtree(root, curr);
			}
			if(count == max_read)
				return io_status::success;
			if(!feof(fp))
				return io_status::eof;
			return io_status::success;
		}
	private:
		static void delete_subtree (tree_node *curr) {
			if(curr == nullptr)
				return ;
			delete_subtree (curr->left);
			delete_subtree (curr->right);
			delete curr;
		}
		static void print_subtree (tree_node *curr, int level, int r,
						FILE *fp = stdout) {
			if(curr == nullptr || level > r)
				return ;
			int spaces = level * 2;
			for(int i = 0; i < spaces; i++)
				printf(" ");
			curr->print(fp);
			print_subtree (curr->left, level + 1, r, fp);
			print_subtree (curr->right, level + 1, r, fp);
		}
		static void add_node_subtree (tree_node *curr, tree_node *x) {
			if(*x < *curr){
				if(curr->left == nullptr)
					curr->left = x;
				else
					add_node_subtree(curr->left, x);
			}
			else{
				if(curr->right == nullptr)
					curr->right = x;
				else
					add_node_subtree(curr->right, x);
			}
		}
		void clear () {
			root = nullptr;
		}

// TASKS
	public:
	// task 01
		int num_end_elements () {
			tree curr_tree;
			int res = 0;
			if(root == nullptr)
				return 0;
			if(root->left == nullptr && root->right == nullptr)
				return 1;
			curr_tree.root = root->left;
			res += curr_tree.num_end_elements();
			curr_tree.root = root->right;
			res += curr_tree.num_end_elements();
			curr_tree.clear();
			return res;
		}

	// task 02
		int get_depth () {
			tree curr_tree;
			int res_left, res_right;
			if(root == nullptr)
				return 0;
			curr_tree.root = root->left;
			res_left = curr_tree.get_depth();
			curr_tree.root = root->right;
			res_right = curr_tree.get_depth();
			curr_tree.clear();
			return max(res_left, res_right) + 1;
		}
	// task 03
		int get_level_width (int level, int curr_level = 0){
			tree left_subtree, right_subtree;
			int res = 0;
			if(root == nullptr)
				return 0;
			if(curr_level == level)
				return 1;
			left_subtree.root = root->left;  right_subtree.root = root->right;
			res += left_subtree.get_level_width(level, curr_level + 1);
			res += right_subtree.get_level_width(level, curr_level + 1);
			left_subtree.clear();  right_subtree.clear();
			return res;
		}
		int get_max_width () {
			int curr_width = 1, max_width = 1, curr_level;
			if(root == nullptr)
				return 0;
			for(curr_level = 1; curr_width > 0; curr_level++){
				curr_width = this->get_level_width(curr_level);
				if(curr_width > max_width)
					max_width = curr_width;
			}
			return max_width;
		}
	// task 04
		int task4 () {
			tree left_subtree, right_subtree;
			int res, diff;
			if(root == nullptr)
				return 0;
			left_subtree.root = root->left;
			right_subtree.root = root->right;
			diff = abs(left_subtree.get_depth() - right_subtree.get_depth());
			res = max(left_subtree.task4(), right_subtree.task4());
			left_subtree.clear();  right_subtree.clear();
			return max(diff, res);
		}
	// task05
		int num_having_one_child () {
			tree curr_tree;
			int res = 0;
			if(root == nullptr)
				return 0;
			if( (root->left == nullptr && root->right != nullptr) ||
					(root->right == nullptr && root->left != nullptr) )
				res++;
			curr_tree.root = root->right;
			res += curr_tree.num_having_one_child();
			curr_tree.root = root->left;
			res += curr_tree.num_having_one_child();
			curr_tree.clear();
			return res;
		}
} ;

# endif // TREE_H
