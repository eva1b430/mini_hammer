#ifndef GOAL_COMPOSITE_H
#define GOAL_COMPOSITE_H
#include "Vehicle.h"
#include "Goal.h"
#include "2D/Vector2D.h"
#include "misc/Cgdi.h"
#include <list>

using namespace std;
class Goal_Composite : public Goal
{
public:
	// �������б�
	typedef std::list<Goal*> SubgoalList;

public:
	// ��ʵ���ͻ���ӵ��һ�µĲ����б���Ϊ������ʵ����
	Goal_Composite(Vehicle* pOwner, GoalType_Type emType)
		: Goal(pOwner, emType)
	{

	}
	~Goal_Composite(void)
	{
		RemoveAllSubgoals();
	}

	// ����һ��������
	void AddSubGoal(Goal* g)
	{
		// �Ǽ��뵽ǰ��
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

	virtual void RenderText(int& xOffset, int& yOffset)
	{
		// �Ȼ����Լ�״̬
		Goal::RenderText(xOffset, yOffset);
		xOffset += 10;

		gdi->TransparentText();
		SubgoalList::const_reverse_iterator it;

		// �����������ͼ
		for (it = m_SubGoals.rbegin(); 
			it != m_SubGoals.rend(); 
			++it)
		{
			(*it)->RenderText(xOffset, yOffset);
		}

		xOffset -= 10;
	}

	void  Render()
	{
		if (!m_SubGoals.empty())
		{
			m_SubGoals.front()->Render();
		}
	}

protected:
	// ִ��������
	int ProcessSubgoals()
	{
		while (!m_SubGoals.empty() &&
			   (m_SubGoals.front()->IsComplete() || m_SubGoals.front()->HasFailed()))
		{
			// ������û�а취����������һ��ʧ�ܣ����ս��ˣ������������������±�����
			m_SubGoals.front()->Terminate();
			delete m_SubGoals.front();
			m_SubGoals.pop_front();
		}

		// ����һ�����������˵��ֱ�������б�Ϊ�գ��ű�ʾ���Ѿ����
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
	// ����
	SubgoalList   m_SubGoals;
	

};

#endif // GOAL_COMPOSITE_H
