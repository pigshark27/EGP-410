#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	
	mType = Steering::ARRIVE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* ArriveSteering::getSteering()
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

	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	

	//face sprite at target
	float dir = atan2(diff.getY(), diff.getX()); //+ atan(1) * 4 / 2
	//pOwner->getPositionComponent()->setFacing(dir);

	

	//movement
	distance = diff.getLength();
	if (distance <= targetRad) 
	{
		data.acc = 0;
		data.vel = 0;
		data.rotAcc = 0;
		data.rotVel = 0;
	}
	if (distance > slowRad)
	{
		targetSpeed = pOwner->getMaxSpeed();
	}
	else
	{
		targetSpeed =  pOwner->getMaxSpeed() * distance / slowRad;
	}
	
	diff.normalize();
	diff *= targetSpeed;

	data.acc = diff - data.vel;
	data.acc /= 0.1;

	this->mData = data;
	return this;
}

