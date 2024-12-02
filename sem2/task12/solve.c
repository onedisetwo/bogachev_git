#include "solve.h"
#include "errors.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-16
#define EQUAL_D(a, b, eps) (fabs(a - b) <= eps * fabs(a + b))

// в итоге .next у последнего node с данными ведёт на пустышку с полями 0
// если node есть, то выделена память на обе ячейки, если нет, то ни на одну
int read_file(node *head, const char *filename){
	const int BUF_LEN = 1233;
	char buf[BUF_LEN];
	int len;
	FILE *fp;
	node *curr_node = head;
	if(curr_node == 0)
		curr_node = (node*)malloc(sizeof(node));
	if(!(fp = fopen(filename, "r")))
		return ERROR_OPEN;
	while(fgets(buf, BUF_LEN, fp)){
		len = strlen(buf);
		if(buf[len - 1] == '\n'){
			buf[len - 1] = 0;
			len--;
		}
		curr_node->string = (char*)malloc((len + 1) * sizeof(char));
		curr_node->next = (node*)malloc(sizeof(node));
		if(!curr_node->string || !curr_node->next){
			if(curr_node->string) 	free(curr_node->string);
			if(curr_node->next)	free(curr_node->next);
			free_list(head);
			fclose(fp);
			return ERROR_MEM;
		}
		(curr_node->next)->string = 0;
		(curr_node->next)->next = 0;
		strcpy(curr_node->string, buf);
		curr_node = curr_node->next;
	}
	if(!feof(fp)){
		free_list(head);
		fclose(fp);
		return ERROR_READ;
	}
	fclose(fp);
	return SUCCESS;
}

void print_list(node *head, const int p){
	int i;
	node *curr_node = head;
	for(i = 0; i < p && curr_node->string != 0; i++){
		printf("%s\n", curr_node->string);
		curr_node = curr_node->next;
	}
}

void free_list(node *head){
	node *next_node, *curr_node;
	if(head->string)
		free(head->string);
	curr_node = head->next;
	while(curr_node != 0){
		next_node = curr_node->next;
		free(curr_node->string);
		free(curr_node);
		curr_node = next_node;
	}
	free(curr_node);
}

int solve1(node *head){
	node *curr_node;
	int count = 1, cmp_rate;
	char *max_str;
	if(head->string == 0)
		return 0;
	max_str = head->string;
	curr_node = head->next;
	while(curr_node->string != 0){
		cmp_rate = strcmp(max_str, curr_node->string);
		if(cmp_rate == 0)
			count++;
		if(cmp_rate < 0){
			count = 1;
			max_str = curr_node->string;
		}
		curr_node = curr_node->next;
	}
	return count;
}

int solve2(node *head){
	node *curr_node;
	int count = 0;
	char *str_prev;
	if(head->string == 0)
		return 0;
	str_prev = head->string;
	curr_node = head->next;
	while(curr_node->string != 0){
		if(strcmp(str_prev, curr_node->string) < 0)
			count++;
		str_prev = curr_node->string;
		curr_node = curr_node->next;
	}
	return count;
}

int solve3(node *head){
	node *curr_node;
	int count = 0;
	char *str_prev, *str_next;
	if(head->string == 0)
		return 0;
	str_prev = head->string;
	curr_node = head->next;
	while(curr_node->string != 0){
		str_next = (curr_node->next)->string;
		if(str_next == 0)
			break;
		if(strcmp(curr_node->string, str_prev) >= 0 &&
			strcmp(curr_node->string, str_next) >= 0)
			count++;
		str_prev = curr_node->string;
		curr_node = curr_node->next;
	}
	return count;
}

int solve4(node *head){
	node *curr_node;
	int count = 0, max_count = 0;
	char *str_prev, *str_next;
	if(head->string == 0)
		return 0;
	str_prev = head->string;
	curr_node = head->next;
	while(curr_node->string != 0){
		str_next = (curr_node->next)->string;
		if(str_next == 0)
			break;
		if(strcmp(curr_node->string, str_prev) >= 0 &&
			strcmp(curr_node->string, str_next) >= 0){
			max_count = (count > max_count ? count : max_count);
			count = 0;
		}
		else
			count++;
		str_prev = curr_node->string;
		curr_node = curr_node->next;
	}
	return max_count;
}

int solve5(node *head){
	node *curr_node;
	int count = 0, max_count = 0;
	char *str_prev;
	if(head->string == 0)
		return 0;
	str_prev = head->string;
	curr_node = head->next;
	while(curr_node->string != 0){
		if(strcmp(curr_node->string, str_prev) > 0){
			count += (count == 0 ? 2 : 1);
		}
		else{
			max_count = (count > max_count ? count : max_count);
			count = 0;
		}
		str_prev = curr_node->string;
		curr_node = curr_node->next;
	}
	return (max_count > count ? max_count : count);
}

