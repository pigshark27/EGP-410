#include <cassert>

#include "Steering.h"
#include "FlockingSteering.h"
#include "FaceSteering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "AlignmentSteering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


FlockingSteering::FlockingSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = Steering::FLOCKING;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* FlockingSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	if (first)
	{
		data.acc = 0;
		data.rotAcc = 0;
		data.vel = 0;
		data.rotVel = 0;
		first = false;
	}
	//movement
	if (inHood(pOwner))
	{
		//flock
		CohesionSteering cohesion(mOwnerID, target, mTargetID, false);
		cohesion.getSteering();
		SeparationSteering separation(mOwnerID, target, mTargetID, false);
		separation.getSteering();
		AlignmentSteering alignment(mOwnerID, target, mTargetID, false);
		alignment.getSteering();

		flockTarget = ((cohesion.target * 0.5) + (separation.target * 0.25) + (alignment.target * 0.25)); //test values

		//FaceSteering lookSteering(mOwnerID, flockTarget, mTargetID, false);
		//lookSteering.getSteering();
		//data.rotAcc = lookSteering.getSteering()->getData().rotAcc;
		//data.rotVel = lookSteering.getSteering()->getData().rotVel;
		flockTarget.normalize();
		data.acc = flockTarget;//* data.maxSpeed;
		data.acc *= data.maxAccMagnitude;

		float faceTarget = atan2(data.vel.getY(), data.vel.getX()) + 0.5 * PI - PI/2;
		pOwner->getPositionComponent()->setFacing(faceTarget);

		//std::cout << "Target: " << target.getX() << ", " << target.getY() << std::endl; // print statement
		//std::cout << "Cohesion Target: " << cohesion.target.getX() << ", " << cohesion.target.getY() << std::endl; // print statement
	}
	
	else
	{
		//wander
		WanderSteering wander(mOwnerID, target, mTargetID, false);
		wander.getSteering();
		data = wander.getData();
	}
	this->mData = data;
	return this;
	
	
	
	
}

Vector2D FlockingSteering::getDirectionVector(float angle)
{
	return Vector2D(cos(angle), sin(angle));
}

bool FlockingSteering::inHood(Unit* owner)
{
	float hoodCount = 0;
	std::map<UnitID, Unit*> unitMap = gpGame->getUnitManager()->mUnitMap;
	for (auto it = unitMap.begin(); it != unitMap.end(); ++it)
	{
		if (it->second->mID != owner->mID) {
			if ((owner->getPositionComponent()->getPosition() - it->second->getPositionComponent()->getPosition()).getLength() <= hoodRad)
			{
				hoodCount += 1;
			}
		}
	}
	if (hoodCount == 0)
	{
		return false;
	}
	return true;
}
