#include <cassert>

#include "Steering.h"
#include "ArriveFaceSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


ArriveFaceSteering::ArriveFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	
	mType = Steering::ARRIVEFACE;
	
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* ArriveFaceSteering::getSteering()
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

	ArriveSteering arrive(mOwnerID, mTargetLoc, mTargetID, false);
	FaceSteering face(mOwnerID, mTargetLoc, mTargetID, false);

	data.acc = arrive.getSteering()->getData().acc;
	data.vel = arrive.getSteering()->getData().vel;
	data.rotAcc = face.getSteering()->getData().rotAcc;
	data.rotVel = face.getSteering()->getData().rotVel;

	this->mData = data;
	return this;
}