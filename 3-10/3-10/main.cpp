#include <iostream>
#include "Node.h"
#include <vector>

void fit(std::vector<double> items);


int main()
{

	std::vector<double> v = { 0.1, 0.2, 0.3, 0.4, 0.5,
		0.3, 0.2, 0.5, 0.1, 0.4, 0.1, 0.2, 0.3, 0.4, 0.5,
		0.3};
	fit(v);

	//Node bst = Node(0.5);
	//bst.insert(0.2);
	//bst.insert(0.1);
	//bst.insert(0.3);
	//bst.insert(0.7);
	//bst.insert(0.6);
	//bst.insert(0.8);
	//bst.inorder();
	//std::cout << std::endl;
	//bst.getLeft()->getRight()->remove();
	//bst.getRight()->remove();
	////std::cout << bst.getLeft()->getParent()->data();
	//bst.inorder();
	////Node* m = bst.min();
	////std::cout << m->data();


	system("pause");
	return 0;
}

void fit(std::vector<double> items)
{
	Node bst = Node(items[0]);

	for (std::vector<double>::iterator it = items.begin() + 1;
		it != items.end(); ++it)
	{
		bst.bestfill(*it);
	}
	std::cout << "the number of bin is: " << bst.countbin() << std::endl;
}