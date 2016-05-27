#include "Projectile_Rocket.h"

Projectile_Rocket::~Projectile_Rocket(void)
{

}

void Projectile_Rocket::Update()
{
	BaseEntity::Update(-1);

	// Åö×²¼ì²â

	m_vVelocity = GetMaxSpeed() * GetHeading();

	//make sure vehicle does not exceed maximum velocity
	m_vVelocity.Truncate(m_dMaxSpeed);

	//update the position
	m_vPos += m_vVelocity;

	if (m_vVelocity.LengthSq() > 0.00000001)
	{    
		m_vHeading = Vec2DNormalize(m_vVelocity);

		m_vSide = m_vHeading.Perp();

		float angel = GetAngelByHeading();

		setRotation(180 - angel);
	}

	// ¼òµ¥µÄÉ¾³ýÐÐÎª
	if (m_vOrigin.Distance(m_vPos) > 180.0f)
	{
		m_bDead = true;
	}
}

void Projectile_Rocket::Render()
{

}

