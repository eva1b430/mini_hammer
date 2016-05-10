#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "MovingEntity.h"
#include "GameWorld.h"
#include "2D/Vector2D.h"
#include <string>

using namespace std;
// 文件控制（箭矢只负责判定命中，命中效果运行脚本，箭矢属性不由自身修改，由发射器修改）
// 箭矢得到方式：完全依赖于发射器
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
								Vector2D(0,0),	// 速度是0
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

	// 检测终结和碰撞
	bool isDead()const{return m_bDead;}
	bool HasImpacted()const{return m_bImpacted;}
	
protected:
	// 发射者的ID，做碰撞时候用到
	int			m_nShooterID;

	// 发射起点
	Vector2D    m_vOrigin;
	// 发射朝向
	Vector2D    m_vTarget;
	
	// 逻辑世界
	GameWorld*	m_pWorld;

	// 伤害
	int         m_nDamageInflicted;

	// 是否终结
	bool        m_bDead;
	// 是否碰撞
	bool        m_bImpacted;
	// 碰撞点
	Vector2D    m_vImpactPoint;
	// 缓冲时间
	//double      m_dTimeOfCreation;


};
#endif

