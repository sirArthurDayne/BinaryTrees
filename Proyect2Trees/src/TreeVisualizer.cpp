#include"TreeVisualizer.h"

//NODES OBJECTS
NodeBET* rootBETnode;
nodeptr rootBSTnode(nullptr);
BST bstTree(rootBSTnode);

//CONSTRUCTOR
TreeVisualizer::TreeVisualizer()
{
	sAppName = "BINARY TREES VISUALIZE by Xavier(SirArthurDayne)";
}

//ENGINE OVERRIDE FUNCTIONS
bool TreeVisualizer::OnUserCreate() 
{
	state = PRESENTATION;//setup default state
	//setup menus
	bstMenuOption = 1;
	betMenuOption = 1;

	return true;
}

bool TreeVisualizer::OnUserUpdate(float fElapsedTime) 
{
	Clear(olc::VERY_DARK_BLUE);

	if (state == PRESENTATION)
		DrawPresentation();
	//init 0
	else if (state == MAIN_MENU)
		DrawMainMenu();

	///////1. BST STATES///////
	else if (state == BST_MENU)
		DrawBstMenu();

	else if (state == BST_INSERT_MODE)//1.1
	{
		if (DrawInsertMode())
			state = BST_MENU;
	}
	
	else if (state == BST_DELETE_MODE)//1.2
	{
		if (DrawDeleteBstNode())
			state = BST_MENU;
	}
	
	else if (state == BST_TREE)//1.3
	{
		Clear(olc::BLACK);
		if (DrawBSTree(bstTree.getRoot(), ScreenWidth() / 2, 0, ScreenWidth() / 2, 30, ScreenWidth() * 0.20, ScreenHeight() * 0.20))//letter is the data
			state = BST_MENU;
	}
	else if (state == NODE_INFO)//1.4
	{
		if (DrawNodeInfo())
			state = BST_MENU;
	}
	
	else if (state == TREE_INFO)//1.5
	{
		if (DrawBSTreeInfo())
			state = BST_MENU;
	}
	
	else if (state == BST_TRAVERSAL)//1.6
	{
		if (DrawBstTraversalls())
			state = BST_MENU;
	}
	

	///////2. BET STATES///////
	else if (state == BET_MENU)
		DrawBetMenu();

	else if (state == BET_INSERT_MODE)//2.1
	{
		if (DrawBETInsertMode())
			state = BET_MENU;
	}

	
	else if (state == BET_TREE)
	{
		Clear(olc::BLACK);
		if (DrawBETree(rootBETnode, ScreenWidth() / 2, 0, ScreenWidth() / 2, 30, ScreenWidth() * 0.20, ScreenHeight() * 0.20))
			state = BET_MENU;
	}
	else if (state == BET_TRAVERSAL)
	{
		if (DrawBETTraversals())
			state = BET_MENU;
	}


	if (GetKey(olc::ESCAPE).bReleased)
		return false;

	return true;
}


//MENUS 
void TreeVisualizer::DrawPresentation()
{
	Clear(olc::BLACK);


	DrawString(ScreenWidth() / 2 - 90, 160, "DATA STRUCTURE PROYECT: BINARY TREES");

	DrawString(ScreenWidth() / 2 - 80, 250, "DEVELOP BY: ");
	DrawString(ScreenWidth() / 2 - 100, 300, "LAMELA, XAVIER (SirArthurDayne)");

	DrawString(ScreenWidth() / 2 - 120, ScreenHeight() - 50, "SPECIAL THANKS TO ZLEAPINGBEAR");
	DrawString(ScreenWidth() - 200, ScreenHeight() - 25, "'CLICK' TO CONTINUE...");

	if (GetMouse(0).bPressed)
		state = MAIN_MENU;
}

