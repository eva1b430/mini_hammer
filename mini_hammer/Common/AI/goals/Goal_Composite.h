#ifndef GOAL_COMPOSITE_H
#define GOAL_COMPOSITE_H
#include "Vehicle.h"
#include "Goal.h"
#include "2D/Vector2D.h"
#include <list>

using namespace std;
class Goal_Composite : public Goal
{
public:
	// 子任务列表
	typedef std::list<Goal*> SubgoalList;

public:
	// 其实它和基类拥有一致的参数列表，因为它不能实例化
	Goal_Composite(Vehicle* pOwner, GoalType_Type emType)
		: Goal(pOwner, emType)
	{

	}
	~Goal_Composite(void)
	{
		RemoveAllSubgoals();
	}

	// 加入一个新任务
	void AddSubGoal(Goal* g)
	{
		// 是加入到前面
		m_SubGoals.push_front(g);
	}

	void RemoveAllSubgoals()
	{
		for (SubgoalList::iterator it = m_SubGoals.begin();
			it != m_SubGoals.end();
			++it)
		{  
			(*it)->Terminate();

			delete *it;
		}

		m_SubGoals.clear();
	}

	void  Render()
	{
		if (!m_SubGoals.empty())
		{
			m_SubGoals.front()->Render();
		}
	}

protected:
	// 执行子任务
	int ProcessSubgoals()
	{
		while (!m_SubGoals.empty() &&
			   (m_SubGoals.front()->IsComplete() || m_SubGoals.front()->HasFailed()))
		{
			// 子任务没有办法复活，因此它们一旦失败，就终结了，但组合任务本身可以重新被激活
			m_SubGoals.front()->Terminate();
			delete m_SubGoals.front();
			m_SubGoals.pop_front();
		}

		// 对于一个组合任务来说，直到任务列表为空，才表示它已经完成
		if (!m_SubGoals.empty())
		{
			int StatusOfSubGoals = m_SubGoals.front()->Process();

			if (StatusOfSubGoals == GoalStatus_Completed && m_SubGoals.size() > 1)
			{
				return GoalStatus_Active;
			}

			return StatusOfSubGoals;
		}
		else
		{
			return GoalStatus_Completed;
		}
	}

private:
	// 容器
	SubgoalList   m_SubGoals;
	

};

#endif // GOAL_COMPOSITE_H
