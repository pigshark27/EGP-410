#pragma once
#include "GameMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include <Trackable.h>

class InputManager
{
public:

	InputManager();
	~InputManager();

	void process();

private:
	GameApp* gpGameApp;
	int x, y;
	int iNum;
};

