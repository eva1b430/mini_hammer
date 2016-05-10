// ValueSetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "ValueSetDialog.h"
#include "afxdialogex.h"


// ValueSetDialog dialog

IMPLEMENT_DYNAMIC(ValueSetDialog, CDialog)

ValueSetDialog::ValueSetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ValueSetDialog::IDD, pParent)
{

}

ValueSetDialog::~ValueSetDialog()
{
}

void ValueSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_valueEdit);
}


BEGIN_MESSAGE_MAP(ValueSetDialog, CDialog)
END_MESSAGE_MAP()


// ValueSetDialog message handlers
