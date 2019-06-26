#pragma once

#define OLC_PGE_APPLICATION
#include"olcPixelGameEngine.h"



typedef struct Node* nodeptr;

struct Node
{
public:
	int letter;
	struct Node* left;
	struct Node* right;

public:
	
	Node(int data)
	{
		letter = data;
		left = right = nullptr;
	}
	Node(int data, nodeptr _left, nodeptr _right)
	{
		letter = data;
		left = _left;
		right = _right;
	}

	// operaciones de acceso 
	int getNodeValue()	{ return letter; }  
	nodeptr getLeftSubTree()	{ return left; }  
	nodeptr getRightSubTree(){ return right; }
	// operaciones de modificación  
	void setNodeValue(int data)	{ letter = data; }
	void setleftBranch(nodeptr n)	{ left	 = n;	 }  
	void setRightBranch(nodeptr n){ right  = n;	 } 
};

//BINARY SEARCH TREE
class BST 
{
private:
	nodeptr m_root;

public:
	BST()
	{
		m_root = nullptr;
	}

	BST(nodeptr r) { m_root = r; }
	void setRoot(nodeptr r) { m_root = r; }
	nodeptr getRoot() { return m_root; }
	
	Node getRootDirection() 
	{ 
		if (m_root)
			return *m_root;
		else
			throw "empty tree";
	}
	
	
	nodeptr getLeftChildNode() 
	{ 
		if (m_root)
			return m_root->getLeftSubTree();
		else
			throw " no left tree";
	}
	
	nodeptr getRightChildNode() 
	{ 
		if (m_root)
			return m_root->getRightSubTree();
		else
			throw " no right tree";
	}
	
	nodeptr newTree(nodeptr leftBranch, int data, nodeptr rightBranch) 
	{
		return new Node(data, leftBranch, rightBranch);
	}


	
	void DeleteTree(nodeptr root) 
	{ 
		if (root != nullptr) 
		{ //post order track
			DeleteTree(root->getLeftSubTree()  );      
			DeleteTree(root->getRightSubTree() );      
			std::cout << "\nNode deleted. ";
			root = nullptr; 
		} 
	}

	int HeightTree(nodeptr root)
	{
		if (root == nullptr) //empty tree
			return 0;
		else
		{
			int leftHeight = HeightTree(root->getLeftSubTree());
			int rightHeight   = HeightTree(root->getRightSubTree());    
			if (leftHeight > rightHeight)
				return leftHeight + 1;
			else
				return rightHeight + 1;
		}
	}
	
	int NodesAmount(nodeptr root) 
	{ 
		if (root == nullptr)       
			return 0;    
		else      
			return 1 + NodesAmount(root->getLeftSubTree()) + NodesAmount(root->getRightSubTree()); 
	}



	bool IsComplete(nodeptr root)
	{
		if (root == nullptr)
			return true;
		else
		{
			if (HeightTree(root->getLeftSubTree()) != HeightTree(root->getRightSubTree()))
				return false;
		}
		//black box
		return IsComplete(root->getLeftSubTree()) && IsComplete(root->getRightSubTree());
	}

	bool isEmpty() { return m_root == nullptr; }

	void InsertNode(int data)
	{
		nodeptr tempNode = new Node(data);//node that holds data
		nodeptr current(nullptr), parent(nullptr);
		
		// if tree empty
		if (m_root == nullptr)
			m_root = tempNode;
		else
		{
			current = m_root;//help to travel the tree
			parent = nullptr;//no conexion

			while (true)
			{
				parent = current;

				//insert on left tree branch
				if (data < parent->getNodeValue())
				{
					current = current->getLeftSubTree();

					//check for empty, its that the case add the new node
					if (current == nullptr)
					{
						parent->setleftBranch(tempNode);
						return;
					}
				}
				else//insert on right tree branch
				{
					current = current->getRightSubTree();

					//inset on right branch
					if (current == nullptr)
					{
						parent->setRightBranch(tempNode);
						return;//exit funcion
					}
				}

			}

		}
		

	}

	nodeptr Search(int data) 
	{
		nodeptr current = m_root;
		std::cout<< "Visiting elements: ";

		while (current->getNodeValue() != data) {

			if (current != NULL) 
			{
				std::cout<< current->getNodeValue() << " , ";

				//go to left tree
				if (current->getNodeValue() > data) 
				{
					current = current->getLeftSubTree();
				}  //else go to right tree
				else 
				{
					current = current->getRightSubTree();
				}

				//not found
				if (current == NULL) 
				{
					return nullptr;
				}
			}
		}

		return current;
	}


