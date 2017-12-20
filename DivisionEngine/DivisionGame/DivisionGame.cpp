// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "Kernel.h"


int main()
{
	// 1. init engine 
	Division::Kernel divisionEngine(Division::D3D9);
	
	// 2. specify window type
	// 3. specify renderer
	// 4. specify scene
	//divisionEngine.loadScene("scene1", "scenefile.json");
	divisionEngine.loadScene("scene2", "scenefile2.json");

	// 5. run engine
	divisionEngine.run();
	
	
	

	return 0;
}