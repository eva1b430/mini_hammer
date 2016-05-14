// CbehaviorView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "CbehaviorView.h"
#include "misc/Cgdi.h"
#include "memdc.h"
#include "GlobalVar.h"
#include "Goal.h"
#include "Goal_Composite.h"
#include "Goal_Think.h"


// CbehaviorView

IMPLEMENT_DYNCREATE(CbehaviorView, CView)

CbehaviorView::CbehaviorView()
{

}

CbehaviorView::~CbehaviorView()
{
}

BEGIN_MESSAGE_MAP(CbehaviorView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CbehaviorView ��ͼ
void CbehaviorView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

	CMemoryDC *pMemDC = NULL;
	pDC = pMemDC = new CMemoryDC(pDC);

	RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right;
	int nHeight = rect.bottom;

	pMemDC->FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));
	gdi->StartDrawing(pDC->GetSafeHdc());
	//gdi->TextAtPos(0, 0, "Hello");
	list<Vehicle*>& vehicleList = GlobalVar::instance().GetGameWorld()->GetAllBots();
	if (vehicleList.size() > 0)
	{
		int xOffset = 0;
		int yOffset = 0;

		Vehicle* pFirstVehicle = (*vehicleList.begin());
		pFirstVehicle->GetBrain()->RenderText(xOffset, yOffset);
	}
	gdi->StopDrawing(pDC->GetSafeHdc());

	delete pMemDC;

	return ;
}


// CbehaviorView ���

#ifdef _DEBUG
void CbehaviorView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CbehaviorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CbehaviorView ��Ϣ�������


BOOL CbehaviorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CView::OnEraseBkgnd(pDC);

	return TRUE;
}


void CbehaviorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()

	OnPrepareDC(&dc); 
	OnDraw(&dc); //������OnDraw
}


void CbehaviorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	SetTimer(2, 0.1, NULL);
}


void CbehaviorView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	KillTimer(2);
}


void CbehaviorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Invalidate();

	CView::OnTimer(nIDEvent);
}