	void EliminateNode(int data)
	{
		m_root = EliminateNode(m_root, data);//send the modify tree structure to root node
	}

	nodeptr EliminateNode(nodeptr subRoot, int data)
{
	//in case that node doesnt exit
	if (subRoot == nullptr)
		std::cout << "The node was not found in tree\n";
	else if (data < subRoot->getNodeValue() )//check left branch
	{
		nodeptr leftNode;
		
		leftNode = EliminateNode(subRoot->getLeftSubTree(), data);
		subRoot->setleftBranch(leftNode);
	}
	else if (data > subRoot->getNodeValue() )
	{
		nodeptr rightNode;
		rightNode = EliminateNode(subRoot->getRightSubTree(), data);
		subRoot->setRightBranch(rightNode);
	}
	else // node found
	{
		nodeptr deleteNode;//Transfer data from the found node to this deletenODE
		deleteNode = subRoot;
		//check if deleteNode doesnt have left child
		if (deleteNode->getLeftSubTree() == nullptr)
			subRoot = deleteNode->getRightSubTree();
		//check if deleteNode doesnt have right child
		else if (deleteNode->getRightSubTree() == nullptr)
			subRoot = deleteNode->getLeftSubTree();
		else//if have 2 child nodes
		{
			//to keep structure, replace the node data with the largest of the minor keys in the subtree
			deleteNode = ReplaceNode(deleteNode);
		}
		//after done proccess of finding and setting nodes, we delete all data inside that node
		deleteNode = nullptr;
	}

	return subRoot;
}

	nodeptr ReplaceNode(nodeptr changeNode)
	{
	/*
		As the minor keys are in the left branch, the first branch of the left branch is lowered, 
		and it continues down the right branches (major keys) until reaching the node that does not have a right branch. 
		This is the largest of the minors, whose data must replace the node to be deleted. 
		What you do is copy the value of the data and link your father with the left child.
	*/
	nodeptr a, p;
	p = changeNode;
	a = changeNode->getLeftSubTree();//all the left tree branch
	while (a->getRightSubTree() != nullptr)//travel the tree from that rightbranch
	{
		p = a;
		a = a->getRightSubTree();
	}
	//copy in 'changeNode' the value of the node 'a' is pointing to
	changeNode->setNodeValue( a->getNodeValue() );

	//'a' is the new left child of 'changeNode'
	if (p == changeNode)
		p->setleftBranch(a->getLeftSubTree());//link left branch
	else
		p->setRightBranch( a->getRightSubTree() );//link right branch
	
	return a;
}

	void getShortestPath(nodeptr root, olc::PixelGameEngine* pge)
	{
		//find path
		std::vector<nodeptr> nodeptrList;
		nodeptrList.push_back(root);
		
		bool search = true;
		while (search) 
		{
			if (nodeptrList.back() == m_root)
				search = false;
			else 
				nodeptrList.push_back( getParentNode( nodeptrList.back()->getNodeValue() ) );
		}

		//print path
		int x = 25;
		int y = 125;
		while (nodeptrList.size() > 1) 
		{
			std::string pathText = "FROM NODE " + std::to_string(nodeptrList.back()->getNodeValue()) + " TO NODE " + std::to_string(nodeptrList.at(nodeptrList.size() - 2)->getNodeValue());

			pge->DrawString(x, y, pathText, olc::GREEN);

			nodeptrList.pop_back();
			nodeptrList.shrink_to_fit();
			y += 15;
		}
	}

	//call
	nodeptr getParentNode(int data)
	{
		return getParentNode(m_root, data);
	}
	//node parent algorithm
	nodeptr getParentNode(nodeptr root, int data)
	{
		if (root == nullptr)
			return nullptr;
		
		nodeptr parentNode(nullptr);

		while (root != nullptr)
		{
			if (data < root->getNodeValue())//left
			{
				parentNode = root;//posible parent
				root = root->getLeftSubTree();
			}
			else if (data > root->getNodeValue())//right
			{
				parentNode = root;
				root = root->getRightSubTree();
			}
			else break;
		}

		return parentNode;
	}

	int getLeafNodesAmount(nodeptr root)
	{
		if (root == nullptr)
			return 0;
		if (root->getLeftSubTree() == nullptr && root->getRightSubTree() == nullptr)
			return 1;
		else
			return getLeafNodesAmount(root->getLeftSubTree()) + getLeafNodesAmount(root->getRightSubTree());
		
	}


