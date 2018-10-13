#pragma once

#include "GameMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"
#include <Trackable.h>



class WeightManager
{
public:

	WeightManager();
	~WeightManager();

	float C = 0.5;
	float S = 0.25;
	float A = 0.25;
	
	void cUp();
	void cDown();

	void sUp();
	void sDown();

	void aUp();
	void aDown();

	void normalizeWeight();
	void outputFile();


private:
	
};