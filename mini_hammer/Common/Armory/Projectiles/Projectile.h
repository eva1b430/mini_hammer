#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "MovingEntity.h"
#include "GameWorld.h"
#include "2D/Vector2D.h"
#include <string>

using namespace std;
// �ļ����ƣ���ʸֻ�����ж����У�����Ч�����нű�����ʸ���Բ��������޸ģ��ɷ������޸ģ�
// ��ʸ�õ���ʽ����ȫ�����ڷ�����
class EngineEntity;
class Projectile : public MovingEntity
{
public:
	//MovingEntity(	Vector2D position,
	//	double    radius,
	//	Vector2D velocity,
	//	Vector2D heading,
	//	double    mass,
	//	double    max_speed,
	//	double    max_force,
	//	double    turn_rate	)

	Projectile(	Vector2D	target,
				GameWorld*	world,
				int			ShooterID,
				int			damage,
				Vector2D	origin,
				double		radius,
				Vector2D	heading,
				double		mass,
				double		MaxSpeed, 
				double		MaxForce)
				: MovingEntity(	origin,
								radius,
								Vector2D(0,0),	// �ٶ���0
								heading,
								mass,
								MaxSpeed,
								MaxForce,
								0)
				, m_vTarget(target)
				, m_pWorld(world)
				, m_nShooterID(ShooterID)
				, m_nDamageInflicted(damage)
				, m_bDead(false)
				, m_bImpacted(false)
				, m_vOrigin(origin)
				
	{
		//m_dTimeOfCreation = Clock->GetCurrentTime();
	}


	~Projectile(void);

	virtual void Update() = 0;
	virtual void Render() = 0;

	// ����ս����ײ
	bool isDead()const{return m_bDead;}
	bool HasImpacted()const{return m_bImpacted;}
	
protected:
	// �����ߵ�ID������ײʱ���õ�
	int			m_nShooterID;

	// �������
	Vector2D    m_vOrigin;
	// ���䳯��
	Vector2D    m_vTarget;
	
	// �߼�����
	GameWorld*	m_pWorld;

	// �˺�
	int         m_nDamageInflicted;

	// �Ƿ��ս�
	bool        m_bDead;
	// �Ƿ���ײ
	bool        m_bImpacted;
	// ��ײ��
	Vector2D    m_vImpactPoint;
	// ����ʱ��
	//double      m_dTimeOfCreation;


};
#endif

