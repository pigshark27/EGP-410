#include <cassert>

#include "Steering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


SeparationSteering::SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = Steering::SEPARATION;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

}

Steering* SeparationSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	
	target = getNeighborhoodPos(pOwner, currentRotation, targetRotation);


	this->mData = data;
	return this;
}


Vector2D SeparationSteering::getNeighborhoodPos(Unit* pOwner, float currentRot, float targetRot)
{
	Vector2D myPos = pOwner->getPositionComponent()->getPosition();
	Vector2D neighborhoodPos(0,0);
	float hoodCount = 0;
	std::map<UnitID, Unit*> unitMap = gpGame->getUnitManager()->mUnitMap;


	for (auto it = unitMap.begin(); it != unitMap.end(); ++it)
	{
		if (it->second->mID != pOwner->mID)
		{
			if ((myPos - it->second->getPositionComponent()->getPosition()).getLength() <= separationRadius)
			{
				neighborhoodPos += it->second->getPositionComponent()->getPosition();
				hoodCount += 1;
			}
		}

	}
	if (hoodCount == 0)
	{
		return Vector2D(0, 0);
	}
	neighborhoodPos.setX(neighborhoodPos.getX() / hoodCount);
	neighborhoodPos.setY(neighborhoodPos.getY() / hoodCount);
	Vector2D hoodDirection = Vector2D(neighborhoodPos.getX() - myPos.getX(), neighborhoodPos.getY() - myPos.getY());
	hoodDirection *= -1;
	return hoodDirection;
}
