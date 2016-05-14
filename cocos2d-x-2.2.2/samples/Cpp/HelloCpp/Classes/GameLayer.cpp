#include "GameLayer.h"
#include "AppMacros.h"
#include "GlobalVar.h"
#include "GameWorld.h"

using namespace cocos2d;
bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// ���һ��AI
	m_pGameWorld = new GameWorld;
	GlobalVar::instance().SetGameWorld(m_pGameWorld);
	GlobalVar::instance().GetPathfinder()->CreateGraphGrid(800, 600, 10, 10);
    
    return true;
}

void GameLayer::onEnter()
{
	CCLayer::onEnter();

	// ���
	scheduleUpdate();
}

void GameLayer::onExit()
{
	// ���
	unscheduleUpdate();

	CCLayer::onExit();
}

void GameLayer::update(float delta)
{
	if (m_pGameWorld)
	{
		m_pGameWorld->Update(delta);
	}
}

void GameLayer::onEnterTransitionDidFinish()
{
	// �����߼���
	m_pGameWorld = GlobalVar::instance().GetGameWorld();
	m_pGameWorld->bindToCCLayer(this);
}
