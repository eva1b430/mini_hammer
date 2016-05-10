#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "cocos2d.h"
#include <list>

using namespace std;
using namespace cocos2d;

// 逻辑世界
class Pathfinder;
class Vehicle;
// 定义一个智能体容器
typedef list<Vehicle*> VehicleList;
class GameWorld
{
public:
	GameWorld(void);
	~GameWorld(void);

	void Update(double time_elapsed);
	void bindToCCLayer(CCLayer* pLayer);

	// 获取所有的敌人
	list<Vehicle*>& GetAllBots(){return m_Bots;}

	Vehicle* getOwn(){return m_pVehicleOwn;}

private:
	Pathfinder*			m_pPathFinder;
	Vehicle*			m_pVehicleOwn;

	// 其他的敌人
	list<Vehicle*>      m_Bots;
};
#endif

