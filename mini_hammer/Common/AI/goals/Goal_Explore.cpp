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

	// ��õ���ͼ��һ�����ͼ���
	if (!m_bDestinationIsSet)
	{
		m_CurrentDestination = GlobalVar::instance().GetPathfinder()->GetGraph()->GetRandomNodePos();
		m_bDestinationIsSet = true;
	}

	// ͣ��һ�¹滮һ��·��
	int nIndexClosestOwner = GlobalVar::instance().GetPathfinder()->GetGraph()->GetClosestNodeToPosition(m_pOwner->GetPos());
	int nIndexClosestTarget = GlobalVar::instance().GetPathfinder()->GetGraph()->GetClosestNodeToPosition(m_CurrentDestination);

	Graph_SearchDijkstra djk(*GlobalVar::instance().GetPathfinder()->GetGraph(), 
							nIndexClosestOwner,
							nIndexClosestTarget);

	// ͨ��Dijikstra�㷨
	Vector2D posSmall = GlobalVar::instance().GetPathfinder()->GetGraph()->GetNode(nIndexClosestOwner).GetPos();
	//AddSubGoal(new Goal_SeekToPosition(m_pOwner, m_CurrentDestination));

	// ����������·��������
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
	// ʲôҲ����
}

void Goal_Explore::Render()
{
	ccPointSize(8);
	ccDrawPoint(GlobalVar::instance().HammerPosToCocosPos(m_CurrentDestination));

	Goal_Composite::Render();
}