int solve6(node *head){
	node *curr_node;
	int count = 0;
	char *str_prev;
	if(head->string == 0)
		return 0;
	str_prev = head->string;
	curr_node = head->next;
	if(curr_node->string != 0 && strcmp(str_prev, curr_node->string) == 0)
		count++;
	while(curr_node->string != 0){
		if(strcmp(curr_node->string, str_prev) != 0 &&
			(curr_node->next)->string != 0 &&
			strcmp(curr_node->string, (curr_node->next)->string) == 0)
			count++;
		str_prev = curr_node->string;
		curr_node = curr_node->next;
	}
	return count;
}

int solve7(node *head){
	node *curr_node;
	int count = 0, max_count = 0, flag = 0;
	char *str_prev;
	if(head->string == 0)
		return 0;
	str_prev = head->string;
	curr_node = head->next;
	if(curr_node->string != 0 && strcmp(str_prev, curr_node->string) == 0)
		flag = 1;
	while(curr_node->string != 0){
		if(strcmp(curr_node->string, str_prev) != 0)
			count += (flag == 1 ? 1 : 0);
		else{
			flag = 1;
			max_count = (count > max_count ? count - 1: max_count);
			count = 0;
		}
		str_prev = curr_node->string;
		curr_node = curr_node->next;
	}
	return max_count;
}

int get_list_len(node *head){
	node *curr_node = head;
	int len = 0;
	while(curr_node->next != 0){
		len++;
		curr_node = curr_node->next;
	}
	return len;
}

node* solve8(node *head){
	node *curr_node, *prev_node, *orig_head = head, *tmp;
	if(!head->next)
		return head;
	while((head->next)->string != 0 && strcmp(head->string, (head->next)->string) >= 0){
		free(head->string);
		tmp = head->next;
		if(orig_head != head)
			free(head);
		head = tmp;
	}
	curr_node = head->next;
	prev_node = head;
	if(!curr_node || !curr_node->next)
		return head;
	while((curr_node->next)->string != 0){
		if(strcmp(curr_node->string, (curr_node->next)->string) >= 0){
			prev_node->next = curr_node->next;
			free(curr_node->string);
			free(curr_node);
			curr_node = prev_node->next;
		}
		else{
			prev_node = curr_node;
			curr_node = curr_node->next;
		}
	}
	return head;
}

node* solve9(node *head){
	node *curr_node, *prev_node;
	char *str_prev = 0;
	if(head->next == 0)
		return head;
	prev_node = head;
	curr_node = head->next;
	if(!curr_node->next)
		return head;
	str_prev = prev_node->string;
	while((curr_node->next)->string != 0){
		if(strcmp(curr_node->string, (curr_node->next)->string) >= 0 &&
			strcmp(curr_node->string, str_prev) >= 0){
			prev_node->next = curr_node->next;
			if(str_prev != prev_node->string)
				free(str_prev);
			str_prev = curr_node->string;
			free(curr_node);
			curr_node = prev_node->next;
		}
		else{
			if(str_prev != prev_node->string)
				free(str_prev);
			prev_node = prev_node->next;
			curr_node = prev_node->next;
			str_prev = prev_node->string;
		}
	}
	if(str_prev != prev_node->string)
		free(str_prev);
	return head;
}

node* solve10(node *head){
	node *curr_node, *prev_node, *orig_head = head, *tmp;
	int del_next = 0;
	if(head->next == 0)
		return head;
	while((head->next)->string != 0 && strcmp(head->string, (head->next)->string) >= 0){
		free(head->string);
		tmp = head->next;
		if(orig_head != head)
			free(head);
		head = tmp;
		del_next = 1;
	}
	if(del_next == 1){
		free(head->string);
		tmp = head->next;
		if(orig_head != head)
			free(head);
		head = tmp;
	}
	curr_node = head->next;
	prev_node = head;
	if(!curr_node || !curr_node->next)
		return head;
	del_next = 0;
	while((curr_node->next)->string != 0){
		if(strcmp(curr_node->string, (curr_node->next)->string) >= 0){
			prev_node->next = curr_node->next;
			free(curr_node->string);
			free(curr_node);
			curr_node = prev_node->next;
			del_next = 1;
		}
		else{
			if(del_next == 1){
				prev_node->next = curr_node->next;
				free(curr_node->string);
				free(curr_node);
				curr_node = prev_node->next;
				del_next = 0;
			}
			else{
				prev_node = curr_node;
				curr_node = curr_node->next;
			}
		}
	}
	if(del_next == 1){
		prev_node->next = curr_node->next;
		free(curr_node->string);
		free(curr_node);
		del_next = 0;
	}
	return head;
}
