#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H
#include "Trigger.h"
#include "GameWorld.h"
#include <list>


using namespace std;

// 触发器管理容器
class TriggerSystem
{
public:
	typedef list<Trigger*> TriggerList;

public:
	TriggerSystem(void)
	{

	}
	~TriggerSystem(void)
	{
		// 
		TriggerList::iterator itrTrigger;
		for (itrTrigger = m_Triggers.begin();
			itrTrigger != m_Triggers.end();
			itrTrigger++)
		{
			if ((*itrTrigger))
			{
				delete (*itrTrigger);
				(*itrTrigger) = NULL;
			}
		}

		m_Triggers.clear();
	}

private:
	// 触发器容器
	TriggerList m_Triggers;

	void Update(VehicleList& vehicles)
	{
		// 刷新触发器状态
		VehicleList::iterator itr;
		for (itr = vehicles.begin();
			itr != vehicles.end();
			itr++)
		{
			TriggerList::iterator itrTrigger;
			for (itrTrigger = m_Triggers.begin();
				itrTrigger != m_Triggers.end();
				itrTrigger++)
			{
				// 先更新状态

				// 再检测触发条件
				(*itrTrigger)->Try(*itr);
			}
		}
	}

	void Register(Trigger* trigger)
	{
		m_Triggers.push_back(trigger);
	}
};
#endif /*TRIGGERSYSTEM_H*/

