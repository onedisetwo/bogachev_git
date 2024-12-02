#include "list1.h"

// TASKS

// TASK 01
void list1::swap_next_2_nodes (list1_node *curr){
        list1_node *next1 = curr->next;
        list1_node *next2 = (next1 == nullptr ? nullptr : next1->next);
        if(next1 == nullptr || next2 == nullptr)
                return ;
        next1->next = next2->next;
        next2->next = next1;
        curr->next = next2;
}

void list1::bubble_sort () {
	list1_node *curr;
	list1 sorted_list;
	if(head == nullptr || head->next == nullptr)
		return ;
	curr = head;
	while(head->next->next != nullptr){
		if(*head > *head->next){
			curr = head->next;
			head->next = curr->next;
			curr->next = head;
			head = curr;
		}
		for(curr = head; curr->next != nullptr && (curr->next->next) != nullptr;
				curr = curr->next){
			if(*curr->next > *curr->next->next)
				swap_next_2_nodes(curr);
		}
		sorted_list.insert_head(curr->next);
		curr->next = nullptr;
	}
	if(*head > *head->next){
		curr = head->next;
		sorted_list.insert_head(head);
		sorted_list.insert_head(curr);
	}
	else {
		sorted_list.insert_head(head->next);
		sorted_list.insert_head(head);
	}
	*this = (list1&&)sorted_list;
}


// TASK 02
list1_node* list1::find_prev_of_min () {
	list1_node *curr, *prev_min = nullptr;
	for(curr = head; curr->next != nullptr; curr = curr->next){
		if(*curr->next < (prev_min != nullptr ? *prev_min->next : *head)){
			prev_min = curr;
		}
	}
	return prev_min;
}

void list1::min_sort () {
	list1_node *min, *prev_of_min;
	list1 sorted_list;
	if(head == nullptr || head->next == nullptr)
		return ;
	while(head != nullptr){
		prev_of_min = find_prev_of_min();
		if(prev_of_min != nullptr){
			min = prev_of_min->next;
			prev_of_min->next = min->next;
		}
		else{
			min = head;
			head = head->next;
		}
		sorted_list.insert_tail(min);
	}
	*this = (list1&&)sorted_list;
}


// TASK 03
void list1::linear_insertion (list1_node *given) {
	list1_node *curr;
	if(head == nullptr){
		insert_head(given);
		return ;
	}
	if(head->next == nullptr){
		if(*head > *given)
			insert_head(given);
		else
			insert_tail(given);
		return ;
	}
	if(*head >= *given){
		insert_head(given);
		return ;
	}
	for(curr = head; curr->next != nullptr; curr = curr->next) {
		if(*curr->next >= *given){
			given->next = curr->next;
			curr->next = given;
			return ;
		}
	}
	insert_tail(given);
}

void list1::lin_ins_sort () {
	list1 sorted_list;
	list1_node *tmp;
	while(head != nullptr){
		tmp = head->next;
		sorted_list.linear_insertion(head);
		head = tmp;
	}
	*this = (list1&&)sorted_list;
}


// TASK 04

void list1::init_merge_lists (list1* lm1, list1* lm2) {
	list1_node* tmp;
	while(lm1->head != nullptr && lm2->head != nullptr){
		if(*lm1->head < *lm2->head){
			tmp = lm1->head->next;
			insert_tail(lm1->head);
			lm1->head = tmp;
		}
		else{
			tmp = lm2->head->next;
			insert_tail(lm2->head);
			lm2->head = tmp;
		}
	}
	// в списке который заканчивается первым head = null,
	// а tail всё ещё указывает на последний элемент
	if(lm1->head == nullptr)
		*this += *lm2;
	if(lm2->head == nullptr)
		*this += *lm1;
}

void list1::neumann_sort () {
	list1 sorted_list, merged_pair, lm1, lm2;
	list1_node *new_pair;
	int gr_size = 1, flag = 1, i;
	for(gr_size = 1; ; gr_size *= 2){
		new_pair = head;
		for(lm1.init(head), flag = 0; new_pair != nullptr; lm1.init(new_pair)){
			for(i = 1; i < gr_size && lm1.tail->next != nullptr;
				i++, lm1.tail = lm1.tail->next) ;
			if(lm1.tail->next == nullptr){
				if(flag != 0)
					sorted_list += lm1;
				break;
			}
			lm2.init(lm1.tail->next);
			lm1.tail->next = nullptr;
			for(i = 1; i < gr_size && lm2.tail->next != nullptr;
				i++, lm2.tail = lm2.tail->next) ;
			new_pair = lm2.tail->next;
			lm2.tail->next = nullptr;
			merged_pair.init_merge_lists (&lm1, &lm2);
			sorted_list += merged_pair;
			merged_pair.clear();
			flag = 1;
		}
		if(flag == 0)
			break;
		*this = (list1&&)sorted_list;
	}
	lm1.clear();
	lm2.clear();
	sorted_list.clear();
}


// TASK 05

list1_node* list1::get_middle () {
	list1_node *quick = head, *slow = head;
	while(quick != nullptr && quick->next != nullptr){
		quick = quick->next->next;
		slow = slow->next;
	}
	return slow;
}

void list1::quick_sort () {
	list1 listL, listU, listM, sorted_list;
	list1_node *tmp, *mid, *insPos = nullptr;
	int lenL, lenU;
	if(head == nullptr || head->next == nullptr)
		return ;
	while(head != nullptr){
		lenL = 0;
		lenU = 0;
		mid = get_middle();
		for(; head != nullptr; ){
			if(head->next != nullptr){
				tmp = head->next;
				head->next = tmp->next;
			}
			else{
				tmp = head;
				head = nullptr;
			}

			if(*tmp < *mid){
				listL.insert_tail(tmp);
				lenL++;
			}
			else if(*tmp > *mid){
				listU.insert_tail(tmp);
				lenU++;
			}
			else
				listM.insert_tail(tmp);
		}

		if(lenL < lenU){
			listL.quick_sort();
			listL.update_tail();
			listM -= listL;
			listL.clear();
			if(insPos == nullptr)
				sorted_list -= listM;
			else
				sorted_list.insert_next(insPos, &listM);
			insPos = listM.tail;
			*this = (list1&&)listU;
		}
		else{
			listU.quick_sort();
			listU.update_tail();
			listM += listU;
			listU.clear();
			if(insPos == nullptr)
				sorted_list -= listM;
			else
				sorted_list.insert_next(insPos, &listM);
			*this = (list1&&)listL;
		}
		listM.clear();
	}
	*this = (list1&&)sorted_list;
}
