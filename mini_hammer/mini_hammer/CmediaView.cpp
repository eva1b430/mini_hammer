// CmediaView.cpp : ʵ���ļ�
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


// CmediaView ��ͼ

void CmediaView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CmediaView ���

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


// CmediaView ��Ϣ�������
