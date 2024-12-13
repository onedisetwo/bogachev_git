# ifndef B_TREE_H
# define B_TREE_H

# include <cmath>

# include "io_status.h"
# include "student.h"
# include "list2.h"

template <class T> class b_tree;

template <class T>
class b_tree_node {
    private:
        T *values = nullptr; ///< 2*m elements array
        int size = 0; ///< number of children
        b_tree_node **children = nullptr; ///< 2*m+1 elements array
    public:
        b_tree_node () = default;
		b_tree_node (const b_tree_node&) = delete;
		b_tree_node (b_tree_node&& x) : T ((T&&)x) {
			erase_links();
			values = x.values;
			x.erase_links();
		}
		~b_tree_node () {
			delete[] values;
			erase_links();
		}
        void print (int p = 0, FILE *fp = stdout) const {
            for(int i = 0; i < size; ++i){
                for(int j = 0; j < p; j++)
                       fprintf(fp, "  ");
                fprintf(fp, "values[%2d] ", i + 1);
                values[i].print(fp);
            }
        }
		friend class b_tree<T>;
	private:
		void erase_links () {
			delete[] children;
		}
		io_status init (int m) {
			values = new T[2*m];
			if(values == nullptr)
				return io_status::memory;
			children = new b_tree_node<T>*[2*m + 1];
			if(children == nullptr)
				return io_status::memory;
			return io_status::success;
		}
		// Insert value ’x’ with children ’down’ at position ’index’
		// into the node (assuming enough space)
		void add_value (T& x, b_tree_node<T>* down, int index) {
			for(int i = size; i > index; i--){
				values[i] = static_cast<T&&>(values[i - 1]);
				children[i + 1] = children[i];
			}
			values[index] = static_cast<T&&>(x);
			children[index + 1] = down;
			size++;
		}
/*		int bin_search (T& x) const { //<left
		    int left = 0, right = size - 1, mid;
		    while(left != right){
		        mid = (left + right) / 2;
		        if(values[mid] < x)
		            left = mid + 1;
		        else
		            right = mid;
		    }
			if(values[left] < x)
				return size;
			else
			return left;
		}*/
		int bin_search (T& x) const { //<right
		    int left = 0, right = size - 1, mid;
		    while(left != right){
		        mid = (left + right) / 2;
		        if(values[mid] <= x)
		            left = mid + 1;
		        else
		            right = mid;
		    }
			if(values[left] <= x)
				return size;
			else
				return left;
		}
	private:
		int count_children () {
			return (children[0] == nullptr ? 0 : size + 1);
		}
		int get_size () const {
			int res = 0;
			for(int i = 0; i < size; i++){
				res += values[i].get_length();
			}
			return res;
		}
} ;

