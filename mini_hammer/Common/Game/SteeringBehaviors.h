#ifndef STEERINGBEHAVIORS_H
#define STEERINGBEHAVIORS_H
#include "2D/Vector2D.h"

class Vehicle;
class SteeringBehaviors
{
public:
	enum Behavior_Type
	{
		none               = 0x00000,
		seek               = 0x00002,
		arrive             = 0x00008,
		wander             = 0x00010,
		separation         = 0x00040,
		wall_avoidance     = 0x00200,
	};

public:
	SteeringBehaviors(Vehicle* agent);
	~SteeringBehaviors(void);

	// �������
	Vector2D Calculate();

	// ����Ƿ���ĳ����Ϊ
	bool On(Behavior_Type bt){return (m_nFlags & bt) == bt;}

	// ������Ϊ
	void SeekOn(){m_nFlags |= seek;}
	void ArriveOn(){m_nFlags |= arrive;}

	// ȡ��ĳ����Ϊ
	void SeekOff()  {if(On(seek))   m_nFlags ^=seek;}
	void ArriveOff(){if(On(arrive)) m_nFlags ^=arrive;}

	// ��ѯ�Ƿ����ھ߱�ĳ����Ϊ
	bool isSeekOn(){return On(seek);}
	bool isArriveOn(){return On(arrive);}

	// ʵ�־����ĳ����Ϊ
	Vector2D Seek(Vector2D TargetPos);
	Vector2D Arrive(Vector2D TargetPos);

	void SetTarget(Vector2D t){m_vTarget = t;}
	Vector2D  GetTarget()const{return m_vTarget;}

private:
	// �����Ƶ�������
	Vehicle*			m_pVehicle;
	// ��Ϊ������
	int					m_nFlags;
	// ��Ϊ���������ĺ���
	Vector2D			m_vSteeringForce;

	// Ŀ��λ��
	Vector2D			m_vTarget;
};
#endif

