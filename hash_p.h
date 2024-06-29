//Structure for node of hash, this hash will store names of places in the graph
typedef struct hnode{
	char *place;
	int ver;
	struct hnode *next;
}hnode;

typedef struct hash_p{
	hnode **head;
	int num;
}hash_p;

void init_place(hash_p *h, char file_name[]);
void add_place(hash_p *h, char name[], int ver, int hf);
int find_source(hash_p h, char name[]);
void print_places(hash_p h);
