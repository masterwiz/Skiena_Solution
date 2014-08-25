#include <iostream>
#include <cstdlib>
#include <algorithm>
/*
we find a random pivot p, seperate list into two piles
low pile is all elements smaller than p sorted
high pile is all elements greater than p sorted
1) leaving p at its final location unchanged in future.
2) after partition with pivot without sort yet,
no element flot to the other side, allow use to sort independently
*/

typedef int item_type;


void quicksort(item_type *s, int l, int h);
int partition(item_type *s, int l, int h);
// partition return the pivot index

int main()
{
	item_type test[] = { 2, 5, 9, 6, 7, 4, 8, 10, 3, 1 };
	quicksort(test, 0, 9);
	//for (int i = 0; i <= 9; ++i)
	//{
	//	std::cout << test[i] << ',';
	//}
	//std::cout << std::endl;

	system("pause");
	return 0;
}

void quicksort(item_type *s, int l, int h)
{


	if ((h - l) > 0)
	{

		for (int i = 0; i <= 9; ++i)
		{
			std::cout << s[i] << ',';
		}
		std::cout << std::endl;
		// as long as there's more than one item, we have to
		// determine which side it belong to besides pivot
		int p = partition(s, l, h);
		quicksort(s, l, p - 1);
		quicksort(s, p + 1, h);
	}
}

int partition(item_type *s, int l, int h)
{
	// here we want to linear search the pivot position 
	// from a random list, how to do it?

	// we use the last item as our measurement
	// starting from first element, we move all the way right before the last
	// element. we also set a bar to seperate smaller than last and
	// larger than last elements
	// at first, bar is at the first element. 
	
	// if we find anything smaller than last, we raise the bar to next and
	// continue iterate to next
	// if we found anything larger or equal, we still iterate, but keep bar at 
	// it's location
	// if after we find larger, we find smaller, we swap that particular item
	// at i with bar, since bar always stay as first element >= than last
	// and i is a new found smaller, swapping and increasing bar keep
	// bar at first larger, and have i to be larger or equal
	// as well (originally smaller)

	// in the end, we swap last and bar location, making last greater than pivot
	// and bar to be the pivot position

	int pivot = h;
	int bar = l;

	for (int i = l; i < h; ++i)
	{
		if (s[i] < s[pivot])
		{
			std::swap(*(s+i), *(s+bar));
			++bar;
		}
	}
	std::swap(*(s + pivot), *(s + bar));
	// the swap only swaped the value
	// the pivot location is the bar location after we swap
	return l;
}

/*
	partition takes n times most, what's the sorting time?
	it's n*h where h is the height
	if each time we take the median, it's going to be
	nlog(n). since height is log
	however, if each time we always pick the ending one 
	largest or smallest in the sequence, we have to make
	n-1=h, hence worst case is n**2
	
	NOTE: quicksort has worse worst case, than heapsort and mergesort
	n**2 comparing to nlogn. but the average expect speed of mergesort
	is better
*/