#include "Game.h"
#include "GameMessageManager.h"
#include "KeyDownMessage.h"
#include "UnitManager.h"
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
	if(mKey == 0)
	{
		gpGame->mShouldExit = true;
	}
	if (mKey == 1)
	{
		
		Unit* pUnit = gpGame->mpUnitManager->createRandomUnit(*gpGame->mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
	}
	if (mKey == 2)
	{
		gpGame->mpUnitManager->deleteRandomUnit();
	}

}