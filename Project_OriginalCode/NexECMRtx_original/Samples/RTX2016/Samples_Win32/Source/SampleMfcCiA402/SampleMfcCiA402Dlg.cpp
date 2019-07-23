
// SampleMfcCiA402Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SampleMfcCiA402.h"
#include "SampleMfcCiA402Dlg.h"
#include "afxdialogex.h"
#include "Nexecm.h"
#include "NexCoeMotion.h"

#define TOTAL_AXES  (1)

//Bit define in status world
#define AXIS_TARGET_REACH_BIT              0x000A

//====================================================================
//Axis Parameter
//Soft limit group
#define INDEX_SOFT_LIMIT_ENABLE            0x2041 //SubIndex:0
#define LENOFBYTE_SOFT_LIMIT_ENABLE        0x0002
//========================================
//Home Parameter group
//Home method parameter
//#define INDEX_HOME_METHOD                  0x6098 //SubIndex:0                                   ###define in NexCoeMotion.h
#define LENOFBYTE_HOME_METHOD              0x0002
#define HOME_METHOD_NEGATIVE_LIMIT         0x0001 //Start negative move to find negitive limit switch first. And trnn back when negative limit switch is "On", then stop in first index singal.
#define HOME_METHOD_POSITIVE_LIMIT         0x0002 //Start positive move to find positive limit switch first. And turn back when positive limit switch is "On", then stop in first index signal.

//Fllowoings are reserved.
#define HOME_METHOD_HOME_SENSOR_POSITIVE_R 0x0003 //Start positive move to find home sensor first. And turn back when home sensor is "On", then stop in first index signal.
#define HOME_METHOD_HOME_SENSOR_POSITIVE_C 0x0004 //Start positive move to find home sensor first. And stop in first index signal after home sensor is "On"
#define HOME_METHOD_HOME_SENSOR_NEGATIVE_R 0x0005 //Start negative move to find home sensor first. And turn back when home sensor is "On", then stop in first index signal.
#define HOME_METHOD_HOME_SENSOR_NEGATIVE_C 0x0006 //Start negative move to find home sensor first. And stop in first index signal after home sensor is "On"
#define HOME_METHOD_INDEX_SIGNAL_POSITIVE  0x0021 //Start positive move and stop at first index signal.
#define HOME_METHOD_INDEX_SIGNAL_NEGATIVE  0x0022 //Start negative move and stop at first index signal.
#define HOME_METHOD_CUR_POS_IS_HOME_POINT  0x0023 //Current position is home.

//Home speed parameter
//#define INDEX_HOME_SPEED                   0x6099 //High speed SubIndex:0 / Low speed SubIndex:1 ###define in NexCoeMotion.h
//#define INDEX_HOME_SPEED_ACC               0x609a //SubIndex:0                                   ###define in NexCoeMotion.h
#define LENOFBYTE_HOME_SPEED               0x0004

//========================================
//Define AxisId and DioId mapping to slave addr 
#define AXIS_ID_X                          0x0000
#define AXIS_ID_Y                          0x0001
#define AXIS_ID_Z                          0x0002
#define DIO_ID                             0x0003

I32_T   timeOut = 1000;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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


// CSampleMfcCiA402Dlg dialog




CSampleMfcCiA402Dlg::CSampleMfcCiA402Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSampleMfcCiA402Dlg::IDD, pParent)
	, mCheck(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->m_pThread = 0;
}

void CSampleMfcCiA402Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DIO, mCheck);
}

BEGIN_MESSAGE_MAP(CSampleMfcCiA402Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Start, &CSampleMfcCiA402Dlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_Servo_On_X, &CSampleMfcCiA402Dlg::OnBnClickedButtonServoOnX)
	ON_BN_CLICKED(IDC_BUTTON_Stop_X, &CSampleMfcCiA402Dlg::OnBnClickedButtonStopX)
	ON_BN_CLICKED(IDC_BUTTON_Servo_On_Y, &CSampleMfcCiA402Dlg::OnBnClickedButtonServoOnY)
	ON_BN_CLICKED(IDC_BUTTON_Servo_On_Z, &CSampleMfcCiA402Dlg::OnBnClickedButtonServoOnZ)
	ON_BN_CLICKED(IDC_BUTTON_Set_X, &CSampleMfcCiA402Dlg::OnBnClickedButtonSetX)
	ON_BN_CLICKED(IDC_BUTTON_Move_X, &CSampleMfcCiA402Dlg::OnBnClickedButtonMoveX)
	ON_BN_CLICKED(IDC_BUTTON_Home_X, &CSampleMfcCiA402Dlg::OnBnClickedButtonHomeX)
	ON_BN_CLICKED(IDC_BUTTON_Set_Y, &CSampleMfcCiA402Dlg::OnBnClickedButtonSetY)
	ON_BN_CLICKED(IDC_BUTTON_Move_Y, &CSampleMfcCiA402Dlg::OnBnClickedButtonMoveY)
	ON_BN_CLICKED(IDC_BUTTON_Home_Y, &CSampleMfcCiA402Dlg::OnBnClickedButtonHomeY)
	ON_BN_CLICKED(IDC_BUTTON_Stop_Y, &CSampleMfcCiA402Dlg::OnBnClickedButtonStopY)
	ON_BN_CLICKED(IDC_BUTTON_Set_Z, &CSampleMfcCiA402Dlg::OnBnClickedButtonSetZ)
	ON_BN_CLICKED(IDC_BUTTON_Move_Z, &CSampleMfcCiA402Dlg::OnBnClickedButtonMoveZ)
	ON_BN_CLICKED(IDC_BUTTON_Home_Z, &CSampleMfcCiA402Dlg::OnBnClickedButtonHomeZ)
	ON_BN_CLICKED(IDC_BUTTON_Stop_Z, &CSampleMfcCiA402Dlg::OnBnClickedButtonStopZ)
	ON_BN_CLICKED(IDC_BUTTON_Auto, &CSampleMfcCiA402Dlg::OnBnClickedButtonAuto)
	ON_BN_CLICKED(IDC_BUTTON_Close, &CSampleMfcCiA402Dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_CHECK_DIO, &CSampleMfcCiA402Dlg::OnBnClickedCheckDio)
