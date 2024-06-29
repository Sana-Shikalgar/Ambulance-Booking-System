#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"hash_p.h"

//Hash Function
int hash_function1(char* name, int size){
    int hash_value = 0;
    int prime = 31; // A prime number

    // Compute the hash value
    for (int i = 0; name[i] != '\0'; i++) {
	    if(name[i] == 32)
		    continue;
	    hash_value = (hash_value * prime + name[i]) % size;
    }
 
    return hash_value;
}

//Initializing the graph
void init_place(hash_p *h, char file_name[]){
        int size, ver, var;
	int hf;
	char name[32];

        FILE *fp = fopen(file_name, "r");
        if(!fp){
                printf("Error while opening the file!\n");
                return;
        }

        fscanf(fp, "%d", &(h->num)); //Total number of vertices
	size = h->num * 0.7;

        h->head = (hnode **) malloc(sizeof(hnode *) * size);
        if(!(h->head))
                return; //If could not malloc space return

        for(int i = 0; i < size; i++)
		h->head[i] = NULL;
	
	var = h->num;
        while(var){
		name[0] = '\0';
//		fscanf(fp, "%d\t%[^\n]s", &ver, name);
		fscanf(fp, "%d\t", &ver);
                fscanf(fp, "%[^\n]s", name);
            	hf = hash_function1(name, size); //Hash funtion for the given place name

                add_place(h, name, ver, hf);
		var --;
        }
	
        fclose(fp);

        return;
}

//Adding new locations to the hash table
void add_place(hash_p *h, char name[], int ver, int index){
        hnode *temp = NULL;
        
	hnode *hx = (hnode *) malloc(sizeof(hnode));
	hx->place = strdup(name);
        hx->ver = ver;
        hx->next = NULL;
	
	if(!(h->head[index])){
                h->head[index] = hx;
		return;
	}

        temp = h->head[index];

        while(temp && temp->next)
                temp = temp->next;
        temp->next = hx;

        return;
}

//Finding a the vertex name in hash
int find_source(hash_p h, char name[]){
	int ver = -1;
	int size = h.num * 0.7;
	int index = hash_function1(name, size);
	
	hnode *p = h.head[index];
	
	while(p){
		if(!(strcmp(p->place, name))){
			ver = p->ver;
			break;
		}
		p = p->next;
	}

//	printf("%d\n", ver);

	return ver;
}

//Printing all the stored places in hash
void print_places(hash_p h){
        hnode *p = NULL;
	int size = h.num * 0.7;

        for(int i = 0; i < size; i++){
                if(h.head[i])
			p = h.head[i];
		else
			p = NULL;

                while(p){
                        printf("%d\t%d\t", i, p->ver);
                        printf("%s\n", p->place);
                        p = p->next;
                }
		printf("\n");
        }

        return;
}
