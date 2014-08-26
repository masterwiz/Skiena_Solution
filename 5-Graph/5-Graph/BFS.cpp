#include "Graph.h"
#include <queue>

//preprocess
//for each vertex u in V[G] - {s}  // s is the start
//	state[u] 'undiscovered'
//		p[u] = nil // u has no parents, yet
//state[s] = 'discovered'
//p[s]=nil // s has no parents, always
//start finding path
//Q={s} // starting a queue
//while Q not empty
//	u = dequeue[Q]
//	process vertex u as desired
//	for each v in adj[u]
//		process edge (u,v) as desired
//		if state[v] = "undiscovered" 
//			state[v] = "discovered"
//			p[v] = u
//			enqueue[Q,v] // this ensured the shortest path do not overlap
//	state[u] = "processed"

void initialize_search(graph *g);
void bfs(graph *g, int start);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int v, int y);

void find_path(int start, int end, int parents[]);

void connected_components(graph *g);

void twocolor(graph *g);
void twocolor_process_edge(int v, int y);
int complement(int color);



bool processed[MAXV + 1]; // after we traversed all outgoing edges
bool discovered[MAXV + 1]; // first time we visit
// could use enumerate type
int parents[MAXV + 1];

void initialize_search(graph *g)
{
	for (int i = 1; i <= g->nvertices; ++i)
	{
		processed[i] = discovered[i] = false;
		parents[i] = -1;
	}
}

// once discovered we put on a queue
// since FIFO, oldest will processed first
// those are close to root, say we have a all three layer, 
// second layer has three vertex, we processed all of them
// moving to third layer, we enqueue child of first vertex 
// from second layer, but then we dequeue second vertex from
// second layer, ever before touching those of third layer from
// first vertex 2nd layer


void bfs(graph *g, int start)
{
	std::queue<int> q;
	q.push(start);
	discovered[start] = true;
	edgenode *p;

	int v, y; // current vertex and successor

	while (q.empty() == false)
	{
		v = q.front();
		q.pop();
		process_vertex_early(v);
		p = g->edges[v];
		while (p != NULL)
		{
			y = p->y;
			if (processed[y] == false || g->directed)
				// has to be false /* not yet finished all processing with childs
				// to count as edge.
			{
				process_edge(v, y);
				// this has nothing to do if it is discovered
				// perfect to check edges, like twocolor
			}
			if (discovered[y] == false)
			{
				q.push(y);
				discovered[y] = true;
				parents[y] = v;
			}
			p = p->next;
		}
		processed[v] = true;
		process_vertex_late(v);
	}
}

// exact behavior depends on 
// void process_vertex_early(int v);
// void process_vertex_late(int v);
// void process_edge(int v, int y);
// what we do to vertex before of after processed
// and their connections

// assuming we want to do things early

void process_vertex_late(int v)
{
}

void process_vertex_early(int v)
{
	std::cout << "processed vertex %d\n", v;
}

void process_edge(int v, int y)
{
	std::cout << "processed edge (%d, %d)\n", v, y;
	// if we say ++nedges, we are counting edges
}

// find path
// parents array is very useful for finding a path
// we trace back to root is the distance shortest

// note it is unweighted

void find_path(int start, int end, int parents[])
{
	if ((start == end) || (end == -1))
		std::cout << "\n%d", start;
	else
	{
		find_path(start, parents[end], parents);
		printf(" %d", end);
	}
}

// find social network connected components
// after we bfs if there's anything that is not discovered
void connected_components(graph *g)
{
	int c = 0;
	initialize_search(g);
	for (int i = 1; i <= g->nvertices; ++i)
	{
		if (discovered[i] == false)
		{
			++c;
			printf("component %d:", c);
			bfs(g, i); // finding all component related to i, and set them discovered
			printf("\n");
		}
	}
}

// use fewest coler to unique laber vertex of each edge
// this often araise in scheduling appications
// two color?

// 1) each vertex is opposite color of parent
// 2) check any nondiscovered edge links two vertices of same color
// -> meaning not picolor

int color[MAXV + 1]; // color for each, -1 uncolor, 0, white, 1 black
bool bipartite = true;

void twocolor(graph *g)
{
	for (int i = 1; i <= g->nvertices; ++i)
		color[i] = -1;

	initialize_search(g);
	for (int i = 1; i <= g->nvertices; ++i)
	{
		if (discovered[i] == false)
		{
			color[i] = 0;
			// if a newly discovered component starting with white
			bfs(g, i);
			// inside here change child to black
		}
	}
}

void twocolor_process_edge(int v, int y)
{
	if (color[v] == color[y])
	{
		bipartite = false;
		printf("not pibartite due to (%d, %d)\n", v, y);
	}
	color[y] = complement(color[v]);
}

int complement(int color)
{
	if (color == 0) return 1;
	if (color == 1) return 0;
	return -1;
}