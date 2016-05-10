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
	// 这条边的起止索引值，边连接两个Node
	int		m_nFrom;
	int		m_nTo;

	// 代价
	double	m_fCost;
};
#endif