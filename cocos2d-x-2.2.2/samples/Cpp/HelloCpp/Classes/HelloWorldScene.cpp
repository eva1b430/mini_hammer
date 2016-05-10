#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "GlobalVar.h"
USING_NS_CC;


//#include "AIEntity.h"

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// ���һ��AI
	m_pGameWorld = new GameWorld;
	GlobalVar::instance().SetGameWorld(m_pGameWorld);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::onEnter()
{
	CCLayer::onEnter();

	// ���
	scheduleUpdate();
}

void HelloWorld::onExit()
{
	// ���
	unscheduleUpdate();

	CCLayer::onExit();
}

void HelloWorld::update(float delta)
{
	if (m_pGameWorld)
	{
		m_pGameWorld->Update(delta);
	}
}

void HelloWorld::onEnterTransitionDidFinish()
{
	// �����߼���
	m_pGameWorld = GlobalVar::instance().GetGameWorld();
	m_pGameWorld->bindToCCLayer(this);
}
