#include "Goal_Think.h"
#include "Goal_SeekToPosition.h"
#include "Goal_Explore.h"
#include "Goal_FollowPath.h"

int Goal_Think::Process()
{
	// ������ߵ�Active
	ActivateIfInactive();

	int SubgoalStatus = ProcessSubgoals();

	if (SubgoalStatus == GoalStatus_Completed || SubgoalStatus == GoalStatus_Failed)
	{
		m_emStatus = GoalStatus_Inactive;
	}

	return m_emStatus;
}

void Goal_Think::Activate()
{
	RemoveAllSubgoals();

	// ��ʵ��������Ŀ�����۵ó�����Ŀ��
// 	float offsetX = 100 - rand() % 200;
// 	float offsetY = 100 - rand() % 200;
// 	Vector2D posTarget = Vector2D(200.0f, 200.0f);
// 	posTarget.x += offsetX;
// 	posTarget.y += offsetY;
// 	AddSubGoal(new Goal_SeekToPosition(m_pOwner, posTarget));

	AddSubGoal(new Goal_Explore(m_pOwner));

	//Arbitrate();

	m_emStatus = GoalStatus_Active;
}

void Goal_Think::Terminate()
{
	// ʲôҲ������Goal_Think����߼���ģ�����Զ����
}