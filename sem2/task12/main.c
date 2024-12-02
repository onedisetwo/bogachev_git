#include <stdio.h>
#include "main.h"
#include "errors.h"
#include <math.h>

int read_file(const node *head, const char *filename){
	const int BUF_LEN = 1233;
	char *buf;
	int len;
	FILE *fp;
	node *curr_node = head;
	if(!(fp = fopen(filename, "r"))
		return ERROR_OPEN;
	while(fgets(buf, BUF_LEN, fp)){
		len = strlen(buf);
		if(buf[len - 1] == '\n'){
			buf[len - 1] = 0;
			len--;
		}
		curr_node->string = (char*)malloc(len * sizeof(char));
		curr_node->next = (node*)malloc(sizeof(node));
		if(!curr_node->string || !curr_node->next){
			if(curr_node->string) 	free(curr_node->string);
			if(curr_node->next)	free(curr_node->next);
			free_list(head);
			fclose(fp);
			return ERROR_MEM;
		}
		strcpy(curr_node->string, buf);
		curr_node = curr_node->next;
	}
	if(feof(fp)){
		free_list(head);
		fclose(fp);
		return ERROR_READ;
	}
	fclose(fp);
	return SUCCESS;
}

void print_list(const node *head, const int p){
	int i;
	node *curr_node = head;
	for(i = 0; i < p; i++){
		printf("%s\n", (*curr_node).string);
		*curr_node = curr_node.next;
	}
}

void free_list(const node *head){
	node *next_node = head->next, *curr_node = head;
	while(curr_node != 0){
		free(curr_node.string);
		next_node = curr_node->next;
		free(curr_node);
	}
}
