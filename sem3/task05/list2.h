#include "student.h"

class list2_node : public student {
	private:
		list2_node *next = nullptr;
		list2_node *prev = nullptr;
	public:
               	list2_node () = default;
                list2_node (const list2_node &x) = delete;
                list2_node (list2_node&& r) {
                        *(student*)this = (student&&)r;
                        next = r.next;
                        r.next = nullptr;
			prev = r.prev;
			r.prev = nullptr;
                }
                ~list2_node () {
                        next = nullptr;
			prev = nullptr;
                }
                list2_node& operator= (const list2_node& r) = delete;
                list2_node& operator= (list2_node&& r) {
                        *(student*)this = (student&&)r;
                        next = r.next;
                        r.next = nullptr;
			prev = r.prev;
			r.prev = nullptr;
                        return *this;
                }
                list2_node *get_next () const {
                        return next;
                }
                void set_next (list2_node *r){
                        next = r;
                }
		list2_node *get_prev () const {
                        return prev;
                }
                void set_prev (list2_node *r){
                        prev = r;
                }
		friend class list2;
};

class list2 {
	private:
		list2_node *head = nullptr;
		list2_node *tail = nullptr;
	public:
		~list2 () {
		       	list2_node *curr, *next;
		        for(curr = head; curr; curr = next){
		                next = curr->get_next();
		                delete curr;
		        }

		}
		io_status read (FILE *fp = stdin, unsigned int max_read = -1) {
			list2_node buf;
		        io_status ret;
		        list2_node *curr, *last;
			unsigned int len = 0;
		        ret = buf.read(fp);
			len++;
		        if(ret != io_status::success){
		                if(feof(fp)){
		                        return io_status::success;
		                }
		                return ret;
		        }
		        head = new list2_node;
		        if(head == nullptr)
		                return io_status::memory;
		        *head = (list2_node&&) buf;
		        curr = head;
		        last = curr;
		        while(buf.read(fp) == io_status::success && len < max_read){
				len++;
		                last = new list2_node;
		                if(last == nullptr){
		                        //delete_list(*head);
		                        return io_status::memory;
		                }
		                *last = (list2_node&&) buf;
		                curr->set_next(last);
				last->set_prev(curr);
		                curr = last;
		        }
		        if(!feof(fp)){
		                //delete_list(*head);
		                return io_status::format;
		        }
			tail = last;
		        return io_status::success;
		}
		void print (unsigned int r = 10, FILE *fp = stdout) {
		        const list2_node *curr;
		        unsigned int p = 0;
		        for(curr = head; curr && p < r; curr = curr->next, p++)
		                curr->print(fp);
		}
		unsigned int get_length () {
		        const list2_node *curr;
		        unsigned int p;
		        for(p = 0, curr = head; curr; curr = curr->next, p++) ;
			return p;
		}

		void delete_node (list2_node* curr){
			list2_node *tmp;
			if(curr == head){
				tmp = head->next;
				delete head;
				head = tmp;
				if(head != nullptr)
					head->prev = nullptr;
				return ;
			}
			if(curr == tail){
				tmp = tail->prev;
				delete tail;
				tail = tmp;
				tail->next = nullptr;
				return ;
			}
			(curr->prev)->next = curr->next;
			(curr->next)->prev = curr->prev;
			delete curr;
		}

		void delete_chunk (list2_node* first, list2_node *last){
			list2_node *curr, *next;
			if(first == last){
				delete_node(first);
				return ;
			}
			for(curr = first->next; curr != last; curr = next){
				next = curr->next;
				delete curr;
			}
			first->next = last;
			last->prev = first;
			delete_node(first);
			delete_node(last);
		}

/*		list2_node* get_tail () {
			list2_node *curr;
			for(curr = head; curr->next != nullptr; curr = curr->next) ;
			return curr;
		}*/

		list2_node* get_k_right_cycle (list2_node* curr, int k){
			for(int i = 0; i < k; i++)
				curr = (curr != tail) ? curr->next : head;
			return curr;
		}

		list2_node* get_k_right_no_cycle (list2_node* curr, int k){
			for(int i = 0; i < k && curr != nullptr; i++)
				curr = curr->get_next();
			return curr;
		}

		void right_shift (int k) ; // task 01
		void solve2 (int k) ;
		void solve3 (int k) ;
		void solve4 (int k) ;
		void solve5 (int k) ;
		void solve6 (int k) ;
		void solve7 (int k) ;
		void solve8 (int k) ;
};

