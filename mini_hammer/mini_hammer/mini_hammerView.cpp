#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "mini_hammer.h"
#endif

#include "mini_hammerDoc.h"
#include "mini_hammerView.h"
#include "misc/Cgdi.h"
#include "memdc.h"

#include "VehicleDialog.h"
#include "WeaponDialog.h"
#include "ProjectileDialog.h"
#include "AIDialog.h"

#include "cocos2d.h"
#include "CCEGLView.h"
#include "CCApplication.h"
#include "AppDelegate.h"
#include "GlobalVar.h"
#include "GameWorld.h"
#include "Regulator.h"
#include "Vehicle.h"

#include "EditLayer.h"
#include "SimulationLayer.h"

using namespace cocos2d;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmini_hammerView

IMPLEMENT_DYNCREATE(Cmini_hammerView, CView)

BEGIN_MESSAGE_MAP(Cmini_hammerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cmini_hammerView::OnFilePrintPreview)

	ON_COMMAND(ID_BUTTON_SOURCE, &Cmini_hammerView::OnTouchSource)
	ON_COMMAND(ID_BUTTON_TARGET, &Cmini_hammerView::OnTouchTarget)
	ON_COMMAND(ID_BUTTON_OBSTACLE, &Cmini_hammerView::OnTouchObstacle)
	ON_COMMAND(ID_BUTTON_MUD, &Cmini_hammerView::OnTouchMud)
	ON_COMMAND(ID_BUTTON_WATER, &Cmini_hammerView::OnTouchWater)
	ON_COMMAND(ID_BUTTON_WIPEOUT, &Cmini_hammerView::OnTouchWipeOut)
	ON_COMMAND(ID_BUTTON_HEALTHGIVER, &Cmini_hammerView::OnAddHealthGiver)
	ON_COMMAND(ID_BUTTON_ROCKETGIVER, &Cmini_hammerView::OnAddRocketGiver)
	ON_COMMAND(ID_BUTTON_RUN, &Cmini_hammerView::OnRun)
	ON_COMMAND(ID_BUTTON_STOP, &Cmini_hammerView::OnStop)

	ON_UPDATE_COMMAND_UI(ID_BUTTON_SOURCE, &Cmini_hammerView::OnTouchSourceUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TARGET, &Cmini_hammerView::OnTouchTargetUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_OBSTACLE, &Cmini_hammerView::OnTouchObstacleUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MUD, &Cmini_hammerView::OnTouchMudUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WATER, &Cmini_hammerView::OnTouchWaterUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_WIPEOUT, &Cmini_hammerView::OnTouchWipeOutUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_HEALTHGIVER, &Cmini_hammerView::OnAddHealthGiverUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ROCKETGIVER, &Cmini_hammerView::OnAddRocketGiverUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RUN, &Cmini_hammerView::OnRunUpdate)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_STOP, &Cmini_hammerView::OnStopUpdate)

	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ENABLE_GRAPH, &Cmini_hammerView::OnEnableGraph)
	ON_COMMAND(ID_ENABLE_TRIGGER, &Cmini_hammerView::OnEnableTrigger)
	//ON_UPDATE_COMMAND_UI(ID_ENABLE_GRAPH, &Cmini_hammerView::OnUpdateEnableGraph)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//ON_COMMAND(ID_FILE_SAVE, &Cmini_hammerView::OnFileSave)
	//ON_COMMAND(ID_FILE_OPEN, &Cmini_hammerView::OnFileOpen)
	ON_COMMAND(ID_32786, &Cmini_hammerView::OnVehicle)
	ON_COMMAND(ID_32787, &Cmini_hammerView::OnWeapon)
	ON_COMMAND(ID_32788, &Cmini_hammerView::OnProjectile)
	ON_COMMAND(ID_32789, &Cmini_hammerView::OnAIDialog)
END_MESSAGE_MAP()

// Cmini_hammerView construction/destruction

AppDelegate app;
Cmini_hammerView::Cmini_hammerView()
	: m_pGame(NULL)
	, m_bInitCocos2dX(FALSE)
	, m_emMode(em_ViewMode_Edit)
{
	// TODO: add construction code here
	m_pGame = new GameWorld;
	GlobalVar::instance().SetGameWorld(m_pGame);

// 	AppDelegate app;
// 	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
// 	eglView->setViewName("HelloCpp");
// 	eglView->setFrameSize(400, 300);
// 	CCApplication::sharedApplication()->run(true);	
}

Cmini_hammerView::~Cmini_hammerView()
{
	if (m_pGame)
	{
		delete m_pGame;
		m_pGame = NULL;
	}
}

