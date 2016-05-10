#include "AIEntity.h"

// �����ṩ9��������ʼ��������������ֻ�е�һ����ֵ��λ�ò�������������ֵ�������Բ���
AIEntity::AIEntity(cocos2d::CCPoint pos)
	: Vehicle(		NULL,
					Vector2D(pos.x, pos.y), /* λ�� */
					1.0f,					/* �뾶 */
					Vector2D(0.0f, 0.0f),	/* ���ٶ� */
					1.0f,					/* Rotation */
					1.0f,					/* ���� */
					100.0f,					/* ����ٶ� */
					100.0f,					/* ��������� */
					0.2f)					/* ת������ */
					
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

	// ���
	scheduleUpdate();
}

void AIEntity::onExit()
{
	// ���
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
