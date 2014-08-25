//Take a sequence of 2n real numbers as input.
//Design an O(n log n) algorithm that
//partitions the numbers into n pairs, with the 
//property that the partition minimizes
//the maximum sum of a pair.For example, say we 
//are given the numbers(1, 3, 5, 9).
//The possible partitions are((1, 3), (5, 9)), 
//((1, 5), (3, 9)), and((1, 9), (3, 5)).The pair
//sums for these partitions are(4, 14), (6, 12), 
//and(10, 8).Thus the third partition has
//10 as its maximum sum, which is the minimum 
//over the three partitions.


// team making
// best has to work with worst
// how? say 1,7,8,10,11,13 
// if we rank and get each end, 
// (1,13), (7,11), (8,9) max is 15. 
// will this always work, might be a better solution
// if number is skewed?
// remember middle two are at the middle location
// if you don't sum them up, then one will go with smaller number
// but theother will go with a larger number, worse
// hence middle has to match, same argument for others

#include <iostream>
#include <algorithm>
#include <vector>

bool sortcomp(int i, int j)
{
	return i < j;
}

int main()
{


	std::vector<int> myvec = { 4, 18, 13, 5, 8, 14, 9, 21, 10, 6 };
	std::sort(myvec.begin(), myvec.end(), sortcomp);

	for (std::vector<int>::iterator it = myvec.begin(); it != myvec.end(); ++it)
	{
		std::cout << *it << ',' << myvec.back() << std::endl;
		myvec.pop_back();

	}
	std::cout << std::endl;

	system("pause");
	return 0;
}