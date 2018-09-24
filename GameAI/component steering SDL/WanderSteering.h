#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

protected:
	virtual Steering* getSteering();

	Vector2D diff;
	float distance;
	float targetSpeed;
	float targetOrientation;

	Vector2D target;
	float wanderOffset = 170;
	float wanderRadius = 10;
	float wanderRate = 0.5; //2 * 3.1415926;
	float wanderOrientation = 0;


private:
	Vector2D getDirectionVector(float direction);

};