BOOL Cmini_hammerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cmini_hammerView drawing

 void Cmini_hammerView::OnDraw(CDC* pDC)
 {
	 Cmini_hammerDoc* pDoc = GetDocument();
	 ASSERT_VALID(pDoc);
	 if (!pDoc)
		 return;

	 // TODO: add draw code for native data here

	 /*if (m_pPathFinder)
	 {
	 CMemoryDC *pMemDC = NULL;
	 pDC = pMemDC = new CMemoryDC(pDC);

	 RECT rect;
	 GetClientRect(&rect);
	 int nWidth = rect.right;
	 int nHeight = rect.bottom;

	 pMemDC->FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));
	 gdi->StartDrawing(pDC->GetSafeHdc());
	 m_pPathFinder->Render();
	 gdi->StopDrawing(pDC->GetSafeHdc());

	 delete pMemDC;

	 return ;
	 }*/
 }


// Cmini_hammerView printing


void Cmini_hammerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

void Cmini_hammerView::OnTouchSource()
{
	m_nCmdID = ID_BUTTON_SOURCE;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_Source);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_Source);
	}
}
void Cmini_hammerView::OnTouchTarget()
{
	m_nCmdID = ID_BUTTON_TARGET;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_Target);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_Target);
	}
}
void Cmini_hammerView::OnTouchObstacle()
{
	m_nCmdID = ID_BUTTON_OBSTACLE;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_Obstacle);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_Obstacle);
	}
}
void Cmini_hammerView::OnTouchMud()
{
	m_nCmdID = ID_BUTTON_MUD;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_Mud);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_Mud);
	}
}
void Cmini_hammerView::OnTouchWater()
{
	m_nCmdID = ID_BUTTON_WATER;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_Water);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_Water);
	}
}
void Cmini_hammerView::OnTouchWipeOut()
{
	m_nCmdID = ID_BUTTON_WIPEOUT;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_Normal);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_Normal);
	}
}

void Cmini_hammerView::OnAddHealthGiver()
{
	// 添加触发器
	m_nCmdID = ID_BUTTON_HEALTHGIVER;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_HealthGiver);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_HealthGiver);
	}
}

void Cmini_hammerView::OnAddRocketGiver()
{
	m_nCmdID = ID_BUTTON_ROCKETGIVER;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		pPathFinder->ChangeBrush(Pathfinder::emTerrain_WeaponGiver);
	}

	if (app.getEditLayer())
	{
		app.getEditLayer()->changeEditMark(Pathfinder::emTerrain_WeaponGiver);
	}
}

void Cmini_hammerView::OnRun()
{
	m_nCmdID = ID_BUTTON_RUN;
	m_emMode = em_ViewMode_Simulation;
	app.disableEdit();
}

void Cmini_hammerView::OnStop()
{
	m_nCmdID = ID_BUTTON_STOP;
	m_emMode = em_ViewMode_Edit;
	app.enablEdit();
}

BOOL Cmini_hammerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cmini_hammerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cmini_hammerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cmini_hammerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cmini_hammerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cmini_hammerView diagnostics

#ifdef _DEBUG
void Cmini_hammerView::AssertValid() const
{
	CView::AssertValid();
}

void Cmini_hammerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmini_hammerDoc* Cmini_hammerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmini_hammerDoc)));
	return (Cmini_hammerDoc*)m_pDocument;
}

 void Cmini_hammerView::OnPaint()
 {
 	CPaintDC dc(this); 
 	OnPrepareDC(&dc); 
 	OnDraw(&dc); //调用了OnDraw
 }

void Cmini_hammerView::OnInitialUpdate()
{
	RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right;
	int nHeight = rect.bottom;
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (!m_bInitCocos2dX)
	{
		pPathFinder->CreateGraphGrid(nWidth, nHeight, 10, 10);
	}

	// 
	CreateCocos2dXWindow();
}

#endif //_DEBUG


// Cmini_hammerView message handlers


void Cmini_hammerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 拿到了坐标
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{
		if (m_emMode == em_ViewMode_Edit)
		{
			pPathFinder->PaintTrigger(point);
		}

		Vehicle* pOwn = NULL;
		pOwn = GlobalVar::instance().GetGameWorld()->getOwn();
		if (pOwn)
		{
			Vector2D pos = Vector2D(point.x, point.y);
			pOwn->GetSteering()->SetTarget(pos);
		}

		// 绘制触发器
		CCSprite* pSprite = NULL;
		if (GlobalVar::instance().GetPathfinder()->m_CurrentTerrainBrush == Pathfinder::emTerrain_HealthGiver)
		{
			pSprite = CCSprite::create("media/image/1.png");
			app.getEditLayer()->addChild(pSprite);
			pSprite->setPosition(GlobalVar::instance().HammerPosToCocosPos(Vector2D(point.x, point.y)));
		} 
		else if(GlobalVar::instance().GetPathfinder()->m_CurrentTerrainBrush == Pathfinder::emTerrain_WeaponGiver)
		{
			pSprite = CCSprite::create("media/image/2.png");
			app.getEditLayer()->addChild(pSprite);
			pSprite->setPosition(GlobalVar::instance().HammerPosToCocosPos(Vector2D(point.x, point.y)));
		}
		else
		{
			// do nothing
		}
	}

	//Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void Cmini_hammerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// 如果是编辑模式，则接收事件，否则返回
	if (m_emMode == em_ViewMode_Simulation)
	{
		return ;
	}

	// TODO: Add your message handler code here and/or call default
	if (nFlags == MK_LBUTTON)
	{
		Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
		if (pPathFinder)
		{
			pPathFinder->PaintTerrain(point);
		}
	}

	HCURSOR hCur = LoadCursor(NULL, IDC_CROSS);
	::SetCursor(hCur);

	app.getEditLayer()->updateEditMarkPosition(GlobalVar::instance().HammerPosToCocosPos(Vector2D(point.x, point.y)));

	//Invalidate();

	CView::OnMouseMove(nFlags, point);
}


