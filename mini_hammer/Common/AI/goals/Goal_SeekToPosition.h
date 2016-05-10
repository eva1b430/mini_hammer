#ifndef GOAL_SEEK_TO_POSITION_H
#define GOAL_SEEK_TO_POSITION_H
#include "Vehicle.h"
#include "Goal.h"
#include "2D/Vector2D.h"

class Goal_SeekToPosition : public Goal
{
public:
	Goal_SeekToPosition(Vehicle* pOwner, Vector2D posTarget)
		: Goal(pOwner, GoalType_Seek_To_Position)
		, m_vPosition(posTarget)
	{

	}
	~Goal_SeekToPosition(void);

	void Activate();
	int  Process();
	void Terminate();

private:
	Vector2D  m_vPosition;


};

#endif

