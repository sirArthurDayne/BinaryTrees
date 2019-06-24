#pragma once
#include"BST.h"

static int screenW = 640, screenH = 480;

//Nodes class objects
NodeBET* rootBETnode;
nodeptr rootBSTnode(nullptr);
BST bstTree(rootBSTnode);


//state machine
enum STATES {
	MAIN_MENU, BST_MENU, BST_INSERT_MODE, BST_DELETE_MODE, BST_TREE, BET_MENU, NODE_INFO, TREE_INFO, BST_TRAVERSAL
};

/////////////////////////////////// THIS IS FOR ALL THE STUFF YOU NORMALY DO IN THE PGE.... /////////////////////////////////
class TreeVisualizer : public olc::PixelGameEngine
{
private:
	//setting
	STATES state;

	
	
	
	//user stores
	std::vector<int> userNumberList;//user array for BST
	std::string userInfixExpression;//user array for BET

	//menu vars
	int bstMenuOption;
	int betMenuOption;

public:
	TreeVisualizer()
	{
		sAppName = "Proyect 2 Binary Trees";
	}
public:
	bool OnUserCreate() override
	{
		state = MAIN_MENU;//setup default
		
		
		bstMenuOption = 1;
		betMenuOption = 1;

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_BLUE);

		//init
		if (state == MAIN_MENU)
			DrawMainMenu();
		//option1
		else if (state == BST_MENU)
			DrawBstMenu();
		
		else if (state == BST_INSERT_MODE)//1.1
		{
			if (InsertNodeMode(fElapsedTime))
				state = BST_MENU;
		}
		else if (state == BST_DELETE_MODE)//1.2
		{
			if (DeleteNodeMode(fElapsedTime))
				state = BST_MENU;
		}
		else if (state == BST_TREE)//1.3
		{
			Clear(olc::BLACK);
			if ( DrawBSTree(bstTree.getRoot(),ScreenWidth()/2, 0, ScreenWidth() / 2, 30, ScreenWidth() * 0.20, ScreenHeight() * 0.20))//letter is the data
				state = BST_MENU;
		}
		else if (state == NODE_INFO)//1.4
		{
			if (DrawNodeInfo(fElapsedTime))
				state = BST_MENU;
		}
		else if (state == TREE_INFO)//1.5
		{
			if (DrawBSTreeInfo())
				state = BST_MENU;
		}
		else if (state == BST_TRAVERSAL)
		{
			
		}
		//option2
		else if (state == BET_MENU)
			DrawBetMenu();

		if (GetKey(olc::ESCAPE).bReleased)
			return false;

