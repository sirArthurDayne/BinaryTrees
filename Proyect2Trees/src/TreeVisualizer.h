#pragma once
#include"BST.h"

static int screenW = 640, screenH = 480;
//static int screenW = 1080, screenH = 720;

//Nodes class objects
NodeBET* rootBETnode;
nodeptr rootBSTnode(nullptr);
BST bstTree(rootBSTnode);

/////////////////////TEXT INPUT MANAGER///////////////////////////////////////
class TextField {
private:
	int maxLetters = 25, screenW = 240, screenH = 220;
	std::string fieldTxt = "";
	bool isInvisible = false;
	bool isHidden = false;
	const char keyLayout[37] = { ' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9' };
	const char shiftLayout[37] = { ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',')','!','@','#','$','%','^','&','*','(' };
	const char numLayout[15] = { '0','1','2','3','4','5','6','7','8','9','*','/','+','-','.' };



	char  lGetLetterPressed() {
		if (Canvas->GetKey(olc::Key(63)).bPressed) return '<';
		else if (Canvas->GetKey(olc::Key(53)).bPressed) return ' ';
		for (int i = 1; i < 37; i++) {
			if (Canvas->GetKey(olc::Key::SHIFT).bHeld) {
				if (Canvas->GetKey(olc::Key(i)).bPressed) return shiftLayout[i];
			}
			else if (Canvas->GetKey(olc::Key(i)).bPressed) return keyLayout[i];
		}

		for (int i = 69; i <= 83; i++) {
			if (Canvas->GetKey(olc::Key(i)).bPressed) return numLayout[i - 69];
		}
		return '�';
	}


public:
	TextField(olc::PixelGameEngine &Canvas) {
		this->Canvas = &Canvas;
		fieldTxt = "";
	}

	void updateField() {
		bool aClick = false;
		if (Canvas->GetMouse(0).bPressed) aClick = true;
		else if (Canvas->GetMouse(0).bHeld) aClick = true;
		else if (Canvas->GetMouse(0).bReleased) aClick = true;
		bool tEnter = false;
		if (Canvas->GetKey(olc::ENTER).bPressed) tEnter = true;
		else if (Canvas->GetKey(olc::ENTER).bHeld) tEnter = true;
		else if (Canvas->GetKey(olc::ENTER).bReleased) tEnter = true;
		if (true) {
			char newLetter = lGetLetterPressed();
			if (newLetter == '<' && fieldTxt.length() > 0) {
				std::string tempString = "";
				for (int i = 0; i < fieldTxt.length() - 1; i++) tempString += fieldTxt[i];
				fieldTxt.clear();
				fieldTxt = tempString;
				fieldTxt.shrink_to_fit();
			}
			else if (newLetter != '�' && newLetter != '<' && fieldTxt.size() <= maxLetters) fieldTxt += newLetter;
		}
	}

	olc::PixelGameEngine *Canvas;

	std::string getString() { return fieldTxt; }

};


//state machine
enum STATES {
	PRESENTATION, MAIN_MENU, BST_MENU, BST_INSERT_MODE, BST_DELETE_MODE, BST_TREE, BET_MENU, NODE_INFO, TREE_INFO, BST_TRAVERSAL, BET_INSERT_MODE, BET_TREE, BET_TRAVERSAL
};


/////////////////////////////////// THIS IS FOR ALL THE STUFF YOU NORMALY DO IN THE PGE.... /////////////////////////////////

class TreeVisualizer : public olc::PixelGameEngine
{
private:
	
	
	TextField text = TextField(*this);
	
