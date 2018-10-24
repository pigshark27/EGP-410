#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "GridGraph.h"
#include "KeyDownMessage.h"
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"
#include "SpriteManager.h"

KeyDownMessage::KeyDownMessage(const int& key)
	:GameMessage(BUTTON_DOWN)
	, mKey(key)
{
}

KeyDownMessage::~KeyDownMessage()
{
}

void KeyDownMessage::process()
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	if (gpGameApp != NULL)
	{
		//exit game
		if (mKey == 0)
		{
			gpGame->markForExit();
		}
		//F Depth First Search
		if (mKey == 1)
		{
			gpGameApp->mpPathfinder = new DepthFirstPathfinder(gpGameApp->mpGridGraph);

		}
		//D Dijkstra Pathfinding
		if (mKey == 2)
		{
			gpGameApp->mpPathfinder = new DijkstraPathfinder(gpGameApp->mpGridGraph);
		}
		//A A* pathfinding
		if (mKey == 3)
		{
			gpGameApp->mpPathfinder = new AStarPathfinder(gpGameApp->mpGridGraph);
		}
	}
}