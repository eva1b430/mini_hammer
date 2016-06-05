#ifndef TRIGGER_H
#define TRIGGER_H
#include "BaseEntity.h"
#include "GraphNode.h"
#include "2D/Vector2D.h"
#include "Vehicle.h"

// �ṩһ����򵥵�����Բ�Σ�
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

// ����������
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

	// ������WE֧��ͼ�λ��༭������
	virtual void  Try(Vehicle* pVehicle) = 0;

	// �������ԣ���������ò��ϣ�
	virtual void  Update()
	{

	}

private:
	// ��Ӧ����ͼ�������
	int			m_iGraphNodeIndex;
};

// ���򴥷�����������������һ�֣�
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
	// ��Ӧ������
	TriggerRegionCircle* m_pRegion;
};

#endif /*TRIGGER_H*/