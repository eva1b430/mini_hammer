#include "Goal_SeekToPosition.h"
Goal_SeekToPosition::~Goal_SeekToPosition(void)
{

}

int Goal_SeekToPosition::Process()
{
	ActivateIfInactive();

	if (m_pOwner->IsAtPosition(m_vPosition))
	{
		m_emStatus = GoalStatus_Completed;
	}

	return m_emStatus;
}

void Goal_SeekToPosition::Activate()
{
	m_emStatus = GoalStatus_Active;

	m_pOwner->GetSteering()->SetTarget(m_vPosition);
	m_pOwner->GetSteering()->SeekOn();
}

void Goal_SeekToPosition::Terminate()
{
	m_pOwner->GetSteering()->SeekOff();
	m_pOwner->GetSteering()->ArriveOff();

	m_emStatus = GoalStatus_Completed;
}
