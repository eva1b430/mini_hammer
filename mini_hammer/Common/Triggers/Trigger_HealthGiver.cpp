#include "Trigger_HealthGiver.h"

Trigger_HealthGiver::~Trigger_HealthGiver(void)
{
}

void Trigger_HealthGiver::Try(Vehicle* pVehicle)
{
	// �������Կ��ӻ��༭
	if (m_pRegion->isTouching(pVehicle->GetPos(), pVehicle->GetBRadius()))
	{
		// �������ݿ��Կ��ӻ��༭
		pVehicle->setScale(2.0f);

		// ��Ѫ

		// ����Ѫ�����ɵ��������������Ϊ����ֻ�ᱻһ�δ�����
	}
}
