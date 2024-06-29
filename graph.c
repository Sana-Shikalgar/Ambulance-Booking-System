#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>
#include"graph.h"
#define SIZE 135

//Initializing the graph
void init_graph(graph *g, char *file_name){
        int size, src, dest, wt;

        FILE *fp = fopen(file_name, "r");
        if(!fp){
                printf("Error while opening the file!\n");
                return;
        }

        fscanf(fp, "%d", &size); //Total number of vertices
	g->head = (gnode **)malloc(sizeof(gnode *) * size);
	if(!g)
                return; //If could not malloc space return

	for(int i = 0; i < size; i++)
		g->head[i] = NULL;
	
	while(fscanf(fp, "%d", &src) != EOF){
		fscanf(fp, "%d", &dest);
		fscanf(fp, "%d", &wt);

		add_node(g, src, dest, wt);
	}

	fclose(fp);

	return;
}

//Add edges to the graph
void add_node(graph *g, int src, int dest, int wt){
	gnode *s = NULL;
       	gnode *d = NULL;
        gnode *temp = NULL;
	int index = src - 1;

	if(!(g->head[index])){
		s = (gnode *) malloc(sizeof(gnode));
		s->ver = src;
		s->dist = 0;
		s->next = NULL;

		g->head[index] = s;
	}

	d = (gnode *) malloc(sizeof(gnode)); 
	d->ver = dest;
	d->dist = wt;
	d->next = NULL;

	temp = g->head[index];

	while(temp && temp->next)
		temp = temp->next;
	temp->next = d;

	return;
}

//Printing the graph
void print_graph(graph g){
	gnode *p = NULL;
	int src;

	for(int i = 0; i < 10; i++){
		p = g.head[i];
		
		if(p){
			src = p->ver;
	                printf("List for vertex %d :  ", src);
			p = p->next;
		}

		while(p){
			printf("(%d, ", p->ver);
			printf("%d) ", p->dist);
			p = p->next;
		}

		printf("\n");
	}

	return;
}


int minDistance(int* dist, bool* visited, int numNodes) {
    int min = INT_MAX;
    int minIndex;

    for (int v = 0; v < numNodes; v++) {
        if (visited[v] == false && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void printPath(int* parent, int node) {
    if (parent[node] == -1)
        return;

    printPath(parent, parent[node]);
    printf("%d ", node);
}

void printSolution(int* dist, int* parent, int src, int numNodes) {
    printf("Node\t Distance\tPath\n");
    for (int i = 0; i < numNodes; i++) {
        printf("%d -> %d\t %d\t\t%d ", src, i+1, dist[i], src);
        printPath(parent, i);
        printf("\n");
    }
}

//dijkstra's algorithm
int dijkstra(graph g, int src, int dest) {
    int numNodes = SIZE;
    int dist[SIZE];
    bool visited[SIZE];
    int parent[SIZE];

    // Initialize distance array and visited array
    for (int i = 0; i < SIZE; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    // Distance of source node from itself is always 0
    dist[src-1] = 0;
   // visited[src-1] = true;

    for (int count = 0; count < numNodes - 1; count++) {
        int u = minDistance(dist, visited, numNodes);
        visited[u] = true;

        gnode* currentNode = g.head[u];

        while (currentNode != NULL) {
            int v = currentNode->ver;

            if (visited[v - 1] == false && dist[u] != INT_MAX && dist[u] + currentNode->dist < dist[v - 1]) {
                dist[v - 1] = dist[u] + currentNode->dist;
                parent[v - 1] = u;
            }

            currentNode = currentNode->next;
        }
    }

    // Print the shortest path and distances
   // printSolution(dist, parent, src, numNodes);

    // Print the shortest distance from source to destination
  //  printf("Shortest distance from Node %d to Node %d: %d\n", src, dest, dist[dest - 1]);
  return dist[dest - 1];
}
