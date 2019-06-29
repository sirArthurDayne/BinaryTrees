#define OLC_PGE_APPLICATION//DEFINITION
#include "olcPixelGameEngine.h"//GRAPHICS ENGINE
#include"ScreenSetUP.h"//SIZE OF WINDOW
#include"TreeVisualizer.h"//PROYECT MAIN CLASS

int main()
{
	//AKS FOR DIMENSIONS
	ScreenSetUP setupPGE;
	if (setup && setupPGE.Construct(300, 150, 2, 2))
		setupPGE.Start();

	//CONSTRUCT AND RUN MAIN APP
	TreeVisualizer app;
	if (!setup && app.Construct(screenW, screenH, 2, 2, fullScreen))
		app.Start();

	
	return 0;
}
