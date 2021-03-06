#include "Kernel.h"
#include <iostream>
#include "Clock.h"
#include "LoggerPool.h"
#include "D3D9Repository.h"

namespace Division
{
	Kernel::Kernel(RepositoryType repoType)
	{
		switch (repoType) {
			case REPOSITORYTYPE_D3D9:
				repository_ = new D3D9Repository();
				break;
			case REPOSITORYTYPE_OPENGL:
				// TODO: implement for OpenGL.
				break;
			default:
				break;
		}		

		resourceManager_ = new ResourceManager(repository_->getTextureLoader(),
			repository_->getMeshLoader());

		sceneManager_ = new SceneManager(resourceManager_, repository_);
	}



	Kernel::~Kernel()
	{
		delete repository_;
		delete resourceManager_;
		delete sceneManager_;
	}



	void Kernel::loadScene(std::string fileName)
	{
		sceneManager_->loadScene(fileName);
	}



	void Kernel::run()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		Clock clock;
		Logger* kernelLog = LoggerPool::getInstance()->getLogger("clock");

		clock.start();
		int frames = 0;
		int lastSec = 0;

		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				++frames;

				if (clock.getRuntime() / 1000 != lastSec) {
					lastSec = clock.getRuntime() / 1000;
					kernelLog->logInfo(frames);
					frames = 0;
				}
				// Get handle of current window  on the foreground.
				HWND win = GetForegroundWindow(); 

				//Check if the window handle is different from the current active window handle.
				if (win != sceneManager_->getInputHandle()) {
					// Set active window handle
					sceneManager_->setInputHandle(win);
				}

				//Render all the scenes
				sceneManager_->renderScenes();
			}
		}
	}



	SceneManager* Kernel::getSceneManager()
	{
		return sceneManager_;
	}



	ResourceManager* Kernel::getResourceManager()
	{
		return resourceManager_;
	}



	Repository* Kernel::getRepository()
	{
		return repository_;
	}
}