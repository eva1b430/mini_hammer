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
	// ӵ������ϵͳ��������
	Vehicle*			m_pVehicle;
};
#endif // WEAPONSYSTEM_H

