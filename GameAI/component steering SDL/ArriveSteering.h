#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();

protected:
	

	Vector2D diff;
	float distance;
	float targetSpeed;
	float targetRad = 2;
	float slowRad = 100;

};