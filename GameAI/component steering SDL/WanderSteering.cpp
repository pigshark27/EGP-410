#include <cassert>

#include "Steering.h"
#include "WanderSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = Steering::WANDER;
	
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//seeking a unit

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	

	//movement

	wanderOrientation += genRandomBinomial() * wanderRate;
	targetOrientation = wanderOrientation + pOwner->getFacing();
	target = pOwner->getPositionComponent()->getPosition() + (getDirectionVector(pOwner->getFacing()) * wanderOffset);

	target += getDirectionVector(targetOrientation) * wanderRadius;
	mTargetLoc = target;


	//Look Steering
	FaceSteering lookSteering(mOwnerID, mTargetLoc, mTargetID,  false);
	lookSteering.setTargetLoc(target);
	
	data.rotAcc = lookSteering.getSteering()->getData().rotAcc;
	data.acc = getDirectionVector(pOwner->getFacing()) * pOwner->getMaxAcc();


	this->mData = data;
	return this;
}

Vector2D WanderSteering::getDirectionVector(float direction)
{
	float x = cos(direction);
	float y = sin(direction);

	return Vector2D(x,y);
}