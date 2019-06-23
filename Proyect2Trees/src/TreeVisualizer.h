#pragma once
#include"BST.h"

static int screenW = 640, screenH = 480;

//state machine
enum STATES {
	MAIN_MENU, BST_MENU, BET_MENU,  NODE_INFO, TREE_INFO
};

/////////////////////////////////// THIS IS FOR ALL THE STUFF YOU NORMALY DO IN THE PGE.... /////////////////////////////////
class TreeVisualizer : public olc::PixelGameEngine
{
private:
	STATES state;
	BST bstTree;
	std::vector<int> userNumberList;//user array for BST
	std::string userInfixExpression;//user array for BET
	nodeptr rootBSTnode;
	NodeBET* rootBETnode;


public:
	TreeVisualizer()
	{
		sAppName = "Proyect 2 Binary Trees";
	}
public:
	bool OnUserCreate() override
	{
		state = MAIN_MENU;//setup default
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_BLUE);

		if (state == MAIN_MENU)
			DrawMainMenu();
		else if (state == BST_MENU)
			DrawBstMenu();
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

		if (GetKey(olc::Key::UP).bReleased)
			option++;
		else if (GetKey(olc::Key::DOWN).bReleased)
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

		int option = 1;
		if (option > 6 || option < 1) option = 1;

		if (GetKey(olc::Key::UP).bReleased)
			option++;
		else if (GetKey(olc::Key::DOWN).bReleased)
			option--;

		FillRect(ScreenWidth()/2 -100, 20 + (16 * ((option - 1) / 2)), 200, 11, olc::VERY_DARK_GREY);
		DrawRect(ScreenWidth()/2 -100, 20 + (16 * ((option - 1) / 2)), 200, 11, olc::WHITE);

		DrawString(ScreenWidth() /2- 100, 20, "1. Insert Node to tree", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 40, "2. Delete Node from tree", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 60, "3. Info about a node", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 80, "4. Info about tree ", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 100, "5. See Tree ", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 120, "6. Traversal:", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 140, "  6.1 PREORDER", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 160, "  6.2 INORDER", olc::WHITE);
		DrawString(ScreenWidth() /2- 100, 180, "  6.3 POSTORDER", olc::WHITE);
		DrawString(ScreenWidth() /2+ 100 , ScreenHeight() - 25, "Press M to MainMenu", olc::WHITE);


		
		if (GetKey(olc::Key::M).bReleased)
			state = MAIN_MENU;

	}

	void InsetNodeMode()
	{
		
	
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


