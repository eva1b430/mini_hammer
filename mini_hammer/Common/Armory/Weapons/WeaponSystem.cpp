#include "WeaponSystem.h"
#include "RocketLauncher.h"


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
	Weapon* pWeapon = NULL;
	switch(entity_type)
	{
	case BaseEntity::emBaseEntity_Type_Rail_Gun:
		{

		}
		break;
	case BaseEntity::emBaseEntity_Type_Rocket_Launcher:
		{
			pWeapon = new RocketLauncher(m_pVehicle);
		}
		break;
	case BaseEntity::emBaseEntity_Type_Shotgun:
		{

		}
		break;
	default:
		{

		}
		break;
	}

	m_WeaponMap[entity_type] = pWeapon;

	// ¼òµ¥Âß¼­µÄÌí¼Ó
	m_pCurrentWeapon = pWeapon;
}

void WeaponSystem::ShootAt( Vector2D pos )
{
	if (m_pCurrentWeapon)
	{
		m_pCurrentWeapon->ShootAt(pos);
	}
}
