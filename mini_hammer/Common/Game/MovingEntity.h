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

	// �ٶȿ���
	Vector2D  GetVelocity()const{return m_vVelocity;}
	void      SetVelocity(const Vector2D& NewVel){m_vVelocity = NewVel;}

	// ��ȡ���������������޸ģ�
	double    GetMass()const{return m_dMass;}

	// ��ȡ����
	Vector2D  GetSide()const{return m_vSide;}

	// ����ٶȿ���
	double    GetMaxSpeed()const{return m_dMaxSpeed;}
	void      SetMaxSpeed(double new_speed){m_dMaxSpeed = new_speed;}

	// �������������
	double    GetMaxForce()const{return m_dMaxForce;}
	void      SetMaxForce(double mf){m_dMaxForce = mf;}

	bool      IsSpeedMaxedOut()const{return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.LengthSq();}
	double    GetSpeed()const{return m_vVelocity.Length();}
	double    GetSpeedSq()const{return m_vVelocity.LengthSq();}

	// ������ƣ�����ı䣬��Ӧ�Ĳ���Ҳ�ᷢ���ı�
	Vector2D  GetHeading()const{return m_vHeading;}
	void      SetHeading(Vector2D new_heading);

	// ��������ܷ��㣬ͨ��һ��Ŀ��λ�ã��Ϳ��������޸ĳ��򣬺Ͳ���
	bool      RotateHeadingToFacePosition(Vector2D target);

	// ת�����ʿ���
	double    GetMaxTurnRate()const{return m_dMaxTurnRate;}
	void      SetMaxTurnRate(double val){m_dMaxTurnRate = val;}

	// ͨ��Heading�������ؼн�
	float	  GetAngelByHeading();

protected:
	// �����ٶ�
	Vector2D	m_vVelocity;
	// ���峯��
	Vector2D	m_vHeading;
	// �������
	Vector2D	m_vSide;
	// ��������
	double		m_dMass;
	// ��������ٶ�
	double		m_dMaxSpeed;
	// �������������
	double		m_dMaxForce;
	// ���ת������
	double		m_dMaxTurnRate;
};

// �ú���ͨ������һ��Ŀ��λ�ã��޸�MovingEntity�ĳ��򡢲���
inline bool MovingEntity::RotateHeadingToFacePosition(Vector2D target)
{
	Vector2D toTarget = Vec2DNormalize(target - m_vPos);

	// ͨ��������˼��㹫ʽ������н�
	double angle = acos(m_vHeading.Dot(toTarget));

	// �Ѿ�����ȷ����
	if (angle < 0.00001) 
	{
		return true;
	}

	//clamp the amount to turn to the max turn rate
	// ͨ���˴��������ף��ú������������͵�����ת�򣬶��Ƿ����߼�ѭ���н��е�
	if (angle > m_dMaxTurnRate) 
	{
		angle = m_dMaxTurnRate;
	}

	//The next few lines use a rotation matrix to rotate the player's heading
	//vector accordingly
	C2DMatrix RotationMatrix;

	//notice how the direction of rotation has to be determined when creating
	//the rotation matrix
	// �б�����ʱ��
	RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));
	RotationMatrix.TransformVector2Ds(m_vHeading);
	RotationMatrix.TransformVector2Ds(m_vVelocity);

	//finally recreate m_vSide
	m_vSide = m_vHeading.Perp();

	return false;
}

inline void MovingEntity::SetHeading(Vector2D new_heading)
{
	// ���õĳ���һ����һ����λ����
	assert( (new_heading.LengthSq() - 1.0) < 0.00001);

	m_vHeading = new_heading;

	// ���Ĳ���
	m_vSide = m_vHeading.Perp();
}

#endif

