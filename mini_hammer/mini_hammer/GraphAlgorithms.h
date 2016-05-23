#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H
#include "GraphNode.h"
#include "GraphEdge.h"
#include "Graph.h"
#include "misc/PriorityQueue.h"
#include <vector>
#include <list>

using namespace std;
// 提供两种搜索算法（Dijkstra, A Star）
class Graph_SearchDijkstra
{
private:
	Graph&				m_Graph;
	// SPT
	vector<GraphEdge*>	m_ShortestPathTree;
	// 
	vector<double>		m_CostToThisNode;
	// 开启，关闭列表
	vector<GraphEdge*>	m_SearchFrontier;

	// 起止点
	int                 m_iSource;
	int					m_iTarget;

	//
	void Search()
	{
		IndexedPriorityQLow<double> pq(m_CostToThisNode, m_Graph.GetNodesNum());
		pq.insert(m_iSource);

		while(!pq.empty())
		{
			int NextClosestNode = pq.Pop();
			m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];
			if (NextClosestNode == m_iTarget) 
			{
				// 找到目标点
				return;
			}

			Graph::EdgeList& edgeList = m_Graph.GetEdgeByNodeIndex(NextClosestNode);
			list<GraphEdge>::iterator itrEdge;
			for (itrEdge = edgeList.begin(); itrEdge != edgeList.end(); itrEdge++)
			{
				double NewCost = m_CostToThisNode[NextClosestNode] + itrEdge->GetCost();

				if (m_SearchFrontier[itrEdge->GetTo()] == 0)
				{
					m_CostToThisNode[itrEdge->GetTo()] = NewCost;

					pq.insert(itrEdge->GetTo());

					m_SearchFrontier[itrEdge->GetTo()] = &(*itrEdge);
				}
				else if ( (NewCost < m_CostToThisNode[itrEdge->GetTo()]) &&
						(m_ShortestPathTree[itrEdge->GetTo()] == 0) )
				{
					m_CostToThisNode[itrEdge->GetTo()] = NewCost;
					pq.ChangePriority(itrEdge->GetTo());
					m_SearchFrontier[itrEdge->GetTo()] = &(*itrEdge);
				}
			}
		}
	}

public:
	// 构造时候就调用了搜索
	Graph_SearchDijkstra(Graph& refGraph, int source, int target = -1)
		: m_Graph(refGraph),
		m_ShortestPathTree(refGraph.GetNodesNum()),                              
		m_SearchFrontier(refGraph.GetNodesNum()),
		m_CostToThisNode(refGraph.GetNodesNum()),
		m_iSource(source),
		m_iTarget(target)
	{
		Search();
	}

	// 获取最小代价树
	vector<GraphEdge*> GetSPT()
	{
		return m_ShortestPathTree;
	}

	// 最短路径
	list<int> GetPathToTarget()
	{
		std::list<int> path;
		if (m_iTarget < 0)  
		{
			return path;
		}

		// 从SPT
		int nd = m_iTarget;
		path.push_front(nd);
		while ((nd != m_iSource) && (m_ShortestPathTree[nd] != 0))
		{
			nd = m_ShortestPathTree[nd]->GetFrom();
			path.push_front(nd);
		}

		return path;
	}

	// 获取整条路径的代价
	double GetCostToTarget()
	{
		return m_CostToThisNode[m_iTarget];
	}

	double GetCostToNode(unsigned int nd)
	{
		return m_CostToThisNode[nd];
	}
};

class Graph_SearchAStar
{

};


#endif // GRAPHALGORITHMS_H

