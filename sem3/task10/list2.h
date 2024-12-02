# ifndef LIST2_H
# define LIST2_H

#include "student.h"

class list2;
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
		static int m;
		static int r;
	public:
		list2 () = default;
		list2 (list2&& x) {
			head = x.head;
			x.head = nullptr;
		}
		~list2 () {
		       	list2_node *curr, *next;
		        for(curr = head; curr; curr = next){
		                next = curr->get_next();
		                delete curr;
		        }
		}
		static void set_m (int m) { list2::m = m; }
		static void set_r (int r) { list2::r = r; }
		io_status read (FILE *fp = stdin) {
			list2_node buf;
			io_status ret;
			list2_node *curr, *last;
			int len = 0;
			ret = buf.read(fp);
			len++;
			if(ret != io_status::success){
					if(feof(fp)){
							return io_status::eof;
					}
					return ret;
			}
			head = new list2_node;
			if(head == nullptr)
					return io_status::memory;
			*head = (list2_node&&) buf;
			curr = head;
			last = curr;
			while(len < m && buf.read(fp) == io_status::success){
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
			if(!feof(fp) && len < m){
					//delete_list(*head);
					return io_status::format;
			}
// 			для версии с tail:
//			tail = last;
			return io_status::success;
		}
		void print (FILE *fp = stdout, int spaces = 0) const {
		        const list2_node *curr;
		        int p = 0;
		        for(curr = head; curr && p < r; curr = curr->next, p++){
					for(int i = 0; i < spaces; i++)
						fprintf(fp, " ");
					curr->print(fp);
				}
		}
		unsigned int get_length () const {
		        const list2_node *curr;
		        unsigned int p;
		        for(p = 0, curr = head; curr; curr = curr->next, p++) ;
			return p;
		}
		int operator< (const list2& b) const {
			if(head == nullptr)
				return 1;
			return ( head < b.head ? 1 : 0 );
		}
/*		void delete_node (list2_node* curr){
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
		}*/

/*		list2_node* get_tail () {
			list2_node *curr;
			for(curr = head; curr->next != nullptr; curr = curr->next) ;
			return curr;
		}*/
};

# endif //LIST2_H