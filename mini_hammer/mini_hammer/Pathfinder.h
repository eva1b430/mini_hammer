#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "Graph.h"
#include "atltypes.h"

#include <list>
#define GRID_CELL_SIZE 25


class Pathfinder
{
public:
	// ����Ԫ������
	enum TerrainItem_Type
	{
		emTerrain_Normal = 0,		// 
		emTerrain_Obstacle = 1,		// �ϰ�
		emTerrain_Water = 2,		// ˮ
		emTerrain_Mud = 3,			// ��
		emTerrain_Source = 4,		// Դ��
		emTerrain_Target = 5,		// Ŀ���

		// ������
		emTerrain_HealthGiver = 6,	// �ظ�
		emTerrain_WeaponGiver = 7	// BUF
	};

public:
	Pathfinder(void);
	~Pathfinder(void);

	// �ڻ��ƻص��е���
	void Render();

	// ��������
	void CreateGraphGrid(int nRectWidth, int nRectHeight, int nWidthItemNum, int nHeightItemNum);
	void AddAllNeighboursToGridNode(int row, int col, int NumCellsX, int NumCellsY);
	void AddAllNeighboursToGridNodeTrigger(int nTriggerIndex, int row, int col, int NumCellsX, int NumCellsY);
	bool CheckNeighbourValid(int x, int y, int NumCellsX, int NumCellsY);

	// �޸ĵ���Ԫ������
	void ChangeBrush(const TerrainItem_Type NewBrush)
	{
		m_CurrentTerrainBrush = NewBrush;
	}

	// ���Ƶ���Ԫ��
	void PaintTerrain(CPoint p);
	void PaintTrigger(CPoint p);

	// ���ڵ���ͼ��ʾģʽ�л�
	void ToggleShowGraph(){m_bShowGraph = !m_bShowGraph;}
	void SwitchGraphOn(){m_bShowGraph = true;}
	void SwitchGraphOff(){m_bShowGraph = false;}
	bool isShowGraphOn()const{return m_bShowGraph;}

	// ���Ƶ���ͼ
	void PaintNavGraph();

	// ��ȡ����Ԫ�ض�Ӧ��Ȩ��ϵ��
	void WeightNavGraphNodeEdges(Graph& graph, int nNodeIndex, double weight);
	double GetTerrainCostWeight(TerrainItem_Type emTerrainType);

	// �����㷨
	void UpdateAlgorithm();

	Graph* GetGraph(){return m_pGraph;}

	void Save( char* FileName);
	void Load( char* FileName);

	// ����ɱ�������ά���飩
	void CreatePathCostTable(Graph& graph);

public:
	// ��ǰѡ���ĵ���Ԫ��
	TerrainItem_Type				m_CurrentTerrainBrush;
	// ͼ����
	Graph*							m_pGraph;

	double							m_fCellWidth;
	double							m_fCellHeight;

	int								m_nWidthItemNum;
	int								m_nHeightItemNum;

	//std::vector<TerrainItem_Type>	m_TerrainType;

	// �Ƿ���ʾ����ͼ
	bool							m_bShowGraph;

	// ·��
	std::list<int>					m_Path;
	// SPT
	vector<GraphEdge*>				m_SubTree;

	// �ɱ���
	vector<vector<double> >			m_PathCostTable;
};
#endif