#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H

class Vehicle;
class WeaponSystem
{
public:
	WeaponSystem(Vehicle* pVehicle)
		: m_pVehicle(pVehicle)
	{

	}

	~WeaponSystem(void);

private:
	// 拥有武器系统的智能体
	Vehicle*			m_pVehicle;
};
#endif // WEAPONSYSTEM_H

