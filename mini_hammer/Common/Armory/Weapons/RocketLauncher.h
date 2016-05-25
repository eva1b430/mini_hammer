#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H
#include "Weapon.h"

class RocketLauncher : public Weapon
{
public:
	RocketLauncher(Vehicle* pVehicle)
		: Weapon(pVehicle, 3)
	{

	}

	~RocketLauncher(void);

	// 朝向某一个位置开火
	virtual void  ShootAt(Vector2D pos);
};
#endif

