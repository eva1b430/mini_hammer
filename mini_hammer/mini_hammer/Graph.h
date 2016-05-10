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

	// �Ƿ���һ��Ψһ��Edge����������ı���ֹ��Graph�е�ĳһ����һ�£����ʾ�����ı����ظ���
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

	// ��Graph���Ƴ�һ�����õı�
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
				// ��㣬����ֹ����һ��������һ��Ϊ��ЧIndex����ʾ����Edgeȥ������
				if (m_Nodes[curEdge->GetTo()].GetIndex() == GraphNode::em_Invalid_Node_Index || 
					m_Nodes[curEdge->GetFrom()].GetIndex() == GraphNode::em_Invalid_Node_Index)
				{
					curEdge = (*curEdgeList).erase(curEdge);
				}
			}
		}
	}

	// ͨ��һ��Node Index����һ��Node
	GraphNode& GetNode(int nNodeIndex)
	{
		assert( (nNodeIndex < (int)m_Nodes.size()) &&
				(nNodeIndex >=0) &&
				"<Graph::GetNode>: invalid index" );

		return m_Nodes[nNodeIndex];
	}

	// ͨ��From Node Index��To Node Index����һ����
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

	// ��ȡ��һ��û�б�����Graph��Node Index
	int GetNextFreeNodeIndex()
	{
		return m_nNextNodeIndex;
	}

	// ��һ��Node����Graph��
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

	// ��һ��Node��Graph���Ƴ�
	void RemoveNode(int nNodeIndex)
	{
		assert(nNodeIndex < (int)m_Nodes.size() && "<Graph::RemoveNode>: invalid node index");

		// �����������Node��IndexΪ��Ч
		m_Nodes[nNodeIndex].SetIndex(GraphNode::em_Invalid_Node_Index);

		// ����ͼ
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
			// ����ͼ
			RemoveInvalidEdges();
		}
	}

	// ���һ����
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

			// ����ͼ����Ҫ���һ���ߵ����
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

	// ��Graph��ɾ��һ����
	void RemoveEdge(int nFrom, int nTo)
	{
		assert ( (nFrom < (int)m_Nodes.size()) &&
				 (nTo < (int)m_Nodes.size()) &&
				 "<Graph::RemoveEdge>:invalid node index" );

		EdgeList::iterator curEdge;
		
		// ����ͼ��Ҫ��Ӧ��ɾ�����
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

	// ����һ��Edge�Ĵ��ۣ��ú���û�п�����ߣ����ǵ�������Ҫ���ĵģ�����ͼʱ�򣬴����������
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

	// ��ȡGraph�е�Node��
	int GetNodesNum()
	{
		return m_Nodes.size();
	}

	// ��ȡGraph�б���ӹ���Node��
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

	// ��ȡGraph��Edge����
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

	// �Ƿ�������ͼ
	bool isDigraph()
	{
		return m_bDigraph;
	}

	// ����Graph�Ƿ���0��Node
	bool isEmpty()
	{
		return m_Nodes.empty();
	}

	// ���Node�Ƿ��Ѿ�����
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

	// ���Edge�Ƿ��Ѿ�����
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

	// ���Graph
	void ClearGraph()
	{
		m_nNextNodeIndex = 0; 
		m_Nodes.clear(); 
		m_Edges.clear();
	}

	// �����Edge
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

	// ͨ��Node Index�ҵ�������ı�
	EdgeList& GetEdgeByNodeIndex(int nNodeIndex)
	{
		assert( (nNodeIndex < m_Edges.size()) &&
			"<Graph::GetEdgeByNodeIndex>: invalid 'from' index" );

		return m_Edges[nNodeIndex];
	}

	// ��ȡһ�������ͼ���
	Vector2D GetRandomNodePos()
	{
		int RandIndex = RandInt(0, GetActiveNodesNum() - 1);
		return m_Nodes[RandIndex].GetPos();
	}

	// ͨ��һ�����귵����ӽ���ͼ�������
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

	// �ο�GetEdge���������vector��ÿһ��Ԫ����һ��list���������˴�ĳһ���ڵ���������б�
	EdgeListVector	m_Edges;

	// ��һ���������뵽Graph�е�Node Index
	int             m_nNextNodeIndex;

	// �Ƿ�������ͼ
	bool            m_bDigraph;
};
#endif