void TreeVisualizer::DrawMainMenu()
{
	DrawString(ScreenWidth() / 2 - 50, 20, "MAIN MENU");

	FillRect(ScreenWidth() / 2 - 100, 90, 230, 20, olc::DARK_RED);
	DrawString(ScreenWidth() / 2 - 100, 100, "1. BINARY SEARCH TREE");

	FillRect(ScreenWidth() / 2 - 100, 140, 230, 20, olc::DARK_GREEN);
	DrawString(ScreenWidth() / 2 - 100, 150, "2. BINARY EXPRESSION TREE");

	DrawString(ScreenWidth() / 2 - 100, 360, "CLICK TO SELECT...");


	//INPUT
	if (GetMouse(0).bReleased)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if (mouseX > ScreenWidth() / 2 - 100 && mouseX < (ScreenWidth() / 2 - 100) + 90 && mouseY > 90 && mouseY < 120)
			state = BST_MENU;

		else if (mouseX > ScreenWidth() / 2 - 100 && mouseX < (ScreenWidth() / 2 - 100) + 200 && mouseY > 140 && mouseY < 160)
			state = BET_MENU;
	}

}

void TreeVisualizer::DrawBetMenu()
{
	Clear(olc::VERY_DARK_GREEN);


	if (betMenuOption > 3 || betMenuOption < 1) betMenuOption = 1;

	//keys input
	if (GetKey(olc::Key::UP).bPressed) betMenuOption--;
	else if (GetKey(olc::Key::DOWN).bPressed) betMenuOption++;

	//mouse input
	int mouseX = GetMouseX();
	int mouseY = GetMouseY() / 20 + 20;


	if (mouseX > 250 && mouseX < 350 && mouseY == 20) betMenuOption = 1;
	else if (mouseX > 250 && mouseX < 350 && mouseY == 21) betMenuOption = 2;
	else if (mouseX > 250 && mouseX < 350 && mouseY == 22) betMenuOption = 3;

	//selected
	FillRect(ScreenWidth() / 2 - 100, 20 * betMenuOption, 200, 11, olc::VERY_DARK_GREY);
	DrawRect(ScreenWidth() / 2 - 100, 20 * betMenuOption, 200, 11, olc::WHITE);

	//button text
	DrawString(ScreenWidth() / 2 - 310, 10, "BINARY EXPRESSION TREE");
	DrawString(ScreenWidth() / 2 - 100, 20, "1. INSERT EXPRESSION", olc::WHITE);
	DrawString(ScreenWidth() / 2 - 100, 40, "2. SEE TREE", olc::WHITE);
	DrawString(ScreenWidth() / 2 - 100, 60, "3. TRAVERSALS:", olc::WHITE);
	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);

	//option selected
	if (GetMouse(0).bReleased || GetKey(olc::Key::ENTER).bReleased)//choose
	{
		if (betMenuOption == 1)
			state = BET_INSERT_MODE;
		else if (betMenuOption == 2)
			state = BET_TREE;
		else if (betMenuOption == 3)
			state = BET_TRAVERSAL;
	}

	//exit
	if (GetKey(olc::Key::M).bReleased)
		state = MAIN_MENU;
}

