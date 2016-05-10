#ifndef __AI_ENTITY_H__
#define __AI_ENTITY_H__

#include "cocos2d.h"
#include "Vehicle.h"

using namespace cocos2d;
class AIEntity : public cocos2d::CCSprite
	, public Vehicle
{
public:
	AIEntity(cocos2d::CCPoint pos);
	~AIEntity(void);

	static AIEntity* create(cocos2d::CCPoint pos);
	static AIEntity* create(cocos2d::CCPoint pos, const char *pszFileName);

	// Ω”ø⁄÷ÿ‘ÿ
	virtual void Render();

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	virtual void setPosition(const cocos2d::CCPoint& pos);
};
#endif //__AI_ENTITY_H__
