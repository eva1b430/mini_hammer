#include "Goal.h"
#include "misc/Cgdi.h"


Goal::~Goal(void)
{

}

std::string Goal::GetGoalName()
{
	switch(m_emType)
	{
	case GoalType_Think:
		return "think";
	case GoalType_Explore:
		return "explore";
	case GoalType_Arrive_At_Position:
		return "arriveAtPosition";
	case GoalType_Seek_To_Position:
		return "seekToPosition";
	case GoalType_Follow_Path:
		return "followPath";
	case GoalType_Traverse_Edge:
		return "traverseEdge";
	case GoalType_Move_To_Position:
		return "moveToPosition";
	case GoalType_Get_Health:
		return "getHealth";
	case GoalType_Get_Shotgun:
		return "getShotgun";
	case GoalType_Get_Rocket_Launcher:
		return "getRocketLauncher";
	case GoalType_Get_Railgun:
		return "getRailgun";
	case GoalType_Wander:
		return "wander";
	case GoalType_Negotiate_Door:
		return "negotiateDoor";
	case GoalType_Attack_Target:
		return "attackTarget";
	case GoalType_Hunt_Target:
		return "huntTarget";
	case GoalType_Strafe:
		return "strafe";
	case GoalType_Adjust_Range:
		return "adjustRange";
	case GoalType_Say_Phrase:
		return "sayPhrase";
	default:
		return "UNKNOWN GOAL TYPE!";
	}
}

void Goal::RenderText(int& xOffset, int& yOffset)
{
	gdi->TransparentText();
	yOffset += 15;

	std::string strState = "";
	if (IsComplete()) 
	{
		gdi->TextColor(0,255,0);
		strState = "（已完成）";
	}
	if (IsInactive()) 
	{
		gdi->TextColor(0,0,0);
		strState = "（未激活）";
	}
	if (HasFailed()) 
	{
		gdi->TextColor(255,0,0);
		strState = "（已失败）";
	}
	if (IsActive()) 
	{
		gdi->TextColor(0,0,255);
		strState = "（已激活）";
	}

	gdi->TextAtPos(xOffset, yOffset, GetGoalName() + strState);
}
