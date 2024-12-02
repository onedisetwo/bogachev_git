#include "list_node.h"

double max(double a, double b){
	return (a > b) ? a : b;
}

double abs(double a){
	return (a < 0) ? -a : a;
}

int solve1 (list_node *head) {
	list_node *max_node, *curr;
	int max_num = 0;
	max_node = head;
	for(curr = head; curr; curr = curr->get_next()){
		if(*curr == *max_node)
			max_num++;
		else if(*curr > *max_node){
			max_node = curr;
			max_num = 1;
		}
	}
	return max_num;
}

int solve2 (list_node *head) {
	int ans = 0;
	list_node *curr, *c_next;
	for(curr = head; curr; curr = c_next){
		c_next = curr->get_next();
		if(!c_next)
			break;
		if(*c_next > *curr)
			ans++;
	}
	return ans;
}

int solve3 (list_node *head) {
	int ans = 0;
	list_node *curr = head, *c_next1, *c_next2;
	if(!curr)
		return 0;
	c_next1 = curr->get_next();
	if(!c_next1)
		return 0;
	c_next2 = c_next1->get_next();
	if(!c_next2)
		return 0;
	for(curr = head; ; curr = c_next1, c_next1 = c_next2, c_next2 = c_next2->get_next()){
		if(!c_next2)
			break;
		if(*c_next1 > *curr && *c_next1 > *c_next2)
			ans++;
	}
	return ans;
}

int solve4 (list_node *head) {
	int ans;
	list_node *curr = head, *c_next;
	if(!curr)
		return 4;
	c_next = head->get_next();
	if(!c_next)
		return 4;
	if(*c_next > *curr)
		ans = 1;
	else if(*c_next < *curr)
		ans = 2;
	else
		ans = 3;
	for(; ; curr = c_next){
		c_next = curr->get_next();
		if(!c_next)
			break;
		if(*c_next > *curr){
			if(ans != 1)
				return 0;
		}
		else if(*c_next < *curr){
			if(ans != 2)
				return 0;
		}
		else
			if(ans != 3)
				return 0;
	}
	return ans;
}

int solve5 (list_node *head) {
	int max_len = -1, curr_len = 0;
	list_node *curr, *c_next;
	for(curr = head; curr; curr = c_next){
		c_next = curr->get_next();
		if(!c_next)
			break;
		if(*curr < *c_next){
			if(curr_len == 0)
				curr_len++;
			curr_len++;
		}
		else{
			max_len = max(max_len, curr_len);
			curr_len = 0;
		}
	}
	max_len = max(max_len, curr_len);
	return max_len;
}

int solve6 (list_node *head) {
	int flag = 0, num = 0;
	list_node *curr, *c_next;
	for(curr = head; curr; curr = c_next){
		c_next = curr->get_next();
		if(!c_next)
			break;
		if(*curr == *c_next){
			if(flag == 0){
				num++;
				flag = 1;
			}
		}
		else{
			flag = 0;
		}
	}
	return num;
}

int solve7 (list_node *head) {
	int flag = 0, max_dist = 0, curr_dist = 0, if_const = 0;
	list_node *curr, *c_next;
	for(curr = head; curr; curr = c_next){
		c_next = curr->get_next();
		if(!c_next)
			break;
		if(*curr == *c_next){
			if(flag == 0){
				max_dist = max(max_dist, curr_dist - 1);
				curr_dist = 0;
				flag = 1;
			}
			if_const = 1;
		}
		else{
			if(if_const != 0){
				curr_dist++;
				flag = 0;
			}
		}
	}
	return max_dist;
}

int solve8 (list_node *head) {
	int max_len = -1, curr_len = 0, const_len = 0;
	list_node *curr, *c_next;
	for(curr = head; curr; curr = c_next){
		c_next = curr->get_next();
		if(!c_next)
			break;
		if(*curr == *c_next){
			const_len++;
		}
		if(*curr < *c_next){
			if(curr_len <= 0)
				curr_len = const_len + 1;
			else
				curr_len += const_len;
			curr_len++;
			const_len = 0;
		}
		if(*curr > *c_next){
			if(curr_len >= 0)
				curr_len = -const_len - 1;
			else
				curr_len -= const_len;
			curr_len--;
			const_len = 0;
		}
		if(curr_len == 0)
			max_len = max(max_len, const_len + 1);
		else
			max_len = max(max_len, abs(curr_len) + const_len);
	}
	max_len = max(max_len, abs(curr_len) + const_len);
	return max_len;
}
