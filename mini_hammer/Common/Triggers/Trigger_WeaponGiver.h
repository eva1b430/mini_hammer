#ifndef TRIGGER_WEAPONGIVER_H
#define TRIGGER_WEAPONGIVER_H
#include "Trigger.h"

// װ�����޷�����װ����ʲô�����սű���������ʵ���ǰ��ڽ�ɫ���ϵģ���װ����
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

