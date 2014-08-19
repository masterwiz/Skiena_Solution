#include "node.h"
#include <iostream>

using namespace std;

int main()
{
	Node *head = new Node(1);
	head->append(2);
	head->append(3);
	head->append(4);
	head->append(5);

	head->traverse();

	Node::ReverseSLL(&head);
	// pass head's address which is same
	// as the equal to place where p2p points
	// **head_f = &head_main
	head->traverse();

	system("pause");
	return 0;
}
