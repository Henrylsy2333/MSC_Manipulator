
// SampleMfcCiA402.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSampleMfcCiA402App:
// See SampleMfcCiA402.cpp for the implementation of this class
//

class CSampleMfcCiA402App : public CWinApp
{
public:
	CSampleMfcCiA402App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSampleMfcCiA402App theApp;