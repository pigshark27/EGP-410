#include "Game.h"
#include "GameMessageManager.h"
#include "KeyDownMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "WeightManager.h"

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
//exit game
	if(mKey == 0)
	{
		gpGame->mShouldExit = true;
	}
//spawn 1
	if (mKey == 1)
	{
		Unit* pUnit = gpGame->mpUnitManager->createRandomUnit(*gpGame->mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
	}
//delete 1 (random)
	if (mKey == 2)
	{
		gpGame->mpUnitManager->deleteRandomUnit();
	}
//spawn 10
	if (mKey == 3)
	{
		for (int i = 0; i < 10; i++)
		{
			Unit* pUnit = gpGame->mpUnitManager->createRandomUnit(*gpGame->mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
		}
	}
//Weighting

//c up
	if (mKey == 4)
	{
		gpGame->mpWeightManager->cUp();
	}
//c down
	if (mKey == 5)
	{
		gpGame->mpWeightManager->cDown();
	}
//s up
	if (mKey == 6)
	{
		gpGame->mpWeightManager->sUp();
	}
//s down
	if (mKey == 7)
	{
		gpGame->mpWeightManager->sDown();
	}
//a up
	if (mKey == 8)
	{
		gpGame->mpWeightManager->aUp();
	}
//a down
	if (mKey == 9)
	{
		gpGame->mpWeightManager->aDown();
	}
//write to file
	if (mKey == 10)
	{
		gpGame->mpWeightManager->outputFile();
	}

}