// ProjectileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "ProjectileDialog.h"
#include "afxdialogex.h"


// ProjectileDialog dialog

IMPLEMENT_DYNAMIC(ProjectileDialog, CDialog)

ProjectileDialog::ProjectileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ProjectileDialog::IDD, pParent)
{

}

ProjectileDialog::~ProjectileDialog()
{
}

void ProjectileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_projectileList);
}


BEGIN_MESSAGE_MAP(ProjectileDialog, CDialog)
END_MESSAGE_MAP()


// ProjectileDialog message handlers
