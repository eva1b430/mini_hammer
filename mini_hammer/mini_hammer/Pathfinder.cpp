#include "Pathfinder.h"
#include "misc/Cgdi.h"
#include "GraphAlgorithms.h"
#include <fstream>

Pathfinder::Pathfinder(void)
	: m_CurrentTerrainBrush(emTerrain_Normal)
	, m_pGraph(NULL)
	, m_fCellWidth(0.0f)
	, m_fCellHeight(0.0f)
	, m_nWidthItemNum(0)
	, m_nHeightItemNum(0)
	, m_bShowGraph(NULL)
{

}


Pathfinder::~Pathfinder(void)
{
	if (m_pGraph)
	{
		delete m_pGraph;
		m_pGraph = NULL;
	}
}

void Pathfinder::Render()
{
	for (int nd=0; nd < m_pGraph->GetNodesNum(); ++nd)
	{
		int left   = (int)(m_pGraph->GetNode(nd).GetPos().x - m_fCellWidth/2.0);
		int top    = (int)(m_pGraph->GetNode(nd).GetPos().y - m_fCellHeight/2.0);
		int right  = (int)(1+m_pGraph->GetNode(nd).GetPos().x + m_fCellWidth/2.0);
		int bottom = (int)(1+m_pGraph->GetNode(nd).GetPos().y + m_fCellHeight/2.0);

		//render dots at the corners of the cells
		gdi->DrawDot(left, top, RGB(0,0,0));
		gdi->DrawDot(right-1, top, RGB(0,0,0));
		gdi->DrawDot(left, bottom-1, RGB(0,0,0));
		gdi->DrawDot(right-1, bottom-1, RGB(0,0,0));

		gdi->GreyPen();

		// 修改为GL绘制

		// 绘制地形
		switch (m_pGraph->GetNode(nd).GetTerrainType())
		{
		case 0:
			gdi->WhiteBrush();
			break;

		case 1:
			gdi->BlackBrush();
			break;

		case 2:
			gdi->LightBlueBrush();
			break;

		case 3:
			gdi->BrownBrush();
			break;

		default:
			gdi->WhiteBrush();
			break;

		}//end switch

		gdi->Rect(left, top, right, bottom);
	}

	PaintNavGraph();
}

void Pathfinder::CreateGraphGrid(int nRectWidth, int nRectHeight, int nWidthItemNum, int nHeightItemNum)
{
	double midX = GRID_CELL_SIZE/2;
	double midY = GRID_CELL_SIZE/2;

	m_fCellWidth = GRID_CELL_SIZE;
	m_fCellHeight = GRID_CELL_SIZE;

	m_nWidthItemNum = nWidthItemNum;
	m_nHeightItemNum = nHeightItemNum;

	//m_TerrainType.assign(nWidthItemNum * nHeightItemNum, emTerrain_Normal);

	if (m_pGraph)
	{
		delete m_pGraph;
		m_pGraph = NULL;
	}
	
	m_pGraph = new Graph;

	//first create all the nodes
	for (int row=0; row<nHeightItemNum; ++row)
	{
		for (int col=0; col<nWidthItemNum; ++col)
		{
			if (m_pGraph)
			{
				GraphNode node;
				node.SetIndex(m_pGraph->GetNextFreeNodeIndex());
				node.SetPos(Vector2D(midX + (col*GRID_CELL_SIZE), midY + (row*GRID_CELL_SIZE)));
				node.SetTerrainType(emTerrain_Normal);
				m_pGraph->AddNode(node);
			}
		}
	}

	// 添加边
	for (int row = 0; row < nHeightItemNum; ++row)
	{
		for (int col = 0; col < nWidthItemNum; ++col)
		{
			AddAllNeighboursToGridNode(row, col, nWidthItemNum, nHeightItemNum);
		}
	}

	UpdateAlgorithm();
}