	int getLevelNode(nodeptr root, int data, int level = 1)
	{
		/* Helper function for getLevel().
		It returns level of the data if data is
		present in tree, otherwise returns 0.*/

		//if node doesnt exits
		if (root == nullptr)
			return 0;

		//if node is found
		if (root->getNodeValue() == data)
			return level;

		int downlevel = getLevelNode(root->getLeftSubTree(), data, level + 1);
		
		if (downlevel != 0)
			return downlevel;

		downlevel = getLevelNode(root->getRightSubTree(), data, level + 1);

		return downlevel;

	}
	
	//TESTING
	nodeptr getBrotherNode(nodeptr node)
	{	
		nodeptr parent = getParentNode( node->getNodeValue() );

		if (parent != nullptr)
		{
			nodeptr parentleftChild = parent->left;
			nodeptr parentRightChild = parent->right;
		
			if (parentleftChild != nullptr && parentRightChild == nullptr)//solo el izq
			{
				if (parentleftChild->getNodeValue() != node->letter)
					return parentleftChild;
				else
					return nullptr;//porque encontro el mismo nodo q llamo la funcion
			}
			else if (parentleftChild == nullptr && parentRightChild != nullptr)//solo el derecho
			{
				if (parentRightChild->getNodeValue() != node->letter)
					return parentRightChild;
				else
					return nullptr;//porque encontro el mismo nodo q llamo la funcion osea no tiene hermano
			}
			else if (parentleftChild != nullptr && parentRightChild != nullptr)//ambos hijos
			{
				if (parentleftChild->getNodeValue() != node->letter && parentRightChild->getNodeValue() == node->letter)
					return parentleftChild;
				else if (parentleftChild->getNodeValue() == node->letter && parentRightChild->getNodeValue() != node->letter)
					return parentRightChild;
			}
			
		}
		else
			return nullptr;

		
		
	}

	int LenghtOfaNode(int data)
	{
		nodeptr current = m_root;
		int iter = 0;

		while (current->getNodeValue() != data) {

			if (current != NULL)
			{
				iter++;
				//go to left tree
				if (current->getNodeValue() > data)
				{
					current = current->getLeftSubTree();
				}  //else go to right tree
				else
				{
					current = current->getRightSubTree();
				}

				//not found
				if (current == NULL)
				{
					return 0;
				}
			}
		}

		return iter;
	}


	void PreOrder(nodeptr root, std::string& container)
	{

		if (root != nullptr)//proccess 
			container += std::to_string(root->getNodeValue()) + " - ";
		
		if (root != nullptr && root->getLeftSubTree() != nullptr)//si hay lado izq
			PreOrder(root->getLeftSubTree(), container);
		if (root != nullptr && root->getRightSubTree() != nullptr)//si hay lado der
			PreOrder(root->getRightSubTree(), container);
	}
	
	
	void InOrder(nodeptr root, std::string& container)
	{
		if (root != nullptr && root->getLeftSubTree() != nullptr)//left branch
			InOrder(root->getLeftSubTree(), container);
		
		if (root != nullptr)//process you want to do
			container += std::to_string(root->getNodeValue()) + " - ";

		if (root != nullptr && root->getRightSubTree() != nullptr)//right branch
			InOrder(root->getRightSubTree(), container);
	}


	void PostOrder(nodeptr root, std::string& container)
	{
		if (root != nullptr && root->getLeftSubTree() != nullptr)
			PostOrder(root->getLeftSubTree(), container);
		if (root != nullptr && root->getRightSubTree() != nullptr)
			PostOrder(root->getRightSubTree(), container);
		
		if (root != nullptr)//process
			container += std::to_string(root->getNodeValue()) + " - ";
	}


};



// Binary Expression Tree functions 
// TODO: Convert all this magic into a class
//typedef NodeBET* nodebetptr;

class NodeBET 
{
private:
	char letter;
	NodeBET* right;
	NodeBET* left;

public:
	NodeBET(char data)
	{
		letter = data;
		right = left = nullptr;
	}

	//setters & getters
	void setNodeValue(char data) { letter = data; }
	void setleftBranch(NodeBET* n) { left = n; }
	void setRightBranch(NodeBET* n) { right = n; }

	NodeBET* getLeftSubTree() { return left; }
	NodeBET* getRightSubTree() { return right; }
	char getNodeValue() { return letter; }


};

