#ifndef GOAL_FOLLOWPATH_H
#define GOAL_FOLLOWPATH_H

#include "Vehicle.h"
#include "Goal_Composite.h"


class Goal_FollowPath : public Goal_Composite
{
public:
	// 不能是引用，因为这里要删掉一些边，所以会修改
	Goal_FollowPath(Vehicle* pOwner, std::list<int>	path)
		: Goal_Composite(pOwner, Goal::GoalType_Follow_Path)
		, m_Path(path)
	{

	}

	~Goal_FollowPath(void)
	{

	}

	int  Process();
	void Activate();
	void Terminate();

	void Render();

private:
	// 给定路径
	std::list<int>	m_Path;
};
#endif // GOAL_FOLLOWPATH_H