void Pathfinder::WeightNavGraphNodeEdges(Graph& graph, int nNodeIndex, double weight)
{
	assert(nNodeIndex < graph.GetNodesNum());

	Graph::EdgeList& edgeList = m_pGraph->GetEdgeByNodeIndex(nNodeIndex);
	list<GraphEdge>::iterator itrEdge;
	for (itrEdge = edgeList.begin(); itrEdge != edgeList.end(); itrEdge++)
	{
		//calculate the distance between nodes
		double dist = Vec2DDistance(graph.GetNode(itrEdge->GetFrom()).GetPos(),
			graph.GetNode(itrEdge->GetTo()).GetPos());

		graph.SetEdgeCost(itrEdge->GetFrom(), itrEdge->GetTo(), dist * weight);

		if (!graph.isDigraph())
		{      
			graph.SetEdgeCost(itrEdge->GetTo(), itrEdge->GetFrom(), dist * weight);
		}
	}
}

bool Pathfinder::CheckNeighbourValid(int x, int y, int NumCellsX, int NumCellsY)
{
	return !((x < 0) || (x >= NumCellsX) || (y < 0) || (y >= NumCellsY));
}

void Pathfinder::AddAllNeighboursToGridNodeTrigger(int nTriggerIndex, int row, int col, int NumCellsX, int NumCellsY)
{
	// -1, 0, 1,
	for (int i=-1; i<2; ++i)
	{
		for (int j=-1; j<2; ++j)
		{
			int nodeX = col + j;
			int nodeY = row + i;

			//skip if equal to this node
			if ( (i == 0) && (j==0) ) 
			{
				continue;
			}

			//check to see if this is a valid neighbour
			if (CheckNeighbourValid(nodeX, nodeY, NumCellsX, NumCellsY))
			{
				// calculate the distance to this node
				Vector2D PosNode      = m_pGraph->GetNode(row*NumCellsX+col).GetPos();
				Vector2D PosNeighbour = m_pGraph->GetNode(nodeY*NumCellsX+nodeX).GetPos();

				double dist = PosNode.Distance(PosNeighbour);

				// 添加边
				GraphEdge NewEdge;
				NewEdge.SetFrom(nTriggerIndex);
				NewEdge.SetTo(nodeY * NumCellsX + nodeX);
				NewEdge.SetCost(dist * 0.5);

				m_pGraph->AddEdge(NewEdge);

				// 无向图添加逆边
				if (!m_pGraph->isDigraph())
				{
					GraphEdge NewEdge;
					NewEdge.SetFrom(nodeY * NumCellsX + nodeX);
					NewEdge.SetTo(nTriggerIndex);
					NewEdge.SetCost(dist * 0.5);

					m_pGraph->AddEdge(NewEdge);
				}
			}
		}
	}
}

void Pathfinder::AddAllNeighboursToGridNode(int row, int col, int NumCellsX, int NumCellsY)
{
	// -1, 0, 1,
	for (int i=-1; i<2; ++i)
	{
		for (int j=-1; j<2; ++j)
		{
			int nodeX = col + j;
			int nodeY = row + i;

			//skip if equal to this node
			if ( (i == 0) && (j==0) ) 
			{
				continue;
			}

			//check to see if this is a valid neighbour
			if (CheckNeighbourValid(nodeX, nodeY, NumCellsX, NumCellsY))
			{
				// calculate the distance to this node
				Vector2D PosNode      = m_pGraph->GetNode(row*NumCellsX+col).GetPos();
				Vector2D PosNeighbour = m_pGraph->GetNode(nodeY*NumCellsX+nodeX).GetPos();

				double dist = PosNode.Distance(PosNeighbour);

				// 添加边
				GraphEdge NewEdge;
				NewEdge.SetFrom(row * NumCellsX + col);
				NewEdge.SetTo(nodeY * NumCellsX + nodeX);
				NewEdge.SetCost(dist);

				m_pGraph->AddEdge(NewEdge);

				// 无向图添加逆边
				if (!m_pGraph->isDigraph())
				{
					GraphEdge NewEdge;
					NewEdge.SetFrom(nodeY * NumCellsX + nodeX);
					NewEdge.SetTo(row * NumCellsX + col);
					NewEdge.SetCost(dist);

					m_pGraph->AddEdge(NewEdge);
				}
			}
		}
	}
}

