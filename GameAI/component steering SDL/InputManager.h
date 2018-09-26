#include "GameMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"
#include <Trackable.h>

class InputManager
{
public:
	
	InputManager();
	~InputManager();

	void process();

private:
	int x, y;
	int iNum;
};

