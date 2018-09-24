#include <cassert>

#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::FACE;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* FaceSteering::getSteering()
{

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::FACE)
	{
		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		direction = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	//face
	distance = direction.getLength();
	if (distance == 0)
	{
		data.rotAcc = 0.0f;
		data.rotVel = 0.0f;
	}
	
	data.vel = 0;
	data.acc = 0;

	targetRotation = atan2(-direction.getX(), direction.getY()) + 3.1415926;
	targetRotation = targetRotation * RAD2DEG + 270;
	targetRotation = fmod(targetRotation, 360);

	currentRotation = (pOwner->getFacing()) * RAD2DEG + 270;
	currentRotation = fmod(currentRotation, 360);

	std::cout << "targetRotation: " <<targetRotation << " currentRotation: " << currentRotation << std::endl; // print statement


	if (currentRotation < targetRotation + 2 && currentRotation > targetRotation - 2)
	{
		data.rotVel = 0.0f;
		data.rotAcc = 0.0f;
	}
	else
	{
		if (currentRotation < 0)
		{
			//targetRotation += 360;
		}
		if (fmod(targetRotation - currentRotation + 360, 360) < 180)
		{
			data.rotVel = 2.0f;
			data.rotAcc = 1.0f;
		}
		else
		{
			data.rotVel = -2.0f;
			data.rotAcc = 1.0f;
		}
		

	}
	


	this->mData = data;
	return this;
}