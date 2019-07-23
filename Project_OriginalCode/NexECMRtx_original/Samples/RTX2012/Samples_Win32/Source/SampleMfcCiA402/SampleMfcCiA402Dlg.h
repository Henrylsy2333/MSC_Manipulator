
// SampleMfcCiA402Dlg.h : header file
//

#pragma once

#include "nex_type.h"
#include "NexCoeMotion.h"
#include "Nexecm.h"

// CSampleMfcCiA402Dlg dialog
class CSampleMfcCiA402Dlg : public CDialogEx
{
// Construction
public:
	CSampleMfcCiA402Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SAMPLEMFCCIA402_DIALOG };

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

	CANAxis_T mAxis[3];

	U16_T   masterId;
	UINT    TimerHandle;
	U16_T   misUpdate;
	U16_T   mDoData;
	U16_T   mDiData;
	U32_T   Count;
	CBrush   m_greenbrush;
	CBrush   m_whitebrush;
	COLORREF m_greencolor;
	COLORREF m_whitecolor;

	void    StopDriver();
	void    DioCheck();
	void    AutoRunCheck();

	RTN_ERR  mStopAutoMove();
	RTN_ERR  mStartAutoMove();

	RTN_ERR  mSoftLimitSet();
	RTN_ERR  mServoOn();
	RTN_ERR  mServoOff();
	RTN_ERR  mStartMove( I32_T TarPosX, I32_T TarPosY, I32_T TarPosZ );
	RTN_ERR  mStopMove();
	RTN_ERR  mHomeMove( CANAxis_T Axis, U16_T Method, U32_T Speed );

	I32_T mAutoRunMoveIndex;
	I32_T mStartAutoMoveFlag;
	I32_T mTargetPosArray_X[17];
	I32_T mTargetPosArray_Y[17];
	I32_T mTargetPosArray_Z[17];

	CWinThread *m_pThread;

	LRESULT OnUpdateControl( WPARAM wParam, LPARAM lParam);
	static UINT ThreadFunc( LPVOID pvParam );
	U16_T mThreadStop;
	U16_T mGetHomeTypeRealNum(U16_T ComboIndex );
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonStop();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonServoOnX();
	afx_msg void OnBnClickedButtonStopX();
	afx_msg void OnBnClickedButtonServoOnY();
	afx_msg void OnBnClickedButtonServoOnZ();
	afx_msg void OnBnClickedButtonSetX();
	afx_msg void OnBnClickedButtonMoveX();
	afx_msg void OnBnClickedButtonHomeX();
	afx_msg void OnBnClickedButtonSetY();
	afx_msg void OnBnClickedButtonMoveY();
	afx_msg void OnBnClickedButtonHomeY();
	afx_msg void OnBnClickedButtonStopY();
	afx_msg void OnBnClickedButtonSetZ();
	afx_msg void OnBnClickedButtonMoveZ();
	afx_msg void OnBnClickedButtonHomeZ();
	afx_msg void OnBnClickedButtonStopZ();
	afx_msg void OnBnClickedButtonAuto();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonServoOnZ1();
	int mCheck;
	afx_msg void OnBnClickedCheckDio();
};



