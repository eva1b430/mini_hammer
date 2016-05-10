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

	// 计算合力
	Vector2D Calculate();

	// 检查是否开启某种行为
	bool On(Behavior_Type bt){return (m_nFlags & bt) == bt;}

	// 设置行为
	void SeekOn(){m_nFlags |= seek;}
	void ArriveOn(){m_nFlags |= arrive;}

	// 取消某种行为
	void SeekOff()  {if(On(seek))   m_nFlags ^=seek;}
	void ArriveOff(){if(On(arrive)) m_nFlags ^=arrive;}

	// 查询是否正在具备某种行为
	bool isSeekOn(){return On(seek);}
	bool isArriveOn(){return On(arrive);}

	// 实现具体的某种行为
	Vector2D Seek(Vector2D TargetPos);
	Vector2D Arrive(Vector2D TargetPos);

	void SetTarget(Vector2D t){m_vTarget = t;}
	Vector2D  GetTarget()const{return m_vTarget;}

private:
	// 被控制的智能体
	Vehicle*			m_pVehicle;
	// 行为类掩码
	int					m_nFlags;
	// 行为类计算出来的合力
	Vector2D			m_vSteeringForce;

	// 目标位置
	Vector2D			m_vTarget;
};
#endif

