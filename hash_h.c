#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"hash_h.h"

//Hash Function
int hash_function2(char* name, int size){
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
void init_hosp(hash_h *h, char file_name[]){
        int size, ver, amb, var;
        int hf;
        char name[32];

        FILE *fp = fopen(file_name, "r");
        if(!fp){
                printf("Error while opening the file!\n");
                return;
        }

        fscanf(fp, "%d", &(h->num)); //Total number of vertices
	size = h->num * 0.7;

        h->head = (node **) malloc(sizeof(node *) * size);
        if(!(h->head))
                return; //If could not malloc space return

        for(int i = 0; i < size; i++)
                h->head[i] = NULL;
	
	var = h->num;
        while(var){
                name[0] = '\0';
//              fscanf(fp, "%d\t%[^\n]s", &ver, name);
                fscanf(fp, "%d\t", &ver);
		fscanf(fp, "%d\t", &amb);
                fscanf(fp, "%[^\n]s", name);
                hf = hash_function2(name, size); //Hash funtion for the given place name

                add_hosp(h, name, ver, amb, hf);
                var --;
        }

        fclose(fp);

        return;
}

//Adding new hospital to the hash table
void add_hosp(hash_h *h, char name[], int ver, int amb, int index){
        node *temp = NULL;

        node *hx = (node *) malloc(sizeof(node));
        hx->name = strdup(name);
        hx->ver = ver;
	hx->amb = amb;
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
node* find_dest(hash_h hp, char name[]){
        node* hosp = NULL;
	int size = hp.num * 0.7;
        int index = hash_function2(name, size);

        node *p = hp.head[index];

        while(p){
                if(!(strcmp(p->name, name))){
                        hosp = p;
                        break;
                }
                p = p->next;
        }

//      printf("%d\n", ver);

        return hosp;
}

//Printing all the stored hospitals in hash
void print_hosp(hash_h hp){
        node *p = NULL;
	int size = hp.num * 0.7;

        for(int i = 0; i < size; i++){
                if(hp.head[i])
                        p = hp.head[i];
                else
                        p = NULL;

                while(p){
                        printf("%d\t%d\t", i, p->ver);
			printf("%d\t", p->amb);
                        printf("%s\n", p->name);
                        p = p->next;
                }
                printf("\n");
        }

        return;
}

