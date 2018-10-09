#include <cassert>

#include "Steering.h"
#include "AlignmentSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


AlignmentSteering::AlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = Steering::ALIGNMENT;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

}

Steering* AlignmentSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();


	//movement
	target = getHoodAlignment(pOwner);


	this->mData = data;
	return this;
}


Vector2D AlignmentSteering::getHoodAlignment(Unit* pOwner)
{
	Vector2D neighborhoodVelocity(0,0);
	float hoodCount = 0;
	std::map<UnitID, Unit*> unitMap = gpGame->getUnitManager()->mUnitMap;
	for (auto it = unitMap.begin(); it != unitMap.end(); ++it)
	{
		if (it->second->mID != pOwner->mID) {
			if ((pOwner->getPositionComponent()->getPosition() - it->second->getPositionComponent()->getPosition()).getLength() <= alignmentRadius)
			{
				neighborhoodVelocity += it->second->getPhysicsComponent()->getVelocity();
				hoodCount += 1;
			}
		}
	}
	if (hoodCount == 0)
	{
		return Vector2D(0, 0);
	}
	neighborhoodVelocity.setX(neighborhoodVelocity.getX() / hoodCount);
	neighborhoodVelocity.setY(neighborhoodVelocity.getY() / hoodCount);
	return neighborhoodVelocity;
}