template <class T>
class b_tree {
	private:
		int m;
		b_tree_node<T> *root = nullptr;
	public:
		b_tree (int i = 0) { m = i; }
		~b_tree () {
			delete_subtree (root);
			erase_links();
		}
        io_status read (FILE *fp = stdin, unsigned int max_read = -1) {
            student x;
            unsigned int count = 0;
			io_status ret;
            while(x.read(fp) == io_status::success && count < max_read) {
//				x.print();
				ret = add_value (x);
				if(ret != io_status::success)
					return ret;
//				print(4);
//				printf("\n");
			}
            if(count == max_read)
                return io_status::success;
            if(!feof(fp))
                return io_status::eof;
            return io_status::success;
        }
		void print (int r, FILE *fp = stdout) const {
			print_subtree (root, 0, r, fp);
		}
	private:
		void erase_links () {
			m = 0;
			root = nullptr;
		}
		static void delete_subtree (b_tree_node<T> *curr) {
			if(curr == nullptr)
				return ;
			for(int i = 0; i <= curr->size; i++)
				delete_subtree(curr->children[i]);
			delete curr;
		}
		static void print_subtree (b_tree_node<T> *curr, int level,
				int r, FILE *fp = stdout) {
			if(curr == nullptr || level > r)
				return ;
			curr->print (level, fp);
			for(int i = 0; i <= curr->size; i++){
				if(curr->children[i] && level + 1 <= r) {
					for(int j = 0; j < level; j++)
						fprintf(fp, "  ");
					fprintf(fp, "children[%2d]\n", i);
					print_subtree(curr->children[i], level + 1, r, fp);
				}
			}
		}
		io_status add_value (T& x) {
			if(root == nullptr){
				root = new b_tree_node<T>();
				if(root == nullptr)
					return io_status::memory;
				if(root->init(m) != io_status::success){
					delete root;
					return io_status::memory;
				}
				root->values[0] = static_cast<T&&>(x);
				root->size = 1;
				return io_status::success;
			}
			b_tree_node<T> *curr = root, *down = nullptr;
			io_status r = add_value_subtree(curr, down, x, m);
			if(r != io_status::create)
				return r;
			// был создан новый корень
			b_tree_node<T> *p = new b_tree_node<T>();
			if(p == nullptr)
				return io_status::memory;
			if(p->init(m) != io_status::success){
				delete p;
				return io_status::memory;
			}
			p->values[0] = static_cast<T&&>(x);
			p->children[0] = curr;
			p->children[1] = down;
			p->size = 1;
			root = p;
			return io_status::success;
		}
		static io_status add_value_subtree (b_tree_node<T>*& curr,
				b_tree_node<T>*& down, T& x, int m) {
			int index = curr->bin_search(x);
			b_tree_node<T> *p = curr->children[index];

			if(p != nullptr) { ///< Есть потомок
				io_status r = add_value_subtree(p, down, x, m);
				if(r != io_status::create)
					return r;
				/// был создан новый узел, который возвращается в down
			}
			else
				down = nullptr;

			if(curr->size < 2*m) {
				curr->add_value(x, down, index);
				return io_status::success;
			}
			else {
				p = new b_tree_node<T>();
				if(p == nullptr)
					return io_status::memory;
				if(p->init(m) != io_status::success) {
					delete p;
					return io_status::memory;
				}
				if(index == m) { ///< x ровно посередине
					for(int i = 1; i <= m; i++){
						p->values[i - 1] = static_cast<T&&>(curr->values[i + m - 1]);
						p->children[i] = curr->children[i + m];
						curr->children[i + m] = nullptr;
					}
					p->children[0] = down; ///< меньше всех
				}
				if(index < m) { ///< x в левой половине
					for(int i = 0; i < m; i++) {
						p->values[i] = static_cast<T&&>(curr->values[i + m]);
						p->children[i] = curr->children[i + m];
						curr->children[i + m] = nullptr;
					}
					p->children[m] = curr->children[2*m];
					curr->children[2*m] = nullptr;
					for(int i = m; i > index; i--){
						curr->values[i] = static_cast<T&&>(curr->values[i - 1]);
						curr->children[i + 1] = curr->children[i];
					}
					curr->children[index + 1] = down;
					curr->values[index] = static_cast<T&&>(x);
					x = static_cast<T&&>(curr->values[m]);
					/// новый x - максимальный
				}
				if(index > m) { ///< x в правой половине
					p->children[0] = curr->children[m + 1];
					curr->children[m + 1] = nullptr;
					for(int i = 1; i < index - m; i++) {
						p->values[i - 1] = static_cast<T&&> (curr->values[i + m]);
						p->children[i] = curr->children[i + m + 1];
						curr->children[i + m + 1] = nullptr;
					}
					p->values[index - m - 1] = static_cast<T&&>(x);
					p->children[index - m] = down;
					for(int i = index - m + 1; i <= m; i++) {
						p->values[i - 1] = static_cast<T&&> (curr->values[i + m - 1]);
						p->children[i] = curr->children[i + m];
						curr->children[i + m] = nullptr;
					}
					x = static_cast<T&&>(curr->values[m]);
					/// новый x - максимальный
				}
				down = p;
				p->size = m;
				curr->size = m;
				return io_status::create;
			}
			return io_status::success;
		}
	public:
		int tasks1_6 (int task_num, int k) const {
			switch(task_num) {
				case 1:  return task1(k);
				case 2:  return task2(k);
				case 3:  return task3(k);
				case 4:  return task4(k);
				case 5:  return task5(k);
				case 6:  return task6(k);
			}
			return -111;
		}
	private:
		int count_k_size (b_tree_node<T> *curr, int k) const ;
		int task1 (int k) const {
			return count_k_size(root, k);
		}
		int count_vertices_in_subtree (b_tree_node<T> *curr, int k, int *total) const ;
		int task2 (int k) const {
			int res = 0;
			count_vertices_in_subtree (root, k, &res);
			return res;
		}
		int count_levels_in_subtree (b_tree_node<T> *curr, int k, int *total) const ;
		int task3 (int k) const {
			int res = 0;
			count_levels_in_subtree (root, k, &res);
			return res;
		}
//		int get_count_total (b_tree_node<T> *curr) const ;
		int count_vertices_on_level (b_tree_node<T> *curr, int level, int curr_level, int *level_size) const ;
		int get_count_tiny_subtrees (b_tree_node<T> *curr, int k) const ;
		int task4 (int k) const {
			return get_count_tiny_subtrees(root, k);
		}
		int count_sizes_on_level (b_tree_node<T> *curr, int level, int curr_level) const ;
		int task5 (int k) const {
			return count_sizes_on_level(root, k, 0);
		}
		int count_sizes_on_k_branches (b_tree_node<T> *curr, int k, int curr_level) const ;
		int task6 (int k) const {
			return count_sizes_on_k_branches(root, k, 1);
		}
} ;


# endif //B_TREE_H

