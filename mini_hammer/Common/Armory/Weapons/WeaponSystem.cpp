#include "WeaponSystem.h"


WeaponSystem::WeaponSystem(Vehicle* pVehicle)
	: m_pVehicle(pVehicle)
{
	map<BaseEntity::BaseEntity_Type, Weapon*>::iterator itr;
	for (itr = m_WeaponMap.begin(); itr != m_WeaponMap.end(); itr++)
	{
		delete itr->second;
		itr->second = NULL;
	}
	m_WeaponMap.clear();

	m_pCurrentWeapon = NULL;
}

WeaponSystem::~WeaponSystem(void)
{

}

void WeaponSystem::AddWeapon(BaseEntity::BaseEntity_Type entity_type)
{

}
