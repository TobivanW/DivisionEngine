#include "D3D9Repository.h"
#include "LoggerPool.h"
#include "FileLoader.h"
#include "D3D9Mesh.h"
#include "D3D9Camera.h"

namespace Division
{
	D3D9Repository::D3D9Repository()
	{
		if (NULL == (direct3D_ = Direct3DCreate9(D3D_SDK_VERSION))) {
			LoggerPool::getInstance()->getLogger("D3DRepository")
				->logError("Failed to create Direct3D object");
			return;
		}

		// Set up the dx parameters.
		D3DPRESENT_PARAMETERS direct3DParams;
		ZeroMemory(&direct3DParams, sizeof(direct3DParams));
		direct3DParams.Windowed = TRUE;
		direct3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		direct3DParams.BackBufferFormat = D3DFMT_UNKNOWN;
		direct3DParams.EnableAutoDepthStencil = true;
		direct3DParams.AutoDepthStencilFormat = D3DFMT_D16;

		// Create a dummy window to create a direct3D device without a visible window present.
		HWND windowHandle = CreateWindowA("STATIC", "dummy", NULL, 100, 100, 800, 600,
			NULL, NULL, NULL, NULL);

		// Attempt to create the direct3D device, log on fail.
		HRESULT result = direct3D_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &direct3DParams, &direct3DDevice_);

		if (FAILED(result)) {
			LoggerPool::getInstance()->getLogger("D3DRepository")
				->logError("Failed to create Direct3D device");
			return;
		}
	}



	D3D9Repository::~D3D9Repository()
	{
		if (textureLoader_)
			delete textureLoader_;
		if (meshLoader_)
			delete meshLoader_;
	}



	ResourceLoader* D3D9Repository::getTextureLoader()
	{
		if (!textureLoader_)
			textureLoader_ = new D3D9TextureLoader(direct3DDevice_);
			
		return textureLoader_;
	}



	ResourceLoader* D3D9Repository::getMeshLoader()
	{
		if (!meshLoader_)
			meshLoader_ = new D3D9MeshLoader(direct3DDevice_);
		
		return meshLoader_;
	}



	Entity* D3D9Repository::getTerrain(std::string filename, ResourceManager* rm,
									   std::string texturefile = "")
	{
		return new D3D9Terrain(rm, filename, texturefile);
	}
	


	Entity* D3D9Repository::getSkyBox(ResourceManager* rm)
	{
		return new D3D9SkyBox(rm, 1);
	}


	Renderer* D3D9Repository::getRenderer()
	{
		return new D3D9Renderer(direct3DDevice_);
	}



	Window* D3D9Repository::getWindow(std::string title)
	{
		return new Win32Window(title);
	}



	Entity* D3D9Repository::getCamera(ResourceManager* resourceManager, 
									  float x, float y, float z, float xAngle,
									  float yAngle, float zAngle)
	{
		return new D3D9Camera(resourceManager, x, y, z, xAngle, yAngle, zAngle);
	}



	InputManager* D3D9Repository::getInputManager()
	{
		return new DirectInputManager();
	}
	


	void* D3D9Repository::getFrameworkInterface()
	{
		return direct3D_;
	}
}