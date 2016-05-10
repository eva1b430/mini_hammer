#include "EditLayer.h"
#include "AppMacros.h"
#include "GlobalVar.h"
#include "Graph.h"
#include "Pathfinder.h"
#include "Vehicle.h"
#include "Goal_Think.h"
USING_NS_CC;

// CCScene* EditLayer::scene()
// {
//     CCScene *scene = CCScene::create();
//     EditLayer *layer = EditLayer::create();
// 
// 	scene->addChild(layer);
// 
//     return scene;
// }

// on "init" you need to initialize your instance
bool EditLayer::init()
{
	ChangeColor(GL_Grey);
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//setTouchEnabled(false);
    
    return true;
}


void EditLayer::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void EditLayer::onEnter()
{
	CCLayer::onEnter();

	// 添加
	scheduleUpdate();
}

void EditLayer::onExit()
{
	// 添加
	unscheduleUpdate();

	CCLayer::onExit();
}

void EditLayer::update(float delta)
{
	CCLayer::update(delta);
}

void EditLayer::draw()
{
	CCLayer::draw();

	// 
	RenderGraph();

	// 
	ChangeColor(GL_Blue);
	list<Vehicle*>::iterator itr;
	for (itr = GlobalVar::instance().GetGameWorld()->GetAllBots().begin();
		itr != GlobalVar::instance().GetGameWorld()->GetAllBots().end();
		itr++)
	{
		(*itr)->GetBrain()->Render();

		ccPointSize(8);
		ccDrawPoint(GlobalVar::instance().HammerPosToCocosPos((*itr)->GetPos()));
	}
}

void EditLayer::RenderGraph()
{
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	Graph* pGraph = pPathFinder->GetGraph();
	if (pGraph)
	{
		// 有图
		for (int nd=0; nd < pGraph->GetNodesNum(); ++nd)
		{
			int left   = (int)(pGraph->GetNode(nd).GetPos().x - pPathFinder->m_fCellWidth/2.0);
			int top    = (int)(pGraph->GetNode(nd).GetPos().y - pPathFinder->m_fCellHeight/2.0);
			int right  = (int)(1+pGraph->GetNode(nd).GetPos().x + pPathFinder->m_fCellWidth/2.0);
			int bottom = (int)(1+pGraph->GetNode(nd).GetPos().y + pPathFinder->m_fCellHeight/2.0);

			// 绘制地形
			switch ((Pathfinder::TerrainItem_Type)pGraph->GetNode(nd).GetTerrainType())
			{
			case Pathfinder::emTerrain_Normal:
				ChangeColor(GL_White);
				break;

			case Pathfinder::emTerrain_Obstacle:
				ChangeColor(GL_Black);
				break;

			case Pathfinder::emTerrain_Water:
				ChangeColor(GL_Blue);
				break;

			case Pathfinder::emTerrain_Mud:
				ChangeColor(GL_Brown);
				break;

			case Pathfinder::emTerrain_HealthGiver:
				ChangeColor(GL_Red);
				break;

			case Pathfinder::emTerrain_WeaponGiver:
				ChangeColor(GL_Light_Grey);
				break;

			default:
				ChangeColor(GL_White);
				break;

			}//end switch

			if (pGraph->GetNode(nd).GetTerrainType() == Pathfinder::emTerrain_HealthGiver ||
				pGraph->GetNode(nd).GetTerrainType() == Pathfinder::emTerrain_WeaponGiver)
			{
				ccDrawCircle( GlobalVar::instance().HammerPosToCocosPos(pGraph->GetNode(nd).GetPos()), 10, 
					CC_DEGREES_TO_RADIANS(90), 6, false);
			}
			else
			{
				ccColor4F color = ccc4FFromccc4B(m_pTerrainColor);

				CCPoint filledVertices[] = { GlobalVar::instance().HammerPosToCocosPos(Vector2D(left, top)), 
					GlobalVar::instance().HammerPosToCocosPos(Vector2D(right, top)),
					GlobalVar::instance().HammerPosToCocosPos(Vector2D(right, bottom)),
					GlobalVar::instance().HammerPosToCocosPos(Vector2D(left, bottom))};

				ccDrawSolidPoly(filledVertices, 4, color);
			}
		}
	}

	RenderNavGraph();

	// 绘制SPT
	ChangeColor(GL_Purple);
	glLineWidth(1.0f);

	for (unsigned int e=0; e < pPathFinder->m_SubTree.size(); ++e)
	{   
		if (pPathFinder->m_SubTree[e])
		{
			Vector2D from = pPathFinder->m_pGraph->GetNode(pPathFinder->m_SubTree[e]->GetFrom()).GetPos();
			Vector2D to   = pPathFinder->m_pGraph->GetNode(pPathFinder->m_SubTree[e]->GetTo()).GetPos();

			ccDrawLine(GlobalVar::instance().HammerPosToCocosPos(from), 
						GlobalVar::instance().HammerPosToCocosPos(to));
		}
	}

	// 绘制最短路径
	ChangeColor(GL_Red);
	glLineWidth(5.0f);
	if (pPathFinder->m_Path.size() > 0)
	{
		std::list<int>::iterator it = pPathFinder->m_Path.begin();
		std::list<int>::iterator nxt = it;
		++nxt;

		for (it; nxt != pPathFinder->m_Path.end(); ++it, ++nxt)
		{
			ccDrawLine( GlobalVar::instance().HammerPosToCocosPos(pPathFinder->m_pGraph->GetNode(*it).GetPos()),
				GlobalVar::instance().HammerPosToCocosPos(pPathFinder->m_pGraph->GetNode(*nxt).GetPos()));
		}
	}

}

