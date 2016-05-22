#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "Graph.h"
#include "atltypes.h"

#include <list>
#define GRID_CELL_SIZE 25


class Pathfinder
{
public:
	// 地形元素类型
	enum TerrainItem_Type
	{
		emTerrain_Normal = 0,		// 
		emTerrain_Obstacle = 1,		// 障碍
		emTerrain_Water = 2,		// 水
		emTerrain_Mud = 3,			// 泥
		emTerrain_Source = 4,		// 源点
		emTerrain_Target = 5,		// 目标点

		// 触发器
		emTerrain_HealthGiver = 6,	// 回复
		emTerrain_WeaponGiver = 7	// BUF
	};

public:
	Pathfinder(void);
	~Pathfinder(void);

	// 在绘制回调中调用
	void Render();

	// 创建世界
	void CreateGraphGrid(int nRectWidth, int nRectHeight, int nWidthItemNum, int nHeightItemNum);
	void AddAllNeighboursToGridNode(int row, int col, int NumCellsX, int NumCellsY);
	void AddAllNeighboursToGridNodeTrigger(int nTriggerIndex, int row, int col, int NumCellsX, int NumCellsY);
	bool CheckNeighbourValid(int x, int y, int NumCellsX, int NumCellsY);

	// 修改地形元素类型
	void ChangeBrush(const TerrainItem_Type NewBrush)
	{
		m_CurrentTerrainBrush = NewBrush;
	}

	// 绘制地形元素
	void PaintTerrain(CPoint p);
	void PaintTrigger(CPoint p);

	// 对于导航图显示模式切换
	void ToggleShowGraph(){m_bShowGraph = !m_bShowGraph;}
	void SwitchGraphOn(){m_bShowGraph = true;}
	void SwitchGraphOff(){m_bShowGraph = false;}
	bool isShowGraphOn()const{return m_bShowGraph;}

	// 绘制导航图
	void PaintNavGraph();

	// 获取地形元素对应的权重系数
	void WeightNavGraphNodeEdges(Graph& graph, int nNodeIndex, double weight);
	double GetTerrainCostWeight(TerrainItem_Type emTerrainType);

	// 更新算法
	void UpdateAlgorithm();

	Graph* GetGraph(){return m_pGraph;}

	void Save( char* FileName);
	void Load( char* FileName);

	// 计算成本表（填充二维数组）
	void CreatePathCostTable(Graph& graph);

public:
	// 当前选定的地形元素
	TerrainItem_Type				m_CurrentTerrainBrush;
	// 图数据
	Graph*							m_pGraph;

	double							m_fCellWidth;
	double							m_fCellHeight;

	int								m_nWidthItemNum;
	int								m_nHeightItemNum;

	//std::vector<TerrainItem_Type>	m_TerrainType;

	// 是否显示导航图
	bool							m_bShowGraph;

	// 路径
	std::list<int>					m_Path;
	// SPT
	vector<GraphEdge*>				m_SubTree;

	// 成本表
	vector<vector<double> >			m_PathCostTable;
};
#endif