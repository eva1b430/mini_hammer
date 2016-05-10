#ifndef PROJECTILE_ROCKET_H
#define PROJECTILE_ROCKET_H
#include "Projectile.h"
#include "GameWorld.h"
#include "2D/Vector2D.h"
#include "Vehicle.h"

class EngineEntity;
class Projectile_Rocket : public Projectile
{
public:
	//Projectile(	Vector2D	target,
	//	GameWorld*	world,
	//	int			ShooterID,
	//	int			damage,
	//	Vector2D	origin,
	//	double		radius,
	//	Vector2D	heading,
	//	double		mass,
	//	double		MaxSpeed, 
	//	double		MaxForce)

	Projectile_Rocket(Vehicle* shooter, Vector2D target)
		: Projectile(target,
					 shooter->GetWorld(),
					 shooter->GetID(),
					 20,
					 shooter->GetPos(),
					 100,
					 shooter->GetHeading(),
					 1.0f,
					 200.0f,
					 100.0f)
	{

	}

	~Projectile_Rocket(void);

	void Update();
	
protected:
	
};
#endif // PROJECTILE_ROCKET_H

