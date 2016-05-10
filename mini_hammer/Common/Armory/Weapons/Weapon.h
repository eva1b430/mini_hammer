#ifndef WEAPON_H
#define WEAPON_H
#include "2D/Vector2D.h"

// 文件控制（发射器只负责标记某种箭矢，发射间隔，发射行为，以及修改箭矢属性）
// 发射器得到方式：初始得到，通过物品得到，升级约束得到
class Vehicle;
class Weapon
{
public:
	Weapon(Vehicle* pVehicle, double dMaxProjectileSpeed)
		: m_pVehicle(pVehicle)
		, m_dMaxProjectileSpeed(dMaxProjectileSpeed)
	{

	}

	~Weapon(void);

	// 朝向某一个位置开火
	virtual void  ShootAt(Vector2D pos) = 0;

protected:
	// 拥有武器的智能体
	Vehicle*			m_pVehicle;

	// 攻击间隔
	double				m_dMaxProjectileSpeed;
};
#endif

