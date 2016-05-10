#ifndef GOAL_H
#define GOAL_H
#include "Vehicle.h"

class Goal
{
public:
	// 目标状态
	enum GoalStatus_Type
	{
		GoalStatus_Active = 0,			// 激活
		GoalStatus_Inactive,			// 待激活
		GoalStatus_Completed,			// 已完成
		GoalStatus_Failed				// 已失败
	};

	// 目标类型
	enum GoalType_Type
	{
		GoalType_Think,
		GoalType_Explore,
		GoalType_Arrive_At_Position,
		GoalType_Seek_To_Position,
		GoalType_Follow_Path,
		GoalType_Traverse_Edge,
		GoalType_Move_To_Position,
		GoalType_Get_Health,
		GoalType_Get_Shotgun,
		GoalType_Get_Rocket_Launcher,
		GoalType_Get_Railgun,
		GoalType_Wander,
		GoalType_Negotiate_Door,
		GoalType_Attack_Target,
		GoalType_Hunt_Target,
		GoalType_Strafe,
		GoalType_Adjust_Range,
		GoalType_Say_Phrase
	};

public:
	// 该类不提供默认构造
	Goal(Vehicle* pOwner, GoalType_Type emType)
		: m_pOwner(pOwner)
		, m_emType(emType)
		, m_emStatus(GoalStatus_Inactive)
	{
		// 默认目标状态是“待激活”
	}

	~Goal(void);

	bool         IsComplete()const{return m_emStatus == GoalStatus_Completed;} 
	bool         IsActive()const{return m_emStatus == GoalStatus_Active;}
	bool         IsInactive()const{return m_emStatus == GoalStatus_Inactive;}
	bool         HasFailed()const{return m_emStatus == GoalStatus_Failed;}
	int          GetType()const{return m_emType;}

	//logic to run when the goal is activated.
	virtual void Activate() = 0;

	//logic to run each update-step
	virtual int  Process() = 0;

	//logic to run when the goal is satisfied. (typically used to switch
	//off any active steering behaviors)
	virtual void Terminate() = 0;

	// 辅助调试
	virtual void Render(){}

protected:
	void ActivateIfInactive()
	{
		if (IsInactive())
		{
			Activate();
		}
	}

	void ReactivateIfFailed()
	{
		// 状态切换到待激活
		if (HasFailed())
		{
			m_emStatus = GoalStatus_Inactive;
		}
	}

protected:
	// 拥有者
	Vehicle*		m_pOwner;

	// 任务类型
	GoalType_Type	m_emType;

	// 任务状态
	GoalStatus_Type m_emStatus;
};

#endif

