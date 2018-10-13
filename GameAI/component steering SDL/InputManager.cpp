#include <sstream>
#include <SDL.h>

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"
#include "PlayerMoveToMessage.h"
#include "KeyDownMessage.h"
#include "GameMessage.h"

#include "InputManager.h"


InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::process()
{
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		Vector2D pos(x, y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

		//get keyboard state
	const Uint8 *state = SDL_GetKeyboardState(NULL);

		//if escape key was down then exit the loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		GameMessage* pMessage = new KeyDownMessage(0);
		MESSAGE_MANAGER->addMessage(pMessage, 1);
	}
	if (state[SDL_SCANCODE_RETURN])
	{
		GameMessage* pMessage = new KeyDownMessage(1);
		MESSAGE_MANAGER->addMessage(pMessage, 1);
	}
	if (state[SDL_SCANCODE_D])
	{
		GameMessage* pMessage = new KeyDownMessage(2);
		MESSAGE_MANAGER->addMessage(pMessage, 1);
	}
	if (state[SDL_SCANCODE_A])
	{
		GameMessage* pMessage = new KeyDownMessage(3);
		MESSAGE_MANAGER->addMessage(pMessage, 1);
	}

//C
	if (state[SDL_SCANCODE_Q])
	{
		if (state[SDL_SCANCODE_EQUALS])
		{
			GameMessage* pMessage = new KeyDownMessage(4);
			MESSAGE_MANAGER->addMessage(pMessage, 1);
		}
		if (state[SDL_SCANCODE_MINUS])
		{
			GameMessage* pMessage = new KeyDownMessage(5);
			MESSAGE_MANAGER->addMessage(pMessage, 1);
		}
		
	}
//S
	if (state[SDL_SCANCODE_W])
	{
		if (state[SDL_SCANCODE_EQUALS])
		{
			GameMessage* pMessage = new KeyDownMessage(6);
			MESSAGE_MANAGER->addMessage(pMessage, 1);
		}
		if (state[SDL_SCANCODE_MINUS])
		{
			GameMessage* pMessage = new KeyDownMessage(7);
			MESSAGE_MANAGER->addMessage(pMessage, 1);
		}

	}
//A
	if (state[SDL_SCANCODE_E])
	{
		if (state[SDL_SCANCODE_EQUALS])
		{
			GameMessage* pMessage = new KeyDownMessage(8);
			MESSAGE_MANAGER->addMessage(pMessage, 1);
		}
		if (state[SDL_SCANCODE_MINUS])
		{
			GameMessage* pMessage = new KeyDownMessage(9);
			MESSAGE_MANAGER->addMessage(pMessage, 1);
		}

	}
//to File
	if (state[SDL_SCANCODE_F])
	{
		GameMessage* pMessage = new KeyDownMessage(10);
		MESSAGE_MANAGER->addMessage(pMessage, 1);
	}

}