END_MESSAGE_MAP()


// CSampleMfcCiA402Dlg message handlers

BOOL CSampleMfcCiA402Dlg::OnInitDialog()
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
	SetDlgItemText( IDC_EDIT_Servo_On_X, "0" ); //Actual position
	SetDlgItemText( IDC_EDIT_Soft_X1, "800000" );//P soft limit
	SetDlgItemText( IDC_EDIT_Soft_X2, "-800000" );//N soft limit
	SetDlgItemText( IDC_EDIT_Move_X, "0" ); //Target position
	SetDlgItemText( IDC_EDIT_Home_X, "0" ); //Axis status

	SetDlgItemText( IDC_EDIT_Servo_On_Y, "0" ); //Actual position
	SetDlgItemText( IDC_EDIT_Soft_Y1, "1200000" );//P soft limit
	SetDlgItemText( IDC_EDIT_Soft_Y2, "-1200000" );//N soft limit
	SetDlgItemText( IDC_EDIT_Move_Y, "0" ); //Target position
	SetDlgItemText( IDC_EDIT_Home_Y, "0" ); //Axis status


	SetDlgItemText( IDC_EDIT_Servo_On_Z, "0" ); //Actual position
	SetDlgItemText( IDC_EDIT_Soft_Z1, "4000000" );//P soft limit
	SetDlgItemText( IDC_EDIT_Soft_Z2, "-4000000" );//N soft limit
	SetDlgItemText( IDC_EDIT_Move_Z, "0" ); //Target position
	SetDlgItemText( IDC_EDIT_Home_Z, "0" ); //Axis status

	CComboBox *comb = (CComboBox *)GetDlgItem( IDC_COMBO1 );
	comb->ResetContent();
	comb->AddString("Mode1" );
	comb->AddString("Mode2" );
	comb->AddString("Mode3" );
	comb->AddString("Mode4" );
	comb->AddString("Mode5" );
	comb->AddString("Mode6" );
	comb->AddString("Mode33" );
	comb->AddString("Mode34" );
	comb->AddString("Mode35" );
	comb->SetCurSel( 0 );

	comb = (CComboBox *)GetDlgItem( IDC_COMBO2 );
	comb->ResetContent();
	comb->AddString("Mode1" );
	comb->AddString("Mode2" );
	comb->AddString("Mode3" );
	comb->AddString("Mode4" );
	comb->AddString("Mode5" );
	comb->AddString("Mode6" );
	comb->AddString("Mode33" );
	comb->AddString("Mode34" );
	comb->AddString("Mode35" );
	comb->SetCurSel( 0 );

	comb = (CComboBox *)GetDlgItem( IDC_COMBO3 );
	comb->ResetContent();
	comb->AddString("Mode1" );
	comb->AddString("Mode2" );
	comb->AddString("Mode3" );
	comb->AddString("Mode4" );
	comb->AddString("Mode5" );
	comb->AddString("Mode6" );
	comb->AddString("Mode33" );
	comb->AddString("Mode34" );
	comb->AddString("Mode35" );
	comb->SetCurSel( 0 );

	this->misUpdate = 0;
	this->TimerHandle = SetTimer( NULL, 100, NULL );

	this->mDiData = 0;
	this->mDoData = 0;

	this->m_greencolor = RGB(0,255,0);
	this->m_whitecolor = RGB(255, 255, 255);
	
	this->m_greenbrush.CreateSolidBrush(this->m_greencolor);
	this->m_whitebrush.CreateSolidBrush(this->m_whitecolor);

	this->mDoData = 1;

	//====================================================================================
	//Make poins for auto run process.
	this->mTargetPosArray_X[0] = 0;
	for( int i = 1; i < sizeof(this->mTargetPosArray_X)/sizeof(this->mTargetPosArray_X[0]); ++i )
	{
		this->mTargetPosArray_X[i] = -700000 + ( ( i - 1 )  /2 ) * 200000;
	}

	this->mTargetPosArray_Y[0] = 0;
	this->mTargetPosArray_Y[1] = -1000000;
	for( int i = 2, j = 0; i < sizeof(this->mTargetPosArray_Y)/sizeof(this->mTargetPosArray_Y[0]); ++i )
	{
		if( --j < 0 )
		{
			this->mTargetPosArray_Y[i] = (~this->mTargetPosArray_Y[i-1]) + 1;
			j = 1;
		}
		else
		{
			this->mTargetPosArray_Y[i] = this->mTargetPosArray_Y[i-1];
		}

	}

	this->mTargetPosArray_Z[0] = 0;
	this->mTargetPosArray_Z[1] = 20000;
	for( int i = 2; i < sizeof(this->mTargetPosArray_Z)/sizeof(this->mTargetPosArray_Z[0]); ++i )
	{
		this->mTargetPosArray_Z[i] = (~this->mTargetPosArray_Z[i-1]) + 1;
	}
	//====================================================================================
	// Create Thread to execute auto run process.
	this->mAutoRunMoveIndex = 0;
	this->mStartAutoMoveFlag = 0;

	this->mThreadStop = 0;

	this->m_pThread = AfxBeginThread( ThreadFunc, this, THREAD_PRIORITY_HIGHEST, 0, 0, NULL );

	if(!m_pThread) EndDialog(IDCANCEL);

	//====================================================================================
	// Load NEXCOM EtherCAT master.
	RTN_ERR ret;
	ret = NEC_LoadRtxApp( "C:\\Program Files\\NEXCOM\\NexECMRtx\\Lib\\NexECMRtx\\x32\\NexECMRtx.rtss" );
	if( ret != 0 ) { MessageBox("NEC_LoadRtxApp failed!"); }

	Sleep(2000);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSampleMfcCiA402Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSampleMfcCiA402Dlg::OnPaint()
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
HCURSOR CSampleMfcCiA402Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

U32_T CheckStartMaster = 0;

void CSampleMfcCiA402Dlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	
	I32_T   i = 0;
	
	if ( CheckStartMaster == 0 )
	{
		ret = NEC_StartDriver();
		if( ret != 0 ) { MessageBox("NEC_StarDriver failed!"); }

		ret = NEC_GetRtMasterId( &this->masterId );
		if( ret != 0 ) { MessageBox( "NEC_GetRtMasterId failed!" ); }
	
		ret = NEC_ResetEcMaster( this->masterId );
		if( ret != 0 ) { MessageBox( "NEC_ResetEcMaster failed!" ); }
	
		ret = NEC_SetParameter( this->masterId, NEC_PARA_S_ECM_CYCLETIMEUS, timeOut );
		if( ret != 0 ) { MessageBox( "NEC_SetParameter failed!" ); StopDriver(); return; }

		ret = NEC_CoE402Reset();
		if( ret != 0 ) { MessageBox( "NEC_CoE402Reset failed!" ); StopDriver(); return; }
	
		ret = NEC_StartNetworkEx( this->masterId, "C:\\ENI_NexCAT_Export.xml", START_NETWORK_OPT_MASK_NIC_PORT, timeOut );
		if( ret != 0 ) { MessageBox( "NEC_StartNetworkEx failed!" ); StopDriver(); return; }

		ret = NEC_GetSlaveCount( this->masterId, &this->Count);
		if( ret != 0 ) { MessageBox("NEC_GetSlaveCount failed!" ); StopDriver(); return; }

		if (this->Count != TOTAL_AXES+1)
		{
			CWnd* Pfield;
			Pfield = GetDlgItem( IDC_CHECK_DIO );
			Pfield->EnableWindow( FALSE ); 

			MessageBox("Please check DIO slave is connected at least slave. " ); 
			((CButton*)GetDlgItem(IDC_CHECK_DIO))->SetCheck(FALSE);
		}
		
		if ( (this->Count != TOTAL_AXES) )
		{
			if (this->Count != (TOTAL_AXES+1))
			{
				MessageBox("Please check slave count and 'TOTAL_AXES' define in 'SampleMfcCiA402Dlg.cpp' " ); 
				StopDriver(); 
				return;
			}
		}
	
		for( i = 0; i < TOTAL_AXES; ++i )
		{
			ret = NEC_CoE402GetAxisId( this->masterId, i, &this->mAxis[i]);
			if( ret != 0 ) { MessageBox( "NEC_CoE402GetAxisId failed!" ); StopDriver(); return; }

		}
	
		for( i = 0; i < TOTAL_AXES; ++i )
		{
			ret = NEC_CoE402UpdatePdoMapping( this->mAxis[i] );
			if( ret != 0 ) { MessageBox( "NEC_CoE402UpdatePdoMapping failed!" ); StopDriver(); return; }
		}

		for( i = 0; i < TOTAL_AXES; ++i )
		{
			ret = NEC_CoE402FaultReset( this->mAxis[i], timeOut );
			if( ret != 0 ) { MessageBox("NEC_CoE402FaultReset failed!" ); StopDriver(); return; }
		}
		//Start to read axis information.
		this->misUpdate = 1;
		CheckStartMaster = 1;
		GetDlgItem(IDC_BUTTON_Start)->SetWindowTextA("Stop Master");
	}
	else
	{
		CheckStartMaster = 0;
		this->misUpdate = 0;
	
		for( i = 0; i < TOTAL_AXES; ++i )
		{
			NEC_CoE402SetCtrlWord( this->mAxis[i], 0 );
		}

		NEC_StopNetwork( this->masterId, timeOut );	
		NEC_ResetEcMaster( this->masterId );

		NEC_StopDriver();
		GetDlgItem(IDC_BUTTON_Start)->SetWindowTextA("Start Master");

	}


	
}


void CSampleMfcCiA402Dlg::StopDriver()
{

	this->misUpdate = 0;
	
	Sleep(500);
	
	NEC_StopNetwork( this->masterId, timeOut ); 
	NEC_StopDriver();
}









