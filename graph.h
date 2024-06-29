#include<stdbool.h>
//Structure for node of graph
typedef struct gnode{
	int ver;
	int dist;
	struct gnode* next;
}gnode;

typedef struct graph{
	gnode **head;
}graph;

void init_graph(graph *g, char file_name[]);
void add_node(graph *g, int src, int dest, int wt);
void print_graph(graph g);
int minDistance(int* dist, bool* visited, int numNodes);
void printPath(int* parent, int node);
void printSolution(int* dist, int* parent, int src, int numNodes);
int dijkstra(graph g, int src, int dest);
