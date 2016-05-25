#ifndef BASEENTITY_H
#define BASEENTITY_H
#include "cocos2d.h"
#include "2D/Vector2D.h"
#include "GlobalVar.h"

using namespace cocos2d;
class BaseEntity : public CCSprite
{
public:
	enum BaseEntity_Type
	{
		emBaseEntity_Type_Default			= -1,
		emBaseEntity_Type_Wall				= 0,
		emBaseEntity_Type_Bot				= 1,
		emBaseEntity_Type_Unused			= 2,
		emBaseEntity_Type_Waypoint			= 3,
		emBaseEntity_Type_Health			= 4,
		emBaseEntity_Type_Spawn_Point		= 5,

		emBaseEntity_Type_Rail_Gun			= 6,
		emBaseEntity_Type_Rocket_Launcher	= 7,
		emBaseEntity_Type_Shotgun			= 8,
		emBaseEntity_Type_Blaster			= 9,

		emBaseEntity_Type_Obstacle			= 10,
		emBaseEntity_Type_Sliding_Door		= 11,
		emBaseEntity_Type_Door_Trigger		= 12
	};

public:
	// 提供三种构造函数
	BaseEntity()
		: m_nID(NextValidID())
		, m_dBoundingRadius(0.0)
		, m_vPos(Vector2D())
		, m_emEntityType(emBaseEntity_Type_Default)
		, m_bTag(false)
	{

	}

	BaseEntity(BaseEntity_Type entity_type)
		: m_nID(NextValidID())
		, m_dBoundingRadius(0.0)
		, m_vPos(Vector2D())
		, m_emEntityType(entity_type)
		, m_bTag(false)
	{

	}

	BaseEntity(BaseEntity_Type entity_type, Vector2D pos, double r)
		: m_nID(NextValidID())
		, m_dBoundingRadius(r)
		, m_vPos(pos)
		, m_emEntityType(entity_type)
		, m_bTag(false)
	{}

	virtual ~BaseEntity(void);

	// cocos2dx的函数
	virtual void update(float delta)
	{
		// 拦截cocos2dx场景图的逻辑循环
		return ;

		//CCSprite::update(delta);

		//// 调用子类的
		//Update(delta);

		//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//Vector2D pos = GetPos();
		//setPosition(ccp(pos.x, winSize.height - pos.y));
	}

	virtual void onEnter()
	{
		CCSprite::onEnter();

		// 添加
		scheduleUpdate();
	}
	virtual void onExit()
	{
		// 添加
		unscheduleUpdate();

		CCSprite::onExit();
	}

	//virtual void setPosition(const cocos2d::CCPoint& pos)
	//{
	//	CCSprite::setPosition(pos);

	//	Vector2D pos2D = Vector2D(pos.x, pos.y);
	//	SetPos(pos2D);
	//}

	// 逻辑帧
	virtual void Update(double time_elapsed)
	{
		// 调用子类的
		//Update(time_elapsed);

		Vector2D pos = GetPos();
		setPosition(GlobalVar::instance().HammerPosToCocosPos(pos));

		//CCSprite::update(time_elapsed);
	}

	// 渲染帧
	virtual void Render()
	{

	}

	// 位置控制
	Vector2D     GetPos()const{return m_vPos;}
	void         SetPos(Vector2D new_pos){m_vPos = new_pos;}

	// 包围体半径控制
	double       GetBRadius()const{return m_dBoundingRadius;}
	void         SetBRadius(double r){m_dBoundingRadius = r;}

	// 获取ID
	int          GetID()const{return m_nID;}

	// Type控制
	BaseEntity_Type			GetEntityType()const{return m_emEntityType;}
	void					SetEntityType(BaseEntity_Type new_type){m_emEntityType = new_type;}

private:
	// BaseEntity的ID
	int					m_nID;

	// 类型
	BaseEntity_Type		m_emEntityType;

	// 是否被标记
	bool				m_bTag;

	int NextValidID()
	{
		static int NextID = 0;
		return NextID++;
	}

protected:
	// 位置
	Vector2D			m_vPos;

	// 包围体半径
	double				m_dBoundingRadius;
};
#endif // BASEENTITY_H

