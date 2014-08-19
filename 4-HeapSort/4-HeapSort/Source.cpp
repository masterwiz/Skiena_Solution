#include <iostream>
#include <cstdlib>

#define PQ_SIZE 100

typedef int item_type;

/*
remember this, pq is a similar structure to binary tree
importantly, it save memeory because while enforcing the parent child
rule, we also have a complete tree that easy to traverse without pointer
however, we don't really enfore the relationship within
same layer (level), we don't know the rank between left and right child
but we can't move around subtree simply using pointer
beap not bst. we know nothing about the relative order
search must be linear
*/



/*
this is a increasing heap, parent smaller than child
min-heap
*/
typedef struct priority_queue
{
	item_type q[PQ_SIZE + 1];
	// for easiness, we assume array starting at index 1
	// each layer l will store 2^l keys
	// in index 2^(l-1) to 2^l-1
	// for item k
	// left key is always 2k, right is 2k+1
	// parent is int(k/2)
	int n; // number of items, starting 0 with nothing
} priority_queue;

int pq_parent(int n);
int pq_young_child(int n);
void pq_insert(priority_queue *q, item_type x);
void bubble_up(priority_queue *q, int p);
void pq_init(priority_queue *q);
void make_heap(priority_queue *q, item_type s[], int n);
int heap_compare(priority_queue *q, int i, int count, int x);

// how to delete?
// this is called heapify, or bubble down
// as since we have a min-heap, parent should always smaller than
// two child. 
// now question is how to do heap sort?
// remember heap is weak sorted, thus, we know
// root will be the smallest/
// each time we emit root out as the minimum
// then fill with the last right most leaf (at location n)
// to retain heap rank, we have to compare this new value
// with each child. if current root is the minimum, then it has
// to be the minimum of the heap, else, we switch with the min of 
// two child, and continue to switch to minimun of child
// hence, we retain the heap structure and weakly ranked
// this is called bubble down or heapify, as we
// merged two heap together. 
item_type extract_min(priority_queue *q);
void bubble_down(priority_queue *q, int p);
// repeating this emit process, we heapsorted the heap. 

int pq_parent(int n)
{
	if (n == 1) return (-1); // if first, parent is none, -1
	else return n / 2; // integer as well
}

int pq_young_child(int n)
{
	// left child
	return n * 2;
}

void pq_insert(priority_queue *q, item_type x)
{
	if (q->n >= PQ_SIZE)
	{
		// n=100 there's 100 item, at index 100 not 99 
		// (assuming starting at 1)
		std::cout << "warining: size overflow with" << x << std::endl;
	}
	else
	{
		++q->n;
		q->q[q->n] = x;
		bubble_up(q, q->n);
		// we still have to enforce the parent child relationship
		// whenever i insert  x at n, i must bubble up the number
		// swapping with parent that's greater than x
		// until gets to the correct place, or root
	}
}

void bubble_up(priority_queue *q, int p)
{
	if (pq_parent(p) == -1) return;
	// if root, stop;
	if (q->q[pq_parent(p)] > q->q[p])
		// if parent greater than current
		// keep move up to parent
	{
		// swap, then bubble up starting new position
		item_type temp = q->q[pq_parent(p)];
		q->q[pq_parent(p)] = q->q[p];
		q->q[p] = temp;
		// each swap takes at most log(n) as height
		// n insert takes nlog(n)
		bubble_up(q, pq_parent(p));
	}
}

void pq_init(priority_queue *q)
{
	q->n = 0;
}

void make_heap(priority_queue *q, item_type s[], int n)
{
	int i;
	pq_init(q);

	for (i = 0; i < n; ++i)
	{
		pq_insert(q, s[i]);
	}
}

item_type extract_min(priority_queue *q)
{
	int min = -1;
	if (q->n < 0) std::cout << "end of priority queue" << std::endl;
	else
	{
		min = q->q[1]; // starting at 1
		// moving last leaf to root
		q->q[1] = q->q[q->n];
		--q->n;
		bubble_down(q, 1);
	}

	return min;
}

void bubble_down(priority_queue *q, int p)
{
	int min_ind = p;
	int c = pq_young_child(p);

	for (int i = 0; i <= 1; ++i)
	{
		// iterate for two child
		if ((c + i) <= q->n)
		{
			// if this child exist
			if (q->q[min_ind] > q->q[c + i])
				min_ind = c + i;
			// always comparing and update min loc
		}
	}
	if (min_ind != p)
	{
		// we need to switch and bubble down
		int temp = q->q[min_ind];
		q->q[min_ind] = q->q[p];
		q->q[p] = temp;

		// bubble down starting at min ind
		bubble_down(q, min_ind);
	}
}

/*
remember that we bubble down at most log(n) height times
for n item, we do nlog(n) times
this is heapsort

worst nlogn which is best expected from any sorting algorithm
it is implace sort so no extra memory
although, other sorting algorithms prove slightly faster in
practice
*/




int main()
{
	struct priority_queue queue;
	priority_queue* q = &queue;
	item_type s[] = { 1, 7, 6, 9, 10, 2, 14, 15, 4, 5, 11, 3, 8, 13, 12 };

	make_heap(q, s, 15);


	//for (int i = 0; i <= 14; ++i)
	//	s[i] = extract_min(q);
	//for (int i = 0; i <= 14; ++i)
	//	std::cout << s[i] << ' ';
	//std::cout << std::endl << std::endl;

	std::cout << heap_compare(q, 1, 7, 7);
	std::cout << std::endl;

	system("pause");
}



/*
problem find the kth smallest and if it is smaller than x
the process should take O(k), regardless the heap size

wrong: extract_min k times, will take klog(n)
wrong: since kth smallest can't be pass k level
we linear search through all k level item
and count how many are smaller than x
this will take O(min(n, 2^k))
*/

int heap_compare(priority_queue *q, int i, int count, int x)
{
	// if root >=x no heap is smaller than x
	// else, we only find through childs if parent
	// is smaller than x. thus, we take parent+2 child
	// at most 3k = O(k)

	if ((count <= 0) || (i > q->n)) return count;
	// remember we are pushing from root smallest to leafs 
	
	if (q->q[i] < x)
	{
		// search both child with count -1 because we found 1 
		// that is parent 
		count = heap_compare(q, pq_young_child(i), count - 1, x);
		// priviously already count-1, we don't have to do it again
		// cuz count is shared across the recursion
		// as return value
		count = heap_compare(q, pq_young_child(i) + 1, count, x);
	}
	// in the end
	// if count is 0; means that we found all k number smaller than 
	// x, hence, k must smaller than x
	// else, k is greater or equal to x
	return count;
}

