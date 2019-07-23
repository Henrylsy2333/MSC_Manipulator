//////////////////////////////////////////////////////////////////
//
// SampleNexECMRtx.c - C file
//
// This file was generated using the RTX Application Wizard 
// for Visual Studio.  
//
//////////////////////////////////////////////////////////////////
    
#include "SampleNexECMRtx.h"

/*
	This sample demostrate NexECMRtx as an EtherCAT master communication with an EtherCAT slave I/O device (eg. AXE-9200 16DI-16DO )
	Action: Control digital output on/off ervery seconds.
*/


typedef struct
{
	U16_T  masterId;
	U8_T  *InputProcessDataPtr; 
	U32_T  InPDSizeInByte; 
	U8_T  *OutputProcessDataPtr; 
	U32_T  OutPDSizeInByte;
}USER_DAT;

void __RtCyclicCallback( void *UserDataPtr );
void __RtEventCallback( void *UserDataPtr, U32_T EventCode ); 
void __RtErrorCallback( void *UserDataPtr, I32_T ErrorCode );

void 
_cdecl
main(
       int  argc,
       char **argv,
       char **envp
    )
{
    //
    // TO DO:  your program code here
    //
	RTN_ERR     ret;
	U16_T       masterId = 0;
	TClintParam clientParam;
	USER_DAT    data;

	ret = NEC_RtInitMaster( masterId );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtInitMaster() error %d \n", ret );
		return;
	}
	
	ret = NEC_RtSetParameter( masterId, 0, 1000 );  // Set master cycle time = 1 ms
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtSetParameter() error %d \n", ret );
		return;
	}

	// Config user data
	data.masterId = masterId;
	ret = NEC_RtGetProcessDataPtr(  masterId
		, &data.InputProcessDataPtr, &data.InPDSizeInByte
		, &data.OutputProcessDataPtr, &data.OutPDSizeInByte );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtGetProcessDataPtr() error %d \n", ret );
		return;
	}


	// Register client
	clientParam.version         = NEC_RtRetVer();
	clientParam.userDataPtr     = &data;
	clientParam.cyclicCallback  = __RtCyclicCallback;
	clientParam.eventCallback   = __RtEventCallback;
	clientParam.errorCallback   = __RtErrorCallback;

	ret = NEC_RtRegisterClient( masterId, &clientParam );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtRegisterClient() error %d \n", ret );
		return;
	}
	
	ret = NEC_RtStartMaster( masterId );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtStartMaster() error %d \n", ret );
		return;
	}

	ret = NEC_RtSetMasterState( masterId, ECM_STA_OPERATION );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtSetMasterState() error %d \n", ret );
		return;
	}

	RtPrintf( " blocked until user stop master... \n" );
	ret = NEC_RtWaitMasterStop( masterId ); 
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtWaitMasterStop() error %d \n", ret );
		return;
	}

	// Normally Master already stopped here...
	// add check code here...
	RtPrintf( " User stop the master \n" );

	ret = NEC_RtUnregisterClient( masterId, &clientParam );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtUnregisterClient() error %d \n", ret );
		return;
	}

	ret = NEC_RtCloseMaster( masterId ); 
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtCloseMaster() error %d \n", ret );
		return;
	}

    ExitProcess(0);
}


void __RtCyclicCallback( void *UserDataPtr )
{
	USER_DAT      *pData = (USER_DAT *)UserDataPtr;
	U16_T          state;
	static I32_T   cnt = 0;

	NEC_RtGetMasterState( pData->masterId, &state );

	switch( state )
	{
	case ECM_STA_OPERATION:
		cnt++;

		if( cnt > 1000 )
		{
			cnt = 0;
			// In this sample the ProcessData offset 26 is a AXE-9200 DIO memory area 
			pData->OutputProcessDataPtr[26] = ~pData->OutputProcessDataPtr[26]; // Every 1000 ms will inverse DO outputs.
		}

		break;
	}
}


void __RtEventCallback( void *UserDataPtr, U32_T EventCode )
{
	RTN_ERR ret;
	USER_DAT *pData = (USER_DAT *)UserDataPtr;
	U16_T state;

	switch( EventCode )
	{
	case EVENT_ECM_STATE_CHANGE:
		ret = NEC_RtGetMasterState( pData->masterId, &state );
		RtPrintf( "State change event! state change to: %d \n", state ); 
		break;
	}
}

void __RtErrorCallback( void *UserDataPtr, I32_T ErrorCode )
{
	RTN_ERR ret;
	USER_DAT *pData = (USER_DAT *)UserDataPtr;

	RtPrintf( "\n\n\n ********************************************************************** \n" );
	RtPrintf( "[x] ERROR!! __RtErrorCallback() ErrorCode = %d \n", ErrorCode );
	RtPrintf( "    Stop master!!\n" );
	RtPrintf( "********************************************************************** \n\n\n" );

	ret = NEC_RtStopMasterCb( pData->masterId );

	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "__RtErrorCallback:NEC_RtStopMasterCb() error %d \n", ret );
		return;
	}
}