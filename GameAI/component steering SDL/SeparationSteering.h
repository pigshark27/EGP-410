#include <Trackable.h>
#include <map>
#include "Steering.h"
#include "Unit.h"

class SeparationSteering : public Steering
{
public:
	SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();

	Vector2D target;
protected:


	Vector2D diff;
	float distance;
	float separationRadius = 100;
	float separationAngle = 180;
	Vector2D direction;
	float targetRotation;
	float currentRotation;
	float PI = 3.1415926;
	float RAD2DEG = 180 / PI;
	float DEG2RAD = PI / 180;


	Vector2D getNeighborhoodPos(Unit* pOwner, float currentRot, float targetRot);

private:



};