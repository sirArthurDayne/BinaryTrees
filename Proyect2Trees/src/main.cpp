#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include"TreeVisualizer.h"

int main()
{
	ScreenSetUP setupPGE;
	if (setup && setupPGE.Construct(300, 150, 2, 2))
		setupPGE.Start();

	TreeVisualizer app;
	if (!setup && app.Construct(screenW, screenH, 2, 2, fullScreen))
		app.Start();

	
	return 0;
}
