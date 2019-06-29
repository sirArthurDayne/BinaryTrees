#pragma once
#include"BST.h"

/////////////////////TEXT INPUT MANAGER FOR EXPRESSION TREE///////////////////////////////////////
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
		return 'å';
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
			else if (newLetter != 'å' && newLetter != '<' && fieldTxt.size() <= maxLetters) fieldTxt += newLetter;
		}
	}

	olc::PixelGameEngine *Canvas;

	std::string getString() { return fieldTxt; }

};


///////////////////////////STATES MACHINE////////////////////////////////////////////////////
enum STATES {
	PRESENTATION, MAIN_MENU, BST_MENU, BST_INSERT_MODE, BST_DELETE_MODE, BST_TREE, BET_MENU, NODE_INFO, TREE_INFO, BST_TRAVERSAL, BET_INSERT_MODE, BET_TREE, BET_TRAVERSAL
};


/////////////////////////////////// PGE APPLICATION.... /////////////////////////////////

class TreeVisualizer : public olc::PixelGameEngine
{
private:
	
	//aloud text class to work inside the pge app
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
	TreeVisualizer();
	
private:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	//MENUS 
	void DrawPresentation();
	void DrawMainMenu();
	void DrawBetMenu();
	void DrawBstMenu();
	
	//BST DRAW FUNCTIONS
	bool DrawInsertMode();
	bool DrawDeleteBstNode();
	bool DrawNodeInfo();
	bool DrawBSTree(nodeptr root, int lineFromX, int lineFromY, int x, int y, int incX, int incY);
	bool DrawBSTreeInfo();
	bool DrawBstTraversalls();

	//BET DRAW FUNCTIONS
	bool DrawBETInsertMode();
	bool DrawBETree(NodeBET* root, int lineFromX, int lineFromY, int x, int y, int incX, int incY);
	bool DrawBETTraversals();
	

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

