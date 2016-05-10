#ifndef GOAL_FOLLOWPATH_H
#define GOAL_FOLLOWPATH_H

#include "Vehicle.h"
#include "Goal_Composite.h"


class Goal_FollowPath : public Goal_Composite
{
public:
	// ���������ã���Ϊ����Ҫɾ��һЩ�ߣ����Ի��޸�
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
	// ����·��
	std::list<int>	m_Path;
};
#endif // GOAL_FOLLOWPATH_H
