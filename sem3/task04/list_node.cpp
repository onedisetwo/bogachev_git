#include "student.h"
#include "list_node.h"

void delete_list (list_node *head){
	list_node *curr, *next;
	for(curr = head; curr; curr = next){
		next = curr->get_next();
		delete curr;
	}
}

void print_list (int r, const list_node *head){
	const list_node *curr;
	int p = 0;
	for(curr = head; curr && p < r; curr = curr->get_next(), p++)
		curr->print();
}

[[nodiscard]] io_status read_list (FILE *fp, list_node **head){
	list_node buf;
	io_status ret;
	list_node *curr, *tail;
	ret = buf.read(fp);
	if(ret != io_status::success){
		if(feof(fp)){
			*head = nullptr;
			return io_status::success;
		}
		return ret;
	}
	*head = new list_node;
	if(*head == nullptr)
		return io_status::memory;
	**head = (list_node&&) buf;
	curr = *head;
	tail = curr;
	while(buf.read(fp) == io_status::success){
		tail = new list_node;
		if(tail == nullptr){
			delete_list(*head);
			return io_status::memory;
		}
		*tail = (list_node&&) buf;
		curr->set_next(tail);
		curr = tail;
	}
	if(!feof(fp)){
		delete_list(*head);
		return io_status::format;
	}
	return io_status::success;
}
