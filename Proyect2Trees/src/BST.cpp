#include"BST.h"

BST::BST()
{
	m_root = nullptr;
}

BST::BST(nodeptr r) { m_root = r; }

void BST::setRoot(nodeptr r) { m_root = r; }

nodeptr BST::getRoot() { return m_root; }

Node BST::getRootDirection()
{
	if (m_root)
		return *m_root;
	else
		throw "empty tree";
}

nodeptr BST::getLeftChildNode()
{
	if (m_root)
		return m_root->left;
	else
		throw " no left tree";
}

nodeptr BST::getRightChildNode()
{
	if (m_root)
		return m_root->right;
	else
		throw " no right tree";
}

nodeptr BST::newTree(nodeptr leftBranch, int data, nodeptr rightBranch)
{
	return new Node(data, leftBranch, rightBranch);
}

void BST::DeleteTree(nodeptr root)
{
	if (root != nullptr)
	{ //post order track
		DeleteTree(root->left);
		DeleteTree(root->right);
		std::cout << "\nNode deleted. ";
		root = nullptr;
	}
}

int BST::HeightTree(nodeptr root)
{
	if (root == nullptr) //empty tree
		return 0;
	else
	{
		int leftHeight = HeightTree(root->left);
		int rightHeight = HeightTree(root->right);
		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}

int BST::NodesAmount(nodeptr root)
{
	if (root == nullptr)
		return 0;
	else
		return 1 + NodesAmount(root->left) + NodesAmount(root->right);
}

bool BST::IsComplete(nodeptr root)
{
	if (root == nullptr)
		return true;
	else
	{
		if (HeightTree(root->left) != HeightTree(root->right))
			return false;
	}
	return IsComplete(root->left) && IsComplete(root->right);
}

bool BST::isEmpty() { return m_root == nullptr; }

void BST::InsertNode(int data)
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

nodeptr BST::Search(int data)
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


void BST::EliminateNode(int data)
{
	m_root = EliminateNode(m_root, data);//send the modify tree structure to root node
}

nodeptr BST::EliminateNode(nodeptr subRoot, int data)
{
	//in case that node doesnt exit
	if (subRoot == nullptr)
		std::cout << "The node was not found in tree\n";
	else if (data < subRoot->value)//check left branch
	{
		nodeptr leftNode;
		leftNode = EliminateNode(subRoot->left, data);
		subRoot->left = leftNode;
	}
	else if (data > subRoot->value)//check the right branch
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

nodeptr BST::ReplaceNode(nodeptr changeNode)
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

void BST::getShortestPath(nodeptr root, olc::PixelGameEngine* pge)
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
			nodeptrList.push_back(getParentNode(nodeptrList.back()->value));
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
nodeptr BST::getParentNode(int data)
{
	return getParentNode(m_root, data);
}
//node parent algorithm
nodeptr BST::getParentNode(nodeptr root, int data)
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

int BST::getLeafNodesAmount(nodeptr root)
{
	if (root == nullptr)
		return 0;
	if (root->left == nullptr && root->right == nullptr)
		return 1;
	else
		return getLeafNodesAmount(root->left) + getLeafNodesAmount(root->right);

}

int BST::getLevelNode(nodeptr root, int data, int level)
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

nodeptr BST::getBrotherNode(nodeptr node)
{
	nodeptr parent = getParentNode(node->value);//we search for parent of that node

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

int BST::LenghtOfaNode(int data)
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


void BST::PreOrder(nodeptr root, std::string& container)
{
	//RAIZ - IZQ - DERECHA
	if (root != nullptr)//proccess 
		container += std::to_string(root->value) + " - ";

	if (root != nullptr && root->left != nullptr)//si hay lado izq
		PreOrder(root->left, container);
	if (root != nullptr && root->right != nullptr)//si hay lado der
		PreOrder(root->right, container);
}


void BST::InOrder(nodeptr root, std::string& container)
{
	//IZQ - RAIZ -DERECHA
	if (root != nullptr && root->left != nullptr)//left branch
		InOrder(root->left, container);

	if (root != nullptr)//process you want to do
		container += std::to_string(root->value) + " - ";

	if (root != nullptr && root->right != nullptr)//right branch
		InOrder(root->right, container);
}


void BST::PostOrder(nodeptr root, std::string& container)
{
	//IZQ - DER -RAIZ
	if (root != nullptr && root->left != nullptr)//left branch
		PostOrder(root->left, container);

	if (root != nullptr && root->right != nullptr)//right branch
		PostOrder(root->right, container);
	
	if (root != nullptr)//process you want to do
		container += std::to_string(root->value) + " - ";
}