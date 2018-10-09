#include "ComponentManager.h"
#include "SteeringComponent.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "WanderChaseSteering.h"
#include "ArriveFaceSteering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "AlignmentSteering.h"
#include "FlockingSteering.h"


SteeringComponent::SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID) 
	:Component(id)
	, mPhysicsComponentID(physicsComponentID)
	, mpSteering(NULL)
{
}

SteeringComponent::~SteeringComponent()
{
	delete mpSteering;
}

void SteeringComponent::applySteering(PhysicsComponent& physicsComponent)
{
	if (mpSteering != NULL)
	{
		//allow Steering to run
		mpSteering->update();
		//set physics data to that of the Steering
		physicsComponent.setData(mpSteering->getData());
		//update component's data
		mData.targetLoc = mpSteering->getTargetLoc();
	}
}

void SteeringComponent::setData(const SteeringData& data)
{
	mData = data;

	switch (data.type)
	{
		case Steering::SEEK:
		{
			//cleanup old steering - todo: check for already existing steering and reuse if possible
			delete mpSteering;
			//create new steering
			mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::FLEE:
		{
			mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, true);
			break;
		}
		case Steering::ARRIVE:
		{
			mpSteering = new ArriveSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::FACE:
		{
			mpSteering = new FaceSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::WANDER:
		{
			mpSteering = new WanderSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::WANDERCHASE:
		{
			mpSteering = new WanderChaseSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::ARRIVEFACE:
		{
			mpSteering = new ArriveFaceSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::COHESION:
		{
			mpSteering = new CohesionSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::SEPARATION:
		{
			mpSteering = new SeparationSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::ALIGNMENT:
		{
			mpSteering = new AlignmentSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::FLOCKING:
		{
			mpSteering = new FlockingSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		default:
		{

		}
	};
}

