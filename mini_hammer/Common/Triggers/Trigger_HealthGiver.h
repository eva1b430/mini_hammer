#ifndef TRIGGER_HEALTHGIVER_H
#define TRIGGER_HEALTHGIVER_H
#include "Trigger.h"

// 补给
class Trigger_HealthGiver : public RegionTrigger
{
public:
	Trigger_HealthGiver( Vector2D pos, 
						 double radius )
						 : RegionTrigger(pos, radius)
	{

	}
	~Trigger_HealthGiver(void);

	// 可以脚本化
	void Try(Vehicle* pVehicle);
};
#endif /*TRIGGER_HEALTHGIVER_H*/

