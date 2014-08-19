#include "Node.h"
#include <cstdlib>
#include <iostream>


Node*& Node::getLeft()
{
	return left;
}

Node*& Node::getRight()
{
	return right;
}

Node*& Node::getParent()
{
	return parent;
}

double& Node::data()
{
	return weight;
}

void Node::insert(double x)
{
	if (x <= weight)
	{
		if (left == NULL)
		{
			left = new Node(x);
			left->getParent() = this;
		}
		else
		{
			left->insert(x);
		}
	}

	if (x > weight)
	{
		if (right == NULL)
		{
			right = new Node(x);
			right->getParent() = this;
		}
		else
		{
			right->insert(x);
		}
	}
}

void Node::inorder()
{
	if (this->left != NULL)
	{
		this->left->inorder();
	}
	std::cout << this->weight;
	if (this->right != NULL)
	{
		this->right->inorder();
	}


}

Node* Node::min()
{
	Node* temp = this;
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}

void Node::remove()
{

	if (this->left == NULL && this->right == NULL)
	{
		if (this->weight <= this->parent->weight)
		{
			// left child and leaf
			this->parent->left = NULL;
			delete this;
			return;
		}
		else
		{
			// right child and leaf
			this->parent->right = NULL;
			delete this;
			return;
		}
	}
	else
	{
		if (this->weight <= this->parent->weight)
		{
			// left child and not leaf
			// every child in this is smaller than
			// parent
			// if we have only one child
			// just connect with parent
			// else, move the min of right to this 
			// position and remove that min from leaf
			if (this->left == NULL)
			{
				this->parent->left = this->right;
				this->right->parent = this->parent;
				delete this;
				return;
			}
			else if (this->right == NULL)
			{
				this->parent->left = this->left;
				this->left->parent = this->parent;
				delete this;
				return;
			}
			else
			{
				Node* rightmin = this->right->min();
				float t = rightmin->weight;
				//std::cout << rightmin->data();
				rightmin->remove();
				this->weight = t;
				//delete rightmin;
				return;
			}
		}
		else
		{
			// right child and not leaf
			// every child in this is greater than
			// parent
			// if we have only one child
			// just connect with parent
			// else, move the min of right to this 
			// position and remove that min from leaf
			if (this->left == NULL)
			{
				this->parent->right = this->right;
				this->right->parent = this->parent;
				delete this;
				return;
			}
			else if (this->right == NULL)
			{
				this->parent->right = this->left;
				this->left->parent = this->parent;
				delete this;
				return;
			}
			else
			{
				Node* rightmin = this->right->min();
				float t = rightmin->weight;
				//std::cout << rightmin->data();
				rightmin->remove();
				this->weight = t;
				//delete rightmin;
				return;
			}
		}
	}
}

void Node::bestfill(double x)
{
	Node* minspace = NULL;
	Node* current = this;
	while (current != NULL)
	{
		if (current->weight + x <= 1)
		{
			// try larger base
			minspace = current;
			current = current->right;
		}
		else
		{
			current = current->left;
		}
	}
	// now minspace is the min place to update
	// or empty;
	if (minspace == NULL)
	{
		this->insert(x);
	}
	else
	{
		double newweight = minspace->weight + x;
		// now keep moving new minspace weight up
		if (minspace->parent == NULL)
		{
			minspace->weight = minspace->weight + x;
		}
		else
		{
			minspace->remove();
			this->insert(newweight);
		}
	}
	// left less weight, right more weight;
	// best fill find the one with minimon space
	// we constantly increasing base space(weight) iff we found current
	// space fit
	// and we decrease base space iff we found current space not fit
	// if we find a space where remaining is smaller we move minspace
	// if in the end minspace is NULL, insert new one
	// else, put into minspace and rearrange. 
}

int Node::countbin()
{
	if (this == NULL)
	{
		return 0;
	}
	else
	{
		return this->left->countbin() + 1 + this->right->countbin();
	}
}