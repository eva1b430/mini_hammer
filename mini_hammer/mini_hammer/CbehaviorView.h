#pragma once


// CbehaviorView ��ͼ
class Goal_Composite;
class CbehaviorView : public CView
{
	DECLARE_DYNCREATE(CbehaviorView)

protected:
	CbehaviorView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CbehaviorView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


