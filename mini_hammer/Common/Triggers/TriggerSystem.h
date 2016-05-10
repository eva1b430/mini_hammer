#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H
#include "Trigger.h"
#include "GameWorld.h"
#include <list>


using namespace std;

// ��������������
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
	// ����������
	TriggerList m_Triggers;

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
};
#endif /*TRIGGERSYSTEM_H*/

