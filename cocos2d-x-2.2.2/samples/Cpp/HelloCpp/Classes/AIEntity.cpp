#include "AIEntity.h"

// 必须提供9个参数初始化，不过理论上只有第一个数值是位置参数，其他的数值都是属性参数
AIEntity::AIEntity(cocos2d::CCPoint pos)
	: Vehicle(		NULL,
					Vector2D(pos.x, pos.y), /* 位置 */
					1.0f,					/* 半径 */
					Vector2D(0.0f, 0.0f),	/* 加速度 */
					1.0f,					/* Rotation */
					1.0f,					/* 质量 */
					100.0f,					/* 最大速度 */
					100.0f,					/* 最大驱动力 */
					0.2f)					/* 转身速率 */
					
{
	
}


AIEntity::~AIEntity(void)
{
	
}

AIEntity* AIEntity::create(cocos2d::CCPoint pos)
{
	AIEntity *pAIEntity = new AIEntity(pos);
	if (pAIEntity && pAIEntity->init())
	{
		pAIEntity->autorelease();
		return pAIEntity;
	}
	CC_SAFE_DELETE(pAIEntity);
	return NULL;
}

AIEntity* AIEntity::create(cocos2d::CCPoint pos, const char *pszFileName)
{
	AIEntity *pAIEntity = new AIEntity(pos);
	if (pAIEntity && pAIEntity->initWithFile(pszFileName))
	{
		pAIEntity->autorelease();
		return pAIEntity;
	}
	CC_SAFE_DELETE(pAIEntity);
	return NULL;
}

void AIEntity::Render()
{
	
}

void AIEntity::onEnter()
{
	CCSprite::onEnter();

	// 添加
	scheduleUpdate();
}

void AIEntity::onExit()
{
	// 添加
	unscheduleUpdate();

	CCSprite::onExit();
}

void AIEntity::update(float delta)
{
	CCSprite::update(delta);
	Vehicle::Update(delta);

	Vector2D pos = GetPos();
	CCSprite::setPosition(ccp(pos.x, pos.y));
}

void AIEntity::setPosition(const cocos2d::CCPoint& pos)
{
	CCSprite::setPosition(pos);

	Vector2D pos2D = Vector2D(pos.x, pos.y);
	Vehicle::SetPos(pos2D);
}
