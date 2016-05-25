#include "Weapon.h"

Weapon::Weapon(Vehicle* pVehicle, double dMaxProjectileSpeed)
	: m_pVehicle(pVehicle)
	, m_dMaxProjectileSpeed(dMaxProjectileSpeed)
	, m_pFireRegulator(NULL)
{
	m_pFireRegulator = new Regulator(4.0f);
}

Weapon::~Weapon(void)
{
	if (m_pFireRegulator)
	{
		delete m_pFireRegulator;
		m_pFireRegulator = NULL;
	}
}

bool Weapon::IsReadyForNextShot()
{
	return m_pFireRegulator->isReady();
}
