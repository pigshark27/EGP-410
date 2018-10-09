#include <cassert>

#include "Steering.h"
#include "WanderChaseSteering.h"
#include "WanderSteering.h"
#include "SeekSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderChaseSteering::WanderChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	
	mType = Steering::WANDERCHASE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* WanderChaseSteering::getSteering()
{

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	
	//seeking unit
	Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
	
	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	
	//movement
	distance = diff.getLength();

	WanderSteering wander(mOwnerID, mTargetLoc, mTargetID, false);
	mTargetLoc = pTarget->getPositionComponent()->getPosition();
	SeekSteering seek(mOwnerID, mTargetLoc, mTargetID, false);
	
	if (distance < targetRad)
	{
		data.rotAcc = seek.getSteering()->getData().rotAcc;
		data.acc = seek.getSteering()->getData().acc;
	}
	else
	{
		data.rotAcc = wander.getSteering()->getData().rotAcc;
		data.acc = wander.getSteering()->getData().acc;
	}
	
	
	this->mData = data;
	return this;
}