//class BET
//{
//	
//
//};
//
bool isLetter(char c)
{
	std::string list = "1234567890qwertyuiopasdfghjklzxcvbnm+-/*^";

	for (char l : list)
	{
		if (c == l)
			return true;
	}

	return false;

}
char getCloseTerm(char c)
{
	if (c == ')') return '(';
	else if (c == ']') return '[';
	else if (c == '}') return '{';
	else return ' ';
}

bool isBalanced(std::string expression)
{
	//this fucntion checks if we have balance size of open & close parenthesis.
	std::stack<char> stack;

	//travell the expression for parenthesis
	
	for (char testChar : expression)
	{
		if (!isLetter(testChar))
		{
			if (testChar == '(' || testChar == '[' || testChar == '{')
				stack.push(testChar);
			else if (stack.top() == getCloseTerm(testChar))
				stack.pop();
			else
				return false;
		}
	}

	return stack.empty();
}



bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') 
		return true;
	
	return false;
}

bool IsOperand(char c)
{
	if (c >= '0' && c <= '9') return true;
	else if (c >= 'a' && c <= 'z') return true;
	else if (c >= 'A' && c <= 'Z') return true;
	
	return false;
}


// Function to get weight of an operator. An operator with higher weight will have higher precedence. 
int GetOperatorWeight(char op)
{
	int weight = -1;

	if		(op == '+' || op == '-') weight = 1;
	else if (op == '*' || op == '/') weight = 2;
	else if (op == '^' ) weight = 3;
	
	return weight;
}

// Function to verify whether an operator is right associative or not. 
bool IsRightAssociative(char op)
{
	if (op == '^') return true;
	
	return false;
}

// Function to perform an operation and return output. 
bool HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative. 
	// return false, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	if (op1Weight == op2Weight)
	{
		if (IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ? true : false;
}

//convert infix to postfix
std::string ConvertToPosfix(std::string expression)
{
	//Function to evaluate Postfix expression and return output
	std::stack<char> stack;
	
	std::string posfixOutput = "";

	for (char c : expression)
	{
		//if empty character, go to next iteration
		if (c == ' ' || c == ',') continue;

		//if openTerm
		else if (c == '(' ) stack.push(c);

		//if character closingTerm, checks for opening in stack 
		else if (c == ')' )
		{
			while ( !stack.empty() && stack.top() != '('  )
			{
				posfixOutput += stack.top();//if not found, add the top to output
				stack.pop();//clean the top
			}
			//if found clean the top again
			stack.pop();
		}
		else if (isOperator(c))
		{
			while ( !stack.empty() && HasHigherPrecedence(stack.top(), c) && stack.top() != '('  )
			{
				posfixOutput += stack.top();
				stack.pop();
			}
			stack.push(c);
		}
		else if (IsOperand(c))// in case this is a operand, just add to output
			posfixOutput += c;

	}
		//clean the stack with remains character
		while (!stack.empty())
		{
			posfixOutput += stack.top();
			stack.pop();
		}


	return posfixOutput;
}

//convert postfix to prefix
std::string ConvertToPrefix(std::string postExpression)
{
	std::stack<std::string> stack;
	//travell
	for (char c : postExpression)
	{
		if (isOperator(c))
		{
			//pop 2 operands elements from the stack
			std::string operand1 = stack.top();
			stack.pop();
			std::string operand2 = stack.top();
			stack.pop();

			//concats the operands and add it to output
			std::string tempOutput = c + operand2 + operand1;

			stack.push(tempOutput);
		}
		else //then is operand
			stack.push( std::string(1, c) );
		
	}

	//the top holds the prefix expression
	return stack.top();
}

NodeBET* ConstructTree(std::string postfix)
{
	std::stack<NodeBET*> stack;

	NodeBET* t1(nullptr); NodeBET* t2(nullptr);
	NodeBET* output(nullptr);

	//traverse
	for (char c : postfix)
	{
		if (!isOperator(c))
		{
			NodeBET* newNode = new NodeBET(c);
			stack.push(newNode);
		}
		else //operator
		{
			NodeBET* newNode = new NodeBET(c);
			//pop 2 elements on top of stack
			t1 = stack.top();
			stack.pop();
			t2 = stack.top();
			stack.pop();

			//make them children
			newNode->setRightBranch(t1);
			newNode->setleftBranch(t2);

			//add to stack
			stack.push(newNode);
		}
		
	}

	//top elemet will be the root of the expression tree
	output = stack.top();
	stack.pop();

	return output;
}

