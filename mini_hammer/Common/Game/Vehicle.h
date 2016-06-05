#ifndef VEHICLE_H
#define VEHICLE_H
#include "MovingEntity.h"
#include "SteeringBehaviors.h"
#include "2D/Vector2D.h"

class GameWorld;
class WeaponSystem;
class Regulator;
class Goal_Think;
class Vehicle : public MovingEntity
{
public:
	Vehicle(	GameWorld* world,
				Vector2D  position,
				double    radius,
				Vector2D  velocity,
				double    rotation,
				double    mass,
				double    max_speed,
				double    max_force,
				double    max_turn_rate);

	virtual ~Vehicle(void);

	// �߼�֡
	virtual void Update(double time_elapsed);

	// ��Ⱦ֡
	virtual void Render();
	virtual void draw(void);
	void PaintFOV();
	void PaintMark();

	// ��ȡSteering��World
	SteeringBehaviors* const	GetSteering()const{return m_pSteering;}
	GameWorld* const			GetWorld()const{return m_pWorld;}

	bool IsAtPosition(Vector2D pos)
	{
		const static double tolerance = 10.0;
		return Vec2DDistanceSq(GetPos(), pos) < tolerance * tolerance;
	}

	void SetFovDisplay(){m_bFovDisplay = true;}
	void SetFovHide(){m_bFovDisplay = false;}

	void SetMarkDisplay(){m_bMarkDisplay = true;}
	void SetMarkHide(){m_bMarkDisplay = false;}

	void EnableThink(){m_bThink = true;}
	void DisableThink(){m_bThink = false;}

	Goal_Think* GetBrain(){return m_pBrain;}

private:
	// �߼�����
	GameWorld*			m_pWorld;
	// ������
	SteeringBehaviors*	m_pSteering;

	//keeps a track of the most recent update time. (some of the
	//steering behaviors make use of this - see Wander)
	double              m_dTimeElapsed;

	// ������ϵͳ
	WeaponSystem*		m_pWeaponSys;

	// ��Ϊ����Ƶ��
	Regulator*          m_pGoalArbitrationRegulator;
	// ��Ұ��Ƶ��
	Regulator*          m_pVisionUpdateRegulator;

	// ��Ϊ�����ڵ�
	Goal_Think*         m_pBrain;

	// ��������Ұ������Ұ�����������ֺ�ҹ�Ͱ��죩
	double              m_dFieldOfView;
	// �Ƿ���ʾFOV
	bool				m_bFovDisplay;
	// �Ƿ���ʾ���
	bool				m_bMarkDisplay;
	// �Ƿ���˼ά
	bool				m_bThink;
};
#endif