void Pathfinder::PaintTrigger(CPoint p)
{
	int x = (int)((double)(p.x)/m_fCellWidth);
	int y = (int)((double)(p.y)/m_fCellHeight);

	if ( (x > m_nWidthItemNum) || (y > (m_nHeightItemNum-1)) ) 
	{
		return;
	}

	//int nIndexOfTerrainType = y * m_nWidthItemNum + x;

	if(m_CurrentTerrainBrush == emTerrain_HealthGiver ||
		m_CurrentTerrainBrush == emTerrain_WeaponGiver)
	{
		//if (!m_pGraph->isNodePresent(y * m_nWidthItemNum + x))
		//{
			// 这时候Terrain需要追加一个值
			//m_TerrainType.push_back(m_CurrentTerrainBrush);

			int yy = (y * m_nWidthItemNum + x) / m_nWidthItemNum;
			int xx = (y * m_nWidthItemNum + x) - (yy * m_nWidthItemNum);

			GraphNode node;

			// 索引从 0 开始
			node.SetIndex(m_pGraph->GetNodesNum());
			node.SetPos(Vector2D(p.x, p.y));
			node.SetTerrainType(m_CurrentTerrainBrush);
			m_pGraph->AddNode(node);

			AddAllNeighboursToGridNodeTrigger(node.GetIndex(), yy, xx, m_nWidthItemNum, m_nHeightItemNum);
		//}
	}
	else
	{
		PaintTerrain(p);

		return ;
	}

	UpdateAlgorithm();
}

void Pathfinder::PaintTerrain(CPoint p)
{
	if(m_CurrentTerrainBrush == emTerrain_HealthGiver ||
		m_CurrentTerrainBrush == emTerrain_WeaponGiver)
	{
		return ;
	}

	int x = (int)((double)(p.x)/m_fCellWidth);
	int y = (int)((double)(p.y)/m_fCellHeight);

	if ( (x > m_nWidthItemNum) || (y > (m_nHeightItemNum-1)) ) 
	{
		return;
	}

	//int nIndexOfTerrainType = y * m_nWidthItemNum + x;

	//m_TerrainType[nIndexOfTerrainType] = m_CurrentTerrainBrush;

	// 还有很多事情要做
	m_pGraph->GetNode(y * m_nWidthItemNum + x).SetTerrainType(m_CurrentTerrainBrush);
	if (m_CurrentTerrainBrush == emTerrain_Obstacle)
	{
		m_pGraph->RemoveNode(y * m_nWidthItemNum + x);
	}
	else
	{
		// 说明需要重加进来节点，如果试图把一个障碍模块换成一个其他元素的
		if (!m_pGraph->isNodePresent(y * m_nWidthItemNum + x))
		{
			int yy = (y * m_nWidthItemNum + x) / m_nWidthItemNum;
			int xx = (y * m_nWidthItemNum + x) - (yy * m_nWidthItemNum);

			GraphNode node;
			node.SetIndex(yy * m_nWidthItemNum + xx);
			node.SetPos(Vector2D(xx * m_fCellWidth + m_fCellWidth / 2.0f, yy * m_fCellHeight + m_fCellHeight / 2.0f));
			node.SetTerrainType(m_CurrentTerrainBrush);
			m_pGraph->AddNode(node);

			AddAllNeighboursToGridNode(yy, xx, m_nWidthItemNum, m_nHeightItemNum);
		}

		// 设置边权重
		WeightNavGraphNodeEdges(*m_pGraph, y * m_nWidthItemNum + x, GetTerrainCostWeight((TerrainItem_Type)m_CurrentTerrainBrush));
	}

	UpdateAlgorithm();
}

