#include <iostream>
#include <cstdlib>
#include <queue>

/*
the effeciency of merge sort depends on
how effecient we can combine two sorted halves into
one single sorted list

remember all smallest must at top of either
of the halves. remove the smallest, we still
have next smallest at top of the halves
we continue removing til end

continues, this takes O(n)
since we split two piece each time
total run time nlog(n)

this is great for linkedlist because we don't
need random access to elements like heapsort or quicksort
where we need [] and swap. however we need extra memory buffer
WHEN SORTING ARRAIES
because it is easier to merge two sorted linked lists
but array need a third list to store result
linkedlist only need rearrange pointer
easier.

the third list can be a queue, FIFO from each halves
to enter queue, and pop back in sorted order
*/

typedef int item_type;


void mergesort(item_type* s, size_t low, size_t high);
void merge(item_type*s, size_t low, size_t middle, size_t high);
// passing s as pointer to the array first element

int main()
{
	item_type test[] = { 2, 4, 6, 8, 10, 9, 7, 5, 3, 1 };
	mergesort(test, 0, 9);
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << test[i] << ',';
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}

void mergesort(item_type* s, size_t low, size_t high)
{
	if (low < high)
	{
		size_t middle = (low + high) / 2;
		mergesort(s, low, middle);
		mergesort(s, middle + 1, high);
		merge(s, low, middle, high);
		// recursively sort each side and merge together
		// low: first index high last index middle
		// deviding index
	}
}

void merge(item_type* s, size_t low, size_t middle, size_t high)
{
	std::queue<item_type> buffer1, buffer2;
	// having queue to hold element for merging
	// FIFO, we pop back to array with sorted order
	size_t i;
	for (i = low; i <= middle; ++i) buffer1.push(s[i]);
	for (i = middle + 1; i <= high; ++i) buffer2.push(s[i]);

	i = low;
	while (!(buffer1.empty() || buffer2.empty()))
	{
		if (buffer1.front() <= buffer2.front())
		{
			s[i++] = buffer1.front();
			buffer1.pop();
		}
		else
		{
			s[i++] = buffer2.front();
			buffer2.pop();
		}
	}
	
	
	// know here, each buffer should already been sorted
	// because each side is sorted, 
	// because base case is sorted already
	// and we merge and remain sorted
	while (!buffer1.empty())
	{
		s[i++] = buffer1.front();
		buffer1.pop();
	}
	while (!buffer2.empty())
	{
		s[i++] = buffer2.front();
		buffer2.pop();
	}
}