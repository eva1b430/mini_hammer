#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "cocos2d.h"
#include <list>

using namespace std;
using namespace cocos2d;

// �߼�����
class Pathfinder;
class Vehicle;
// ����һ������������
typedef list<Vehicle*> VehicleList;
class GameWorld
{
public:
	GameWorld(void);
	~GameWorld(void);

	void Update(double time_elapsed);
	void bindToCCLayer(CCLayer* pLayer);

	// ��ȡ���еĵ���
	list<Vehicle*>& GetAllBots(){return m_Bots;}

	Vehicle* getOwn(){return m_pVehicleOwn;}

private:
	Pathfinder*			m_pPathFinder;
	Vehicle*			m_pVehicleOwn;

	// �����ĵ���
	list<Vehicle*>      m_Bots;
};
#endif

