#ifndef GOAL_THINK_H
#define GOAL_THINK_H
#include "Vehicle.h"
#include "Goal_Composite.h"
#include "2D/Vector2D.h"

class Goal_Think : public Goal_Composite
{
public:
	Goal_Think(Vehicle* pOwner)
		: Goal_Composite(pOwner, Goal::GoalType_Think)
	{

	}

	~Goal_Think(void)
	{
		
	}

	int  Process();
	void Activate();
	void Terminate();
};

#endif // GOAL_THINK_H
