#ifndef GRAPH_H
#define GRAPH_H
#include "GraphNode.h"
#include "GraphEdge.h"
#include <vector>
#include <list>

using namespace std;
class Graph
{
public:
	typedef vector<GraphNode>	NodeVector;
	typedef list<GraphEdge>		EdgeList;
	
	// 
	typedef vector<EdgeList>	EdgeListVector;

public:
	Graph(void);
	~Graph(void);

	// 是否是一条唯一的Edge，如果被检查的边起止和Graph中的某一条边一致，则表示被检测的边是重复的
	bool CheckEdgeUnique(int nFrom, int nTo)
	{
		for ( EdgeList::iterator curEdge = m_Edges[nFrom].begin();
			curEdge != m_Edges[nFrom].end();
			++curEdge )
		{
			if (curEdge->GetTo() == nTo)
			{
				return false;
			}
		}

		return true;
	}

	// 从Graph中移除一个无用的边
	void RemoveInvalidEdges()
	{
		for ( EdgeListVector::iterator curEdgeList = m_Edges.begin(); 
			curEdgeList != m_Edges.end(); 
			++curEdgeList )
		{
			for ( EdgeList::iterator curEdge = (*curEdgeList).begin(); 
				curEdge != (*curEdgeList).end(); 
				++curEdge )
			{
				// 起点，和终止点中一旦有任意一个为无效Index，表示这条Edge去向不明了
				if (m_Nodes[curEdge->GetTo()].GetIndex() == GraphNode::em_Invalid_Node_Index || 
					m_Nodes[curEdge->GetFrom()].GetIndex() == GraphNode::em_Invalid_Node_Index)
				{
					curEdge = (*curEdgeList).erase(curEdge);
				}
			}
		}
	}

	// 通过一个Node Index返回一个Node
	GraphNode& GetNode(int nNodeIndex)
	{
		assert( (nNodeIndex < (int)m_Nodes.size()) &&
				(nNodeIndex >=0) &&
				"<Graph::GetNode>: invalid index" );

		return m_Nodes[nNodeIndex];
	}

	// 通过From Node Index和To Node Index返回一条边
	GraphEdge& GetEdge(int nFrom, int nTo)
	{
		assert( (nFrom < m_Nodes.size()) &&
				(nFrom >=0) &&
				m_Nodes[nFrom].GetIndex() != GraphNode::em_Invalid_Node_Index &&
				"<Graph::GetEdge>: invalid 'from' index" );

		assert( (nTo < m_Nodes.size()) &&
				(nTo >=0) &&
				m_Nodes[nTo].GetIndex() != GraphNode::em_Invalid_Node_Index &&
				"<Graph::GetEdge>: invalid 'to' index" );

		// 
		for ( EdgeList::iterator curEdge = m_Edges[nFrom].begin();
			  curEdge != m_Edges[nFrom].end();
			  ++curEdge )
		{
			if (curEdge->GetTo() == nTo) 
			{
				return *curEdge;
			}
		}

		assert (0 && "<Graph::GetEdge>: edge does not exist");
	}

	// 获取下一个没有被加入Graph的Node Index
	int GetNextFreeNodeIndex()
	{
		return m_nNextNodeIndex;
	}

	// 将一个Node加入Graph中
	int AddNode(GraphNode node)
	{
		if (node.GetIndex() < (int)m_Nodes.size())
		{
			assert ( m_Nodes[node.GetIndex()].GetIndex() == GraphNode::em_Invalid_Node_Index &&
					 "<Graph::AddNode>: Attempting to add a node with a duplicate ID" );

			m_Nodes[node.GetIndex()] = node;
			return m_nNextNodeIndex;
		}
		else
		{
			//make sure the new node has been indexed correctly
			assert (node.GetIndex() == m_nNextNodeIndex && "<Graph::AddNode>:invalid index");

			m_Nodes.push_back(node);
			m_Edges.push_back(EdgeList());

			return m_nNextNodeIndex++;
		}
	}

