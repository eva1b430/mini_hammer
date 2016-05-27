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

	// 逻辑帧
	virtual void Update(double time_elapsed);

	// 渲染帧
	virtual void Render();
	virtual void draw(void);
	void PaintFOV();
	void PaintMark();

	// 获取Steering和World
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
	// 逻辑世界
	GameWorld*			m_pWorld;
	// 控制类
	SteeringBehaviors*	m_pSteering;

	//keeps a track of the most recent update time. (some of the
	//steering behaviors make use of this - see Wander)
	double              m_dTimeElapsed;

	// 发射器系统
	WeaponSystem*		m_pWeaponSys;

	// 行为树分频器
	Regulator*          m_pGoalArbitrationRegulator;
	// 视野分频器
	Regulator*          m_pVisionUpdateRegulator;

	// 行为树根节点
	Goal_Think*         m_pBrain;

	// 智能体视野（该视野甚至可以区分黑夜和白天）
	double              m_dFieldOfView;
	// 是否显示FOV
	bool				m_bFovDisplay;
	// 是否显示标记
	bool				m_bMarkDisplay;
	// 是否开启思维
	bool				m_bThink;
};
#endif

