#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H

#include "Trigger.h"
#include <list>

using namespace std;


// 定义一个智能体容器
typedef list<Vehicle*> VehicleList;
typedef list<Trigger*> TriggerList;
// 触发器管理容器
class TriggerSystem
{
public:
	TriggerSystem(void)
	{
		Clear();
	}
	~TriggerSystem(void)
	{
		
	}

private:
	// 触发器容器
	TriggerList m_Triggers;

public:
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

	void Clear()
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
};
#endif /*TRIGGERSYSTEM_H*/