	// 将一个Node从Graph中移除
	void RemoveNode(int nNodeIndex)
	{
		assert(nNodeIndex < (int)m_Nodes.size() && "<Graph::RemoveNode>: invalid node index");

		// 立刻设置这个Node的Index为无效
		m_Nodes[nNodeIndex].SetIndex(GraphNode::em_Invalid_Node_Index);

		// 无向图
		if (!m_bDigraph)
		{    
			// visit each neighbour and erase any edges leading to this node
			for ( EdgeList::iterator curEdge = m_Edges[nNodeIndex].begin(); 
				  curEdge != m_Edges[nNodeIndex].end();
				  ++curEdge )
			{
				for ( EdgeList::iterator curE = m_Edges[curEdge->GetTo()].begin();
					  curE != m_Edges[curEdge->GetTo()].end();
					  ++curE )
				{
					if (curE->GetTo() == nNodeIndex)
					{
						curE = m_Edges[curEdge->GetTo()].erase(curE);
						break;
					}
				}
			}

			// finally, clear this node's edges
			m_Edges[nNodeIndex].clear();
		}
		else
		{
			// 有向图
			RemoveInvalidEdges();
		}
	}

	// 添加一条边
	void AddEdge(GraphEdge edge)
	{
		assert( (edge.GetFrom() < m_nNextNodeIndex) &&
				(edge.GetTo() < m_nNextNodeIndex) &&
				"<Graph::AddEdge>: invalid node index" );

		if ( (m_Nodes[edge.GetTo()].GetIndex() != GraphNode::em_Invalid_Node_Index) && 
			 (m_Nodes[edge.GetFrom()].GetIndex() != GraphNode::em_Invalid_Node_Index) )
		{
			// 
			if (CheckEdgeUnique(edge.GetFrom(), edge.GetTo()))
			{
				m_Edges[edge.GetFrom()].push_back(edge);
			}

			// 无向图还需要添加一条边的逆边
			if (!m_bDigraph)
			{
				// check to make sure the edge is unique before adding
				if (CheckEdgeUnique(edge.GetTo(), edge.GetFrom()))
				{
					GraphEdge NewEdge = edge;

					NewEdge.SetTo(edge.GetFrom());
					NewEdge.SetFrom(edge.GetTo());

					m_Edges[edge.GetTo()].push_back(NewEdge);
				}
			}
		}
	}

	// 从Graph中删除一条边
	void RemoveEdge(int nFrom, int nTo)
	{
		assert ( (nFrom < (int)m_Nodes.size()) &&
				 (nTo < (int)m_Nodes.size()) &&
				 "<Graph::RemoveEdge>:invalid node index" );

		EdgeList::iterator curEdge;
		
		// 无向图需要相应先删除逆边
		if (!m_bDigraph)
		{
			for (curEdge = m_Edges[nTo].begin();
				curEdge != m_Edges[nTo].end();
				++curEdge)
			{
				if (curEdge->GetTo() == nFrom)
				{
					curEdge = m_Edges[nTo].erase(curEdge);
					break;
				}
			}
		}

		for ( curEdge = m_Edges[nFrom].begin();
			  curEdge != m_Edges[nFrom].end();
			  ++curEdge )
		{
			if (curEdge->GetTo() == nTo)
			{
				curEdge = m_Edges[nFrom].erase(curEdge);
				break;
			}
		}
	}

	// 设置一条Edge的代价，该函数没有考虑逆边，这是调用者需要关心的，无向图时候，代价如何设置
	void SetEdgeCost(int nFrom, int nTo, double fCost)
	{
		assert( (nFrom < m_Nodes.size()) && 
				(nTo < m_Nodes.size()) &&
				"<Graph::SetEdgeCost>: invalid index" );

		for ( EdgeList::iterator curEdge = m_Edges[nFrom].begin(); 
			  curEdge != m_Edges[nFrom].end();
			  ++curEdge )
		{
			if (curEdge->GetTo() == nTo)
			{
				curEdge->SetCost(fCost);
				break;
			}
		}
	}

