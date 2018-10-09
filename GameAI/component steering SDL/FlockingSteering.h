#include <Trackable.h>
#include "Steering.h"
#include <map>
#include "Unit.h"

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();
protected:


	Vector2D diff;
	float distance;
	float targetSpeed = 100;
	float targetOrientation;

	Vector2D target;
	Vector2D flockTarget;
	
	bool first = true;
	float hoodRad = 150;
	float PI = 3.1415926;


private:
	Vector2D getDirectionVector(float direction);
	bool inHood(Unit* owner);
};
