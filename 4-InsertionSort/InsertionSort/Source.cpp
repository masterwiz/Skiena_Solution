#include <iostream>
#include <cstdlib>


typedef int item_type;

/*
even though the worst case is n^2
if data is almost sorted, it will be much better

also note, same as insertion, insert into balanced tree
takes nlog(n), and in-order traverse take linear time
(because recursion only pass each item once)
*/

void insertSort(item_type* v, size_t n)
{
	// v is the pointer to the first element
	// n is last index
	for (size_t i = 0; i < n - 1; ++i)
	{
		size_t j = i + 1;
		while (j != 0 && v[j - 1] > v[j])
		{
			// we want to swtich this and privious one
			// as long as privious one is larger
			// or that we reach the top and no privious
			item_type temp = v[j];
			v[j] = v[j - 1];
			v[j - 1] = temp;
			// we continue so j has to decrease by 1
			--j;
		}
	}
}

int main()
{

	item_type test[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	// array is itself a pointer to the first
	insertSort(test, 10);
	for (size_t i = 0; i < 10; ++i)
	{
		std::cout << test[i] << ", ";
	}




	system("pause");
	return 0;
}