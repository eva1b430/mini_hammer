#include "BaseEntity.h"
#include "GlobalVar.h"

BaseEntity::~BaseEntity(void)
{

}

void BaseEntity::Update(double time_elapsed)
{
	// ���������
	//Update(time_elapsed);

	Vector2D pos = GetPos();
	setPosition(GlobalVar::instance().HammerPosToCocosPos(pos));

	//CCSprite::update(time_elapsed);
}

void BaseEntity::update(float delta)
{
	// ����cocos2dx����ͼ���߼�ѭ��
	return ;

	//CCSprite::update(delta);

	//// ���������
	//Update(delta);

	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//Vector2D pos = GetPos();
	//setPosition(ccp(pos.x, winSize.height - pos.y));
}
