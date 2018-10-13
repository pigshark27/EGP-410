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

#include "WeightManager.h"

#include <iostream>
#include <fstream>
#include <string>



WeightManager::WeightManager()
{
}

WeightManager::~WeightManager()
{
}

void WeightManager::cUp()
{
	C += 0.1;
	normalizeWeight();
}
void WeightManager::cDown()
{
	if (C <= 0)
	{
		C = 0;
		normalizeWeight();
	}
	else
	{
		C -= 0.1;
		normalizeWeight();
	}
}

void WeightManager::sUp()
{
	S += 0.1;
	normalizeWeight();
}
void WeightManager::sDown()
{
	if (S <= 0)
	{
		S = 0;
		normalizeWeight();
	}
	else
	{
		S -= 0.1;
		normalizeWeight();
	}
}

void WeightManager::aUp()
{
	A += 0.1;
	normalizeWeight();
}
void WeightManager::aDown()
{
	if (A <= 0) 
	{
		A = 0;
		normalizeWeight();
	}
	else
	{
		A -= 0.1;
		normalizeWeight();
	}
}

void WeightManager::normalizeWeight()
{
	float mag = pow(C, 2) + pow(S, 2) + pow(A, 2);
	mag = sqrtf(mag);
	C = C / mag;
	S = S / mag;
	A = A / mag;
}

void WeightManager::outputFile()
{
	//output to a file one day
	std::ofstream thisFile("WeightSave.txt", std::ios::app);
	if (!thisFile.fail())
	{
		thisFile << "C: " << C << ", S: " << S << ", A: " << A << "\n";
		thisFile.close();
	}
	
}