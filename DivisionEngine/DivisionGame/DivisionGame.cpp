// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "Kernel.h"


int main()
{
	// Simple interface

	Division::Kernel divisionEngine;

	divisionEngine.loadScene("scenefile.json");
	//divisionEngine.loadScene("scenefile2.json");

	divisionEngine.run();
	
	return 0;
}

//int main()
//{
//	// Sanbox interface
//
//	Division::Kernel divisionEngine(Division::REPOSITORYTYPE_D3D9);
//	Division::ResourceManager* resourceManager = divisionEngine.getResourceManager();
//	Division::SceneManager* sceneManager = divisionEngine.getSceneManager();
//	Division::Repository* repository = divisionEngine.getRepository();
//
//	Division::Scene* scene = sceneManager->createScene("scene2");
//	
//	Division::Window* window = repository->getWindow("window2");
//	Division::Window* window2 = repository->getWindow("window3");
//	// TODO: add window options like size, position, (style)
//
//	Division::Renderer* renderer = repository->getRenderer();
//	renderer->setup();
//	sceneManager->addRenderer("renderer", renderer);
//
//	Division::Entity* tiger = new Division::Entity(resourceManager);
//	tiger->setMesh("tiger.x");
//
//	Division::Entity* skyBox = repository->getSkyBox(resourceManager);
//	skyBox->setTexture("cubemaplayout.png");
//	 
//	scene->addEntity("skybox", skyBox);
//	scene->addEntity("tiger1", tiger);
//
//	Division::Entity* camera = repository->getCamera(resourceManager);
//	camera->setMesh("teapot.x");
//	camera->setTexture("teapot.jpg");
//	Division::Entity* camera2 = repository->getCamera(resourceManager);
//	camera2->setMesh("teapot.x");
//
//	scene->addWindow("window2", window, renderer, camera);
//	scene->addWindow("window3", window2, renderer, camera2);
//
//	divisionEngine.run();
//
//	return 0;
//}