#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H

#include "BaseEntity.h"
#include <map>


using namespace std;
class Vehicle;
class Weapon;
// �������ǲ������κ������ģ���ֻ�ǳ�������ϵͳ
class WeaponSystem
{
public:
	WeaponSystem(Vehicle* pVehicle);
	~WeaponSystem(void);

	// ���������������
	void AddWeapon(BaseEntity::BaseEntity_Type entity_type);

	// 
	void ShootAt(Vector2D pos);

private:
	// ӵ������ϵͳ��������
	Vehicle*									m_pVehicle;
	// ������
	map<BaseEntity::BaseEntity_Type, Weapon*>	m_WeaponMap;
	// ��ǰ����
	Weapon*										m_pCurrentWeapon;
};
#endif // WEAPONSYSTEM_H

