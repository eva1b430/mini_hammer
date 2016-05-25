#ifndef WEAPON_H
#define WEAPON_H
#include "2D/Vector2D.h"
#include "Regulator.h"

// �ļ����ƣ�������ֻ������ĳ�ּ�ʸ����������������Ϊ���Լ��޸ļ�ʸ���ԣ�
// �������õ���ʽ����ʼ�õ���ͨ����Ʒ�õ�������Լ���õ�
class Vehicle;
class Weapon
{
public:
	Weapon(Vehicle* pVehicle, double dMaxProjectileSpeed);
	~Weapon(void);

	// ����ĳһ��λ�ÿ���
	virtual void  ShootAt(Vector2D pos) = 0;

protected:
	bool IsReadyForNextShot();

protected:
	// ӵ��������������
	Vehicle*			m_pVehicle;

	// �ӵ�������ٶȣ��ñ�������Ԥ��׼��λ��
	double				m_dMaxProjectileSpeed;

	// �������
	Regulator*          m_pFireRegulator;
};
#endif

