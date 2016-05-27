#include "MovingEntity.h"

MovingEntity::~MovingEntity(void)
{
}

float MovingEntity::GetAngelByHeading()
{
	double tan_yx = abs(m_vHeading.y)/abs(m_vHeading.x);
	float angle = 0;
	if(m_vHeading.y > 0 && m_vHeading.x < 0)
	{
		angle = atan(tan_yx) * 180 / M_PI - 90;
	} 
	else if (m_vHeading.y > 0 && m_vHeading.x > 0) 
	{
		angle = 90 - atan(tan_yx) * 180 / M_PI;
	} 
	else if(m_vHeading.y < 0 && m_vHeading.x < 0) 
	{
		angle = -atan(tan_yx) * 180 / M_PI - 90;
	} 
	else if(m_vHeading.y < 0 && m_vHeading.x > 0) 
	{
		angle = atan(tan_yx) * 180 / M_PI + 90;
	}

	return angle;
}