void CSampleMfcCiA402Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	RTN_ERR ret;
	I32_T   pos; 
	U16_T   state;
	CString strText;
	
	if( this->misUpdate )
	{
		if(BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_DIO))->GetCheck())
		{
			DioCheck(); //A dio demo process.
		}

		
		ret = NEC_CoE402GetActualPosition( this->mAxis[AXIS_ID_X], &pos ); 
		if( ret ==  0 )
		{
			strText.Format(_T("%d"), pos);
			GetDlgItem(IDC_EDIT_Servo_On_X)->SetWindowText(strText);
		}

		ret = NEC_CoE402GetState( this->mAxis[AXIS_ID_X], &state );
		if( ret == 0 )
		{
			strText.Format(_T("%d"), state);
			GetDlgItem(IDC_EDIT1)->SetWindowText(strText);
		}
		
		if( TOTAL_AXES < 2 ) return;
		ret = NEC_CoE402GetActualPosition( this->mAxis[AXIS_ID_Y], &pos ); 
		if( ret ==  0 )
		{
			strText.Format(_T("%d"), pos);
			GetDlgItem(IDC_EDIT_Servo_On_Y)->SetWindowText(strText);
		}

		ret = NEC_CoE402GetState( this->mAxis[AXIS_ID_Y], &state );
		if( ret == 0 )
		{
			strText.Format(_T("%d"), state);
			GetDlgItem(IDC_EDIT7)->SetWindowText(strText);
		}

		if( TOTAL_AXES < 3 ) return;
		ret = NEC_CoE402GetActualPosition( this->mAxis[AXIS_ID_Z], &pos ); 
		if( ret ==  0 )
		{
			strText.Format(_T("%d"), pos);
			GetDlgItem(IDC_EDIT_Servo_On_Z)->SetWindowText(strText);
		}

		ret = NEC_CoE402GetState( this->mAxis[AXIS_ID_Z], &state );
		if( ret == 0 )
		{
			strText.Format(_T("%d"), state);
			GetDlgItem(IDC_EDIT13)->SetWindowText(strText);
		}	
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonServoOnX()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	U16_T   state;

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}

	ret = NEC_CoE402GetState( this->mAxis[AXIS_ID_X], &state );
	if( ret != 0 ) { MessageBox( "NEC_CoE402GetState failed!" ); return; }

	if( state != COE_STA_OPERATION_ENABLE )
	{
		ret = NEC_CoE402SetOperationMode( this->mAxis[AXIS_ID_X], CiA402_OP_MODE_PROFILE_POSITION, timeOut );
		if( ret != 0 ) { MessageBox( "NEC_CoE402SetOperationMode failed!" ); return; }

		ret = NEC_CoE402ServoOn( this->mAxis[AXIS_ID_X], 1 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return; }
		GetDlgItem( IDC_BUTTON_Servo_On_X )->SetWindowTextA("Servo Off");
	}
	else
	{
		ret = NEC_CoE402ServoOn( this->mAxis[AXIS_ID_X], 0 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return; }
		GetDlgItem( IDC_BUTTON_Servo_On_X )->SetWindowTextA("Servo On");
	}
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonStopX()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	
	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}

	ret = NEC_CoE402Halt( this->mAxis[AXIS_ID_X], 1 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Halt failed!" ); }
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonServoOnY()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	U16_T   state;

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	ret = NEC_CoE402GetState( this->mAxis[AXIS_ID_Y], &state );
	if( ret != 0 ) { MessageBox( "NEC_CoE402GetState failed!" ); return; }

	if( state != COE_STA_OPERATION_ENABLE )
	{
		ret = NEC_CoE402SetOperationMode( this->mAxis[AXIS_ID_Y], CiA402_OP_MODE_PROFILE_POSITION, timeOut );
		if( ret != 0 ) { MessageBox( "NEC_CoE402SetOperationMode failed!" ); return; }

		ret = NEC_CoE402ServoOn( this->mAxis[AXIS_ID_Y], 1 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return; }
		GetDlgItem( IDC_BUTTON_Servo_On_Y )->SetWindowTextA("Servo Off");
	}
	else
	{
		ret = NEC_CoE402ServoOn( this->mAxis[AXIS_ID_Y], 0 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return; }
		GetDlgItem( IDC_BUTTON_Servo_On_Y )->SetWindowTextA("Servo On");

	}


}


void CSampleMfcCiA402Dlg::OnBnClickedButtonServoOnZ()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	U16_T   state;

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	ret = NEC_CoE402GetState( this->mAxis[AXIS_ID_Z], &state );
	if( ret != 0 ) { MessageBox( "NEC_CoE402GetState failed!" ); return; }

	if( state != COE_STA_OPERATION_ENABLE )
	{
		ret = NEC_CoE402SetOperationMode( this->mAxis[AXIS_ID_Z], CiA402_OP_MODE_PROFILE_POSITION, timeOut );
		if( ret != 0 ) { MessageBox( "NEC_CoE402SetOperationMode failed!" ); return; }

		ret = NEC_CoE402ServoOn( this->mAxis[AXIS_ID_Z], 1 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return; }
		GetDlgItem( IDC_BUTTON_Servo_On_Z )->SetWindowTextA("Servo Off");
	}
	else
	{
		ret = NEC_CoE402ServoOn( this->mAxis[AXIS_ID_Z], 0 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return; }
		GetDlgItem( IDC_BUTTON_Servo_On_Z )->SetWindowTextA("Servo On");

	}

}


void CSampleMfcCiA402Dlg::OnBnClickedButtonSetX()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;

	I32_T limitp, limitn;
	
	CString strp, strn;
	GetDlgItemText( IDC_EDIT_Soft_X1, strp );
	GetDlgItemText( IDC_EDIT_Soft_X2, strn );

	limitp = strtol( strp, 0 , 10 );
	limitn = strtol( strn, 0 , 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	ret = NEC_CoE402SetSoftPosLimit( this->mAxis[AXIS_ID_X], limitn, limitp );
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetSoftPosLimit failed!" ); }

	//ret = NEC_CoE402SetParameter( this->mAxis[AXIS_ID_X], INDEX_SOFT_LIMIT_ENABLE, 0, LENOFBYTE_SOFT_LIMIT_ENABLE, 1 ); 
	//if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!" ); }


}


