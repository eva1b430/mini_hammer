#pragma once
#include "afxcmn.h"


// ProjectileDialog dialog
class ProjectileDialog : public CDialog
{
	DECLARE_DYNAMIC(ProjectileDialog)

public:
	ProjectileDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ProjectileDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_PROJECTILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_projectileList;
};
