#include "AppDelegate.h"
#include "AppMacros.h"
#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

AppDelegate::AppDelegate() 
	: m_pGameScene(NULL)
	, m_pGameLayer(NULL)
{

}

AppDelegate::~AppDelegate() 
{

}

bool AppDelegate::applicationDidFinishLaunching() 
{

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	CCSize frameSize = pEGLView->getFrameSize();

    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
#endif
    
    vector<string> searchPath;
	if (frameSize.height > mediumResource.size.height)
	{
        searchPath.push_back(largeResource.directory);

        pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
	else
    {
        searchPath.push_back(smallResource.directory);

        pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }

    // set searching path
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);

    m_pGameScene = cocos2d::CCScene::create();
	m_pGameLayer = GameLayer::create();
	m_pGameScene->addChild(m_pGameLayer);

    // run
    pDirector->runWithScene(m_pGameScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