	// 获取Graph中的Node数
	int GetNodesNum()
	{
		return m_Nodes.size();
	}

	// 获取Graph中被添加过的Node数
	int GetActiveNodesNum()
	{
		int count = 0;
		for (unsigned int n=0; n<m_Nodes.size(); ++n) 
		{
			if (m_Nodes[n].GetIndex() != GraphNode::em_Invalid_Node_Index)
			{
				++count;
			}
		}

		return count;
	}

	// 获取Graph中Edge数量
	int GetEdgesNum()
	{
		int count = 0;
		for ( EdgeListVector::iterator curEdge = m_Edges.begin();
			  curEdge != m_Edges.end();
			  ++curEdge )
		{
			count += curEdge->size();
		}

		return count;
	}

	// 是否是有向图
	bool isDigraph()
	{
		return m_bDigraph;
	}

	// 检测该Graph是否是0个Node
	bool isEmpty()
	{
		return m_Nodes.empty();
	}

	// 检查Node是否已经存在
	bool isNodePresent(int nNodeIndex)
	{
		if ((nNodeIndex >= (int)m_Nodes.size() || 
			(m_Nodes[nNodeIndex].GetIndex() == GraphNode::em_Invalid_Node_Index)))
		{
			return false;
		}
		else 
		{
			return true;
		}
	}

	// 检查Edge是否已经存在
	bool isEdgePresent(int nFrom, int nTo)
	{
		if (isNodePresent(nFrom) && isNodePresent(nTo))
		{
			for ( EdgeList::iterator curEdge = m_Edges[nFrom].begin();
				  curEdge != m_Edges[nFrom].end();
				  ++curEdge )
			{
				if (curEdge->GetTo() == nTo) 
				{
					return true;
				}
			}

			return false;
		}
		else 
		{
			return false;
		}
	}

	// 清空Graph
	void ClearGraph()
	{
		m_nNextNodeIndex = 0; 
		m_Nodes.clear(); 
		m_Edges.clear();
	}

	// 仅清空Edge
	void RemoveEdges()
	{
		for ( EdgeListVector::iterator it = m_Edges.begin(); 
			  it != m_Edges.end(); 
			  ++it )
		{
			it->clear();
		}
	}

	// -------------------------------- //

	// 通过Node Index找到相关联的边
	EdgeList& GetEdgeByNodeIndex(int nNodeIndex)
	{
		assert( (nNodeIndex < m_Edges.size()) &&
			"<Graph::GetEdgeByNodeIndex>: invalid 'from' index" );

		return m_Edges[nNodeIndex];
	}

	// 获取一个随机的图结点
	Vector2D GetRandomNodePos()
	{
		int RandIndex = RandInt(0, GetActiveNodesNum() - 1);
		return m_Nodes[RandIndex].GetPos();
	}

	// 通过一个坐标返回最接近的图结点索引
	int GetClosestNodeToPosition(Vector2D pos)
	{
		double ClosestSoFar = MaxDouble;
		int    ClosestNodeIndex  = GraphNode::em_Invalid_Node_Index;

		for (unsigned int n=0; n<m_Nodes.size(); ++n) 
		{
			if (m_Nodes[n].GetIndex() != GraphNode::em_Invalid_Node_Index)
			{
				double dist = Vec2DDistanceSq(pos, m_Nodes[n].GetPos());

				if (dist < ClosestSoFar)
				{
					ClosestSoFar = dist;
					ClosestNodeIndex = m_Nodes[n].GetIndex();
				}
			}
		}

		return ClosestNodeIndex;
	}


private:
	NodeVector		m_Nodes;

	// 参考GetEdge函数，这个vector中每一个元素是一个list，它保存了从某一个节点出发的所有边
	EdgeListVector	m_Edges;

	// 下一个将被加入到Graph中的Node Index
	int             m_nNextNodeIndex;

	// 是否是有向图
	bool            m_bDigraph;
};
#endif

