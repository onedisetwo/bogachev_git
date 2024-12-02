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
		int get_count_total () const {
			tree curr_tree;
			int res = 1;
			if(root == nullptr)
				return 0;
			curr_tree.root = root->right;  res += curr_tree.get_count_total();
			curr_tree.root = root->left;  res += curr_tree.get_count_total();
			curr_tree.clear();
			return res;
		}
		int get_count_leaf () const { // 7.1
			tree curr_tree;
			int res = 0;
			if(root == nullptr)
				return 0;
			if(root->left == nullptr && root->right == nullptr)
				return 1;
			curr_tree.root = root->right;  res += curr_tree.get_count_leaf();
			curr_tree.root = root->left;  res += curr_tree.get_count_leaf();
			curr_tree.clear();
			return res;
		}
		int get_count_1 () const { // 7.5
			tree curr_tree;
			int res = 0;
			if(root == nullptr)
				return 0;
			if( (root->left == nullptr && root->right != nullptr) ||
					(root->right == nullptr && root->left != nullptr) )
				res++;
			curr_tree.root = root->right;  res += curr_tree.get_count_1();
			curr_tree.root = root->left;  res += curr_tree.get_count_1();
			curr_tree.clear();
			return res;
		}
		int get_count_2 () const {
			tree curr_tree;
			int res = 0;
			if(root == nullptr)
				return 0;
			if(root->left != nullptr && root->right != nullptr)
				res++;
			curr_tree.root = root->right;  res += curr_tree.get_count_2();
			curr_tree.root = root->left;  res += curr_tree.get_count_2();
			curr_tree.clear();
			return res;
		}
		int get_height () const { // 7.2
			tree curr_tree;
			int res_left, res_right;
			if(root == nullptr)
				return 0;
			curr_tree.root = root->right;  res_right = curr_tree.get_height();
			curr_tree.root = root->left;  res_left = curr_tree.get_height();
			curr_tree.clear();
			return max(res_left, res_right) + 1;
		}
	private:
		int get_level_width (tree_node *curr, int level, int curr_level = 0) const { // 7.3 auxiliary
			if(curr == nullptr)
				return 0;
			if(curr_level == level)
				return 1;
			return get_level_width(curr->left, level, curr_level + 1) +
				get_level_width(curr->right, level, curr_level + 1);
		}
	public:
		int get_width () const { // 7.3
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
		int get_balance () const { // 7.4
			tree left_subtree, right_subtree;
			int res, diff;
			if(root == nullptr)
				return 0;
			left_subtree.root = root->left;
			right_subtree.root = root->right;
			diff = abs(left_subtree.get_height() - right_subtree.get_height());
			res = max(left_subtree.get_balance(), right_subtree.get_balance());
			left_subtree.clear();  right_subtree.clear();
			return max(diff, res);
		}

// >>>>>>>>>>> SOLUTIONS <<<<<<<<<<<

// TASK 1
	private:
		void find_max (tree_node *curr, tree_node** max_node) const {
			if(curr == nullptr)
				return ;
			if(*curr > **max_node)
				*max_node = curr;
			find_max(curr->left, max_node);
			find_max(curr->right, max_node);
		}
	public:
		void task1 () {
			tree m_subtree;
			tree_node *max_node = root;
			if(root == nullptr)
				return ;
			find_max(root, &max_node);
			std::swap((student&)*root, (student&)*max_node);
			m_subtree.root = root->left;  m_subtree.task1();
			m_subtree.root = root->right;  m_subtree.task1();
			m_subtree.clear();
		}
// TASK 2
	private:
		void find_min_and_first_unsorted (int level, int &n, int sorted_n, tree_node* curr,
				tree_node **min_node, tree_node **first_unsorted, int curr_level = 0) const {
			if(curr == nullptr)
				return ;
			if(curr_level == level){
				if(n == sorted_n){
					*min_node = curr;  *first_unsorted = curr;
				}
				if(n > sorted_n && curr->get_value() < (*min_node)->get_value())
					*min_node = curr;
				n = n + 1;
			}
			else{
				find_min_and_first_unsorted (level, n, sorted_n, curr->left, min_node,
					first_unsorted, curr_level + 1);
				find_min_and_first_unsorted (level, n, sorted_n, curr->right, min_node,
					first_unsorted, curr_level + 1);
			}
		}
	public:
		void task2 () {
			tree_node* first_unsorted;
			tree_node* min_node;
			for(int level = 1; level < this->get_height(); level++){
				first_unsorted = nullptr;
				min_node = nullptr;
				for(int sorted_n = 0, n = 0; ;
				sorted_n++, n = 0, first_unsorted = nullptr, min_node = nullptr){
					find_min_and_first_unsorted (level, n, sorted_n, root, &min_node, &first_unsorted);
					if(first_unsorted == nullptr)  break;
					std::swap((student&)*first_unsorted, (student&)*min_node);
				}
			}
		}
// TASK 3
	private:
		tree_node* find_left_in_subtree (tree_node *start) const{
			tree_node *curr;
			if(start == nullptr || start->left == nullptr)
				return nullptr;
			for (curr = start; curr->left->left != nullptr; curr = curr->left) ;
			return curr;
		}
		int task3_aux () {
			tree_node *b, *c, *c_parent;
			if(root != nullptr && (root->left == nullptr && root->right != nullptr)){
				b = root->right;
				c_parent = find_left_in_subtree(b);
				if(c_parent == nullptr)
					return 0;
				c = c_parent->left;
				if(c->right == nullptr){ // c->left is nullptr after find_left_in_subtree
					c_parent->left = nullptr;
					c->left = root;
					c->right = b;
					root->right = nullptr;
					root = c;
					return 1;
				}
			}
			return 0;
		}
	public:
		void task3 (tree_node *prev_root = nullptr, int prev_pos = 0) {
			tree child_subtree;
			if(root == nullptr)
				return ;
			if(task3_aux() == 1){
				if(prev_pos == -1)
					prev_root->left = root;
				if(prev_pos == 1)
					prev_root->right = root;
			}
			child_subtree.root = root->left;  child_subtree.task3 (root, -1);
			child_subtree.root = root->right;  child_subtree.task3 (root, 1);
			child_subtree.clear();
		}
// TASK 4
	private:
		tree_node* find_right_in_subtree (tree_node *start) const{
			tree_node *curr;
			if(start == nullptr || start->right == nullptr)
				return nullptr;
			for (curr = start; curr->right->right != nullptr; curr = curr->right) ;
			return curr;
		}
		int task4_aux () {
			tree_node *b, *c, *c_parent;
			if(root != nullptr && (root->left != nullptr && root->right == nullptr)){
				b = root->left;
				c_parent = find_right_in_subtree(b);
				if(c_parent == nullptr)
					return 0;
				c = c_parent->right;
				if(c->left == nullptr){ // c->left is nullptr after find_left_in_subtree
					c_parent->right = nullptr;
					c->right = root;
					c->left = b;
					root->left = nullptr;
					root = c;
					return 1;
				}
			}
			return 0;
		}
	public:
		void task4 (tree_node *prev_root = nullptr, int prev_pos = 0) {
			tree child_subtree;
			if(root == nullptr)
				return ;
			if(task4_aux() == 1){
				if(prev_pos == -1)
					prev_root->left = root;
				if(prev_pos == 1)
					prev_root->right = root;
			}
			child_subtree.root = root->left;  child_subtree.task4 (root, -1);
			child_subtree.root = root->right;  child_subtree.task4 (root, 1);
			child_subtree.clear();
		}
// TASK 5
	private:
/*		int get_subtree_value_task5 (const char *s) const {
			// returns height if all nodes satisfy conditions and -1 if not
			tree m_subtree;
			int len = 0, tmp;
			char *node_name;
			if(root == nullptr)
				return 0;
			node_name = root->get_name();
			if(strstr(node_name, s) == nullptr)
				return -1;
			m_subtree.root = root->left;
			tmp = m_subtree.get_subtree_value_task5 (s);
			if(tmp < 0){
				m_subtree.clear();
				return -1;
			}
			m_subtree.root = root->right;
			len = tmp;
			tmp = m_subtree.get_subtree_value_task5 (s);
			if(tmp < 0){
				m_subtree.clear();
				return -1;
			}
			len = max(len, tmp);
			m_subtree.clear();
			return len + 1;
		}*/
// та же функция но без деревьев внутри, ответы на dataN1e6.txt отличаются
		int get_subtree_value_task5 (tree_node* curr, const char *s) const {
			// returns height if all nodes satisfy conditions and -1 if not
			int len = 0, tmp;
			char *node_name;
			if(curr == nullptr)
				return 0;
			node_name = curr->get_name();
			if(strstr(node_name, s) == nullptr)
				return -1;
			tmp = get_subtree_value_task5 (curr->left, s);
			if(tmp < 0)
				return -1;
			len = tmp;
			tmp = get_subtree_value_task5 (curr->right, s);
			if(tmp < 0)
				return -1;
			len = max(len, tmp);
			return len + 1;
		}
	public:
		void task5 (const student& stud) {
			int k = stud.get_value(), res;
			char *s = stud.get_name();
			tree m_subtree;
			if(root == nullptr)
				return ;
			res = get_subtree_value_task5 (root, s);
			if(res >= k) {
				delete_subtree(root);
				root = nullptr;
				return ;
			}
			m_subtree.root = root->left;
			m_subtree.task5 (stud);
			if(m_subtree.root == nullptr)
				root->left = nullptr;
			m_subtree.root = root->right;
			m_subtree.task5 (stud);
			if(m_subtree.root == nullptr)
				root->right = nullptr;
			m_subtree.clear();
		}
// TASK 6
	private:
/*		int get_subtree_value_task6 (const char *s) const {
			// returns length of longest branch satisfying conditions
			tree m_subtree;
			int len = 0, tmp;
			char *node_name;
			if(root == nullptr)
				return 0;
			node_name = root->get_name();
			if(strstr(node_name, s) == nullptr)
				return -1;
			m_subtree.root = root->left;
			tmp = m_subtree.get_subtree_value_task6 (s);
			m_subtree.root = root->right;
			len = tmp;
			tmp = m_subtree.get_subtree_value_task6 (s);
			len = max(len, tmp);
			m_subtree.clear();
			return len + 1;
		}*/
		int get_subtree_value_task6 (tree_node *curr, const char *s) const {
			// returns length of longest branch satisfying conditions
			int len = 0, tmp;
			char *node_name;
			if(curr == nullptr)
				return 0;
			node_name = curr->get_name();
			if(strstr(node_name, s) == nullptr)
				return -1;
			tmp = get_subtree_value_task6 (curr->left, s);
			len = tmp;
			tmp = get_subtree_value_task6 (curr->right, s);
			len = max(len, tmp);
			return len + 1;
		}
	public:
		void task6 (const student& stud) {
			int k = stud.get_value(), res;
			char *s = stud.get_name();
			tree m_subtree;
			if(root == nullptr)
				return ;
			res = get_subtree_value_task6 (root, s);
			if(res >= k) {
				delete_subtree(root);
				root = nullptr;
				return ;
			}
			m_subtree.root = root->left;
			m_subtree.task6 (stud);
			if(m_subtree.root == nullptr)
				root->left = nullptr;
			m_subtree.root = root->right;
			m_subtree.task6 (stud);
			if(m_subtree.root == nullptr)
				root->right = nullptr;
			m_subtree.clear();
		}
// TASK 7
	private:
		void check_level (int level, int &n, char *s, tree_node* curr, int k, int curr_level = 0) const{
			char *name;
			if(curr == nullptr)
				return ;
			if(n < 0)
				return ;
			if(curr_level == level){
				name = curr->get_name();
				if(strstr(name, s) != nullptr)
					n = n + 1;
				else
					if(n >= k)
						n = n + 1;
					else
						n = 0;
			}
			else{
				check_level(level, n, s, curr->left, k, curr_level + 1);
				if(n < 0)
					return ;
				check_level(level, n, s, curr->right, k, curr_level + 1);
			}
			if(n < 0)
				return ;
		}
		void delete_subtrees_on_level (int level, tree_node *curr, int curr_level = 0) {
			if(curr == nullptr)
				return ;
			if(level == 0){
				delete_subtree(root);
				root = nullptr;
			}
			if(curr_level + 1 != level){
				delete_subtrees_on_level (level, curr->left, curr_level + 1);
				delete_subtrees_on_level (level, curr->right, curr_level + 1);
			}
			else{
				delete_subtree(curr->left);  curr->left = nullptr;
				delete_subtree(curr->right);  curr->right = nullptr;
			}
		}
	public:
		void task7 (const student& stud) {
			int n, level, k = stud.get_value();
			char *s = stud.get_name();
			for(level = 0; level < get_height(); level++){
				n = 0;
				check_level(level, n, s, root, k);
				if(abs(n) >= k){
					delete_subtrees_on_level(level, root);
					break;
				}
			}
		}
} ;

# endif // TREE_H
