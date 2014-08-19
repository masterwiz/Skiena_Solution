#include <cstdlib>

class Node
{
public:
	Node(double x)
	{
		weight = x;
		left = NULL;
		right = NULL;
		parent = NULL;

	}

	Node*& getLeft();
	Node*& getRight();
	Node*& getParent();
	double& data();
	Node* min();
	void inorder();
	void insert(double x);
	void remove();
	void bestfill(double x);
	int countbin();

private:
	double weight;
	Node *left;
	Node *right;
	Node *parent;
};

