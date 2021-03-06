// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "Kernel.h"


// Simple interface
int main()
{
	Division::Kernel divisionEngine;

	divisionEngine.loadScene("example_scene.json");
	//divisionEngine.loadScene("empty_scene.json");

	divisionEngine.run();
	
	return 0;
}

// Sandbox interface
//int main()
//{
//	// Set up the engine with a directx repository.
//	Division::Kernel divisionEngine(Division::REPOSITORYTYPE_D3D9);
//
//	// Get the managing objects from the kernel.
//	Division::ResourceManager* resourceManager = divisionEngine.
//												 getResourceManager();
//	Division::SceneManager* sceneManager = divisionEngine.getSceneManager();
//	Division::Repository* repository = divisionEngine.getRepository();
//
//	// Create an empty scene.
//	Division::Scene* scene = sceneManager->createScene("scene2");
//	
//	// Create two windows, position them next to each other.
//	Division::Window* window = repository->getWindow("First window");
//	window->moveWindow(0, 0, true);
//	window->resizeWindow(720, 720, true);
//
//	Division::Window* window2 = repository->getWindow("Second window");
//	window2->moveWindow(720, 0, true);
//	window2->resizeWindow(720, 720, true);
//
//	// Create a renderer and set it up.
//	Division::Renderer* renderer = repository->getRenderer();
//	renderer->setup();
//	// Add it to the scenemanager so it can manage this renderer.
//	sceneManager->addRenderer("renderer", renderer);
//
//	// Create two cameras and set their mesh/texture for future rendering.
//	Division::Entity* camera = repository->getCamera(resourceManager, 5, 5, 5);
//	camera->setMesh("teapot.x");
//	camera->setTexture("teapot.jpg");
//
//	Division::Entity* camera2 = repository->getCamera(resourceManager);
//	camera2->setMesh("teapot.x");
//
//	// Add the created windows to the empty scene, with a renderer and camera.
//	scene->addWindow("window2", window, renderer, camera);
//	scene->addWindow("window3", window2, renderer, camera2);
//
//	// Create a new entity to appear in the scene, set its mesh and add it to
//	// the scene.
//	Division::Entity* tiger = new Division::Entity(resourceManager);
//	tiger->setMesh("tiger.x");
//	scene->addEntity("tiger1", tiger);
//
//	// Set the scene's skybox with a texture.
//	Division::Entity* skyBox = repository->getSkyBox(resourceManager);
//	skyBox->setTexture("skybox.bmp");
//	scene->setSkyBox(skyBox);
//
//	// Set a terrain on the scene.
//	Division::Entity* terrain = repository->getTerrain("terrainhm.bmp", 
//													   resourceManager, 
//													   "terrain.bmp");
//	scene->addEntity("terrain", terrain);
//
//	// Run the engine.
//	divisionEngine.run();
//
//	return 0;
//}