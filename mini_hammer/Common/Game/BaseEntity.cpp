#include "BaseEntity.h"
#include "GlobalVar.h"

BaseEntity::~BaseEntity(void)
{

}

void BaseEntity::Update(double time_elapsed)
{
	// 调用子类的
	//Update(time_elapsed);

	Vector2D pos = GetPos();
	setPosition(GlobalVar::instance().HammerPosToCocosPos(pos));

	//CCSprite::update(time_elapsed);
}

void BaseEntity::update(float delta)
{
	// 拦截cocos2dx场景图的逻辑循环
	return ;

	//CCSprite::update(delta);

	//// 调用子类的
	//Update(delta);

	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//Vector2D pos = GetPos();
	//setPosition(ccp(pos.x, winSize.height - pos.y));
}
