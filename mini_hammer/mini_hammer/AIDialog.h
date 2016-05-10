#pragma once


// AIDialog dialog

class AIDialog : public CDialog
{
	DECLARE_DYNAMIC(AIDialog)

public:
	AIDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~AIDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_AI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
