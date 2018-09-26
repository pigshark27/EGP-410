#include <cassert>

#include "Steering.h"
#include "SeekSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


SeekSteering::SeekSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/ )
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::SEEK;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* SeekSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//are we seeking a location or a unit?
	
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::SEEK)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		diff = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}


	//float dir = atan2(diff.getY(), diff.getX());
	//pOwner->getPositionComponent()->setFacing(dir);

	//Look Steering
	FaceSteering lookSteering(mOwnerID, mTargetLoc, mTargetID, false);
	data.rotAcc = lookSteering.getSteering()->getData().rotAcc;


	diff.normalize();
	diff *= pOwner->getMaxAcc();
	data.acc = diff;

	this->mData = data;
	return this;
}