void Pathfinder::PaintNavGraph()
{
	if (m_pGraph->GetNodesNum() == 0) 
	{
		return;
	}

	// 灰色
	gdi->SetPenColor(Cgdi::light_grey);

	// 绘制导航图结点
	for (int nd=0; nd < m_pGraph->GetNodesNum(); ++nd)
	{
		GraphNode& refNode = m_pGraph->GetNode(nd);

		// 注意这里的原因
		if(refNode.GetIndex() == GraphNode::em_Invalid_Node_Index)
		{
			continue;
		}

		gdi->Circle(refNode.GetPos(), 2);

		// 绘制邻接边
 		Graph::EdgeList& edgeList = m_pGraph->GetEdgeByNodeIndex(refNode.GetIndex());
 		list<GraphEdge>::iterator itrEdge;
		for (itrEdge = edgeList.begin(); itrEdge != edgeList.end(); itrEdge++)
		{
			gdi->Line(refNode.GetPos(), m_pGraph->GetNode(itrEdge->GetTo()).GetPos());
		}
	}
}

void Pathfinder::UpdateAlgorithm()
{
	// 
	m_Path.clear();
	m_SubTree.clear();

	// SPT
	Graph_SearchDijkstra djk(*m_pGraph, 0, 99);
	m_Path = djk.GetPathToTarget();
	m_SubTree = djk.GetSPT();
}

double Pathfinder::GetTerrainCostWeight(TerrainItem_Type emTerrainType)
{
	const double cost_normal_Weight = 1.0;
	const double cost_water_Weight  = 2.0;
	const double cost_mud_Weight   = 1.5;
	const double cost_obstacle_Weight = 100.0;

	// 其他都返回障碍的权重，非常大
	switch(emTerrainType)
	{
	case emTerrain_Normal:
		return cost_normal_Weight;
	case emTerrain_Water:
		return cost_water_Weight;
	case emTerrain_Mud:
		return cost_mud_Weight;
	default:
		return cost_obstacle_Weight;
	}
}

void Pathfinder::Save(char* FileName)
{
	std::ofstream save(FileName);
	assert (save && "Pathfinder::Save< bad file >");

	//save the size of the grid
	save << m_nWidthItemNum << endl;
	save << m_nHeightItemNum << endl;

	//int nSize = m_TerrainType.size();
	//for (unsigned int t=0; t < m_TerrainType.size(); ++t)
	//{
	//	save << m_TerrainType[t] << endl;
	//}

	// 写入图结点信息
	save << m_pGraph->GetNodesNum() << endl;
	for (int i = 0; i < m_pGraph->GetNodesNum(); i++)
	{
		GraphNode node = m_pGraph->GetNode(i);
		save << "Index: " << node.GetIndex() << " PosX: " << node.GetPos().x << " PosY: " << node.GetPos().y << " TerrainType: " << node.GetTerrainType() <<endl;
	}

	// 写入图边的信息
	save << m_pGraph->GetEdgesNum() << endl;
	for (int i = 0; i < m_pGraph->GetNodesNum(); i++)
	{
		Graph::EdgeList edge = m_pGraph->GetEdgeByNodeIndex(i);
		Graph::EdgeList::iterator itr;
		for (itr = edge.begin(); itr != edge.end(); itr++)
		{
			save << "m_iFrom: " << itr->GetFrom() << " m_iTo: " << itr->GetTo() << " m_dCost: " << itr->GetCost() << endl;
		}
	}

	// 写入触发器
	for (int i = 0; i < m_pGraph->GetNodesNum(); i++)
	{
		GraphNode node = m_pGraph->GetNode(i);
		//save << "Index: " << node.GetIndex() << " PosX: " << node.GetPos().x << " PosY: " << node.GetPos().y << " TerrainType: " << node.GetTerrainType() <<endl;
		if (node.GetTerrainType() == emTerrain_HealthGiver)
		{
			save << "TriggerType: " << node.GetTerrainType() << " Index: " << node.GetIndex() << " PosX: " << node.GetPos().x << " PosY: " << node.GetPos().y << endl;
		}
		else if (node.GetTerrainType() == emTerrain_WeaponGiver)
		{
			save << "TriggerType: " << node.GetTerrainType() << " Index: " << node.GetIndex() << " PosX: " << node.GetPos().x << " PosY: " << node.GetPos().y << endl;
		}
	}
}