void CSampleMfcCiA402Dlg::OnBnClickedButtonMoveX()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	U32_T   maxVel = 0;
	I32_T   tarPos = 0;
	CString str;

	GetDlgItemText( IDC_EDIT_Move_X, str );
	tarPos = strtol( str, 0, 10 );

	GetDlgItemText( IDC_EDIT_Home_X, str );
	maxVel = strtol( str, 0, 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	ret = NEC_CoE402Halt( this->mAxis[AXIS_ID_X], 0 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Halt failed!" ); }

	ret = NEC_CoE402PtpA( this->mAxis[AXIS_ID_X], OPT_ABS, tarPos, maxVel, maxVel*10, maxVel*10 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402PtpA failed!" ); }
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonHomeX()
{
	// TODO: Add your control notification handler code here
	U16_T   homeType; 
	U32_T   homeSped;
	CString str;

	CComboBox *comb = (CComboBox *)GetDlgItem( IDC_COMBO1 );
	
	homeType = comb->GetCurSel();
	homeType = this->mGetHomeTypeRealNum(homeType);
	
	GetDlgItemText( IDC_EDIT_Home_X, str );
	homeSped = strtol( str, 0, 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


 	this->mHomeMove(this->mAxis[AXIS_ID_X], homeType, homeSped );


}


U16_T CSampleMfcCiA402Dlg::mGetHomeTypeRealNum(U16_T ComboIndex )
{
	switch( ComboIndex )
	{
	case 0:
		return HOME_METHOD_NEGATIVE_LIMIT;
		break;

	case 1:
		return HOME_METHOD_POSITIVE_LIMIT; 
		break;

	case 2:
		return HOME_METHOD_HOME_SENSOR_POSITIVE_R; 
		break;

	case 3:
		return HOME_METHOD_HOME_SENSOR_POSITIVE_C; 
		break;

	case 4:
		return HOME_METHOD_HOME_SENSOR_NEGATIVE_R; 
		break;

	case 5:
		return HOME_METHOD_HOME_SENSOR_NEGATIVE_C; 
		break;

	case 6:
		return HOME_METHOD_INDEX_SIGNAL_POSITIVE; 
		break;
	
	case 7:
		return HOME_METHOD_INDEX_SIGNAL_NEGATIVE; 
		break;

	case 8:
		return HOME_METHOD_CUR_POS_IS_HOME_POINT; 
		break;

	}
	return 0;
}

RTN_ERR CSampleMfcCiA402Dlg::mHomeMove( CANAxis_T Axis, U16_T Method, U32_T Speed )
{
	RTN_ERR ret = 0;

	ret = NEC_CoE402SetParameter( Axis, INDEX_HOME_METHOD, 0, 1, Method ); //YAS. SINT=1byte ; HIWIN=2byte ;
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!, INDEX_HOME_METHOD" ); return ret; }

	ret = NEC_CoE402SetParameter( Axis, INDEX_HOME_SPEED, 1, LENOFBYTE_HOME_SPEED, Speed * 10 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!, INDEX_HOME_SPEED" ); return ret; }

	ret = NEC_CoE402SetParameter( Axis, INDEX_HOME_ZERO_SPEED, 2, LENOFBYTE_HOME_SPEED, Speed ); 
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!, INDEX_HOME_ZERO_SPEED" ); return ret; }

	//ret = NEC_CoE402SetParameter( Axis, INDEX_HOME_ACC, 0, LENOFBYTE_HOME_SPEED, Speed*10 ); 
	//if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!, INDEX_HOME_ACC" ); return ret; }

	//ret = NEC_CoE402SetParameter( Axis, INDEX_SOFT_LIMIT_ENABLE, 0, LENOFBYTE_SOFT_LIMIT_ENABLE, 0 ); 
	//if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!, INDEX_SOFT_LIMIT_ENABLE" ); return ret; }

	ret = NEC_CoE402Halt( Axis, 0 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Halt failed!" ); return ret; }

	ret += NEC_CoE402FaultReset( Axis, timeOut ); 
	if( ret != 0 ) { MessageBox( "NEC_CoE402FaultReset failed!" ); return ret; }
	
	ret = NEC_CoE402Home( Axis, 0 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Home failed!" ); return ret; }

	return ret;
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonSetY()
{
	// TODO: Add your control notification handler code here

	RTN_ERR ret;

	I32_T limitp, limitn;
	
	CString strp, strn;
	GetDlgItemText( IDC_EDIT_Soft_Y1, strp );
	GetDlgItemText( IDC_EDIT_Soft_Y2, strn );

	limitp = strtol( strp, 0 , 10 );
	limitn = strtol( strn, 0 , 10 );

	ret = NEC_CoE402SetSoftPosLimit( this->mAxis[AXIS_ID_Y], limitn, limitp );
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetSoftPosLimit failed!" ); }

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	//ret = NEC_CoE402SetParameter( this->mAxis[AXIS_ID_Y], INDEX_SOFT_LIMIT_ENABLE, 0, LENOFBYTE_SOFT_LIMIT_ENABLE, 1 ); 
	//if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!" ); }

}


void CSampleMfcCiA402Dlg::OnBnClickedButtonMoveY()
{
	// TODO: Add your control notification handler code here
	
	RTN_ERR ret;
	U32_T   maxVel = 0;
	I32_T   tarPos = 0;
	CString str;

	GetDlgItemText( IDC_EDIT_Move_Y, str );
	tarPos = strtol( str, 0, 10 );

	GetDlgItemText( IDC_EDIT_Home_Y, str );
	maxVel = strtol( str, 0, 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	ret = NEC_CoE402Halt( this->mAxis[AXIS_ID_Y], 0 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Halt failed!" ); }

	ret = NEC_CoE402PtpA( this->mAxis[AXIS_ID_Y], OPT_ABS, tarPos, maxVel, maxVel*10, maxVel*10 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402PtpA failed!" ); }
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonHomeY()
{
	// TODO: Add your control notification handler code here
	U16_T   homeType; 
	U32_T   homeSped;
	CString str;

	CComboBox *comb = (CComboBox *)GetDlgItem( IDC_COMBO2 );
	
	homeType = comb->GetCurSel();
	homeType = this->mGetHomeTypeRealNum(homeType);
	
	GetDlgItemText( IDC_EDIT_Home_Y, str );
	homeSped = strtol( str, 0, 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}

	this->mHomeMove(this->mAxis[AXIS_ID_Y], homeType, homeSped );

}


void CSampleMfcCiA402Dlg::OnBnClickedButtonStopY()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}

	
	ret = NEC_CoE402Halt( this->mAxis[AXIS_ID_Y], 1 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Halt failed!" ); }
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonSetZ()
{
	// TODO: Add your control notification handler code here

	RTN_ERR ret;

	I32_T limitp, limitn;
	
	CString strp, strn;
	GetDlgItemText( IDC_EDIT_Soft_Z1, strp );
	GetDlgItemText( IDC_EDIT_Soft_Z2, strn );

	limitp = strtol( strp, 0 , 10 );
	limitn = strtol( strn, 0 , 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	ret = NEC_CoE402SetSoftPosLimit( this->mAxis[AXIS_ID_Z], limitn, limitp );
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetSoftPosLimit failed!" ); }

	//ret = NEC_CoE402SetParameter( this->mAxis[AXIS_ID_Z], INDEX_SOFT_LIMIT_ENABLE, 0, LENOFBYTE_SOFT_LIMIT_ENABLE, 1 ); 
	//if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!" ); }

}


void CSampleMfcCiA402Dlg::OnBnClickedButtonMoveZ()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	U32_T   maxVel = 0;
	I32_T   tarPos = 0;
	CString str;

	GetDlgItemText( IDC_EDIT_Move_Z, str );
	tarPos = strtol( str, 0, 10 );

	GetDlgItemText( IDC_EDIT_Home_Z, str );
	maxVel = strtol( str, 0, 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}


	ret = NEC_CoE402Halt( this->mAxis[AXIS_ID_Z], 0 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Halt failed!" ); }

	ret = NEC_CoE402PtpA( this->mAxis[AXIS_ID_Z], OPT_ABS, tarPos, maxVel, maxVel*10, maxVel*10 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402PtpA failed!" ); }
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonHomeZ()
{
	// TODO: Add your control notification handler code here
	U16_T   homeType; 
	U32_T   homeSped;
	CString str;

	CComboBox *comb = (CComboBox *)GetDlgItem( IDC_COMBO3 );
	
	homeType = comb->GetCurSel();
	homeType = this->mGetHomeTypeRealNum(homeType);
	
	GetDlgItemText( IDC_EDIT_Home_Z, str );
	homeSped = strtol( str, 0, 10 );

	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}

	this->mHomeMove(this->mAxis[AXIS_ID_Z], homeType, homeSped );

}


void CSampleMfcCiA402Dlg::OnBnClickedButtonStopZ()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret;
	
	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}

	ret = NEC_CoE402Halt( this->mAxis[AXIS_ID_X], 1 );
	if( ret != 0 ) { MessageBox( "NEC_CoE402Halt failed!" ); }
}


void CSampleMfcCiA402Dlg::OnBnClickedButtonAuto()
{
	// TODO: Add your control notification handler code here
	RTN_ERR ret = 0;
	U16_T   stateX = 0;
	U16_T   stateY = 0;
	U16_T   stateZ = 0;
	I32_T   i = 0;
	if (this->misUpdate != 1){ MessageBox("Please click 'Start Master' first. " ); return;}

	//Clear all status of Axis, include servo on, halt...
	for( i = 0; i < TOTAL_AXES; ++i )
	{
		ret = NEC_CoE402SetCtrlWord( this->mAxis[i], 0 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402SetCtrlWord failed!, Axis:X" ); return; }
	
	}
	
	GetDlgItem( IDC_BUTTON_Servo_On_X  )->SetWindowTextA("Servo On");
	GetDlgItem( IDC_BUTTON_Servo_On_Y )->SetWindowTextA("Servo On");
	GetDlgItem( IDC_BUTTON_Servo_On_Z )->SetWindowTextA("Servo On");

	if( ret != 0 ) { MessageBox( "NEC_CoE402SetCtrlWord failed!" ); }

	if( ret == 0 )
	{
		if( this->mStartAutoMoveFlag == 0 )
		{
			GetDlgItem( IDC_BUTTON_Auto )->SetWindowTextA("Auto Run Stop");
			this->mStartAutoMove();
			this->mAutoRunMoveIndex = 0;
			this->mStartAutoMoveFlag = 1;
		}
		else
		{
			GetDlgItem( IDC_BUTTON_Auto )->SetWindowTextA("Auto Run Start");
			this->mStartAutoMoveFlag = 0;
			this->mStopAutoMove();
		}
	}	
}

RTN_ERR CSampleMfcCiA402Dlg::mStopAutoMove()
{
	this->mStopMove();
	this->mServoOff();

	GetDlgItem( IDC_BUTTON_Auto )->SetWindowTextA("Auto Run Start");

	return 0;
}

RTN_ERR CSampleMfcCiA402Dlg::mStartMove(I32_T TarPosX, I32_T TarPosY, I32_T TarPosZ )
{
	RTN_ERR ret = 0;
	I32_T   tarPos = 0;
	CString str;
	U32_T   maxSpd = 10000;
	U32_T   acc    = 1000;
	U32_T   dec    = 1000;

	ret = NEC_CoE402PtpA( this->mAxis[AXIS_ID_X], OPT_ABS, TarPosX, maxSpd, acc, dec );
	if( ret != 0 ) 
	{ 
		str.Format(_T("%d"), ret );
		MessageBox( "Start PtpA X failed, Error Code:" + str ); this->mStartAutoMoveFlag = 0;this->mStopAutoMove(); return ret; 
	}

	if( TOTAL_AXES < 2 ) return 0;
	ret = NEC_CoE402PtpA( this->mAxis[AXIS_ID_Y], OPT_ABS, TarPosY,  maxSpd, acc, dec * 10 );
	if( ret != 0 )
	{ 
		str.Format(_T("%d"), ret );
		MessageBox( "Start PtpA Y failed, Error Code:" + str ); this->mStartAutoMoveFlag = 0;this->mStopAutoMove(); return ret; 
	}

	if( TOTAL_AXES < 3 ) return 0;
	ret = NEC_CoE402PtpA( this->mAxis[AXIS_ID_Z], OPT_ABS, TarPosZ,  maxSpd, acc, dec );
	if( ret != 0 )
	{ 
		str.Format(_T("%d"), ret );
		MessageBox( "Start PtpA Z failed, Error Code:" + str ); this->mStartAutoMoveFlag = 0;this->mStopAutoMove(); return ret; 
	}

	return ret;
}

RTN_ERR CSampleMfcCiA402Dlg::mStartAutoMove()
{
	RTN_ERR ret = 0;
	I32_T   tarPos = 0;
	U8_T    moveIndex = 0;
	CString str;

	ret += this->mSoftLimitSet();
	ret += this->mServoOn();

	Sleep(500);

	ret += this->mStartMove(this->mTargetPosArray_X[mAutoRunMoveIndex], this->mTargetPosArray_Y[mAutoRunMoveIndex], this->mTargetPosArray_Z[mAutoRunMoveIndex]);

	return ret;
}

RTN_ERR CSampleMfcCiA402Dlg::mStopMove()
{
	RTN_ERR ret = 0;
	I32_T  i = 0;

	for( i = 0; i < TOTAL_AXES; ++i )
	{
		ret = NEC_CoE402Halt( this->mAxis[i], 1 );
		if( ret != 0 ) { MessageBox( "mStopMove failed!" ); }
	}

	return ret;
}

RTN_ERR CSampleMfcCiA402Dlg::mServoOff()
{
	RTN_ERR ret = 0;
	I32_T i = 0; 

	for( i = 0; i < TOTAL_AXES; ++i )
	{
		ret = NEC_CoE402ServoOn( this->mAxis[i], 0 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return ret;  }

	}

	return 0;
}

RTN_ERR CSampleMfcCiA402Dlg::mSoftLimitSet()
{
	RTN_ERR ret = 0;

	I32_T limitp, limitn;

	I32_T i = 0;
	
	CString strp, strn;

	//Enable softlimit ===========================================

	//for( i = 0; i < TOTAL_AXES; ++i )
	//{
	//	ret = NEC_CoE402SetParameter( this->mAxis[i], INDEX_SOFT_LIMIT_ENABLE, 0, LENOFBYTE_SOFT_LIMIT_ENABLE, 1 ); 
	//	if( ret != 0 ) { MessageBox( "NEC_CoE402SetParameter failed!" ); }
	//}

	//Set softlimit for axis X ===========================================
	GetDlgItemText( IDC_EDIT_Soft_X1, strp );
	GetDlgItemText( IDC_EDIT_Soft_X2, strn );
	
	limitp = strtol( strp, 0 , 10 );
	limitn = strtol( strn, 0 , 10 );

	ret = NEC_CoE402SetSoftPosLimit( this->mAxis[AXIS_ID_X], limitn, limitp );

	//Set softlimit for axis Y ===========================================
	if( TOTAL_AXES < 2 ) return 0;

	GetDlgItemText( IDC_EDIT_Soft_Y1, strp );
	GetDlgItemText( IDC_EDIT_Soft_Y2, strn );
	
	limitp = strtol( strp, 0 , 10 );
	limitn = strtol( strn, 0 , 10 );

	ret = NEC_CoE402SetSoftPosLimit( this->mAxis[AXIS_ID_Y], limitn, limitp );
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetSoftPosLimit failed!" ); }

	//Set softlimit for axis Z ===========================================
	if( TOTAL_AXES < 3 ) return 0;

	GetDlgItemText( IDC_EDIT_Soft_Z1, strp );
	GetDlgItemText( IDC_EDIT_Soft_Z2, strn );
	
	limitp = strtol( strp, 0 , 10 );
	limitn = strtol( strn, 0 , 10 );

	ret += NEC_CoE402SetSoftPosLimit( this->mAxis[AXIS_ID_Z], limitn, limitp );
	if( ret != 0 ) { MessageBox( "NEC_CoE402SetSoftPosLimit failed!" ); }

	return ret;
}


RTN_ERR CSampleMfcCiA402Dlg::mServoOn()
{
	RTN_ERR ret = 0;
	I32_T i = 0; 

	for( i = 0; i < TOTAL_AXES; ++i )
	{
		ret = NEC_CoE402ServoOn( this->mAxis[i], 1 );
		if( ret != 0 ) { MessageBox( "NEC_CoE402ServoOn failed!" ); return ret;  }

	}
	
	return 0;
}


void CSampleMfcCiA402Dlg::AutoRunCheck()
{
	RTN_ERR ret = 0;
	I32_T i = 0;
	I32_T tarPosX, tarPosY, tarPosZ;
	U16_T status[3];
	CString strText;

	if( !this->mStartAutoMoveFlag ) return;

	///*ret = NEC_CoE402WaitTargetReached( this->X );
	//if( ret != 0 ) { MessageBox( "NEC_CoE402WaitTargetReached failed!, Axis:X" ); this->mStartAutoMoveFlag = 0;this->mStopAutoMove(); }

	//ret = NEC_CoE402WaitTargetReached( this->Y );
	//if( ret != 0 ) { MessageBox( "NEC_CoE402WaitTargetReached failed!, Axis:Y" ); this->mStartAutoMoveFlag = 0;this->mStopAutoMove(); }

	//ret = NEC_CoE402WaitTargetReached( this->Z );
	//if( ret != 0 ) { MessageBox( "NEC_CoE402WaitTargetReached failed!, Axis:Z" ); this->mStartAutoMoveFlag = 0;this->mStopAutoMove(); }*/

	//this->mAutoRunMoveIndex++;
	//
	//if( mAutoRunMoveIndex >= 17 )
	//	this->mAutoRunMoveIndex = 0;

	//tarPosX = this->mTargetPosArray_X[this->mAutoRunMoveIndex];
	//tarPosY = this->mTargetPosArray_Y[this->mAutoRunMoveIndex];
	//tarPosZ = this->mTargetPosArray_Z[this->mAutoRunMoveIndex];

	//ret = this->mStartMove( tarPosX, tarPosY, tarPosZ ); */
	
	for( i = 0; i < TOTAL_AXES; ++i )
	{
		ret = NEC_CoE402GetStatusWord( this->mAxis[i], &status[i] );
		if( ret != 0 )
		{
			strText.Format(_T("%d"), ret );
			MessageBox( "NEC_CoE402GetStatusWord! ErrorCode:" + strText ); 
			this->mStartAutoMoveFlag = 0;
			this->mStopAutoMove(); return; 
		}
	}

	
	if( this->mStartAutoMoveFlag )
	{
		for( i = 0; i < TOTAL_AXES; ++i )
		{
			if( ( ( status[i] >> AXIS_TARGET_REACH_BIT ) & 0x01 ) != 0x01 )
			{
				return;
			}
		}

		this->mAutoRunMoveIndex++;
	
		if( mAutoRunMoveIndex >= 17 )
			this->mAutoRunMoveIndex = 0;

		tarPosX = this->mTargetPosArray_X[this->mAutoRunMoveIndex];
		tarPosY = this->mTargetPosArray_Y[this->mAutoRunMoveIndex];
		tarPosZ = this->mTargetPosArray_Z[this->mAutoRunMoveIndex];

		this->mStartMove( tarPosX, tarPosY, tarPosZ ); 
	}
}


void CSampleMfcCiA402Dlg::DioCheck()
{
	RTN_ERR ret = 0;
	U16_T SlaveAdd = 0;

	SlaveAdd = TOTAL_AXES;

	if( this->mDoData == 0x0000 ){ this->mDoData = 1; }
	//this->mDoData = 2;

	ret = NEC_SetDo( this->masterId, SlaveAdd, 0, sizeof(this->mDoData), (U8_T *)&this->mDoData );
	if( ret != 0 ) { MessageBox( "NEC_SetDo failed!" ); }
	for( int i = 0; i < 16; ++i )
	{
		if( ( ( this->mDoData >> i ) & 0x0001 ) == 0x0001 )
		{
			GetDlgItem(IDC_EDIT2000 + i)->SetWindowText("1");
		}
		else
		{
			GetDlgItem(IDC_EDIT2000 + i)->SetWindowText("0");
		}
	}

	Sleep(100);

	ret = NEC_GetDi( this->masterId, SlaveAdd, 0, sizeof(this->mDiData), (U8_T *)&this->mDiData );
	if( ret != 0 ) { MessageBox( "NEC_GetDi failed!" ); }
	
	
	for( int i = 0; i < 16; ++i )
	{
		if( ( ( this->mDiData >> i ) & 0x0001 ) == 0x0001 )
		{
			GetDlgItem(IDC_EDIT1000 + i)->SetWindowText("1");
		}
		else
		{
			GetDlgItem(IDC_EDIT1000 + i)->SetWindowText("0");
		}

		GetDlgItem(IDC_EDIT1000 + i)->Invalidate();
		GetDlgItem(IDC_EDIT1000 + i)->UpdateWindow();
		GetDlgItem(IDC_EDIT2000 + i)->Invalidate();
		GetDlgItem(IDC_EDIT2000 + i)->UpdateWindow();
	}

	this->mDoData = this->mDoData << 1;



}

HBRUSH CSampleMfcCiA402Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  Return a different brush if the default is not desired
	int id = 0;

	id = pWnd->GetDlgCtrlID();
	if( id >= IDC_EDIT2000 && id <= IDC_EDIT2000 + 16 )
	{
		id = id - IDC_EDIT2000;

		if( ( ( this->mDoData >> id ) & 0x0001 ) == 0x0001 )
		{
			pDC->SetBkColor(this->m_greencolor);
			hbr = (HBRUSH) m_greenbrush;  
		}
		else
		{
			pDC->SetBkColor(this->m_whitecolor);	
			hbr = (HBRUSH) m_whitebrush;  
		}
	}

	id = pWnd->GetDlgCtrlID();
	if( id >= IDC_EDIT1000 && id <= IDC_EDIT1000 + 16 )
	{
		id = id - IDC_EDIT1000;

		if( ( ( this->mDiData >> id ) & 0x0001 ) == 0x0001 )
		{
			pDC->SetBkColor(this->m_greencolor);
			hbr = (HBRUSH) m_greenbrush;  
		}
		else
		{
			pDC->SetBkColor(this->m_whitecolor);	
			hbr = (HBRUSH) m_whitebrush;  
		}
	}
	
	return hbr;
}

UINT CSampleMfcCiA402Dlg::ThreadFunc( LPVOID pvParam )
{
	CSampleMfcCiA402Dlg *p = (CSampleMfcCiA402Dlg *)pvParam;

	while( p != NULL)
	{
		if( p->misUpdate )
		{
			p->AutoRunCheck();
		}
		Sleep(1);

		if( p->mThreadStop ) break;
	}

	return 0;
}

void CSampleMfcCiA402Dlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	I32_T i = 0;

	this->misUpdate = 0;
	this->mStartAutoMoveFlag = 0;
	this->mThreadStop = 1;
	
	Sleep(1); //Wait to stop thread.

	TerminateThread( this->m_pThread, 0 );

	for( i = 0; i < TOTAL_AXES; ++i )
	{
		NEC_CoE402SetCtrlWord( this->mAxis[i], 0 );
	}
	
	NEC_StopNetwork( this->masterId, timeOut );	
	NEC_ResetEcMaster( this->masterId );

	NEC_StopDriver();

	CDialogEx::OnOK();
}



void CSampleMfcCiA402Dlg::OnBnClickedCheckDio()
{
	// TODO: Add your control notification handler code here
	
	if (this->misUpdate != 1)
	{
		MessageBox("Please click 'Start Master' first. " ); 
		((CButton*)GetDlgItem(IDC_CHECK_DIO))->SetCheck(FALSE);
		return;
	}

	if (this->Count != TOTAL_AXES+1)
	{
		MessageBox("Please check DIO slave is connected at least slave. " ); 
		((CButton*)GetDlgItem(IDC_CHECK_DIO))->SetCheck(FALSE);
		return;
	}

	
	
}