void TreeVisualizer::DrawBstMenu()
{
	Clear(olc::VERY_DARK_BLUE);

	if (bstMenuOption > 6 || bstMenuOption < 1) bstMenuOption = 1;

	if (GetKey(olc::Key::UP).bReleased) bstMenuOption--;

	else if (GetKey(olc::Key::DOWN).bReleased) bstMenuOption++;


	int mouseX = GetMouseX();
	int mouseY = GetMouseY() / 20 + 20;


	if (mouseX > 250 && mouseX < 350 && mouseY == 20) bstMenuOption = 1;
	else if (mouseX > 250 && mouseX < 350 && mouseY == 21) bstMenuOption = 2;
	else if (mouseX > 250 && mouseX < 350 && mouseY == 22) bstMenuOption = 3;
	else if (mouseX > 250 && mouseX < 350 && mouseY == 23) bstMenuOption = 4;
	else if (mouseX > 250 && mouseX < 350 && mouseY == 24) bstMenuOption = 5;
	else if (mouseX > 250 && mouseX < 350 && mouseY == 25) bstMenuOption = 6;

	//selected text
	FillRect(ScreenWidth() / 2 - 100, (20 * bstMenuOption), 200, 11, olc::VERY_DARK_GREY);
	DrawRect(ScreenWidth() / 2 - 100, 20 * bstMenuOption, 200, 11, olc::WHITE);

	//button text
	DrawString(ScreenWidth() / 2 - 310, 10, "BINARY SEARCH TREE");
	DrawString(ScreenWidth() / 2 - 100, 20, "1. INSERT NODE IN TREE", olc::WHITE);
	DrawString(ScreenWidth() / 2 - 100, 40, "2. DELETE NODE IN TREE", olc::WHITE);
	DrawString(ScreenWidth() / 2 - 100, 60, "3. SEE TREE ", olc::WHITE);
	DrawString(ScreenWidth() / 2 - 100, 80, "4. RETRIEVE INFO ABOUT NODE", olc::WHITE);
	DrawString(ScreenWidth() / 2 - 100, 100, "5. RETRIEVE INFO ABOUT TREE ", olc::WHITE);
	DrawString(ScreenWidth() / 2 - 100, 120, "6. TRAVERSALS:", olc::WHITE);



	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);




	//option selected
	if (GetMouse(0).bReleased || GetKey(olc::Key::ENTER).bReleased)//choose
	{
		if (bstMenuOption == 1)
			state = BST_INSERT_MODE;
		else if (bstMenuOption == 2)
			state = BST_DELETE_MODE;
		else if (bstMenuOption == 3)
			state = BST_TREE;
		else if (bstMenuOption == 4)
			state = NODE_INFO;
		else if (bstMenuOption == 5)
			state = TREE_INFO;
		else if (bstMenuOption == 6)
			state = BST_TRAVERSAL;
	}

	//exit
	if (GetKey(olc::Key::M).bReleased)
	{
		state = MAIN_MENU;
		bstMenuOption = 1;
	}
}


//BST DRAW FUNCTIONS

bool TreeVisualizer::DrawInsertMode()
{
	Clear(olc::VERY_DARK_CYAN);
	//title	
	DrawString(10, 20, "PRESS 'ENTER' TO INSERT: ");
	static int number = 0;
	//input 
	if (GetKey(olc::Key::K0).bReleased) number = number * 10 + 0;
	if (GetKey(olc::Key::K1).bReleased) number = number * 10 + 1;
	if (GetKey(olc::Key::K2).bReleased) number = number * 10 + 2;
	if (GetKey(olc::Key::K3).bReleased) number = number * 10 + 3;
	if (GetKey(olc::Key::K4).bReleased) number = number * 10 + 4;
	if (GetKey(olc::Key::K5).bReleased) number = number * 10 + 5;
	if (GetKey(olc::Key::K6).bReleased) number = number * 10 + 6;
	if (GetKey(olc::Key::K7).bReleased) number = number * 10 + 7;
	if (GetKey(olc::Key::K8).bReleased) number = number * 10 + 8;
	if (GetKey(olc::Key::K9).bReleased) number = number * 10 + 9;
	if (GetKey(olc::Key::BACK).bReleased) number /= 10;
	//input number insertion
	DrawString(10, 100, "INSERTING NUMBER: " + std::to_string(number), olc::RED);
	if (GetKey(olc::Key::ENTER).bReleased)
	{
		userNumberList.push_back(number);
		number = 0;
	}

	//draw list
	DrawString(20, 50, "NODE LIST (START FROM ROOT):");
	for (int i = 0; i < userNumberList.size(); i++)
		DrawString(300, 50 + (i * 10), std::to_string(userNumberList.at(i)));
	//exit & insert nodes in tree
	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);
	if (GetKey(olc::Key::M).bReleased)
	{
		//add this to bst class
		for (int i = 0; i < userNumberList.size(); i++)
		{
			bstTree.InsertNode(userNumberList.at(i));//finnally NODE STUFF
		}
		userNumberList.clear();
		bstMenuOption = 1;
		return true;
	}
	return false;
}

