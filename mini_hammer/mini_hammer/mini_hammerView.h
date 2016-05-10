
// mini_hammerView.h : interface of the Cmini_hammerView class
//

#pragma once

class GameWorld;
class Cmini_hammerView : public CView
{
	enum emEditMode
	{
		em_EditModeMode_Edit = 0,		// 编辑模式
		em_EditModeMode_Simulation		// 仿真模式
	};

protected: // create from serialization only
	Cmini_hammerView();
	DECLARE_DYNCREATE(Cmini_hammerView)

// Attributes
public:
	Cmini_hammerDoc* GetDocument() const;

	//创建Cocos2dX窗口  
	BOOL CreateCocos2dXWindow();
private:  
	//是否已经初始化  
	BOOL m_bInitCocos2dX;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate( );

// Implementation
public:
	virtual ~Cmini_hammerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();

	afx_msg void OnTouchSource();
	afx_msg void OnTouchTarget();
	afx_msg void OnTouchObstacle();
	afx_msg void OnTouchMud();
	afx_msg void OnTouchWater();
	afx_msg void OnTouchWipeOut();

	afx_msg void OnAddHealthGiver();
	afx_msg void OnAddRocketGiver();

	afx_msg void OnRun();
	afx_msg void OnStop();

	// UI的一些效果
	afx_msg void OnTouchSourceUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_SOURCE);}
	afx_msg void OnTouchTargetUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_TARGET);}
	afx_msg void OnTouchObstacleUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_OBSTACLE);}
	afx_msg void OnTouchMudUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_MUD);}
	afx_msg void OnTouchWaterUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_WATER);}
	afx_msg void OnTouchWipeOutUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_WIPEOUT);}

	afx_msg void OnAddHealthGiverUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_HEALTHGIVER);}
	afx_msg void OnAddRocketGiverUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_ROCKETGIVER);}
	afx_msg void OnRunUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_RUN);}
	afx_msg void OnStopUpdate(CCmdUI *pCmdUI){pCmdUI->SetCheck(m_nCmdID==ID_BUTTON_STOP);}

	DECLARE_MESSAGE_MAP()
	
private:
	// 是否启动仿真
	emEditMode m_emMode;
	long m_nCmdID;
	GameWorld*		m_pGame;

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEnableGraph();
	afx_msg void OnEnableTrigger();
	//afx_msg void OnUpdateEnableGraph(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();

	afx_msg void OnVehicle();
	afx_msg void OnWeapon();
	afx_msg void OnProjectile();
	afx_msg void OnAIDialog();
};

#ifndef _DEBUG  // debug version in mini_hammerView.cpp
inline Cmini_hammerDoc* Cmini_hammerView::GetDocument() const
   { return reinterpret_cast<Cmini_hammerDoc*>(m_pDocument); }
#endif

