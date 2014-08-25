#include <iostream>
#include <cstdlib>
#include <cstdio>

#define MAXV 1000

// each item only represent one directed relationship
// if undirected, it will show twice as reversed

struct edgenode
{
	int y; // adjacency info
	int weight; // weight
	struct edgenode *next; // pointer
};

struct graph
{
	edgenode *edges[MAXV + 1]; // all adjacency info
	int degree[MAXV + 1]; // out degree of each vertex
	int nvertices; // number of vertices
	int nedges; // number of edges
	bool directed;
};

// graph format initial line number of vertices and edges/
// then a list of edges at one vertex per line

void initialize_graph(graph *g, bool directed);
void read_graph(graph *g, bool directed);
void insert_edge(graph *g, int x, int y, bool directed);


void initialize_graph(graph *g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	for (int i = 1; i < MAXV; ++i) g->degree[i] = 0;
	for (int i = 1; i < MAXV; ++i) g->edges[i] = NULL;
}

void read_graph(graph *g, bool directed)
{
	initialize_graph(g, directed);

	int m; // # of edges
	scanf_s("%d %d", &(g->nvertices), &m);
	int x, y;
	for (int i = 1; i <= m; ++i)
	{
		scanf_s("%d %d", &x, &y);
		insert_edge(g, x, y, directed);
	}
}

void insert_edge(graph *g, int x, int y, bool directed)
{
	edgenode *p = new edgenode();
	p->weight = NULL;
	p->y = y;
	p->next = g->edges[x];
	g->edges[x] = p;
	// think about privous process, and the representation of adjacency list
	// page 151
	// 1->2->5->NULL
	// 2->1->5->3->4->NULL
	// 3->2->4->NULL
	// 4->2->5->3->NULL
	// 5->4->1->2->NULL

	// this means that 1 is adj to 2. from second relation 2 is adj to 1
	// either way, eacn line is describing relationships from one vertex
	// first number 1-5 is the index of edges. each index loc is a pointer
	// to the starting vertex. and all next is their direct next vertex
	// where x is always the starting vertex, y is the connected vertex
	// say we start with 3 with NULL;
	// first we see (3,2), we first name a struct y=2, and next is NULL (because
	// index x=3 at edges is NULL. then we assign this struct to x=3 loc at edges
	// hence, now x=3 loc at edges is a struct that link to 2.
	// next we have (3,4). similarly, a struct y=4, and next is what was at edges
	// loc 3, which is a struct of y=2 and next=NULL. then we assign this newly 
	// created struct to x=3 loc at edges. then loc x=3 at edges
	// will first have a struct to 4, with next to a struct to 2, both are linked
	// with loc 3. 

	++g->degree[x];
	if (directed == false)
	{
		insert_edge(g, y, x, true);
	}
	else
	{
		++g->nedges;
	}
}

void print_graph(graph *g)
{
	edgenode *p;
	for (int i = 1; i <= g->nvertices; ++i)
	{
		std::cout << "%d: ", i;
		p = g->edges[i];
		while (p != NULL)
		{
			std::cout << " %d", p->y;
			p = p->next;
		}
	}
}

int main()
{
	return 0;
}