bool TreeVisualizer::DrawDeleteBstNode()//NOT COMPLETED
{
	//title 
	Clear(olc::VERY_DARK_BLUE);
	DrawString(10, 20, "PRESS 'ENTER' TO DELETE: ");
	//input 
	static int number = 0;
	if (GetKey(olc::Key::K0).bReleased) number = number * 10 + 0;
	if (GetKey(olc::Key::K1).bReleased) number = number * 10 + 1;
	if (GetKey(olc::Key::K2).bReleased) number = number * 10 + 2;
	if (GetKey(olc::Key::K3).bReleased) number = number * 10 + 3;
	if (GetKey(olc::Key::K4).bReleased) number = number * 10 + 4;
	if (GetKey(olc::Key::K5).bReleased) number = number * 10 + 5;
	if (GetKey(olc::Key::K6).bReleased) number = number * 10 + 6;
	if (GetKey(olc::Key::K7).bReleased) number = number * 10 + 7;
	if (GetKey(olc::Key::K8).bReleased) number = number * 10 + 8;
	if (GetKey(olc::Key::K9).bReleased) number = number * 10 + 9;
	if (GetKey(olc::Key::BACK).bReleased) number /= 10;
	//output text
	DrawString(10, 50, "DELETING NUMBER: " + std::to_string(number), olc::RED);
	//delete function call
	if (GetKey(olc::Key::ENTER).bReleased)
	{
		bstTree.EliminateNode(number);
		number = 0;
	}
	//exit of mode 
	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);
	if (GetKey(olc::Key::M).bReleased)
	{
		bstMenuOption = 1;
		return true;
	}
	return false;
}

bool TreeVisualizer::DrawNodeInfo()
{
	//choose the node to extract info
	Clear(olc::VERY_DARK_RED);

	//INPUT
	static int testNode = 0;
	if (GetKey(olc::Key::K0).bReleased) testNode = testNode * 10 + 0;
	if (GetKey(olc::Key::K1).bReleased) testNode = testNode * 10 + 1;
	if (GetKey(olc::Key::K2).bReleased) testNode = testNode * 10 + 2;
	if (GetKey(olc::Key::K3).bReleased) testNode = testNode * 10 + 3;
	if (GetKey(olc::Key::K4).bReleased) testNode = testNode * 10 + 4;
	if (GetKey(olc::Key::K5).bReleased) testNode = testNode * 10 + 5;
	if (GetKey(olc::Key::K6).bReleased) testNode = testNode * 10 + 6;
	if (GetKey(olc::Key::K7).bReleased) testNode = testNode * 10 + 7;
	if (GetKey(olc::Key::K8).bReleased) testNode = testNode * 10 + 8;
	if (GetKey(olc::Key::K9).bReleased) testNode = testNode * 10 + 9;
	if (GetKey(olc::Key::BACK).bReleased) testNode /= 10;

	DrawString(20, 50, std::to_string(testNode), olc::WHITE);

	static bool printInfo = false;

	if (GetKey(olc::Key::ENTER).bReleased)
		printInfo = true;

	if (printInfo)
	{
		nodeptr node = bstTree.Search(testNode);
		//level
		std::string level = "LEVEL: " + std::to_string(bstTree.getLevelNode(bstTree.getRoot(), testNode));
		DrawString(25, 75, level);
		//length to get there
		std::string lenght = "LENGHT: " + std::to_string(bstTree.LenghtOfaNode(testNode));
		DrawString(25, 100, lenght);
		//closeth path
		bstTree.getShortestPath(node, this);
		//father
		nodeptr parent = bstTree.getParentNode(testNode);
		std::string parentText;
		if (parent != nullptr) parentText = "FATHER NODE: " + std::to_string(parent->value);
		else parentText = "FATHER NOT FOUND";
		DrawString(25, 200, parentText);

		//sibling
		nodeptr brother = bstTree.getBrotherNode(node);
		int brotherValue = (brother != nullptr) ? brother->value : 0;
		std::string brotherText = "BROTHER OF: " + std::to_string(testNode) + " IS " + std::to_string(brotherValue);
		DrawString(25, 225, brotherText);

		//childs y grade(amount of childs)
		int leftChild = (node->left != nullptr) ? node->left->value : 0;
		int rightChild = (node->right != nullptr) ? node->right->value : 0;

		int grade = 0;
		std::string sonsText = "";
		std::string gradeText = "";

		if (rightChild != 0 && leftChild != 0) grade = 2;
		else if ((rightChild == 0 && leftChild != 0) || (leftChild == 0 && rightChild != 0)) grade = 1;
		else grade = 0;

		gradeText = "GRADE: " + std::to_string(grade);
		sonsText = "RIGHT CHILD: " + std::to_string(rightChild) + " LEFT CHILD: " + std::to_string(leftChild);
		DrawString(25, 250, gradeText);
		DrawString(25, 275, sonsText);
	}


	if (GetKey(olc::Key::M).bReleased)
	{
		printInfo = false;
		testNode = 0;
		state = BST_MENU;
	}

	return false;
}