void EditLayer::ChangeColor(GLPenColor color)
{
	switch(color)
	{
	case GL_Red:
		{
			m_pTerrainColor = ccc4(255,0,0,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Blue:
		{
			m_pTerrainColor = ccc4(0,0,255,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Green:
		{
			m_pTerrainColor = ccc4(0,255,0,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Black:
		{
			m_pTerrainColor = ccc4(0,0,0,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Pink:
		{
			m_pTerrainColor = ccc4(255,200,200,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Grey:
		{
			m_pTerrainColor = ccc4(200,200,200,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Yellow:
		{
			m_pTerrainColor = ccc4(255,255,0,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Orange:
		{
			m_pTerrainColor = ccc4(255,170,0,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Purple:
		{
			m_pTerrainColor = ccc4(255,0,170,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Brown:
		{
			m_pTerrainColor = ccc4(133,90,0,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_White:
		{
			m_pTerrainColor = ccc4(255,255,255,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Dark_Green:
		{
			m_pTerrainColor = ccc4(0,100,0,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Light_Blue:
		{
			m_pTerrainColor = ccc4(0,255,255,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Light_Grey:
		{
			m_pTerrainColor = ccc4(200,200,200,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Light_Pink:
		{
			m_pTerrainColor = ccc4(255,230,230,EDIT_LAYER_ALPHA);
		}
		break;
	case GL_Hollow:
		{
			m_pTerrainColor = ccc4(255,255,255,EDIT_LAYER_ALPHA);
		}
		break;

	}

	ccColor4F color2 = ccc4FFromccc4B(m_pTerrainColor);
	ccDrawColor4F(color2.r, color2.g, color2.b, color2.a);
}

void EditLayer::RenderNavGraph()
{
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	Graph* pGraph = pPathFinder->GetGraph();
	if (!pGraph)
	{
		return ;
	}
	
	if (pGraph->GetNodesNum() == 0) 
	{
		return ;
	}

	// 灰色
	ChangeColor(GL_Grey);

	// 绘制导航图结点
	glLineWidth(1.0f);
	for (int nd=0; nd < pGraph->GetNodesNum(); ++nd)
	{
		GraphNode& refNode = pGraph->GetNode(nd);

		// 注意这里的原因
		if(refNode.GetIndex() == GraphNode::em_Invalid_Node_Index)
		{
			continue;
		}
	
		ChangeColor(GL_Grey);
		// 绘制邻接边
		Graph::EdgeList& edgeList = pGraph->GetEdgeByNodeIndex(refNode.GetIndex());
		list<GraphEdge>::iterator itrEdge;
		for (itrEdge = edgeList.begin(); itrEdge != edgeList.end(); itrEdge++)
		{
			ccDrawLine( GlobalVar::instance().HammerPosToCocosPos(refNode.GetPos()),
				GlobalVar::instance().HammerPosToCocosPos(pGraph->GetNode(itrEdge->GetTo()).GetPos()));
		}
	}
}