	//creating machine 
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
		state = PRESENTATION;//setup default state
		//setup menus
		bstMenuOption = 1;
		betMenuOption = 1;

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
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
			if (DrawInsertMode(fElapsedTime))
				state = BST_MENU;
		}
		else if (state == BST_DELETE_MODE)//1.2
		{
			if (DrawDeleteBstNode(fElapsedTime))
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
			if (DrawBETInsertMode(fElapsedTime))
			{
				state = BET_MENU;
			}
		}
		else if (state == BET_TREE)
		{
			Clear(olc::BLACK);
			if (DrawBETree(rootBETnode, ScreenWidth() / 2, 0, ScreenWidth() / 2, 30, ScreenWidth() * 0.20, ScreenHeight() * 0.20) )
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
	void DrawPresentation()
	{
		Clear(olc::BLACK);

		DrawString(ScreenWidth()/2 - 150, 50, "UNIVERSIDAD TECNOLOGICA DE PANAMA");
		DrawString(ScreenWidth()/2 - 220, 60, "FACULTAD DE INGENIERIA DE SISTEMAS COMPUTACIONALES");
		DrawString(ScreenWidth()/2 - 220, 100, "DEPARTAMENTO DE LICENCIATURA EN INGENIERIA DE SOFTWARE");
		DrawString(ScreenWidth()/2 - 180, 130, "ESTRUCTURA Y REPRESENTACION DE DATOS 1");

		DrawString(ScreenWidth()/2 - 90, 160, "PROYECTO II: ARBOLES");
		DrawString(ScreenWidth()/2 - 120, 200, "PROF.: NICHOLAS BELIZ OSORIO");
		
		DrawString(ScreenWidth()/2 - 80, 250, "INTEGRANTES: ");
		DrawString(ScreenWidth()/2 - 100, 300, "LAMELA, XAVIER 8-956-720 ");
		DrawString(ScreenWidth()/2 - 100, 330, "HARBIN, CLYDE 8-927-1305 ");
		DrawString(ScreenWidth()/2 - 100, 360, "CHAVEZ, LUIS 8-947-1001");

		DrawString(ScreenWidth() / 2 - 65, ScreenHeight() - 50, "I SEMESTRE 2019");

		if (GetMouse(0).bPressed)
			state = MAIN_MENU;
	}

	void DrawMainMenu()
	{
		DrawString(ScreenWidth() /2 - 50, 20, "PROYECTO II");
		
		FillRect(ScreenWidth() / 2 - 100, 90, 230, 20, olc::DARK_RED);
		DrawString(ScreenWidth() /2 - 100 , 100, "1. ARBOL BINARIO GENERAL");
		
		FillRect(ScreenWidth() / 2 - 100, 140, 230, 20, olc::DARK_GREEN);
		DrawString(ScreenWidth() /2 - 100 , 150, "2. ARBOL BINARIO DE EXPRESION");

		DrawString(ScreenWidth() / 2 - 80, 250, "INTEGRANTES: ");
		DrawString(ScreenWidth() / 2 - 100, 300, "LAMELA, XAVIER 8-956-720 ");
		DrawString(ScreenWidth() / 2 - 100, 330, "HARBIN, CLYDE 8-927-1305 ");
		DrawString(ScreenWidth() / 2 - 100, 360, "CHAVEZ, LUIS 8-947-1001");


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

	void DrawBetMenu()
	{
		Clear(olc::VERY_DARK_GREEN);


		if (betMenuOption > 3 || betMenuOption < 1) betMenuOption = 1;

		//keys input
		if (GetKey(olc::Key::UP).bPressed) betMenuOption--;
		else if (GetKey(olc::Key::DOWN).bPressed) betMenuOption++;

		//mouse input
		int mouseX = GetMouseX();
		int mouseY = GetMouseY() / 20 + 20;
		

		if		(mouseX > 250 && mouseX < 350 && mouseY == 20) betMenuOption = 1;
		else if (mouseX > 250 && mouseX < 350 && mouseY == 21) betMenuOption = 2;
		else if (mouseX > 250 && mouseX < 350 && mouseY == 22) betMenuOption = 3;

		//selected
		FillRect(ScreenWidth() / 2 - 100, 20 * betMenuOption, 200, 11, olc::VERY_DARK_GREY);
		DrawRect(ScreenWidth() / 2 - 100, 20 * betMenuOption, 200, 11, olc::WHITE);

		//button text
		DrawString(ScreenWidth() / 2 - 310, 10, "PROYECTO II: ARBOL BINARIO DE EXPRESION");
		DrawString(ScreenWidth() / 2 - 100, 20, "1. INSERTAR EXPRESION", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 100, 40, "2. VER ARBOL ", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 100, 60, "3. RECORRIDOS:", olc::WHITE);
		

		DrawString(ScreenWidth() / 2 - 80, 250, "INTEGRANTES: ");
		DrawString(ScreenWidth() / 2 - 100, 300, "LAMELA, XAVIER 8-956-720 ");
		DrawString(ScreenWidth() / 2 - 100, 330, "HARBIN, CLYDE 8-927-1305 ");
		DrawString(ScreenWidth() / 2 - 100, 360, "CHAVEZ, LUIS 8-947-1001");


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

	void DrawBstMenu()
	{
		Clear(olc::VERY_DARK_BLUE);

		if(bstMenuOption > 6 || bstMenuOption < 1) bstMenuOption = 1;
		  
		if(GetKey(olc::Key::UP).bReleased) bstMenuOption--;

		else if (GetKey(olc::Key::DOWN).bReleased) bstMenuOption++;

		
			int mouseX = GetMouseX();
			int mouseY = GetMouseY() / 20 + 20;
			

			if		(mouseX > 250 && mouseX < 350 && mouseY == 20 ) bstMenuOption = 1;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 21 ) bstMenuOption = 2;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 22 ) bstMenuOption = 3;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 23 ) bstMenuOption = 4;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 24 ) bstMenuOption = 5;
			else if (mouseX > 250 && mouseX < 350 && mouseY == 25 ) bstMenuOption = 6;
		
			//selected text
			FillRect(ScreenWidth()/2 -100, (20 * bstMenuOption), 200, 11, olc::VERY_DARK_GREY);
			DrawRect(ScreenWidth()/2 -100, 20 * bstMenuOption, 200, 11, olc::WHITE);

		//button text
		DrawString(ScreenWidth() / 2 - 310, 10, "PROYECTO II: ARBOL BINARIO GENERAL");
		DrawString(ScreenWidth() /2- 100, 20, "1. INSERTAR NODO EN ARBOL", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 40, "2. BORRAR NODO DEL ARBOL", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 60, "3. VER ARBOL ", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 80, "4. INFORMACION DE UN NODO", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 100, "5. INFORMACION DEL ARBOL ", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 120, "6. RECORRIDOS:", olc::WHITE);

		DrawString(ScreenWidth() / 2 - 80, 250, "INTEGRANTES: ");
		DrawString(ScreenWidth() / 2 - 100, 300, "LAMELA, XAVIER 8-956-720 ");
		DrawString(ScreenWidth() / 2 - 100, 330, "HARBIN, CLYDE 8-927-1305 ");
		DrawString(ScreenWidth() / 2 - 100, 360, "CHAVEZ, LUIS 8-947-1001");

		
		DrawString(ScreenWidth() /2+ 100 , ScreenHeight() - 25, "PRESIONA 'M' PARA MENU", olc::WHITE);




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

	bool DrawInsertMode(float deltaTime)
	{
		Clear(olc::VERY_DARK_CYAN);
		//title	
		DrawString(10, 20, "PRESIONA 'ENTER' PARA INSERTAR: ");
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
		DrawString(10, 100, "INSERTANDO NUMERO: " + std::to_string(number), olc::RED);
		if (GetKey(olc::Key::ENTER).bReleased)
		{
			userNumberList.push_back(number);
			number = 0;
		}
		
		//draw list
		DrawString(20, 50, "LISTA DE NODOS(EMPIEZA EN RAIZ):");
		for(int i = 0; i < userNumberList.size(); i++)
		DrawString(300, 50 + (i * 10), std::to_string(userNumberList.at(i)));
		//exit & insert nodes in tree
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

	bool DrawDeleteBstNode(float deltaTime)//NOT COMPLETED
	{
		//title 
		Clear(olc::VERY_DARK_BLUE);
		DrawString(10, 20, "PRESIONA 'ENTER' PARA BORRAR: ");
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
		DrawString(10, 50, "BORRANDO NUMERO: " + std::to_string(number), olc::RED);
		//delete function call
		if (GetKey(olc::Key::ENTER).bReleased)
		{
			bstTree.EliminateNode(number);
			number = 0;
		}
		//exit of mode 
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
			std::string level = "NIVEL: " + std::to_string( bstTree.getLevelNode( bstTree.getRoot(), testNode) );
			DrawString( 25, 75, level);
			//length to get there
			std::string lenght = "LONGITUD: " + std::to_string( bstTree.LenghtOfaNode( testNode  ));
			DrawString( 25, 100, lenght);
			//closeth path
			bstTree.getShortestPath(node, this);
			//father
			nodeptr parent = bstTree.getParentNode(testNode);
			std::string parentText;
			if (parent != nullptr) parentText = "NODO PADRE: " + std::to_string(parent->getNodeValue());
			else parentText = "PADRE NO ENCONTRADO";
			DrawString(25, 200, parentText);
			
			//sibling
			nodeptr brother = bstTree.getBrotherNode(node);
			int brotherValue = (brother != nullptr) ? brother->getNodeValue() : 0;
			std::string brotherText = "HERMANO DE " + std::to_string(testNode) + " ES " + std::to_string(brotherValue);
			DrawString(25, 225, brotherText);
			
			//childs y grade(amount of childs)
			int leftChild  = (node->left  != nullptr)  ? node->left->getNodeValue() : 0;
			int rightChild = (node->right != nullptr)  ? node->right->getNodeValue() : 0;

			int grade = 0;
			std::string sonsText = "";
			std::string gradeText = "";

			if (rightChild != 0 && leftChild != 0) grade = 2;
			else if ( (rightChild == 0 && leftChild != 0 )  || (leftChild == 0 && rightChild != 0) ) grade = 1;
			else grade = 0;
			
			gradeText = "GRADO: " + std::to_string(grade);
			sonsText = " HIJO DERECHO: " + std::to_string(rightChild) + " HIJO IZQUIERDO: " + std::to_string(leftChild);
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
		DrawString(ScreenWidth()/2 - 100, 25, "INFORMACION DEL ARBOL BINARIO", olc::WHITE);
		
		//calculations
		nodeptr root = bstTree.getRoot();
		int heightofTree = bstTree.HeightTree(root);
		int totalNodes = bstTree.NodesAmount(root);
		int leafNodes	 = bstTree.getLeafNodesAmount(root);
		bool isComplete  = bstTree.IsComplete(root);

		std::string heighText    = "ALTURA DEL ARBOL: " + std::to_string(heightofTree);
		std::string totalText    = "NODOS TOTALES: " + std::to_string(totalNodes);
		std::string amountText   = "CANTIDAD DE NODOS HOJA: " + std::to_string(leafNodes);
		std::string completeText = (isComplete) ? "ESTA COMPLETO?: SI" : "ESTA COMPLETO?: NO";
		
		//output
		DrawString(ScreenWidth() - 450, 50, heighText, olc::WHITE);
		DrawString(ScreenWidth() - 450, 100, totalText, olc::WHITE);
		DrawString(ScreenWidth() - 450, 150, amountText, olc::WHITE);
		DrawString(ScreenWidth() - 450, 200, completeText , olc::WHITE);
		
		if (GetKey(olc::Key::M).bReleased)
			return true;

		return false;
	}

	bool DrawBstTraversalls()
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

		//exit
		if (GetKey(olc::Key::M).bReleased)
			return true;

		return false;
	}

	//BET DRAW FUNCTIONS
	bool DrawBETInsertMode(float deltaTime)
	{
		//title
		Clear(olc::VERY_DARK_GREEN);
		DrawString(10, 20, "PRESIONA 'ENTER' PARA INGRESAR EXPRESION: ");
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
			DrawString(20, 150, "EXPRESION VALIDA!");
		//validate expresion 
		if (GetKey(olc::Key::ENTER).bReleased && isBalanced(testExpression) )
		{
			userInfixExpression = testExpression;//transfer valid expression data
			reading = false;
		}
		//creating the tree & exit 
		if (GetKey(olc::Key::M).bReleased)
		{
			testExpression = "";
			reading = true;
			//preparing for making tree
			std::string posfix = ConvertToPosfix(userInfixExpression);
			//root node of BET class
			rootBETnode = ConstructTree(posfix);
			return true;
		}

		return false;
	}

	bool DrawBETree(NodeBET* root, int lineFromX, int lineFromY, int x, int y, int incX, int incY)
	{
		DrawLine(lineFromX, lineFromY, x, y, olc::DARK_GREEN);

		if (root->getLeftSubTree() != nullptr)
			DrawBETree(root->getLeftSubTree(), x, y, x - incX, y + incY, incX * 0.5, incY);

		if (root->getRightSubTree() != nullptr)
			DrawBETree(root->getRightSubTree(), x, y, x + incX, y + incY, incX * 0.5, incY);

		FillCircle(x, y, 12, olc::DARK_RED);//color of nodes

		if (root->getLeftSubTree() == nullptr && root->getRightSubTree() == nullptr)//LEAF NODE
		{
			DrawCircle(x, y, 12, olc::MAGENTA);
			std::string c = "";
			DrawString(x - 4, y - 2, c += root->getNodeValue(), olc::WHITE);
		}
		else
		{
			DrawCircle(x, y, 12, olc::YELLOW);
			std::string c = "";
			DrawString(x - 4, y - 2, c += root->getNodeValue(), olc::WHITE);
		}

		if (GetKey(olc::Key::M).bReleased)
			return true;

		return false;
	}

	bool DrawBETTraversals()
	{
		Clear(olc::VERY_DARK_BLUE);
		DrawString(ScreenWidth() / 2 - 100, 25, "RECORRIDOS", olc::WHITE);

		std::string prefixText = "";
		std::string infixText = "";
		std::string posfixText = "";

		infixText = userInfixExpression;
		posfixText = ConvertToPosfix(userInfixExpression);
		prefixText = ConvertToPrefix(posfixText);

		//output
		DrawString(25, 50, "PREFIJO: " + prefixText, olc::WHITE);
		DrawString(25, 100, "INFIJO: " + infixText, olc::WHITE);
		DrawString(25, 150, "POSTFIJO: " + posfixText, olc::WHITE);



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


