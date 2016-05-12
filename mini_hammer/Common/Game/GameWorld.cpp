#include "GameWorld.h"
#include "GlobalVar.h"
#include "Pathfinder.h"
#include "Vehicle.h"

GameWorld::GameWorld(void)
	: m_pPathFinder(NULL)
	, m_pVehicleOwn(NULL)
{
	m_pPathFinder = new Pathfinder;
	GlobalVar::instance().SetPathfinder(m_pPathFinder);
	m_pPathFinder->CreateGraphGrid(800, 600, 10, 10);
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
}

void GameWorld::Update(double time_elapsed)
{
	if (m_pVehicleOwn)
	{
		m_pVehicleOwn->Update(time_elapsed);

		list<Vehicle*>::iterator itr;
		for (itr = m_Bots.begin();
			itr != m_Bots.end();
			itr++)
		{
			(*itr)->Update(time_elapsed);
		}
	}
}

void GameWorld::bindToCCLayer(CCLayer* pLayer)
{
	m_pVehicleOwn = new Vehicle( this,
								Vector2D(20.0f, 20.0f), /* 位置 */
								1.0f,					/* 半径 */
								Vector2D(0.0f, 0.0f),	/* 加速度 */
								1.0f,					/* Rotation */
								1.0f,					/* 质量 */
								100.0f,					/* 最大速度 */
								100.0f,					/* 最大驱动力 */
								0.2f);					/* 转身速率 */

	m_pVehicleOwn->initWithFile("vehicle.png");
	m_pVehicleOwn->autorelease();

	if (m_pVehicleOwn)
	{
		pLayer->addChild(m_pVehicleOwn);
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
			100.0f,					/* 最大速度 */
			100.0f,					/* 最大驱动力 */
			0.2f);					/* 转身速率 */

		pBot->initWithFile("vehicle.png");
		pBot->autorelease();
		pLayer->addChild(pBot);
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
