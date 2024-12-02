#include "list2.h"

int m_gcd (int a, int b){
	while(a != 0 && b != 0){
		if(a > b)
			a = a % b;
		else
			b = b % a;
	}
	return (a != 0) ? a : b;
}

int abs (int a){
	return (a < 0 ? -a : a);
}

void swap_students (list2_node *a, list2_node *b) {
        student buf;
        buf = (student&&)*a;
        *(student*)a = (student&&)*b;
        *(student*)b = (student&&)buf;
}

// TASKS

void list2::right_shift (int k) { // task 01
	unsigned int len = get_length(), g;
        if(len == 0)
		return ;
	if(k < 0)
		k += (abs(k) / len + 1) * len;
	g = m_gcd(len, k);
        list2_node *head_cycle = head;
        list2_node *curr;
        for(unsigned int i = 0; i < g; i++){
		curr = head_cycle;
		curr = get_k_right_cycle(curr, k);
                while(curr != head_cycle){
			swap_students (head_cycle, curr);
			curr = get_k_right_cycle(curr, k);
                }
                head_cycle = head_cycle->next;
        }
}

void list2::solve2 (int k) {
	list2_node *curr, *tmp, *prev;
	int i;
	if(k <= 0 && head != nullptr){
		delete_chunk(head, tail);
		return ;
	}
	for(curr = tail; curr != nullptr; curr = prev){
		prev = curr->prev;
		for(i = 0, tmp = curr->prev; i < k && tmp != nullptr; 
				i++, tmp = tmp->prev)
			if(*tmp < *curr){
				delete_node(curr);
				break;
			}
	}
}

void list2::solve3 (int k) {
	list2_node *curr, *tmp, *next;
	int i;
	if(k <= 0 && head != nullptr){
		delete_chunk(head, tail);
		return ;
	}
	for(curr = head; curr != nullptr; curr = next){
		next = curr->next;
		for(i = 0, tmp = curr->next; i < k && tmp != nullptr; 
				i++, tmp = tmp->next)
			if(*tmp < *curr){
				delete_node(curr);
				break;
			}
	}
}

void list2::solve4 (int k) {
	list2_node *curr, *tmp, *next, *first, *last;
	int i;
	k = abs(k);
	if(k == 0){
		delete_chunk(head, tail);
		return ;
	}
	for(curr = get_k_right_no_cycle(head, k); curr != nullptr; curr = next){
		if(curr == nullptr)
			break;
		next = curr->next;
		for(i = 1, tmp = curr->prev; i <= k && tmp != nullptr; i++, tmp = tmp->prev)
			if(*tmp > *tmp->next)
				break;
		if(i <= k)
			continue;
		for(i = 1, tmp = curr->next; i <= k && tmp != nullptr; i++, tmp = tmp->next)
			if(*tmp > *tmp->prev)
				break;
		if(i <= k)
			continue;
		first = curr;
		last = curr;
		tmp = tmp->prev;
		for(; *curr == *curr->next && tmp->next != nullptr; 
				tmp = tmp->next, curr = curr->next)
			if(*tmp->next <= *tmp)
				last = curr->next;
		next = get_k_right_no_cycle(curr->next, k);
		delete_chunk(first, last);
	}
}

void list2::solve5 (int k) {
	list2_node *curr, *first, *next;
	int i;
	for(curr = head, next = head; ; curr = next) {
		if(curr == nullptr || curr->next == nullptr)
			break;
		if(*curr != *curr->next){
			next = curr->next;
			continue;
		}
		first = curr;
		curr = curr->next;
		for(i = 2; curr->next != nullptr && *curr == *curr->next; i++, curr = curr->next) ;
		next = curr->next;
		if(i > k)
			delete_chunk(first, curr);
	}
}

void list2::solve6 (int k) {
	list2_node *curr, *first, *next;
	int i;
	for(curr = head, next = head; ; curr = next) {
		if(curr == nullptr || curr->next == nullptr)
			break;
		if(*curr < *curr->next){
			next = curr->next;
			continue;
		}
		first = curr;
		curr = curr->next;
		for(i = 2; curr->next != nullptr && *curr >= *curr->next; i++, curr = curr->next) ;
		next = curr->next;
		if(i > k)
			delete_chunk(first, curr);
	}
}

void list2::solve7 (int k) {
	list2_node *curr, *start_eq, *first = nullptr, *next;
	int i;
	for(curr = head, next = head; ; curr = next) {
		if(curr == nullptr || curr->next == nullptr)
			break;
		if(*curr != *curr->next){
			next = curr->next;
			continue;
		}
		start_eq = curr;
		curr = curr->next;
		for(i = 2; curr->next != nullptr && *curr == *curr->next; i++, curr = curr->next) ;
		next = curr->next;
		if(i > k){
			if(first != nullptr && start_eq != first)
				delete_chunk(first, start_eq->prev);
			first = next;
		}
	}
}

void list2::solve8 (int k) {
	list2_node *curr, *start_mon, *first = nullptr, *next;
	int i, len_mon = 0, is_first = 1;
	for(curr = head, next = head; ; curr = next) {
		if(curr == nullptr || curr->next == nullptr)
			break;
		if(*curr > *curr->next){
			next = curr->next;
			len_mon++;
			continue;
		}
		start_mon = curr;
		curr = curr->next;
		for(i = 2; curr->next != nullptr && *curr <= *curr->next; i++, curr = curr->next) ;
		next = curr->next;
		if(first != nullptr && start_mon != first && len_mon > k && is_first == 0)
			delete_chunk(first, start_mon->prev);
		is_first = 0;
		len_mon = 0;
		first = next;
	}
}
