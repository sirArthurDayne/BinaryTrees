#pragma once

#define OLC_PGE_APPLICATION
#include"olcPixelGameEngine.h"

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
			return m_root->left;
		else
			throw " no left tree";
	}
	
	nodeptr getRightChildNode() 
	{ 
		if (m_root)
			return m_root->right;
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
			DeleteTree(root->left);      
			DeleteTree(root->right );      
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
			int leftHeight = HeightTree(root->left);
			int rightHeight   = HeightTree(root->right);    
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
			return 1 + NodesAmount(root->left) + NodesAmount(root->right); 
	}

	bool IsComplete(nodeptr root)
	{
		if (root == nullptr)
			return true;
		else
		{
			if ( HeightTree(root->left) != HeightTree(root->right) )
				return false;
		}
		return IsComplete(root->left) && IsComplete(root->right);
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
				if (data < parent->value)
				{
					current = current->left;

					//check for empty, its that the case add the new node
					if (current == nullptr)
					{
						parent->left = tempNode;
						return;
					}
				}
				else//insert on right tree branch
				{
					current = current->right;

					//inset on right branch
					if (current == nullptr)
					{
						parent->right = tempNode;
						return;//exit funcion
					}
				}

			}

		}
		

	}

	nodeptr Search(int data) 
	{
		nodeptr current = m_root;
		//std::cout<< "Visiting elements: ";

		while (current->value != data) {

			if (current != NULL) 
			{
				//std::cout<< current->value << " , ";
				//go to left tree
				if (current->value > data) 
					current = current->left;
				  //else go to right tree
				else 
					current = current->right;

				//not found
				if (current == NULL) 
					return nullptr;
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
	else if (data < subRoot->value )//check left branch
	{
		nodeptr leftNode;
		leftNode = EliminateNode(subRoot->left, data);
		subRoot->left = leftNode;
	}
	else if (data > subRoot->value )//check the right branch
	{
		nodeptr rightNode;
		rightNode = EliminateNode(subRoot->right, data);
		subRoot->right = rightNode;
	}
	else // node found
	{
		nodeptr deleteNode;//Transfer data from the found node to this deletenODE
		deleteNode = subRoot;
		//check if deleteNode doesnt have left child
		if (deleteNode->left == nullptr)
			subRoot = deleteNode->right;
		//check if deleteNode doesnt have right child
		else if (deleteNode->right == nullptr)
			subRoot = deleteNode->left;
		else//if have 2 child nodes
			deleteNode = ReplaceNode(deleteNode);
			//to keep structure, replace the node data with the largest of the minor keys in the subtree
	
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

		Como las claves menores están en la rama izquierda, se baja al primer nodo de la rama izquierda, 
		y se continúa bajando por las ramas derecha (claves mayores) hasta alcanzar el nodo que no tiene rama derecha. 
		Éste es el mayor de los menores, cuyo dato debe reemplazar al del nodo a eliminar. 
		Lo que se hace es copiar el valor del dato y enlazar su padre con el hijo izquierdo. 

	*/
	nodeptr a, p;
	p = changeNode;
	a = changeNode->left;//all the left tree branch
	while (a->right != nullptr)//travel the tree from that rightbranch
	{
		p = a;
		a = a->right;
	}
	//copy in 'changeNode' the value of the node 'a' is pointing to
	changeNode->value = a->value;

	//'a' is the new left child of 'changeNode'
	if (p == changeNode)
		p->left = a->left;//link left branch
	else
		p->right = a->right;//link right branch
	
	return a;
}

	void getShortestPath(nodeptr root, olc::PixelGameEngine* pge)
	{
		//find path
		/*
			in index 0 = store the node we want the path
			in index n = store the node structure to that path
		*/

		std::vector<nodeptr> nodeptrList;
		nodeptrList.push_back(root);
		
		bool search = true;
		while (search) 
		{
			if (nodeptrList.back() == m_root)
				search = false;
			else //add the parent of the node in that iteration, until found the node
				nodeptrList.push_back( getParentNode( nodeptrList.back()->value ) );
		}

		//print path
		int x = 25;
		int y = 125;
		while (nodeptrList.size() > 1) 
		{
			std::string pathText = "FROM " + std::to_string(nodeptrList.back()->value) + " TO " + std::to_string(nodeptrList.at(nodeptrList.size() - 2)->value);

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
		//we traverse the tree
		while (root != nullptr)
		{
			if (data < root->value)//left
			{
				parentNode = root;//posible parent
				root = root->left;
			}
			else if (data > root->value)//right
			{
				parentNode = root;
				root = root->right;
			}
			else break;//if value = data then, we found the node 
		}

		return parentNode;
	}

	int getLeafNodesAmount(nodeptr root)
	{
		if (root == nullptr)
			return 0;
		if (root->left == nullptr && root->right == nullptr)
			return 1;
		else
			return getLeafNodesAmount(root->left) + getLeafNodesAmount(root->right);
		
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
		if (root->value == data)
			return level;

		int downlevel = getLevelNode(root->left, data, level + 1);
		
		if (downlevel != 0)
			return downlevel;

		downlevel = getLevelNode(root->right, data, level + 1);

		return downlevel;

	}
	
	nodeptr getBrotherNode(nodeptr node)
	{	
		nodeptr parent = getParentNode( node->value );//we search for parent of that node

		if (parent != nullptr)//if parent found...
		{
			nodeptr parentleftChild = parent->left;
			nodeptr parentRightChild = parent->right;
		
			//compare childs value
			if (parentleftChild != nullptr && parentRightChild == nullptr)//if have only left child
			{
				if (parentleftChild->value != node->value)//if not the same
					return parentleftChild;
				else
					return nullptr;//if equal, return null, doesnt have a brother
			}
			else if (parentleftChild == nullptr && parentRightChild != nullptr)//solo el derecho
			{
				if (parentRightChild->value != node->value)
					return parentRightChild;
				else
					return nullptr;//porque encontro el mismo nodo q llamo la funcion osea no tiene hermano
			}
			else if (parentleftChild != nullptr && parentRightChild != nullptr)//ambos hijos
			{
				if (parentleftChild->value != node->value && parentRightChild->value == node->value)//if left not equal return it
					return parentleftChild;
				else if (parentleftChild->value == node->value && parentRightChild->value != node->value)//if right not equal return it
					return parentRightChild;
			}
			
		}
		else//if doesnt have parent, then doesnt have a brother
			return nullptr;
	}

	int LenghtOfaNode(int data)
	{
		nodeptr current = m_root;
		int iter = 0;

		//traverse the tree
		while (current->value != data) {

			if (current != NULL)
			{
				iter++;
				//go to left tree
				if (current->value > data)
					current = current->left;
				  //else go to right tree
				else
					current = current->right;

				//not found
				if (current == NULL)
					return 0;

			}
		}

		return iter;
	}


	void PreOrder(nodeptr root, std::string& container)
	{
		//RAIZ - IZQ - DERECHA
		if (root != nullptr)//proccess 
			container += std::to_string(root->value) + " - ";
		
		if (root != nullptr && root->left != nullptr)//si hay lado izq
			PreOrder(root->left, container);
		if (root != nullptr && root->right != nullptr)//si hay lado der
			PreOrder(root->right, container);
	}
	
	
	void InOrder(nodeptr root, std::string& container)
	{
		//IZQ - RAIZ -DERECHA
		if (root != nullptr && root->left != nullptr)//left branch
			InOrder(root->left, container);
		
		if (root != nullptr)//process you want to do
			container += std::to_string(root->value) + " - ";

		if (root != nullptr && root->right != nullptr)//right branch
			InOrder(root->right, container);
	}


	void PostOrder(nodeptr root, std::string& container)
	{
		//IZQ - DER- RAIZ
		if (root != nullptr && root->left != nullptr)
			PostOrder(root->left, container);
		if (root != nullptr && root->right != nullptr)
			PostOrder(root->right, container);
		
		if (root != nullptr)//process
			container += std::to_string(root->value) + " - ";
	}


};

// Binary Expression Tree functions 
// TODO: Convert all this magic into a class

//typedef NodeBET* BETptr;

struct NodeBET 
{
public:
	char letter;
	NodeBET* right;
	NodeBET* left;

	NodeBET(char data);
};

NodeBET::NodeBET(char data)
{
	letter = data;
	right = left = nullptr;
}




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
	//else if (op == '*' || op == '/') weight = 2;
	else if (op == '*') weight = 2;
	else if (op == '/') weight = 3;
	else if (op == '^' ) weight = 4;
	
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

//most important function
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
			newNode->right = t1;
			newNode->left = t2;

			//add to stack
			stack.push(newNode);
		}
		
	}

	//top elemet will be the root of the expression tree
	output = stack.top();
	stack.pop();

	return output;
}

