#include"Node.h"

Node::Node(int data)
{
	value = data;
	left = right = nullptr;
}

Node::Node(int data, nodeptr _left, nodeptr _right)
{
	value = data;
	left = _left;
	right = _right;
}


