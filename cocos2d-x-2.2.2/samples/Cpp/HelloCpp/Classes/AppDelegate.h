#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "CCScene.h"
#include "GameLayer.h"


class CCScene;
class GameLayer;
using namespace cocos2d;
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();


    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();

private:
	cocos2d::CCScene*		m_pGameScene;
	GameLayer*				m_pGameLayer;
};

#endif // _APP_DELEGATE_H_

