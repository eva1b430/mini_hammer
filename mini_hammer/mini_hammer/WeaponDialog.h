#pragma once
#include "afxcmn.h"


// WeaponDialog dialog

class WeaponDialog : public CDialogEx
{
	DECLARE_DYNAMIC(WeaponDialog)

public:
	WeaponDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~WeaponDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_WEAPON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_weaponList;
};
