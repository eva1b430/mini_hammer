#ifndef WEAPON_H
#define WEAPON_H
#include "2D/Vector2D.h"

// �ļ����ƣ�������ֻ������ĳ�ּ�ʸ����������������Ϊ���Լ��޸ļ�ʸ���ԣ�
// �������õ���ʽ����ʼ�õ���ͨ����Ʒ�õ�������Լ���õ�
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

	// ����ĳһ��λ�ÿ���
	virtual void  ShootAt(Vector2D pos) = 0;

protected:
	// ӵ��������������
	Vehicle*			m_pVehicle;

	// �������
	double				m_dMaxProjectileSpeed;
};
#endif

