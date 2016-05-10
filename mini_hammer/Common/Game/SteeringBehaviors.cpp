#include "SteeringBehaviors.h"
#include "Vehicle.h"

SteeringBehaviors::SteeringBehaviors(Vehicle* agent)
	: m_pVehicle(agent)
	, m_nFlags(none)
{
}


SteeringBehaviors::~SteeringBehaviors(void)
{
}

Vector2D SteeringBehaviors::Calculate()
{
	m_vSteeringForce.Zero();

	if (On(seek))
	{
		m_vSteeringForce += Seek(m_vTarget) * 200.0f;
	}

	if (On(arrive))
	{
		m_vSteeringForce += Arrive(m_vTarget) * 200.0f;
	}

	// ½ÃÕýÇý¶¯Á¦
	m_vSteeringForce.Truncate(m_pVehicle->GetMaxForce());

	return m_vSteeringForce;
}

Vector2D SteeringBehaviors::Seek(Vector2D TargetPos)
{
	Vector2D DesiredVelocity = Vec2DNormalize(TargetPos - m_pVehicle->GetPos()) * m_pVehicle->GetMaxSpeed();

	return (DesiredVelocity - m_pVehicle->GetVelocity());
}

Vector2D SteeringBehaviors::Arrive(Vector2D TargetPos)
{
	Vector2D ToTarget = TargetPos - m_pVehicle->GetPos();

	//calculate the distance to the target
	double dist = ToTarget.Length();

	if (dist > 0)
	{
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration..
		const double DecelerationTweaker = 0.3;

		//calculate the speed required to reach the target given the desired
		//deceleration
		//double speed =  dist / ((double)deceleration * DecelerationTweaker);
		double speed =  dist / ((double)3.0f * DecelerationTweaker);

		//make sure the velocity does not exceed the max
		speed = min(speed, m_pVehicle->GetMaxSpeed());

		//from here proceed just like Seek except we don't need to normalize 
		//the ToTarget vector because we have already gone to the trouble
		//of calculating its length: dist. 
		Vector2D DesiredVelocity =  ToTarget * speed / dist;

		return (DesiredVelocity - m_pVehicle->GetVelocity());
	}

	return Vector2D(0,0);
}
