// VehicleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "VehicleDialog.h"
#include "afxdialogex.h"
#include "ValueSetDialog.h"


// VehicleDialog dialog

IMPLEMENT_DYNAMIC(VehicleDialog, CDialog)

VehicleDialog::VehicleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(VehicleDialog::IDD, pParent)
{

}

VehicleDialog::~VehicleDialog()
{
}

void VehicleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_vehicleList);

	DWORD dwStyle = m_vehicleList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_vehicleList.SetExtendedStyle(dwStyle); //设置扩展风格

	LVCOLUMN lvColumn;
	int nCol;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 120;
	lvColumn.pszText = TEXT("Name");
	nCol = m_vehicleList.InsertColumn(0, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	lvColumn.pszText = TEXT("Value");
	m_vehicleList.InsertColumn(1, &lvColumn);

	LVITEM lvItem;
	int nItem;

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = TEXT("最大驱动力");
	nItem = m_vehicleList.InsertItem(&lvItem);

	m_vehicleList.SetItemText(nItem, 1, TEXT("400"));

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 1;
	lvItem.iSubItem = 0;
	lvItem.pszText = TEXT("Roger A. Miller");
	nItem = m_vehicleList.InsertItem(&lvItem);

	m_vehicleList.SetItemText(nItem, 1, TEXT("Footballer"));

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 2;
	lvItem.iSubItem = 0;
	lvItem.pszText = TEXT("Marie-Julie W. Gross");
	nItem = m_vehicleList.InsertItem(&lvItem);

	m_vehicleList.SetItemText(nItem, 1, TEXT("Student"));

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 3;
	lvItem.iSubItem = 0;
	lvItem.pszText = TEXT("Ella Pius Roger");
	nItem = m_vehicleList.InsertItem(&lvItem);

	m_vehicleList.SetItemText(nItem, 1, TEXT("Architect"));
}


BEGIN_MESSAGE_MAP(VehicleDialog, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &VehicleDialog::OnNMDblclkList1)
END_MESSAGE_MAP()


// VehicleDialog message handlers


void VehicleDialog::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	ValueSetDialog dlg;
	dlg.DoModal();
}
