#pragma once
#include "afxcmn.h"


// VehicleDialog dialog

class VehicleDialog : public CDialog
{
	DECLARE_DYNAMIC(VehicleDialog)

public:
	VehicleDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~VehicleDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_VEHICLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_vehicleList;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
