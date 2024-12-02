struct _node;
typedef struct _node{
	char *string;
	struct _node * next;
} node;

int read_file(node *head, const char *filename);
void print_list(node *head, const int p);
void free_list(node *head);

int solve1(node *head);
int solve2(node *head);
int solve3(node *head);
int solve4(node *head);
int solve5(node *head);
int solve6(node *head);
int solve7(node *head);

int get_list_len(node *head);
node *solve8(node *head);
node *solve9(node *head);
node *solve10(node *head);
