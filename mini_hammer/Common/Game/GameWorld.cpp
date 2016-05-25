#include "GameWorld.h"
#include "GlobalVar.h"
#include "Pathfinder.h"
#include "Vehicle.h"
#include "Projectile.h"
#include "Projectile_Rocket.h"


GameWorld::GameWorld(void)
	: m_pPathFinder(NULL)
	, m_pVehicleOwn(NULL)
	, m_pUILayer(NULL)
{
	m_pPathFinder = new Pathfinder;
	GlobalVar::instance().SetPathfinder(m_pPathFinder);
}


GameWorld::~GameWorld(void)
{
	if (m_pPathFinder)
	{
		delete m_pPathFinder;
		m_pPathFinder = NULL;
	}

	// 不可以如此释放Vehicle对象，因为它被cocos2dx管理，所以不用管
	//if (m_pVehicleOwn)
	//{
	//	delete m_pVehicleOwn;
	//	m_pVehicleOwn = NULL;
	//}

	// 敌人列表也不需要释放，由引擎来做

	// 箭矢列表也不需要释放，有引擎来做
}

void GameWorld::Update(double time_elapsed)
{
	if (m_pVehicleOwn)
	{
		m_pVehicleOwn->Update(time_elapsed);
	}

	list<Vehicle*>::iterator itr;
	for (itr = m_Bots.begin();
		itr != m_Bots.end();
		itr++)
	{
		(*itr)->Update(time_elapsed);
	}

	list<Projectile*>::iterator itrProjectile;
	for (itrProjectile = m_Projectiles.begin();
		itrProjectile != m_Projectiles.end();
		itrProjectile++)
	{
		(*itrProjectile)->Update();
	}
}

void GameWorld::bindToCCLayer(CCLayer* pLayer)
{
	m_pUILayer = pLayer;

	m_pVehicleOwn = new Vehicle( this,
								Vector2D(20.0f, 20.0f), /* 位置 */
								1.0f,					/* 半径 */
								Vector2D(0.0f, 0.0f),	/* 加速度 */
								1.0f,					/* Rotation */
								1.0f,					/* 质量 */
								1.0f,					/* 最大速度 */
								1.0f,					/* 最大驱动力 */
								0.2f);					/* 转身速率 */

	m_pVehicleOwn->initWithFile("media/image/vehicle.png");
	m_pVehicleOwn->autorelease();

	if (m_pVehicleOwn)
	{
		m_pUILayer->addChild(m_pVehicleOwn);
	}
	
	m_pVehicleOwn->SetPos(Vector2D(0.0f, 0.0f));
	//m_pVehicleOwn->GetSteering()->SetTarget(Vector2D(200.0f, 200.0f));
	m_pVehicleOwn->GetSteering()->ArriveOn();
	m_pVehicleOwn->SetFovDisplay();
	//m_pVehicleOwn->EnableThink();

	// 敌人
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	for (int i = 0; i < 2; i++)
	{
		Vehicle* pBot = new Vehicle( this,
			Vector2D(20.0f, 20.0f), /* 位置 */
			1.0f,					/* 半径 */
			Vector2D(0.0f, 0.0f),	/* 加速度 */
			1.0f,					/* Rotation */
			1.0f,					/* 质量 */
			1.0f,					/* 最大速度 */
			1.0f,					/* 最大驱动力 */
			0.2f);					/* 转身速率 */

		pBot->initWithFile("media/image/vehicle.png");
		pBot->autorelease();
		m_pUILayer->addChild(pBot);
		m_Bots.push_back(pBot);

		// 随机一个位置，随机一些目标点
		float x = rand() % 400;
		float y = rand() % 400;
		pBot->SetPos(Vector2D(x, y));
		//pBot->GetSteering()->SetTarget(Vector2D(x, y));
		//pBot->GetSteering()->ArriveOn();
		pBot->EnableThink();
	}
}

void GameWorld::AddRocket(Vehicle* shooter, Vector2D target)
{
	Projectile* pProjectile = new Projectile_Rocket(shooter, target);

	// 添加进来
	m_Projectiles.push_back(pProjectile);

	pProjectile->initWithFile("media/image/missile.png");
	pProjectile->autorelease();
	if (m_pUILayer)
	{
		m_pUILayer->addChild(pProjectile);
	}
}
