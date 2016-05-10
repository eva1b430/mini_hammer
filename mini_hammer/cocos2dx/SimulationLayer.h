#ifndef SIMULATIONLAYER_H
#define SIMULATIONLAYER_H

#include "cocos2d.h"


class GameWorld;
// 仿真
using namespace cocos2d;
class SimulationLayer : public cocos2d::CCLayerColor
{
public:
    virtual bool init();  
    
    // implement the "static node()" method manually
    CREATE_FUNC(SimulationLayer);

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	virtual void draw();
	virtual void onEnterTransitionDidFinish();

	// 添加触摸事件
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	GameWorld*			m_pGameWorld;
};

#endif // SIMULATIONLAYER_H
