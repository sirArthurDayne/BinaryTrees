#pragma once

typedef struct Node* nodeptr;

struct Node
{
public:
	int value;
	struct Node* left;
	struct Node* right;

public:
	Node(int data);

	Node(int data, nodeptr _left, nodeptr _right);

};

