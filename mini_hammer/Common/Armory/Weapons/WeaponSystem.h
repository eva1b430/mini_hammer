#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H

#include "BaseEntity.h"
#include <map>


using namespace std;
class Vehicle;
class Weapon;
class WeaponSystem
{
public:
	WeaponSystem(Vehicle* pVehicle);
	~WeaponSystem(void);

	// 添加武器到武器表
	void AddWeapon(BaseEntity::BaseEntity_Type entity_type);

private:
	// 拥有武器系统的智能体
	Vehicle*									m_pVehicle;
	// 武器表
	map<BaseEntity::BaseEntity_Type, Weapon*>	m_WeaponMap;
	// 当前武器
	Weapon*										m_pCurrentWeapon;
};
#endif // WEAPONSYSTEM_H

