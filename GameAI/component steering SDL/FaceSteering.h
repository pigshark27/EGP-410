#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();
protected:
	

	Vector2D direction;
	float distance;
	float targetRotation;
	float currentRotation;
	float rotationDiff;
	float dir;
	float PI = 3.1415926;
	float RAD2DEG = 180 / PI;
	float DEG2RAD = PI / 180;
	float slowDeg = 90;
};