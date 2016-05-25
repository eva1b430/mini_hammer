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
}

void Projectile_Rocket::Render()
{

}

