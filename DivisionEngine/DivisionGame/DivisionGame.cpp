// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>

#include "DivisionEngine.h"

#include "D3D9GameObject.h"
#include "D3D9Renderer.h"
#include "Win32Window.h"

int main()
{
	// This needs to be split into +/- 5 lines so the user can specify the needs
	Division::DivisionEngine divisionEngine;

	Division::SceneManager* sceneManager = divisionEngine.getSceneManager();
	Division::ResourceManager* resourceManager = divisionEngine.getResourceManager();

	sceneManager->addRenderer("DXrender", new Division::D3D9Renderer(NULL, NULL, NULL));
	Division::Scene* theScene = sceneManager->createScene("The Scene");
	theScene->addWindow("MainWindow", Division::DivisionWindow(new Division::Win32Window("Window", "Window title"), sceneManager->getRenderer("DXrender")));

	Division::Entity* entity = new Division::D3D9GameObject(resourceManager, 0, 0, 0);
	entity->addMesh("tiger.x");

	theScene->addEntity("Tiger", Division::DivisionEntity(entity, theScene->getWindow("MainWindow")->window));

	//TODO intergrate the windowsInputmanger

	//HWND window = win->getWindowHandle();
	//Division::WindowsInputManager* windowsInputManager = &(Division::WindowsInputManager::getInstance(&window));

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			divisionEngine.run();
		}
	}
	// 1. init engine
	// 2. specify window type
	// 3. specify renderer
	// 4. specify scene
	// 5. run engine

	return 0;
}