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

	// ��������ĺ���
	Vector2D SteeringForce = m_pSteering->Calculate();

	// ���ٶ� = F / mass
	Vector2D acceleration = SteeringForce / m_dMass;

	// �ٶ� = �ٶ� + ���ٶ� *��ʱ������
	m_vVelocity = m_vVelocity + acceleration/* * m_dTimeElapsed*/;

	// �����ٶ�
	m_vVelocity.Truncate(m_dMaxSpeed);

	// λ�ú��ٶȵĹ�ϵ
	m_vPos = m_vPos + m_vVelocity/* * time_elapsed*/;

	// ����ٶ�Զ����һ����С��ֵ�����³���
	if (m_vVelocity.LengthSq() > 0.00000001)
	{    
		m_vHeading = Vec2DNormalize(m_vVelocity);
		
		m_vSide = m_vHeading.Perp();

		float angel = GetAngelByHeading();

		setRotation(180 - angel);
	}

	if (m_pWeaponSys)
	{
		// ��������ϵͳ������Զ���У������룩
	}
	m_pWeaponSys->ShootAt(Vector2D(200, 200));

	if (m_pGoalArbitrationRegulator->isReady() && m_bThink)
	{
		// ������Ϊ��
		m_pBrain->Process();
	}

	// ֻ��һ����ɫ�Ų�����
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
				// ���������˵ı��
				(*itr)->SetMarkDisplay();
			}
			else
			{
				// �Ƴ�������˵ĳ�ޱ��
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
	// ����Fov������cocos2dx������Ǳ�������ϵ������Ϊ��ʾFov����һЩ����
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

	// ������Ұ
	ccColor4F color = ccc4FFromccc4B(ccc4(255, 0, 0, 100));
	CCPoint filledVertices[] = { left, 
		convertToNodeSpace(getPosition()),
		right};

	ccDrawSolidPoly(filledVertices, 3, color);

	// ����Heading
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
