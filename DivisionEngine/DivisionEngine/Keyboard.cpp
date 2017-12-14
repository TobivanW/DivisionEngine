#include "Keyboard.h"
#include "LoggerPool.h"

#include <dinput.h>
#include <iostream>

namespace Division
{
	Keyboard::Keyboard(HWND* windowHandle, IDirectInput8* directInput) : 
		directInput_(directInput), windowHandle_(windowHandle)
	{
		initialize();
	}



	Keyboard::~Keyboard()
	{
		release();
	}



	void Keyboard::initialize()
	{
		HRESULT result;

		result = directInput_->CreateDevice(GUID_SysKeyboard, &directInputKeyboard_, 
											NULL);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("keyboard")
				->logError("Couldn't create device, " + result);
			return;
		}

		result = directInputKeyboard_->SetDataFormat(&c_dfDIKeyboard);
		if FAILED(result)
		{
			LoggerPool::getInstance()->getLogger("keyboard")
				->logError("Couldn't set data format, " + result);
			release();
			return;
		}

		result = directInputKeyboard_->SetCooperativeLevel(*windowHandle_, 
															DISCL_EXCLUSIVE | 
															DISCL_FOREGROUND);
		if FAILED(result)
		{
			LoggerPool::getInstance()->getLogger("keyboard")
				->logError("Couldn't set coorperative level, " + result);
			release();
			return;
		}

		doAcquire();
	}


	void Keyboard::release()
	{
		directInput_ = NULL;

		if (directInputKeyboard_) {
			directInputKeyboard_->Unacquire();
			directInputKeyboard_->Release();
			directInputKeyboard_ = NULL;
		}
	}



	void Keyboard::doAcquire()
	{
		HRESULT result;

		for (int i = 0; i < 5; ++i) {

			result = directInputKeyboard_->Acquire();
			if (SUCCEEDED(result))
				return;
		}
	}



	void Keyboard::getInput()
	{
		ZeroMemory(&keys_, sizeof(keys_));

		HRESULT stateResult = directInputKeyboard_->GetDeviceState(sizeof(keys_), (void*)keys_);
		if (FAILED(stateResult)) {
			if (stateResult == DIERR_INPUTLOST || stateResult == DIERR_NOTACQUIRED)
				doAcquire();
		}
	}



	void Keyboard::storeInputStates(InputStates* inputStates)
	{
		getInput();

		if (keys_[DIK_W] & 0x80)
			inputStates->moveForward = true;

		if (keys_[DIK_A] & 0x80)
			inputStates->moveLeft = true;

		if (keys_[DIK_S] & 0x80)
			inputStates->moveBackward = true;

		if (keys_[DIK_D] & 0x80)
			inputStates->moveRight = true;
	}
}