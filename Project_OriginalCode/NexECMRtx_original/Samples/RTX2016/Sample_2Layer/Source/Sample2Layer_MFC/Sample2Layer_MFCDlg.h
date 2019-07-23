
// Sample2Layer_MFCDlg.h : header file
//

#pragma once
#include"Nexecm.h"
#include <rtapi.h>
// CSample2Layer_MFCDlg dialog
class CSample2Layer_MFCDlg : public CDialogEx
{
// Construction
public:
	CSample2Layer_MFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SAMPLE2LAYER_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonMemory();
	afx_msg void OnBnClickedButtonEvent();

	RTN_ERR ret;
	HANDLE oBhandle ;
	HANDLE oBhandle2 ;
	HANDLE oBhandle3;
	HANDLE sMhandle ;
	afx_msg void OnClose();
	
	afx_msg void OnBnClickedButtonEvent2();
};
