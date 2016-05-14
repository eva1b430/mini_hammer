// CmediaView.cpp : 实现文件
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "CmediaView.h"


// CmediaView

IMPLEMENT_DYNCREATE(CmediaView, CView)

CmediaView::CmediaView()
{

}

CmediaView::~CmediaView()
{
}

BEGIN_MESSAGE_MAP(CmediaView, CView)
END_MESSAGE_MAP()


// CmediaView 绘图

void CmediaView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CmediaView 诊断

#ifdef _DEBUG
void CmediaView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CmediaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CmediaView 消息处理程序
