#ifndef TRIGGER_WEAPONGIVER_H
#define TRIGGER_WEAPONGIVER_H
#include "Trigger.h"

// 装备（无法描述装备是什么，按照脚本，发射器实际是绑定在角色身上的，但装备）
class Trigger_WeaponGiver : public RegionTrigger
{
public:
	Trigger_WeaponGiver( Vector2D pos, 
						 double radius )
						 : RegionTrigger(pos, radius)
	{

	}
	~Trigger_WeaponGiver(void);
};
#endif /*TRIGGER_WEAPONGIVER_H*/

