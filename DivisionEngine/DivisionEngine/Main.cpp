#include <Windows.h>
#include <d3d9.h>

bool g_bContinue = true;

//Besides the main function, there must be a message processing function
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		g_bContinue = false;
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//The entry point of a windows application is the WinMain function
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	//Create a window class.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Direct3D Window", NULL };

	//Register the window class.
	RegisterClassEx(&wc);

	//Create the application's window.
	HWND hWnd = CreateWindow("Direct3D Window", "DirectXers - D3D9 Tutorial 1",
		WS_OVERLAPPEDWINDOW, 100, 100, 400, 400,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	//Create the Direct3D Object
	LPDIRECT3D9 pD3D = NULL;
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	//Setup the device presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//The final step is to use the IDirect3D9::CreateDevice method to create the Direct3D device, as illustrated in the
	//following code example.
	LPDIRECT3DDEVICE9 pd3dDevice = NULL;
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pd3dDevice)))
	{
		MessageBox(hWnd, "No HAL HARDWARE_VERTEXPROCESSING! Sample will exit!", NULL, 0);
		pD3D->Release();
		pD3D = NULL;
		return E_FAIL;
	}
	MSG msg;
	while (g_bContinue)
	{
		//Clear render region with blue
		pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

		//before rendering something, you have to call this
		pd3dDevice->BeginScene();

		//
		//rendering of scene objects happens her
		//

		//now end the scene          
		pd3dDevice->EndScene();

		//update screen = swap front and backbuffer
		pd3dDevice->Present(NULL, NULL, NULL, NULL);

		// A window has to handle its messages.
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
	}

	//Do not forget to clean up here
	pd3dDevice->Release();
	pd3dDevice = NULL;
	pD3D->Release();
	pD3D = NULL;
	return 0;
}