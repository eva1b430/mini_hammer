#include "Vehicle.h"
#include "WeaponSystem.h"
#include "Regulator.h"
#include "Goal_Think.h"
#include "GameWorld.h"

Vehicle::Vehicle(	GameWorld* world,
	Vector2D  position,
	double    radius,
	Vector2D  velocity,
	double    rotation,
	double    mass,
	double    max_speed,
	double    max_force,
	double    max_turn_rate)
		: MovingEntity(	position,
						radius,
						velocity,
						Vector2D(sin(rotation), -cos(rotation)),
						mass,
						max_speed,
						max_force,
						max_turn_rate	)
		, m_pWorld(world)
		, m_pSteering(NULL)
		, m_pWeaponSys(NULL)
		, m_dTimeElapsed(0.0f)
		, m_pGoalArbitrationRegulator(NULL)
		, m_pBrain(NULL)
		, m_dFieldOfView(30.0f)
		, m_bFovDisplay(false)
		, m_bMarkDisplay(false)
		, m_bThink(false)
{
	m_pSteering = new SteeringBehaviors(this);
	m_pWeaponSys = new WeaponSystem(this);
	m_pWeaponSys->AddWeapon(BaseEntity::emBaseEntity_Type_Rocket_Launcher);

	m_pGoalArbitrationRegulator = new Regulator(4.0f);
	m_pVisionUpdateRegulator = new Regulator(4.0f);

	m_pBrain = new Goal_Think(this);
	m_pBrain->RemoveAllSubgoals();
}

Vehicle::~Vehicle(void)
{
	if (m_pWeaponSys)
	{
		delete m_pWeaponSys;
		m_pWeaponSys = NULL;
	}

	if (m_pGoalArbitrationRegulator)
	{
		delete m_pGoalArbitrationRegulator;
		m_pGoalArbitrationRegulator = NULL;
	}

	if (m_pVisionUpdateRegulator)
	{
		delete m_pVisionUpdateRegulator;
		m_pVisionUpdateRegulator = NULL;
	}

	if (m_pBrain)
	{
		delete m_pBrain;
		m_pBrain = NULL;
	}

	if (m_pSteering)
	{
		delete m_pSteering;
		m_pSteering = NULL;
	}
}

void Vehicle::Update(double time_elapsed)
{
	BaseEntity::Update(time_elapsed);

	m_dTimeElapsed = time_elapsed;

	// 计算操作的合力
	Vector2D SteeringForce = m_pSteering->Calculate();

	// 加速度 = F / mass
	Vector2D acceleration = SteeringForce / m_dMass;

	// 速度 = 速度 + 加速度 *　时间增量
	m_vVelocity = m_vVelocity + acceleration/* * m_dTimeElapsed*/;

	// 修正速度
	m_vVelocity.Truncate(m_dMaxSpeed);

	// 位置和速度的关系
	m_vPos = m_vPos + m_vVelocity/* * time_elapsed*/;

	// 如果速度远大于一个很小的值，更新朝向
	if (m_vVelocity.LengthSq() > 0.00000001)
	{    
		m_vHeading = Vec2DNormalize(m_vVelocity);
		
		m_vSide = m_vHeading.Perp();

		float angel = GetAngelByHeading();

		setRotation(180 - angel);
	}

	if (m_pWeaponSys)
	{
		// 更新武器系统（按照远，中，近距离）
	}
	m_pWeaponSys->ShootAt(Vector2D(200, 200));

	if (m_pGoalArbitrationRegulator->isReady() && m_bThink)
	{
		// 更新行为树
		m_pBrain->Process();
	}

	// 只有一个角色才参与检测
	if (m_pVisionUpdateRegulator->isReady() && m_bFovDisplay)
	{
		list<Vehicle*>& bots = m_pWorld->GetAllBots();
		list<Vehicle*>::iterator itr;
		for (itr = bots.begin();
			itr != bots.end();
			itr ++)
		{
			if (isSecondInFOVOfFirst(GetPos(),
				GetHeading(),
				(*itr)->GetPos(),
				m_dFieldOfView * M_PI / 180.0f))
			{
				// 添加这个敌人的标记
				(*itr)->SetMarkDisplay();
			}
			else
			{
				// 移除这个敌人的仇恨标记
				(*itr)->SetMarkHide();
			}
		}
	}
}

void Vehicle::Render()
{
	
}

void Vehicle::PaintMark()
{
	ccDrawColor4F(0, 0, 255, 255);
	glLineWidth(1.0f);

	CCPoint myPos = convertToNodeSpace(getPosition());
	ccDrawCircle(myPos, 16, CC_DEGREES_TO_RADIANS(90), 6, false);
}

void Vehicle::PaintFOV()
{
	// 绘制Fov，由于cocos2dx本身就是本地坐标系，所以为显示Fov带来一些方便
	ccDrawColor4F(255, 0, 0, 255);
	glLineWidth(1.0f);

	CCPoint myPos = convertToNodeSpace(getPosition());
	//CCPoint left = ccp(myPos.x + 400, atan(m_dFieldOfView * M_PI / 180) * (myPos.x + 400));
	//CCPoint right = ccp(myPos.x - 400, atan(m_dFieldOfView * M_PI / 180) * (myPos.x + 400));
	CCPoint left = ccp(myPos.x + 400, tan((90 - m_dFieldOfView / 2) * M_PI / 180) * (myPos.x + 400));
	CCPoint right = ccp(myPos.x - 400, tan((90 - m_dFieldOfView / 2) * M_PI / 180) * (myPos.x + 400));
	ccDrawLine(myPos, left);
	ccDrawLine(myPos, right);

	ccDrawColor4F(0, 0, 255, 255);
	ccPointSize(8.0f);
	ccDrawPoint(convertToNodeSpace(getPosition()));

	// 绘制视野
	ccColor4F color = ccc4FFromccc4B(ccc4(255, 0, 0, 100));
	CCPoint filledVertices[] = { left, 
		convertToNodeSpace(getPosition()),
		right};

	ccDrawSolidPoly(filledVertices, 3, color);

	// 绘制Heading
	ccDrawLine(myPos, ccp(myPos.x, myPos.y + 400));
}

void Vehicle::draw(void)
{
	CCSprite::draw();

	if (m_bFovDisplay)
	{
		PaintFOV();
	}

	if (m_bMarkDisplay)
	{
		PaintMark();
	}

	//m_pBrain->Render();
}
