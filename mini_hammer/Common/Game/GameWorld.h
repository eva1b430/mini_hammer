#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "cocos2d.h"
#include <list>
#include "2D/Vector2D.h"

using namespace std;
using namespace cocos2d;

// 逻辑世界
class Pathfinder;
class Vehicle;
class Projectile;
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

	// 获取自己
	Vehicle* getOwn(){return m_pVehicleOwn;}

	// 添加Rocket
	void AddRocket(Vehicle* shooter, Vector2D target);

private:
	Pathfinder*			m_pPathFinder;
	Vehicle*			m_pVehicleOwn;

	// 其他的敌人
	list<Vehicle*>      m_Bots;
	// 所有的箭矢
	list<Projectile*>	m_Projectiles;

	// 绑定的UI模块
	CCLayer*			m_pUILayer;
};
#endif

