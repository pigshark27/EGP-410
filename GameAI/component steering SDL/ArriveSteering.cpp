#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
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

Steering* ArriveSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
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


	float dir = atan2(diff.getY(), diff.getX()) + atan(1) * 4 / 2;
	pOwner->getPositionComponent()->setFacing(dir);

	diff.normalize();
	diff *= pOwner->getMaxAcc();
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.acc = diff;

	data.rotVel = 1.0f;
	this->mData = data;
	return this;
}
