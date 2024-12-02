# ifndef TREE_H
# define TREE_H

# include "student.h"
#include <algorithm>

template<typename Type>
Type max (Type a, Type b) {
	return (a > b ? a : b);
}

template<typename Type>
Type abs (Type a) {
	return (a > 0 ? a : -a);
}

template <class T> class tree;

template <class T>
class tree_node : public T {
	private:
		tree_node *left = nullptr;
		tree_node *right = nullptr;
	public:
		tree_node () = default;
		tree_node (const tree_node& x) = delete;
		tree_node (tree_node&& x) : T ((T&&)x) {
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
			(T&&) *this = (T&&) x;
			erase_links();
			x.erase_links();
			return *this;
		}
		friend class tree<T>;
	private:
		void erase_links () {
			left = nullptr; right = nullptr;
		}
} ;

template <class T>
class tree {
	private:
		tree_node<T> *root = nullptr;
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
			tree_node<T> x;
			unsigned int count = 0;
			while(x.read(fp) == io_status::success && count < max_read) {
				tree_node<T> *curr = new tree_node<T>((tree_node<T>&&)x);
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
		static void delete_subtree (tree_node<T> *curr) {
			if(curr == nullptr)
				return ;
			delete_subtree (curr->left);
			delete_subtree (curr->right);
			delete curr;
		}
		static void print_subtree (tree_node<T> *curr, int level, int r,
						FILE *fp = stdout) {
			if(curr == nullptr || level > r)
				return ;
			int spaces = level * 2;
			/* for(int i = 0; i < spaces; i++)
				fprintf(fp, " "); */
			curr->print(fp, spaces);
			print_subtree (curr->left, level + 1, r, fp);
			print_subtree (curr->right, level + 1, r, fp);
		}
		static void add_node_subtree (tree_node<T> *curr, tree_node<T> *x) {
			if(*x < *curr){ //!!!!!
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
	public:
		int tasks1_5 (int task_num) const {
			switch (task_num) {
				case 1:
					return task1 ();
				case 2:
					return task2 ();
				case 3:
					return task3 ();
				case 4:
					return task4 ();
				case 5:
					return task5 ();
			}
			return 0;
		}
	private:
		int get_count_leaf_students (tree_node<T> *curr) const {
			if(curr == nullptr)
				return 0;
			if(curr->right == nullptr && curr->left == nullptr)
				return curr->get_length();
			return get_count_leaf_students(curr->left) + get_count_leaf_students(curr->right);
		}
		int get_count_max_branch (tree_node<T> *curr) const {
			if(curr == nullptr)
				return 0;
			if(curr->right == nullptr && curr->left == nullptr)
				return curr->get_length();
			return curr->get_length() + max(get_count_max_branch(curr->left), 
				get_count_max_branch(curr->right));
		}
		int get_level_width (tree_node<T> *curr, int level, int curr_level = 0) const { // 7.3 auxiliary
			if(curr == nullptr)
				return 0;
			if(curr_level == level)
				return curr->get_length();
			return get_level_width(curr->left, level, curr_level + 1) +
				get_level_width(curr->right, level, curr_level + 1);
		}
		int get_balance (tree_node<T> *curr) const {
			int res, diff;
			if(curr == nullptr)
				return 0;
			diff = abs(get_count_max_branch(curr->left) - 
				get_count_max_branch(curr->right));
			res = max(get_balance(curr->left), get_balance(curr->right));
			return max(diff, res);
		}
		int get_count_1 (tree_node<T> *curr) const { // 7.5
			int res = 0;
			if(curr == nullptr)
				return 0;
			if( (curr->left == nullptr && curr->right != nullptr) ||
					(curr->right == nullptr && curr->left != nullptr) )
				res += curr->get_length();
			res += get_count_1(curr->right) + get_count_1(curr->left);
			return res;
		}
		
	// TASKS
		int task1 () const {
			return get_count_leaf_students(root);
		}
		int task2 () const {
			return get_count_max_branch (root);
		}
		int task3 () const {
			int width = 1, max_width = 1, level;
			if(root == nullptr)
				return 0;
			for(level = 1; width > 0; level++){
				width = get_level_width(root, level);
				if(width > max_width)
					max_width = width;
			}
			return max_width;
		}
		int task4 () const {
			return get_balance (root);
		}
		int task5 () const {
			return get_count_1 (root);
		}
} ;

# endif // TREE_H
