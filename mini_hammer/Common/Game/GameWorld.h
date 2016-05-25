#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "cocos2d.h"
#include <list>
#include "2D/Vector2D.h"

using namespace std;
using namespace cocos2d;

// �߼�����
class Pathfinder;
class Vehicle;
class Projectile;
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

	// ��ȡ�Լ�
	Vehicle* getOwn(){return m_pVehicleOwn;}

	// ���Rocket
	void AddRocket(Vehicle* shooter, Vector2D target);

private:
	Pathfinder*			m_pPathFinder;
	Vehicle*			m_pVehicleOwn;

	// �����ĵ���
	list<Vehicle*>      m_Bots;
	// ���еļ�ʸ
	list<Projectile*>	m_Projectiles;

	// �󶨵�UIģ��
	CCLayer*			m_pUILayer;
};
#endif