void Cmini_hammerView::OnEnableGraph()
{
	// TODO: Add your command handler code here
	Pathfinder* pPathFinder = GlobalVar::instance().GetPathfinder();
	if (pPathFinder)
	{

	}
}


void Cmini_hammerView::OnEnableTrigger()
{
	// TODO: Add your command handler code here
}


//void Cmini_hammerView::OnUpdateEnableGraph(CCmdUI *pCmdUI)
//{
//	// TODO: Add your command update UI handler code here
//	//if (m_pPathFinder)
//	//{
//	//	pCmdUI->SetCheck(!m_pPathFinder->isShowGraphOn());
//	//	m_pPathFinder->ToggleShowGraph();
//	//}
//}


BOOL Cmini_hammerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	// 双缓冲
	return CView::OnEraseBkgnd(pDC);

	//return TRUE;
}

BOOL Cmini_hammerView::CreateCocos2dXWindow()
{
	if (m_bInitCocos2dX)
	{
		return TRUE;
	}

	// 新建一个CRect变量获取窗口的客户区大小
	CRect   tClientRect;
	GetClientRect(&tClientRect);
	// 取得使用的OpenGL视窗
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	// 以指定的客户区大小创建视窗，这里我们对setFrameSize增加了参数3以传入当前控件的窗口句柄
	eglView->setFrameSize(tClientRect.Width(), tClientRect.Height(), GetSafeHwnd());
	// 调用程序的运行函数，增加参数bool型变量控制是否进行消息循环。因为MFC控件本身有自已的消息响应处理
	// 如果不改动的话，这里就会进入死循环
	cocos2d::CCApplication::sharedApplication()->run(false);
	app.enablEdit();
	// 这里将变量设置为TRUE
	m_bInitCocos2dX = TRUE;

	SetTimer(1, 1, NULL);

	return TRUE;
}


LRESULT Cmini_hammerView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bInitCocos2dX)  
	{  
		//CCEGLView::sharedOpenGLView()->WindowProc(message, wParam, lParam);  
	}

	return CView::WindowProc(message, wParam, lParam);
}


void Cmini_hammerView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//我们写一个renderWorld函数代表Cocos2d-x的世界渲染  
	cocos2d::CCApplication::sharedApplication()->renderWorld();
	//CWnd::OnTimer(nIDEvent);

	CView::OnTimer(nIDEvent);
}


void Cmini_hammerView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if(TRUE == m_bInitCocos2dX)
	{  
		//退出将m_bInitCocos2dX设为FALSE
		m_bInitCocos2dX = FALSE;
		//释放定时器资源  
		KillTimer(1);

		//调用显示设备单件实例对象的end函数  
		CCDirector::sharedDirector()->end();
		//处理一次下一帧，必须调用.  
		CCDirector::sharedDirector()->mainLoop();

		CWnd::OnDestroy();
	}
}


void Cmini_hammerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(TRUE == m_bInitCocos2dX)
	{  
		CRect   tClientRect;
		GetClientRect(&tClientRect);
		//重新设置窗口大小及投影矩阵  
		CCEGLView::sharedOpenGLView()->resize(tClientRect.Width(),tClientRect.Height());
		CCDirector::sharedDirector()->reshapeProjection(CCSizeMake(tClientRect.Width(),tClientRect.Height()));
	}
}


void Cmini_hammerView::OnFileSave()
{
	// TODO: Add your command handler code here
}


void Cmini_hammerView::OnFileOpen()
{
	// TODO: Add your command handler code here
}


void Cmini_hammerView::OnVehicle()
{
	// TODO: Add your command handler code here
	KillTimer(1);
	VehicleDialog dlg(this);
	dlg.DoModal();
	SetTimer(1, 1, NULL);
}


void Cmini_hammerView::OnWeapon()
{
	// TODO: Add your command handler code here
	KillTimer(1);
	WeaponDialog dlg(this);
	dlg.DoModal();
	SetTimer(1, 1, NULL);
}


void Cmini_hammerView::OnProjectile()
{
	// TODO: Add your command handler code here
	KillTimer(1);
	ProjectileDialog dlg(this);
	dlg.DoModal();
	SetTimer(1, 1, NULL);
}


void Cmini_hammerView::OnAIDialog()
{
	// TODO: Add your command handler code here
	KillTimer(1);
	AIDialog dlg(this);
	dlg.DoModal();
	SetTimer(1, 1, NULL);
}
