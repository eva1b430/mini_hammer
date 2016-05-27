#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H
#include "BaseEntity.h"
#include "2D/Vector2D.h"
#include "2D/C2DMatrix.h"

class MovingEntity : public BaseEntity
{
public:
	MovingEntity(	Vector2D position,
					double    radius,
					Vector2D velocity,
					Vector2D heading,
					double    mass,
					double    max_speed,
					double    max_force,
					double    turn_rate	)
		: BaseEntity(emBaseEntity_Type_Default, position, radius)
		, m_vVelocity(velocity)
		, m_vHeading(heading)
		, m_vSide(m_vHeading.Perp())
		, m_dMass(mass)
		, m_dMaxSpeed(max_speed)
		, m_dMaxForce(max_force)
		, m_dMaxTurnRate(turn_rate)
	{
		
	}

	virtual ~MovingEntity(void);

	// 速度控制
	Vector2D  GetVelocity()const{return m_vVelocity;}
	void      SetVelocity(const Vector2D& NewVel){m_vVelocity = NewVel;}

	// 获取质量（质量不可修改）
	double    GetMass()const{return m_dMass;}

	// 获取侧向
	Vector2D  GetSide()const{return m_vSide;}

	// 最大速度控制
	double    GetMaxSpeed()const{return m_dMaxSpeed;}
	void      SetMaxSpeed(double new_speed){m_dMaxSpeed = new_speed;}

	// 最大驱动力控制
	double    GetMaxForce()const{return m_dMaxForce;}
	void      SetMaxForce(double mf){m_dMaxForce = mf;}

	bool      IsSpeedMaxedOut()const{return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.LengthSq();}
	double    GetSpeed()const{return m_vVelocity.Length();}
	double    GetSpeedSq()const{return m_vVelocity.LengthSq();}

	// 朝向控制，朝向改变，相应的侧向也会发生改变
	Vector2D  GetHeading()const{return m_vHeading;}
	void      SetHeading(Vector2D new_heading);

	// 这个函数很方便，通过一个目标位置，就可以立刻修改朝向，和侧向
	bool      RotateHeadingToFacePosition(Vector2D target);

	// 转身速率控制
	double    GetMaxTurnRate()const{return m_dMaxTurnRate;}
	void      SetMaxTurnRate(double val){m_dMaxTurnRate = val;}

	// 通过Heading向量返回夹角
	float	  GetAngelByHeading();

protected:
	// 定义速度
	Vector2D	m_vVelocity;
	// 定义朝向
	Vector2D	m_vHeading;
	// 定义侧向
	Vector2D	m_vSide;
	// 定义质量
	double		m_dMass;
	// 定义最大速度
	double		m_dMaxSpeed;
	// 定义最大驱动力
	double		m_dMaxForce;
	// 最大转身速率
	double		m_dMaxTurnRate;
};

// 该函数通过给定一个目标位置，修改MovingEntity的朝向、侧向
inline bool MovingEntity::RotateHeadingToFacePosition(Vector2D target)
{
	Vector2D toTarget = Vec2DNormalize(target - m_vPos);

	// 通过向量点乘计算公式，反算夹角
	double angle = acos(m_vHeading.Dot(toTarget));

	// 已经是正确朝向
	if (angle < 0.00001) 
	{
		return true;
	}

	//clamp the amount to turn to the max turn rate
	// 通过此处可以明白，该函数不是立即就调整了转向，而是放在逻辑循环中进行的
	if (angle > m_dMaxTurnRate) 
	{
		angle = m_dMaxTurnRate;
	}

	//The next few lines use a rotation matrix to rotate the player's heading
	//vector accordingly
	C2DMatrix RotationMatrix;

	//notice how the direction of rotation has to be determined when creating
	//the rotation matrix
	// 判别正逆时针
	RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));
	RotationMatrix.TransformVector2Ds(m_vHeading);
	RotationMatrix.TransformVector2Ds(m_vVelocity);

	//finally recreate m_vSide
	m_vSide = m_vHeading.Perp();

	return false;
}

inline void MovingEntity::SetHeading(Vector2D new_heading)
{
	// 设置的朝向一定是一个单位向量
	assert( (new_heading.LengthSq() - 1.0) < 0.00001);

	m_vHeading = new_heading;

	// 更改侧向
	m_vSide = m_vHeading.Perp();
}

#endif

