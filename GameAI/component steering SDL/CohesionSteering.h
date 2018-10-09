#include <Trackable.h>
#include <map>
#include "Steering.h"
#include "Unit.h"

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();

	Vector2D target;
protected:


	Vector2D diff;
	float distance;
	float CohesionRadius = 150;
	
	Vector2D getNeighborhoodPos(Unit* pOwner);

private:

	

};