#ifndef DIVISION_WINDOWSINPUTMANAGER_H
#define DIVISION_WINDOWSINPUTMANAGER_H

#include <Windows.h>
#include <dinput.h>

#include "InputDevice.h"

namespace Division
{
	class WindowsInputManager
	{
	public:
		WindowsInputManager(HWND* windowHandle); // TODO: maybe change
		~WindowsInputManager();
		void initializeDirectInput();
		void releaseDirectInput();
		static BOOL CALLBACK enumDevicesCallback(LPCDIDEVICEINSTANCE, LPVOID);
		void initializeInputDevices();
		InputStates getInput();
	private:
		HWND* windowHandle_;
		IDirectInput8* directInput_;
		// We only use keyboard and mouse, so no container for these
		InputDevice* keyboard_;
		InputDevice* mouse_;
		BOOL enumDevices(LPCDIDEVICEINSTANCE);
	};
}

#endif // !DIVISION_WINDOWSINPUTMANAGER_H

