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

	// 添加一个AI
	m_pGameWorld = new GameWorld;
	GlobalVar::instance().SetGameWorld(m_pGameWorld);
	GlobalVar::instance().GetPathfinder()->CreateGraphGrid(800, 600, 10, 10);
    
    return true;
}

void GameLayer::onEnter()
{
	CCLayer::onEnter();

	// 添加
	scheduleUpdate();
}

void GameLayer::onExit()
{
	// 添加
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
	// 链接逻辑层
	m_pGameWorld = GlobalVar::instance().GetGameWorld();
	m_pGameWorld->bindToCCLayer(this);
}
