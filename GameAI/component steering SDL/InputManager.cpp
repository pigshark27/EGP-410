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
	

}