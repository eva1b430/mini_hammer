#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class GameWorld;
class GameLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	virtual void onEnterTransitionDidFinish();

private:
	GameWorld*			m_pGameWorld;
};

#endif // __HELLOWORLD_SCENE_H__
