#include "RocketLauncher.h"
#include "GlobalVar.h"
#include "GameWorld.h"


RocketLauncher::~RocketLauncher(void)
{

}

void RocketLauncher::ShootAt( Vector2D pos )
{
	if (IsReadyForNextShot())
	{
		GlobalVar::instance().GetGameWorld()->AddRocket(m_pVehicle, pos);
	}
}
