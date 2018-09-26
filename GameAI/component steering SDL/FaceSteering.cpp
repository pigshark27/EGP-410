#include <cassert>

#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{

	mType = Steering::FACE;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	currentRotation = 0;
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

		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	
	//face
	distance = direction.getLength();
	if (distance == 0)
	{
		data.rotAcc = 0.0f;
		data.rotVel = 0.0f;
	}
	
	
	targetRotation = atan2(-direction.getX(), direction.getY()); + 3.1415926;
	targetRotation = targetRotation * RAD2DEG + 270;
	targetRotation = fmod(targetRotation, 360);

	currentRotation = (pOwner->getFacing()) * RAD2DEG + 180;
	currentRotation = fmod(currentRotation, 360);

	if (currentRotation < 0)
	{
		currentRotation += 360;
	}

	if (currentRotation < targetRotation + 4 && currentRotation > targetRotation - 4)
	{
		data.rotVel = 0.0f;
		data.rotAcc = 0.0f;
	}
	else
	{
		
		if (fmod(targetRotation - currentRotation + 360, 360) < 180)
		{
			//data.rotVel = 2.0f;
			data.rotAcc = 2.0f;

		}
		if (fmod(targetRotation - currentRotation + 360, 360) >= 180)
		{
			//data.rotVel = -2.0f;
			data.rotAcc = -2.0f;

		}
		

	}
	
	std::cout << "targetRotation: " <<targetRotation << " currentRotation: " << currentRotation << std::endl; // print statement

	this->mData = data;
	return this;
}