void Pathfinder::Load(char* FileName)
{
	ifstream load(FileName);
	assert (load && "Pathfinder::Save< bad file >");

	//load the size of the grid
	int nNodeNum = 0;
	load >> m_nWidthItemNum;
	load >> m_nHeightItemNum;
	load >> nNodeNum;

	//create a graph of the correct size
	//CreateGraphGrid(m_fCellWidth * m_nWidthItemNum, m_fCellHeight * m_nHeightItemNum, m_nWidthItemNum, m_nHeightItemNum);
	m_Path.clear();
	m_SubTree.clear();

	//int terrain;

	//save the terrain
	for (int t=0; t<nNodeNum; ++t)
	{
		char buffer[50];
		int nIndex;
		float nPosX;
		float nPosY;
		int nTerrainType;
		load >> buffer >> nIndex >> buffer >> nPosX >> buffer >> nPosY >> buffer >> nTerrainType;

		int x = (int)((double)(nPosX)/m_fCellWidth);
		int y = (int)((double)(nPosY)/m_fCellHeight);

		if ( (x > m_nWidthItemNum) || (y > (m_nHeightItemNum-1)) ) 
		{
			return;
		}

		//m_pGraph->GetNode(t).SetTerrainType(nTerrainType);

		//UpdateGraphFromBrush(terrain, t);
		// 还有很多事情要做
		if (nTerrainType == emTerrain_Obstacle)
		{
			m_pGraph->GetNode(t).SetTerrainType(nTerrainType);
			m_pGraph->RemoveNode(t);
		}
		else if (nTerrainType == emTerrain_HealthGiver ||
				nTerrainType == emTerrain_WeaponGiver)
		{
			//if (!m_pGraph->isNodePresent(t))
			//{
				int yy = (y * m_nWidthItemNum + x) / m_nWidthItemNum;
				int xx = (y * m_nWidthItemNum + x) - (yy * m_nWidthItemNum);

				GraphNode node;

				// 索引从 0 开始
				node.SetIndex(nIndex);
				node.SetPos(Vector2D(nPosX, nPosY));
				node.SetTerrainType(nTerrainType);
				m_pGraph->AddNode(node);

				AddAllNeighboursToGridNodeTrigger(nIndex, yy, xx, m_nWidthItemNum, m_nHeightItemNum);
			//}
		}
		else
		{
			// 说明需要重加进来节点，如果试图把一个障碍模块换成一个其他元素的
			if (!m_pGraph->isNodePresent(t))
			{
				int yy = (y * m_nWidthItemNum + x) / m_nWidthItemNum;
				int xx = (y * m_nWidthItemNum + x) - (yy * m_nWidthItemNum);

				GraphNode node;
				node.SetIndex(nIndex);
				node.SetPos(Vector2D(nPosX, nPosY));
				node.SetTerrainType(nTerrainType);
				m_pGraph->AddNode(node);

				AddAllNeighboursToGridNode(yy, xx, m_nWidthItemNum, m_nHeightItemNum);
			}

			m_pGraph->GetNode(nIndex).SetTerrainType(nTerrainType);

			// 设置边权重
			//WeightNavGraphNodeEdges(*m_pGraph, t, GetTerrainCostWeight((TerrainItem_Type)terrain));
		}
	}

	// 加载触发器

	UpdateAlgorithm();

}

void Pathfinder::CreatePathCostTable( Graph& graph )
{
	m_PathCostTable.clear();

	// 全部初始化为0.0f，该二维表的两个维度都等于图的节点数量
	vector<double> row(graph.GetNodesNum(), 0.0);
	vector<vector<double> > PathCosts(graph.GetNodesNum(), row);

	for (int source = 0; source != graph.GetNodesNum(); source++)
	{
		Graph_SearchDijkstra djk(graph, 
			source,
			-1);

		for (int target = 0; target != graph.GetNodesNum(); target++)
		{
			if (source != target)
			{
				PathCosts[source][target] = djk.GetCostToNode(target);
			}
		}
	}

	m_PathCostTable = PathCosts;
}
