#include "Trigger_HealthGiver.h"

Trigger_HealthGiver::~Trigger_HealthGiver(void)
{
}

void Trigger_HealthGiver::Try(Vehicle* pVehicle)
{
	// 条件可以可视化编辑
	if (m_pRegion->isTouching(pVehicle->GetPos(), pVehicle->GetBRadius()))
	{
		// 触发内容可以可视化编辑

		// 加血

		// 加完血立即干掉这个触发器，因为它是只会被一次触发的
	}
}
