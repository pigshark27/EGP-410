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

	wanderOrientation = 0;
}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	
	
	//movement

	wanderOrientation += genRandomBinomial() * wanderRate;
	targetOrientation = wanderOrientation + pOwner->getFacing();

	target = (pOwner->getPositionComponent()->getPosition()) + (getDirectionVector(pOwner->getFacing())  * wanderOffset);

	target += getDirectionVector(targetOrientation) * wanderRadius;
	mTargetLoc = target;


	//Look Steering
	FaceSteering lookSteering(mOwnerID, target, mTargetID, false);
	data.rotAcc = lookSteering.getSteering()->getData().rotAcc;
	//data.rotVel = lookSteering.getSteering()->getData().rotVel;

	data.acc = getDirectionVector(pOwner->getFacing()) * pOwner->getMaxAcc();

	//std::cout << "Wander Orientation " << wanderOrientation << std::endl;

	this->mData = data;
	return this;
}

Vector2D WanderSteering::getDirectionVector(float angle)
{
	return Vector2D(cos(angle), sin(angle));
}