bool TreeVisualizer::DrawBSTree(nodeptr root, int lineFromX, int lineFromY, int x, int y, int incX, int incY)
{

		DrawLine(lineFromX, lineFromY, x, y, olc::DARK_GREEN);

		if (root->left != nullptr)
			DrawBSTree(root->left, x, y, x - incX, y + incY, incX * 0.5, incY);

		if (root->right != nullptr)
			DrawBSTree(root->right, x, y, x + incX, y + incY, incX * 0.5, incY);
		FillCircle(x, y, 12, olc::DARK_RED);//color of nodes

			//DRAW THE NODES
			if (root->left == nullptr && root->right == nullptr)//LEAF NODE
			{
				DrawCircle(x, y, 12, olc::MAGENTA);
				DrawString(x - 4, y - 2, std::to_string(root->value), olc::WHITE);
			}
			else
			{
				DrawCircle(x, y, 12, olc::YELLOW);
				DrawString(x - 4, y - 2, std::to_string(root->value), olc::WHITE);
			}

	if (GetKey(olc::Key::M).bReleased)
		return true;

	return false;
}

bool TreeVisualizer::DrawBSTreeInfo()
{
	//title
	Clear(olc::VERY_DARK_GREY);
	DrawString(ScreenWidth() / 2 - 100, 25, "INFORMATION ABOUT TREE", olc::WHITE);

	//calculations
	nodeptr root     = bstTree.getRoot();
	int heightofTree = bstTree.HeightTree(root);
	int totalNodes   = bstTree.NodesAmount(root);
	int leafNodes    = bstTree.getLeafNodesAmount(root);
	bool isComplete  = bstTree.IsComplete(root);

	std::string heighText = "HEIGHT OF TREE: " + std::to_string(heightofTree);
	std::string totalText = "TOTAL NODES: " + std::to_string(totalNodes);
	std::string amountText = "AMOUNT OF LEAF NODES: " + std::to_string(leafNodes);
	std::string completeText = (isComplete) ? "IS COMPLETE?: YES" : "IS COMPLETE?: NO";

	//output
	DrawString(ScreenWidth() - 450, 50, heighText, olc::WHITE);
	DrawString(ScreenWidth() - 450, 100, totalText, olc::WHITE);
	DrawString(ScreenWidth() - 450, 150, amountText, olc::WHITE);
	DrawString(ScreenWidth() - 450, 200, completeText, olc::WHITE);
	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);
	if (GetKey(olc::Key::M).bReleased)
		return true;

	return false;
}

