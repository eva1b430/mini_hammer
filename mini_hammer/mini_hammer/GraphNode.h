#ifndef GRAPHNODE_H
#define GRAPHNODE_H
#include "2D/Vector2D.h"

class GraphNode
{
public:
	enum 
	{
		em_Invalid_Node_Index = -1
	};

public:
	GraphNode(void);
	~GraphNode(void);

	int GetIndex()
	{
		return m_nIndex;
	}

	void SetIndex(int nIndex)
	{
		m_nIndex = nIndex;
	}

	Vector2D& GetPos()
	{
		return m_vPosition;
	}

	void SetPos(Vector2D NewPosition)
	{
		m_vPosition = NewPosition;
	}

	int GetTerrainType()
	{
		return m_emType;
	}

	void SetTerrainType(int emType)
	{
		m_emType = emType;
	}

	void* ExtraInfo()
	{
		return m_ExtraInfo;
	}

	void  SetExtraInfo(void* info)
	{
		m_ExtraInfo = info;
	}

private:
	// �������ֵ
	int								m_nIndex;
	// ����
	Vector2D						m_vPosition;
	// ���ε�Type
	int								m_emType;

	// ������Ϣָ�루��������
	void*							m_ExtraInfo;
};
#endif

