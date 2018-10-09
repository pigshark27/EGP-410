#include <Trackable.h>
#include <map>
#include "Steering.h"
#include "Unit.h"

class AlignmentSteering : public Steering
{
public:
	AlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();

	Vector2D target;
protected:


	Vector2D diff;
	float distance;
	float alignmentRadius = 100;

	Vector2D getHoodAlignment(Unit* pOwner);

private:



};