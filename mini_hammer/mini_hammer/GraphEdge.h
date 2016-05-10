#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
#include "GraphNode.h"

class GraphEdge
{
public:
	GraphEdge(void);
	~GraphEdge(void);

	int GetFrom()
	{
		return m_nFrom;
	}

	void SetFrom(int nFrom)
	{
		m_nFrom = nFrom;
	}

	int GetTo()
	{
		return m_nTo;
	}

	void SetTo(int nTo)
	{
		m_nTo = nTo;
	}

	double GetCost()
	{
		return m_fCost;
	}

	void SetCost(double fCost)
	{
		m_fCost = fCost;
	}

private:
	// �����ߵ���ֹ����ֵ������������Node
	int		m_nFrom;
	int		m_nTo;

	// ����
	double	m_fCost;
};
#endif