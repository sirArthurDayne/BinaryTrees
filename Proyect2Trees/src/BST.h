#pragma once
#include"olcPixelGameEngine.h"
#include"Node.h"
#include"NodeBET.h"

//BINARY SEARCH TREE
class BST 
{
private:
	nodeptr m_root;
public:
	BST();

	BST(nodeptr r);
	void setRoot(nodeptr r);
	nodeptr getRoot();
	
	Node getRootDirection();
	
	nodeptr getLeftChildNode();
	
	nodeptr getRightChildNode();
	
	nodeptr newTree(nodeptr leftBranch, int data, nodeptr rightBranch);
	
	void DeleteTree(nodeptr root);

	int HeightTree(nodeptr root);
	
	int NodesAmount(nodeptr root);

	bool IsComplete(nodeptr root);

	bool isEmpty();

	void InsertNode(int data);

	nodeptr Search(int data);

	void EliminateNode(int data);

	nodeptr EliminateNode(nodeptr subRoot, int data);

	nodeptr ReplaceNode(nodeptr changeNode);

	void getShortestPath(nodeptr root, olc::PixelGameEngine* pge);
	//call
	nodeptr getParentNode(int data);

	//node parent algorithm
	nodeptr getParentNode(nodeptr root, int data);

	int getLeafNodesAmount(nodeptr root);

	int getLevelNode(nodeptr root, int data, int level = 1);

	nodeptr getBrotherNode(nodeptr node);
	
	int LenghtOfaNode(int data);

	void PreOrder(nodeptr root, std::string& container);
	
	void InOrder(nodeptr root, std::string& container);

	void PostOrder(nodeptr root, std::string& container);

};
