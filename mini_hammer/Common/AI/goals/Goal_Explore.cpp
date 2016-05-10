#include "Goal_Explore.h"
#include "GlobalVar.h"
#include "GraphAlgorithms.h"
#include "Goal_SeekToPosition.h"
#include "Goal_FollowPath.h"

int Goal_Explore::Process()
{
	ActivateIfInactive();

	m_emStatus = (GoalStatus_Type)ProcessSubgoals();

	return m_emStatus;
}

void Goal_Explore::Activate()
{
	m_emStatus = GoalStatus_Active;

	RemoveAllSubgoals();

	// 获得导航图中一个随机图结点
	if (!m_bDestinationIsSet)
	{
		m_CurrentDestination = GlobalVar::instance().GetPathfinder()->GetGraph()->GetRandomNodePos();
		m_bDestinationIsSet = true;
	}

	// 停顿一下规划一条路径
	int nIndexClosestOwner = GlobalVar::instance().GetPathfinder()->GetGraph()->GetClosestNodeToPosition(m_pOwner->GetPos());
	int nIndexClosestTarget = GlobalVar::instance().GetPathfinder()->GetGraph()->GetClosestNodeToPosition(m_CurrentDestination);

	Graph_SearchDijkstra djk(*GlobalVar::instance().GetPathfinder()->GetGraph(), 
							nIndexClosestOwner,
							nIndexClosestTarget);

	// 通过Dijikstra算法
	Vector2D posSmall = GlobalVar::instance().GetPathfinder()->GetGraph()->GetNode(nIndexClosestOwner).GetPos();
	//AddSubGoal(new Goal_SeekToPosition(m_pOwner, m_CurrentDestination));

	// 接下来根据路径来进行
	AddSubGoal(new Goal_FollowPath(m_pOwner, djk.GetPathToTarget()));

	//float offsetX = 50 - rand() % 100;
	//float offsetY = 50 - rand() % 100;
	//Vector2D posTarget = Vector2D(200.0f, 200.0f);
	//posTarget.x += offsetX;
	//posTarget.y += offsetY;
	//AddSubGoal(new Goal_SeekToPosition(m_pOwner, m_CurrentDestination));
}

void Goal_Explore::Terminate()
{
	// 什么也不做
}

void Goal_Explore::Render()
{
	ccPointSize(8);
	ccDrawPoint(GlobalVar::instance().HammerPosToCocosPos(m_CurrentDestination));

	Goal_Composite::Render();
}




