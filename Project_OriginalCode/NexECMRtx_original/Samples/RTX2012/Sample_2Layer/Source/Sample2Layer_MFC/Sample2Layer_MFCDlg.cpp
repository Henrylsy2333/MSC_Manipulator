
// Sample2Layer_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sample2Layer_MFC.h"
#include "Sample2Layer_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define EVN_NAME "EventHandle"
#define EVN_NAME2 "EventHandle2"
#define SHM_NAME "MemoryHandle"

typedef	struct
{
	I32_T master;
	I32_T x;
	I32_T y;
	I32_T ans;
}WIN32_DAT;

PVOID location ;
WIN32_DAT *pData ;
CString strText;

U16_T step = 0;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSample2Layer_MFCDlg dialog




CSample2Layer_MFCDlg::CSample2Layer_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSample2Layer_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSample2Layer_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSample2Layer_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CSample2Layer_MFCDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_MEMORY, &CSample2Layer_MFCDlg::OnBnClickedButtonMemory)
	ON_BN_CLICKED(IDC_BUTTON_EVENT, &CSample2Layer_MFCDlg::OnBnClickedButtonEvent)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_EVENT2, &CSample2Layer_MFCDlg::OnBnClickedButtonEvent2)
END_MESSAGE_MAP()


// CSample2Layer_MFCDlg message handlers

BOOL CSample2Layer_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	strText.Format(_T("%d"), 10 );
	GetDlgItem(IDC_EDIT_X)->SetWindowText(strText);

	strText.Format(_T("%d"), 20 );
	GetDlgItem(IDC_EDIT_Y)->SetWindowText(strText);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSample2Layer_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSample2Layer_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSample2Layer_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSample2Layer_MFCDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	
	
	
	oBhandle = RtOpenEvent( NULL, 0, EVN_NAME );
	if ( oBhandle != NULL ) { MessageBox("RtxLayer.rtss program is running already! "); step = 1; RtCloseHandle(oBhandle); return; }
	
	ret = NEC_LoadRtxApp("C:\\Program Files\\NEXCOM\\NexECMRtx\\Samples\\RTX2012\\Sample_2Layer\\VS2010\\Sample2Layer_MFC\\RTSSDebug\\RtxLayer.rtss");
	if ( ret != NULL ) { MessageBox("NEC_LoadRtxApp failed " ); return; }

	step = 1;
}

U32_T CheckMemory = 0;

void CSample2Layer_MFCDlg::OnBnClickedButtonMemory()
{
	// TODO: Add your control notification handler code here
	
	if (step == 0) { MessageBox("Please click 'Start .rtss' first!!"); return; }

	sMhandle = RtOpenSharedMemory( SHM_MAP_ALL_ACCESS , 0 , SHM_NAME , &location );
	if( sMhandle == NULL ) { MessageBox("RtOpenSharedMemory failed " ); return; }

	pData = (WIN32_DAT *) location;

	strText.Format(_T("%d"), pData->master );
	GetDlgItem(IDC_EDIT_VALUE)->SetWindowText(strText);
	CheckMemory = 1;
}


void CSample2Layer_MFCDlg::OnBnClickedButtonEvent()
{
	// TODO: Add your control notification handler code here
	CString NumX, NumY, NumAns;
	
	if (step == 0) { MessageBox("Please click 'Start .rtss' first!!"); return;}
	if (CheckMemory == 0) { MessageBox("Please click 'OpenSharedMemory' first!!"); return;}

	pData = (WIN32_DAT *) location;

	GetDlgItemText( IDC_EDIT_X, NumX );
	GetDlgItemText( IDC_EDIT_Y, NumY );
	GetDlgItemText( IDC_EDIT_ANS, NumAns);

	pData->x = strtol( NumX, 0, 10 );
	pData->y = strtol( NumY, 0, 10 );
	pData->ans = strtol( NumAns, 0, 10 );
	
	oBhandle = RtOpenEvent( NULL, 0, EVN_NAME );
	if( oBhandle == NULL ) { MessageBox("RtOpenEvent failed " ); return; }
	RtSetEvent(oBhandle);

	Sleep(100);

	strText.Format(_T("%d"), pData->ans );
	GetDlgItem(IDC_EDIT_ANS)->SetWindowText(strText);

	RtCloseHandle(oBhandle);
}


void CSample2Layer_MFCDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	RtCloseHandle(oBhandle);
	RtCloseHandle(sMhandle);
	CDialogEx::OnClose();
}



void CSample2Layer_MFCDlg::OnBnClickedButtonEvent2()
{
	// TODO: Add your control notification handler code here
	CString NumX, NumY, NumAns;
	CString strText;
	
	if (step == 0) { AfxMessageBox("Please click 'Start .rtss' first!!"); return; }
	if (CheckMemory == 0) { MessageBox("Please click 'OpenSharedMemory' first!!"); return;}

	pData = (WIN32_DAT *) location;

	GetDlgItemText( IDC_EDIT_X, NumX );
	GetDlgItemText( IDC_EDIT_Y, NumY );
	GetDlgItemText( IDC_EDIT_ANS, NumAns);

	pData->x = strtol( NumX, 0, 10 );
	pData->y = strtol( NumY, 0, 10 );
	pData->ans = strtol( NumAns, 0, 10 );
	
	oBhandle2 = RtOpenEvent( NULL, 0, EVN_NAME2 );
	if( oBhandle2 == NULL ) { MessageBox("RtOpenEvent failed " ); return; }
	RtSetEvent(oBhandle2);

	Sleep(100);

	strText.Format(_T("%d"), pData->ans );
	GetDlgItem(IDC_EDIT_ANS)->SetWindowText(strText);

	RtCloseHandle(oBhandle2);

}
