//Structure for node of hash, this hash will store names of places in the graph
typedef struct node{
        char *name;
        int ver;
	int amb;
        struct node *next;
}node;

typedef struct hash_h{
        node **head;
	int num;
}hash_h;

void init_hosp(hash_h *h, char file_name[]);
void add_hosp(hash_h *h, char name[], int ver, int amb, int hf);
node* find_dest(hash_h h, char name[]);
void print_hosp(hash_h h);
