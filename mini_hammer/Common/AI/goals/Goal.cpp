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
		return "GoalType_Think";
	case GoalType_Explore:
		return "GoalType_Explore";
	case GoalType_Arrive_At_Position:
		return "GoalType_Arrive_At_Position";
	case GoalType_Seek_To_Position:
		return "GoalType_Seek_To_Position";
	case GoalType_Follow_Path:
		return "GoalType_Follow_Path";
	case GoalType_Traverse_Edge:
		return "GoalType_Traverse_Edge";
	case GoalType_Move_To_Position:
		return "GoalType_Move_To_Position";
	case GoalType_Get_Health:
		return "GoalType_Get_Health";
	case GoalType_Get_Shotgun:
		return "GoalType_Get_Shotgun";
	case GoalType_Get_Rocket_Launcher:
		return "GoalType_Get_Rocket_Launcher";
	case GoalType_Get_Railgun:
		return "GoalType_Get_Railgun";
	case GoalType_Wander:
		return "GoalType_Wander";
	case GoalType_Negotiate_Door:
		return "GoalType_Negotiate_Door";
	case GoalType_Attack_Target:
		return "GoalType_Attack_Target";
	case GoalType_Hunt_Target:
		return "GoalType_Hunt_Target";
	case GoalType_Strafe:
		return "GoalType_Strafe";
	case GoalType_Adjust_Range:
		return "GoalType_Adjust_Range";
	case GoalType_Say_Phrase:
		return "GoalType_Say_Phrase";
	default:
		return "UNKNOWN GOAL TYPE!";
	}
}

void Goal::RenderText(int& xOffset, int& yOffset)
{
	gdi->TransparentText();
	yOffset += 15;
	if (IsComplete()) gdi->TextColor(0,255,0);
	if (IsInactive()) gdi->TextColor(0,0,0);
	if (HasFailed()) gdi->TextColor(255,0,0);
	if (IsActive()) gdi->TextColor(0,0,255);

	gdi->TextAtPos(xOffset, yOffset, GetGoalName());
	//xOffset += 10;
}