		return true;
	}
	
	void DrawMainMenu()
	{
		DrawString(ScreenWidth() /2 - 100, 20, "BINARY TREES PROYECT 2");
		
		FillRect(ScreenWidth() / 2 - 100, 90, 200, 20, olc::DARK_RED);
		DrawString(ScreenWidth() /2 - 100 , 100, "1. BINARY SEARCH TREE");
		
		FillRect(ScreenWidth() / 2 - 100, 140, 200, 20, olc::DARK_GREEN);
		DrawString(ScreenWidth() /2 - 100 , 150, "2. BINARY EXPRESSION TREE");

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

	void DrawBetMenu()
	{
		Clear(olc::VERY_DARK_GREEN);


		int option = 1;
		if (option > 6 || option < 1) option = 1;

		if (GetKey(olc::Key::UP).bPressed)
			option++;
		else if (GetKey(olc::Key::DOWN).bPressed)
			option--;

		FillRect(ScreenWidth() / 2 - 100, 20 + (16 * ((option - 1) / 2)), 200, 11, olc::VERY_DARK_GREY);
		DrawRect(ScreenWidth() / 2 - 100, 20 + (16 * ((option - 1) / 2)), 200, 11, olc::WHITE);


		DrawString(ScreenWidth() / 2 - 100, 20, "1. Insert Expression", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 100, 40, "2. See Tree ", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 100, 60, "3. Traversal:", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 100, 80, "  3.1 PREORDER", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 100, 100, "  3.2 INORDER", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 100, 120, "  3.3 POSTORDER", olc::WHITE);



		if (GetKey(olc::Key::M).bReleased)
			state = MAIN_MENU;
	}

	void DrawBstMenu()
	{
		Clear(olc::VERY_DARK_BLUE);

		if(bstMenuOption > 6 || bstMenuOption < 1) bstMenuOption = 1;
		  
		if(GetKey(olc::Key::UP).bReleased) bstMenuOption--;

		else if (GetKey(olc::Key::DOWN).bReleased) bstMenuOption++;

		
			int mouseX = GetMouseX();
			int mouseY = GetMouseY() / 20 + 20;
			std::cout << "mouseX:" << mouseX << "mouseY" << mouseY << std::endl;

			if		(mouseX > 250 && mouseX < 350 && mouseY == 20 ) bstMenuOption = 1;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 21 ) bstMenuOption = 2;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 22 ) bstMenuOption = 3;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 23 ) bstMenuOption = 4;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 24 ) bstMenuOption = 5;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 25 ) bstMenuOption = 6;
		
			FillRect(ScreenWidth()/2 -100, (20 * bstMenuOption), 200, 11, olc::VERY_DARK_GREY);
			DrawRect(ScreenWidth()/2 -100, 20 * bstMenuOption, 200, 11, olc::WHITE);

		//button text
		DrawString(ScreenWidth() /2- 100, 20, "1. Insert Node to tree", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 40, "2. Delete Node from tree", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 60, "3. See Tree ", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 80, "4. Info about a node", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 100, "5. Info about tree ", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 120, "6. Traversal:", olc::WHITE);

		DrawString(ScreenWidth() /2+ 100 , ScreenHeight() - 25, "Press M to MainMenu", olc::WHITE);


		
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
		
	
		if (GetKey(olc::Key::M).bReleased)
		{
			state = MAIN_MENU;
			bstMenuOption = 1;
		}
	}

	bool InsertNodeMode(float deltaTime)
	{
		Clear(olc::VERY_DARK_CYAN);
		
		DrawString(10, 20, "PRESS ENTER TO INSERT: ");
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

		DrawString(10, 100, "INSERTING NUMBER: " + std::to_string(number), olc::RED);
		if (GetKey(olc::Key::ENTER).bReleased)
		{
			userNumberList.push_back(number);
			number = 0;
		}
		
		//draw list
		DrawString(20, 50, "NODES LIST(START FROM ROOT):");
		
		for(int i = 0; i < userNumberList.size(); i++)
		DrawString(300, 50 + (i * 10), std::to_string(userNumberList.at(i)));

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

	bool DeleteNodeMode(float deltaTime)//NOT COMPLETED
	{
		Clear(olc::VERY_DARK_BLUE);

		DrawString(10, 20, "PRESS ENTER TO DELETE: ");
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

		DrawString(10, 50, "DELETING NUMBER: " + std::to_string(number), olc::RED);
		if (GetKey(olc::Key::ENTER).bReleased)
		{
			bstTree.EliminateNode(number);
			number = 0;
		}

	

		if (GetKey(olc::Key::M).bReleased)
		{
			bstMenuOption = 1;
			return true;
		}
		return false;
	}

	bool DrawNodeInfo(float deltaTime)
	{
		//choose the node to extract info
		Clear(olc::VERY_DARK_RED);

		//NOT WORKING
		//static float keytimer = 0;
		//const char numLayout[10] = { '0','1','2','3','4','5','6','7','8','9'};
		//
		//keytimer += deltaTime;
		//if (keytimer > 0.1)
		//{
		//	for (int i = 69; i <= 78; i++) {
		//		if (GetKey(olc::Key(i)).bReleased)
		//		{
		//			testNode.push_back(numLayout[i - 69]);
		//			keytimer = 0;
		//		}
		//	}
		//
		//}
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
			//length to get there
			std::string lenght = "LENGHT: " + std::to_string( bstTree.LenghtOfaNode( testNode  ));
			DrawString( 25, 100, lenght);
			//closeth path

			//hermano
			nodeptr brother = ( bstTree.getBrotherNode(node) != nullptr) ? bstTree.getBrotherNode(node) : 0;
			std::string brotherText;
			if (brother != 0) brotherText = "BROTHER NODE:" + std::to_string(brother->getNodeValue());
			else brotherText = "BROTHER NOT FOUND";

			DrawString(25, 125, brotherText);
			
			//padre
			nodeptr parent = bstTree.getParentNode(testNode);
			std::string parentText;
			
			if (parent != nullptr) parentText = "PARENT NODE: " + std::to_string(parent->getNodeValue());
			else parentText = "PARENT NOT FOUND";
			
			DrawString(25, 175, brotherText);
			
			//hijos y grado(cantidad de hijos)
			nodeptr leftChild = bstTree.getLeftChildNode();
			nodeptr rightChild = bstTree.getRightChildNode();
			int grade;
			std::string sonsText;
			if (rightChild != nullptr || leftChild != nullptr) grade = 1;
			else if (leftChild != nullptr && rightChild != nullptr)
			{
				grade = 2;
				sonsText = "GRADE OF NODE: " + std::to_string(grade) + "  LEFTNODE: " + std::to_string(leftChild->getNodeValue()) + " RIGHTNODE: " + std::to_string(rightChild->getNodeValue());
			}
			else
			{
				grade = 0;
				sonsText = "GRADE OF NODE: " + std::to_string(grade) + "  LEFTNODE: NULL RIGHTNODE: NULL";
			}


			DrawString(25, 200, sonsText);

		}
		

		if (GetKey(olc::Key::M).bReleased)
		{
			printInfo = false;
			testNode = 0;
			state = BST_MENU;
		}

		return false;
	}

	bool DrawBSTree(nodeptr root, int lineFromX, int lineFromY, int x , int y, int incX, int incY)
	{
			
			DrawLine(lineFromX, lineFromY, x, y, olc::DARK_GREEN);

			if (root->getLeftSubTree() != nullptr) 
				DrawBSTree(root->getLeftSubTree() , x, y, x - incX, y + incY, incX * 0.5, incY);
			
			if (root->getRightSubTree() != nullptr)
				DrawBSTree(root->getRightSubTree(), x, y, x + incX, y + incY, incX * 0.5, incY);

			FillCircle(x, y, 12, olc::DARK_RED);//color of nodes
		
			if (root->getLeftSubTree() == nullptr && root->getRightSubTree() == nullptr)//LEAF NODE
			{
				DrawCircle(x,y, 12, olc::MAGENTA);
				DrawString(x-4, y-2, std::to_string(root->getNodeValue()), olc::WHITE);
			}
			else
			{
				DrawCircle(x,y, 12, olc::YELLOW);
				DrawString(x-4, y-2, std::to_string(root->getNodeValue()), olc::WHITE);
			}
			
			if (GetKey(olc::Key::M).bReleased)
				return true;

		return false;
	}

	bool DrawBSTreeInfo()
	{
		//title
		Clear(olc::VERY_DARK_GREY);
		DrawString(ScreenWidth()/2 - 100, 25, "BINARY TREE INFO", olc::WHITE);
		
		//calculations
		nodeptr root = bstTree.getRoot();
		int heightofTree = bstTree.HeightTree(root);
		int totalNodes = bstTree.NodesAmount(root);
		int leafNodes	 = bstTree.getLeafNodesAmount(root);
		bool isComplete  = bstTree.IsComplete(root);

		std::string heighText    = "HEIGHT OF THE TREE: " + std::to_string(heightofTree);
		std::string totalText    = "TOTAL OF NODES IN TREE: " + std::to_string(totalNodes);
		std::string amountText   = "AMOUNT OF LEAFS NODES: " + std::to_string(leafNodes);
		std::string completeText = (isComplete) ? "IS COMPLETE?: YES" : "IS COMPLETE?: NO";
		
		//output
		DrawString(ScreenWidth() - 450, 50, heighText, olc::WHITE);
		DrawString(ScreenWidth() - 450, 100, totalText, olc::WHITE);
		DrawString(ScreenWidth() - 450, 150, amountText, olc::WHITE);
		DrawString(ScreenWidth() - 450, 200, completeText , olc::WHITE);
		
		if (GetKey(olc::Key::M).bReleased)
			return true;

		return false;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////// THIS IS TO GET THE SCREEN RESOLUTION  //////////////////////////////////////////////////
bool fullScreen = false, setup = true;
class ScreenSetUP : public olc::PixelGameEngine
{
public:
	ScreenSetUP()
	{
		sAppName = "Setup Window";
	}
public:
	bool OnUserCreate() override
	{

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		int pointY = GetMouseY() / 50;

		if (GetMouse(0).bReleased)
		{
			if (pointY == 0) {
				setup = false;
				fullScreen = true;
				return false;
			}
			else if (pointY == 1) {
				setup = false;
				fullScreen = false;
				return false;
			}
			else if (pointY == 2) {
				fullScreen = false;
				return false;
			}

		}
		FillRect(5, pointY * 50 + 5, 290, 40, olc::VERY_DARK_BLUE);
		DrawString(10, 25, "FULLSCREEN MODE");
		DrawString(10, 75, "WINDOW MODE");
		DrawString(10, 125, "EXIT");
		return true;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


