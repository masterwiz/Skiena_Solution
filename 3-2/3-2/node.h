#include <cstdlib>
#include <iostream>

using namespace std;


class Node
{
private:
	int value;
	Node* next;
public:
	Node(int v = 0, Node* n = NULL)
	{
		value = v;
		next = n;
	}

	void append(int v)
	{
		Node *temp = new Node(v, NULL);
		Node* ptr = next;
		if (ptr == NULL)
		{
			next = temp;
		}
		else
		{
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}

			ptr->next = temp;
		}
	}

	void traverse()
	{
		if (next == NULL)
		{
			cout << value;
			cout << endl;
		}
		else
		{
			cout << value << ',';
			next->traverse();
		}
	}
	// non member function
	static void ReverseSLL(Node **head)
	{

		if (head == NULL || *head == NULL)
		{
			// if we do not have a pointer to head pointer, 
			// or that head pointer (evaluated from ptp)
			//is empty (we don't have a node from that pointer)
			return;
		}

		Node *prev, *p, *next;

		prev = *head; // prev is equal to evaluation of ptp head, which
		// is the actual pt to head node
		p = prev->next;

		prev->next = NULL; // we kept this info above, reverse
		while (p != NULL)
		{
			// keep moving til p is at end, and prev is at one before end
			// where we reverse and set new head
			next = p->next;
			p->next = prev;
			prev = p;
			p = next;
		}

		// set new head to prev
		// head is passed by pointer, we changed pointer
		// and it reflect through the p2p
		*head = prev;
	}

};

