#ifndef GOAL_EXPLORE_H
#define GOAL_EXPLORE_H

#include "Vehicle.h"
#include "Goal_Composite.h"
class Goal_Explore : public Goal_Composite
{
public:
	Goal_Explore(Vehicle* pOwner)
		: Goal_Composite(pOwner, Goal::GoalType_Think)
		, m_bDestinationIsSet(false)
	{

	}

	~Goal_Explore(void)
	{

	}

	int  Process();
	void Activate();
	void Terminate();
	void Render();

private:
	// ����Ƿ�������һ��Ŀ��
	bool		m_bDestinationIsSet;

	// ��ǰ��Ŀ�귽��
	Vector2D	m_CurrentDestination;
};
#endif // GOAL_EXPLORE_H
