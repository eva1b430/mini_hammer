#include "Goal_FollowPath.h"
#include "GlobalVar.h"
#include "GraphAlgorithms.h"
#include "Goal_SeekToPosition.h"


int Goal_FollowPath::Process()
{
	ActivateIfInactive();

	m_emStatus = (GoalStatus_Type)ProcessSubgoals();

	if (m_emStatus == GoalStatus_Completed && !m_Path.empty())
	{
		Activate(); 
	}

	return m_emStatus;
}

void Goal_FollowPath::Activate()
{
	//RemoveAllSubgoals();

	m_emStatus = GoalStatus_Active;

	// 获取一个边
	int nPathIndex = m_Path.front();

	// 
	m_Path.pop_front();

	Vector2D currentPos = GlobalVar::instance().GetPathfinder()->GetGraph()->GetNode(nPathIndex).GetPos();

	AddSubGoal(new Goal_SeekToPosition(m_pOwner, currentPos));
}

void Goal_FollowPath::Terminate()
{
	// 什么也不做
}

void Goal_FollowPath::Render()
{
	// 绘制最短路径
	glLineWidth(2.0f);
	if (m_Path.size() > 0)
	{
		std::list<int>::iterator it = m_Path.begin();
		std::list<int>::iterator nxt = it;
		++nxt;

		for (it; nxt != m_Path.end(); ++it, ++nxt)
		{
			CCPoint posStart = GlobalVar::instance().HammerPosToCocosPos(GlobalVar::instance().GetPathfinder()->GetGraph()->GetNode(*it).GetPos());
			CCPoint posEnd = GlobalVar::instance().HammerPosToCocosPos(GlobalVar::instance().GetPathfinder()->GetGraph()->GetNode(*nxt).GetPos());
			ccDrawLine(posStart, posEnd);
		}
	}
}




