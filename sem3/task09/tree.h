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

class tree;

class tree_node : public student {
	private:
		tree_node *down = nullptr;
		tree_node *level = nullptr;
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
			level = nullptr; down = nullptr;
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
			tree_node *p, *next;
			for(p = curr->down; p; p = next) {
				next = p->level;
				delete_subtree(p);
			}
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
			for(tree_node *p = curr->down; p; p = p->level)
				print_subtree (p, level + 1, r, fp);
		}
		static void add_node_subtree (tree_node *curr, tree_node *x) {
			if(curr->down == nullptr) {
				curr->down = x;
				return ;
			}
			if(*x < *curr){
				if(*curr->down < *curr)
					add_node_subtree(curr->down, x);
				else {
					x->level = curr->down;
					curr->down = x;
				}
			}
			else if(*x == *curr){
				if(curr->down->level != nullptr){
					x->level = curr->down->level;
					curr->down->level = x;
				}
				else if(*curr->down < *curr){
					curr->down->level = x;
				} else {
					x->level = curr->down;
					curr->down = x;
				}
			}
			else {
				tree_node *p;
				for(p = curr->down; p->level; p = p->level) ;
				if(*p > *curr)
					add_node_subtree (p, x);
				else
					p->level = x;
			}
		}
		void clear () {
			root = nullptr;
		}

	private:
		int get_count_total () const {
			tree curr_tree;
			int res = 1;
			if(root == nullptr)
				return 0;
			for(tree_node *curr = root->down; curr; curr = curr->level) {
				curr_tree.root = curr;
				res += curr_tree.get_count_total();
			}
			curr_tree.clear();
			return res;
		}
		int get_count_total (tree_node *curr) const {
			int res = 1;
			if(curr == nullptr)
				return 0;
			for(tree_node *child = curr->down; child; child = child->level) {
				res += get_count_total(child);
			}
			return res;
		}
		int get_height () const {
			tree curr_tree;
			int max_height = 0;
			if(root == nullptr)
				return 0;
			for(tree_node *curr = root->down; curr; curr = curr->level) {
				curr_tree.root = curr;
				max_height = max(curr_tree.get_height(), max_height);
			}
			curr_tree.clear();
			return max_height + 1;
		}
		int get_count_children (tree_node *curr) const {
			int res;
			for(curr = curr->down, res = 0; curr; curr = curr->level, res++) ;
			return res;
		}
		int get_level_width (tree_node *curr, int level, int curr_level = 0) const {
			int res = 0;
			tree_node *child;
			if(curr == nullptr)
				return 0;
			if(level == 0)
				return 1;
			if(curr_level == level - 1)
				return get_count_children(curr);
			for(child = curr->down; child; child = child->level)
				res += get_level_width(child, level, curr_level + 1);
			return res;
		}
/*		int get_count_leaf (tree_node *curr) const {
			int res = 0;
			if(curr == nullptr)
				return 0;
			if(curr->down == nullptr)
				return 1;
			for(tree_node *child = curr->down; child; child = child->level)
				res += get_count_leaf(child);
			return res;
		}*/
		int get_count_branches_longer_than (tree_node *curr, int k, int curr_len = 1) const {
			int res = 0;
			if(curr == nullptr)
				return 0;
			if(curr_len >= k)
				return get_count_total (curr);
			for(tree_node *child = curr->down; child; child = child->level)
				res += get_count_branches_longer_than(child, k, curr_len + 1);
			if(res > 0)
				return res + 1;
			else
				return 0;
		}
	public:
		int tasks1_6 (int k, int task_num) const {
			switch (task_num) {
				case 1:
					return task1 (k);
				case 2:
					return task2 (k);
				case 3:
					return task3 (k);
				case 4:
					return task4 (k);
				case 5:
					return task5 (k);
				case 6:
					return task6 (k);
			}
			return 0;
		}
	private:
		int task1 (int k) const {
			tree child_tree;
			int children = 0, res = 0;
			if(root == nullptr)
				return 0;
			for(tree_node *curr = root->down; curr; curr = curr->level, children++) {
				child_tree.root = curr;
				res += child_tree.task1(k);
			}
			child_tree.clear();
			res += (children == k) ? 1 : 0;
			return res;
		}
		int task2 (int k) const {
			tree child_tree;
			int res = 0, tmp;
			tmp = get_count_total();
			if(tmp <= k)
				return tmp;
			for(tree_node *curr = root->down; curr; curr = curr->level) {
				child_tree.root = curr;
				res += child_tree.task2(k);
			}
			child_tree.clear();
			return res;
		}
		int task3 (int k) const {
			tree child_tree;
			int res = 0;
			if(get_height() <= k)
				return get_count_total();
			for(tree_node *curr = root->down; curr; curr = curr->level) {
				child_tree.root = curr;
				res += child_tree.task3(k);
			}
			child_tree.clear();
			return res;
		}
		int task4 (int k) const {
			tree child_tree;
			int res = 0, i, tmp;
			for(i = 0, tmp = task5(i); tmp > 0 && tmp <= k; i++, tmp = task5(i)) ;
			if(tmp <= k)
				return get_count_total();
			for(tree_node *curr = root->down; curr; curr = curr->level) {
				child_tree.root = curr;
				res += child_tree.task4(k);
			}
			child_tree.clear();
			return res;
		}
		int task5 (int k) const {
			return get_level_width (root, k);
		}
		int task6 (int k) const {
			return get_count_branches_longer_than(root, k);
		}
} ;

# endif // TREE_H
