#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "student.h"

class list_node : public student {
	private:
		list_node *next = nullptr;
	public:
		list_node () = default;
		list_node (const list_node &x) = delete;
		list_node (list_node&& r) {
			*(student*)this = (student&&)r;
			next = r.next;
			r.next = nullptr;
		}
		~list_node () {
			next = nullptr;
		}
		list_node& operator= (const list_node& r) = delete;
		list_node& operator= (list_node&& r) {
			*(student*)this = (student&&)r;
			next = r.next;
			r.next = nullptr;
			return *this;
		}
		list_node *get_next () const {
			return next;
		}
		void set_next (list_node *r){
			next = r;
		}
};

void delete_list (list_node *head);
void print_list (int r, const list_node *head);
io_status read_list (FILE *fp, list_node **head);

#endif //LIST_NODE_H
