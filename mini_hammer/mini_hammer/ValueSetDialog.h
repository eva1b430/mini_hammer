#pragma once
#include "afxwin.h"


// ValueSetDialog dialog

class ValueSetDialog : public CDialog
{
	DECLARE_DYNAMIC(ValueSetDialog)

public:
	ValueSetDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ValueSetDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_valueEdit;
};
