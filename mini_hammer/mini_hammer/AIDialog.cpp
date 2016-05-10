// AIDialog.cpp : implementation file
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "AIDialog.h"
#include "afxdialogex.h"


// AIDialog dialog

IMPLEMENT_DYNAMIC(AIDialog, CDialog)

AIDialog::AIDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AIDialog::IDD, pParent)
{

}

AIDialog::~AIDialog()
{
}

void AIDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AIDialog, CDialog)
END_MESSAGE_MAP()


// AIDialog message handlers
