#ifndef TRIGGER_H
#define TRIGGER_H
#include "BaseEntity.h"
#include "GraphNode.h"
#include "2D/Vector2D.h"
#include "Vehicle.h"

// 提供一种最简单的区域（圆形）
class TriggerRegionCircle
{
private:
	Vector2D m_vPosCenter;
	double    m_dRadius;

public:

	TriggerRegionCircle(Vector2D pos, 
						double radius)
						: m_vPosCenter(pos)
						, m_dRadius(radius)
	{

	}

	bool isTouching(Vector2D pos, double EntityRadius)const
	{
		return Vec2DDistanceSq(m_vPosCenter, pos) < (EntityRadius + m_dRadius)*(EntityRadius + m_dRadius);
	}
};

// 触发器基类
class Trigger/* : public BaseEntity*/
{
public:
	Trigger(void)
		: m_iGraphNodeIndex(GraphNode::em_Invalid_Node_Index)
	{

	}

	~Trigger(void)
	{

	}

	// 条件（WE支持图形化编辑能力）
	virtual void  Try(Vehicle* pVehicle) = 0;

	// 条件测试（绝大多数用不上）
	virtual void  Update()
	{

	}

private:
	// 对应导航图结点索引
	int			m_iGraphNodeIndex;
};

// 区域触发器（条件触发器的一种）
class RegionTrigger : public Trigger
{
public:
	RegionTrigger( Vector2D pos, 
				   double radius )
				   : m_pRegion(new TriggerRegionCircle(pos, radius))
	{

	}
	~RegionTrigger(void)
	{
		if (m_pRegion)
		{
			delete m_pRegion;
			m_pRegion = NULL;
		}
	}

protected:
	// 对应的区域
	TriggerRegionCircle* m_pRegion;
};

#endif /*TRIGGER_H*/