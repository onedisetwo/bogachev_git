#include "student.h"

class list1_node : public student {
	private:
		list1_node *next = nullptr;
	public:
               	list1_node () = default;
                list1_node (const list1_node &x) = delete;
                list1_node (list1_node&& r) {
                        *(student*)this = (student&&)r;
                        next = r.next;
                        r.next = nullptr;
                }
                ~list1_node () {
                        next = nullptr;
                }
                list1_node& operator= (const list1_node& r) = delete;
                list1_node& operator= (list1_node&& r) {
                        *(student*)this = (student&&)r;
                        next = r.next;
                        r.next = nullptr;
                        return *this;
                }
                list1_node *get_next () const {
                        return next;
                }
                void set_next (list1_node *r){
                        next = r;
                }
		friend class list1;
		friend list1_node* merge_lists (list1_node*, list1_node*) ;
};

class list1 {
	private:
		list1_node *head = nullptr;
		list1_node *tail = nullptr;
	public:
		list1& operator= (list1&& r) {
			head = r.head;
			r.head = nullptr;
			tail = r.tail;
			r.tail = nullptr;
			return *this;
		}
		list1& operator+= (const list1& x){
			if(this == &x)
				return *this;
			if(x.head == nullptr)
				return *this;
			if(head == nullptr)
				head = x.head;
			else
				tail->next = x.head;
			tail = x.tail;
			return *this;
		}
		list1& operator-= (const list1& x){
			if(this == &x)
				return *this;
			if(x.head == nullptr)
				return *this;
			if(head == nullptr)
				tail = x.head;
			else
				x.tail->next = head;
			head = x.head;
			return *this;
		}
		~list1 () {
		       	list1_node *curr, *next;
		        for(curr = head; curr; curr = next){
		                next = curr->get_next();
		                delete curr;
		        }

		}
		io_status read (FILE *fp = stdin, unsigned int max_read = -1) {
			list1_node buf;
		        io_status ret;
		        list1_node *curr, *last;
			unsigned int len = 0;
		        ret = buf.read(fp);
			len++;
		        if(ret != io_status::success){
		                if(feof(fp)){
		                        return io_status::success;
		                }
		                return ret;
		        }
		        head = new list1_node;
		        if(head == nullptr)
		                return io_status::memory;
		        *head = (list1_node&&) buf;
		        curr = head;
		        last = curr;
		        while(buf.read(fp) == io_status::success && len < max_read){
				len++;
		                last = new list1_node;
		                if(last == nullptr){
		                        return io_status::memory;
		                }
		                *last = (list1_node&&) buf;
		                curr->set_next(last);
		                curr = last;
		        }
		        if(!feof(fp)){
		                return io_status::format;
		        }
			tail = last;
		        return io_status::success;
		}
		void print (unsigned int r = 10, FILE *fp = stdout) {
		        const list1_node *curr;
		        unsigned int p = 0;
		        for(curr = head; curr && p < r; curr = curr->next, p++)
		                curr->print(fp);
		}
		int get_less_than_previous () {
			list1_node *curr;
			int count = 0;
			if(head == nullptr || head->next == nullptr)
				return count;
			for(curr = head; curr->next != nullptr; curr = curr->next)
				if(*curr > *curr->next)
					count++;
			return count;
		}

	private:
		void insert_head (list1_node* new_head) {
			if(head == nullptr)
				tail = new_head;
			new_head->next = head;
			head = new_head;
		}
		void insert_tail (list1_node* new_tail) {
			new_tail->next = nullptr;
			if(tail != nullptr)
				tail->next = new_tail;
			else
				head = new_tail;
			tail = new_tail;
		}
		// insert list after insPos
		void insert_next (list1_node* insPos, list1* ll){
			list1_node *tmp;
			if(insPos == nullptr)
				return ;
			if(insPos == tail)
				tail = ll->tail;
			tmp = insPos->next;
			insPos->next = ll->head;
			ll->tail->next = tmp;
		}
		void update_tail () {
			if(tail != nullptr)
				for(; tail->next != nullptr; tail = tail->next);
		}
		void init (list1_node* first) {
			head = first;
			tail = first;
		}
		void clear () {
			head = nullptr;
			tail = nullptr;
		}
	private:
		void swap_next_2_nodes (list1_node *curr) ; // bubble_sort
		list1_node* find_prev_of_min () ; // min_sort
		void linear_insertion (list1_node*) ; // lin_ins_sort
		void init_merge_lists (list1*, list1*) ; //neumann_sort
		list1_node* get_middle(); // quick_sort
	public:	// TASKS
		void bubble_sort () ;
		void min_sort () ;
		void lin_ins_sort () ;
		void neumann_sort () ;
		void quick_sort () ;
};

