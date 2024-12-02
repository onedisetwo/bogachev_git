struct _node;
typedef struct _node{
	char *string;
	struct _node * next;
} node;

int read_file(const node *head, const char *filename);
void print_list(const node *head, const int p);
void free_list(const node *head);
