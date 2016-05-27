#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H

#include "Trigger.h"
#include <list>

using namespace std;


// ����һ������������
typedef list<Vehicle*> VehicleList;
typedef list<Trigger*> TriggerList;
// ��������������
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
	// ����������
	TriggerList m_Triggers;

public:
	void Update(VehicleList& vehicles)
	{
		// ˢ�´�����״̬
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
				// �ȸ���״̬

				// �ټ�ⴥ������
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

