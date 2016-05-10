// WeaponDialog.cpp : implementation file
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "WeaponDialog.h"
#include "afxdialogex.h"


// WeaponDialog dialog

IMPLEMENT_DYNAMIC(WeaponDialog, CDialogEx)

WeaponDialog::WeaponDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(WeaponDialog::IDD, pParent)
{

}

WeaponDialog::~WeaponDialog()
{
}

void WeaponDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_weaponList);
}


BEGIN_MESSAGE_MAP(WeaponDialog, CDialogEx)
END_MESSAGE_MAP()


// WeaponDialog message handlers
