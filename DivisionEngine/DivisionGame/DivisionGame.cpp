// DivisionGame.cpp : Defines the entry point for the console application.
//
#include "DivisionEngine.h"
#include "Win32Window.h"
//#include "D3D9Renderer.h"
#include "WindowsInputManager.h"
#include "LoggerPool.h"
#include <iostream>

int main()
{
	Division::DivisionEngine Engine;
	Division::ResourceManager ResourceManger;
	Division::SceneManager SceneManager;

	Engine.getResourceManager(&ResourceManger);
	Engine.getSceneManager(&SceneManager);

	SceneManager.createScene("Test Scene");
	Division::Scene Test;
	SceneManager.getScene("Test Scene", &Test);
	Test.addWindow("Window", new Division::Win32Window("Window", "Window title"));
	Division::Win32Window win;
	Test.getWindow("Window", &win);

	//SceneManager.addRenderer("DXRenderer", new Division::D3D9Renderer(NULL, NULL, win.getWindowHandle()));


	// For testing the logger.
	Division::LoggerPool* loggerPool = Division::LoggerPool::getInstance();
	Division::Logger* logger1 = loggerPool->getLogger("stuffLogger");
	logger1->logError("er is een error");

	// For testing the input.
	HWND window = win.getWindowHandle();
	Division::WindowsInputManager* windowsInputManager = &(Division::WindowsInputManager::getInstance(&window));

	while (true) {
		Division::InputStates inputStates = windowsInputManager->getInput();
		if (inputStates.moveForward)
			MessageBox(0, L"moving forward", L"alert", MB_OK);
		if (inputStates.action)
			MessageBox(0, L"action", L"alert", MB_OK);
	}

	return 0;
}