// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "Kernel.h"


int main()
{
	Division::Kernel divisionEngine(Division::D3D9);
	
	//divisionEngine.loadScene("scene1", "scenefile.json");
	divisionEngine.loadScene("scene2", "scenefile2.json");

	divisionEngine.run();
	
	
	

	return 0;
}