bool TreeVisualizer::DrawBstTraversalls()
{
	//title
	Clear(olc::VERY_DARK_GREEN);
	DrawString(ScreenWidth() / 2 - 100, 25, "RECORRIDOS", olc::WHITE);

	//calculations
	nodeptr root = bstTree.getRoot();

	std::string preorderText = "PREORDEN: ";
	std::string inorderText = "INORDEN: ";
	std::string postorderText = "POSTORDEN: ";

	bstTree.PreOrder(root, preorderText);
	bstTree.InOrder(root, inorderText);
	bstTree.PostOrder(root, postorderText);

	//output
	DrawString(25, 50, preorderText, olc::WHITE);
	DrawString(25, 100, inorderText, olc::WHITE);
	DrawString(25, 150, postorderText, olc::WHITE);
	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);
	//exit
	if (GetKey(olc::Key::M).bReleased)
		return true;

	return false;
}

//BET DRAW FUNCTIONS
bool TreeVisualizer::DrawBETInsertMode()
{
	//title
	Clear(olc::VERY_DARK_GREEN);
	DrawString(10, 20, "PRESS 'ENTER' FOR EXPRESSION: ");
	static std::string testExpression = "";
	static bool reading = true;
	//Capture Input
	if (reading)
	{
		text.updateField();
		testExpression = text.getString();
		DrawString(100, 100, testExpression, olc::WHITE);
	}
	else
		DrawString(20, 150, "VALID EXPRESSION!");
	//validate expresion 
	if (GetKey(olc::Key::ENTER).bReleased && rootBETnode->isBalanced(testExpression))
	{
		userInfixExpression = testExpression;//transfer valid expression data
		reading = false;
	}
	//creating the tree & exit 
	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);
	if (GetKey(olc::Key::M).bReleased)
	{
		testExpression = "";
		reading = true;
		//preparing for making tree
		std::string posfix = rootBETnode->ConvertToPosfix(userInfixExpression);
		//root node of BET class
		rootBETnode = rootBETnode->ConstructTree(posfix);
		return true;
	}

	return false;
}

bool TreeVisualizer::DrawBETree(NodeBET* root, int lineFromX, int lineFromY, int x, int y, int incX, int incY)
{

		DrawLine(lineFromX, lineFromY, x, y, olc::DARK_GREEN);

		if (root->left != nullptr)
			DrawBETree(root->left, x, y, x - incX, y + incY, incX * 0.5, incY);

		if (root->right != nullptr)
			DrawBETree(root->right, x, y, x + incX, y + incY, incX * 0.5, incY);

		FillCircle(x, y, 12, olc::DARK_RED);//color of nodes

		if (root->left == nullptr && root->right == nullptr)//LEAF NODE
		{
			DrawCircle(x, y, 12, olc::MAGENTA);
			std::string c = "";
			DrawString(x - 4, y - 2, c += root->letter, olc::WHITE);
		}
		else
		{//parent nodes
			DrawCircle(x, y, 12, olc::YELLOW);
			std::string c = "";
			DrawString(x - 4, y - 2, c += root->letter, olc::WHITE);
		}


	if (GetKey(olc::Key::M).bReleased)
		return true;

	return false;
}

bool TreeVisualizer::DrawBETTraversals()
{
	Clear(olc::VERY_DARK_BLUE);
	DrawString(ScreenWidth() / 2 - 100, 25, "TRAVERSALS", olc::WHITE);

	std::string prefixText = "";
	std::string infixText = "";
	std::string posfixText = "";

	infixText = userInfixExpression;
	posfixText = rootBETnode->ConvertToPosfix(userInfixExpression);
	prefixText = rootBETnode->ConvertToPrefix(posfixText);

	//output
	DrawString(25, 50, "PREFIX: " + prefixText, olc::WHITE);
	DrawString(25, 100, "INFIX: " + infixText, olc::WHITE);
	DrawString(25, 150, "POSTFIX: " + posfixText, olc::WHITE);

	DrawString(ScreenWidth() / 2 + 100, ScreenHeight() - 25, "PRESS 'M' FOR MENU", olc::WHITE);


	if (GetKey(olc::Key::M).bReleased)
		return true;

	return false;
}