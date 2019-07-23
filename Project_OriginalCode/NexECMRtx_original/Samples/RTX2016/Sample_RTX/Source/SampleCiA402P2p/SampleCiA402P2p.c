//////////////////////////////////////////////////////////////////
//
// SampleCiA402P2p.c - C file
//
// This file was generated using the RTX Application Wizard 
// for Visual Studio.  
//////////////////////////////////////////////////////////////////
    
#include "SampleCiA402P2p.h"
#include "NexECMRtx.h"
#include "NexCoeMotion.h"
#include "EcErrors.h"


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
	U16_T       coeAxisAddr = 0;
	CANAxis_T   axis;
	int         i, counts;
	U16_T       slaveCnt;

	ret = NEC_RtInitMaster( masterId );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtInitMaster() error %d \n", ret ); return; }
	
	ret = NEC_CoE402Reset();
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402Reset() error %d \n", ret ); return; }

	ret = NEC_RtGetSlaveCount( masterId, &slaveCnt ); // from static data (ENI)
	RtPrintf( " \n\nEni slave count = %d \n", slaveCnt );

	ret = NEC_CoE402GetAxisId( masterId, 0, &axis );
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_CoEGetAxisId() error %d \n", ret ); return; }

	ret = NEC_RtSetParameter( masterId, 0, 1000 );  // Set master cycle time = 1 ms
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtSetParameter() error %d \n", ret ); return; }

	// Config user data
	data.masterId = masterId;
	ret = NEC_RtGetProcessDataPtr(  masterId, &data.InputProcessDataPtr, &data.InPDSizeInByte
		, &data.OutputProcessDataPtr, &data.OutPDSizeInByte );
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_RtGetProcessDataPtr() error %d \n", ret ); return; }

	// Register client
	clientParam.version         = NEC_RtRetVer();
	clientParam.userDataPtr     = &data;
	clientParam.cyclicCallback  = __RtCyclicCallback;
	clientParam.eventCallback   = __RtEventCallback;
	clientParam.errorCallback   = __RtErrorCallback;

	ret = NEC_RtRegisterClient( masterId, &clientParam );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtRegisterClient() error %d \n", ret ); return; }
	
	ret = NEC_RtStartMaster( masterId );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtStartMaster() error %d \n", ret ); return; }

	ret = NEC_RtSetMasterStateWait( masterId, ECM_STA_SAFEOP, 5000  ); 
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtSetMasterStateWait() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402UpdatePdoMapping( CAN_ALL_AXES );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402UpdatePdoMapping() error %d \n", ret ); goto _ERR; }

	ret = NEC_RtChangeStateToOP( masterId, 5000 );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtChangeStateToOP() error %d \n", ret ); goto _ERR; }

	RtPrintf( "Change state to op, going to set mode of operation\n" );

	ret = NEC_CoE402SetOperationMode( axis, CiA402_OP_MODE_PROFILE_POSITION, 5000 );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402SetOperationMode() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402FaultReset( axis, 5000 );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402FaultReset() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402ServoOn( axis, 1 );  // 0:ServoOff, 1:ServoOn
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402ServoOn() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402HomeEx( axis, OPT_WMC, 35, 0, 1000, 10000, 10000 );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402HomeEx() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402SetQuickStopDec( axis, 10000000 );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402SetQuickStopDec() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402SetSoftPosLimit( axis, -2000000, 2000000 );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402SetSoftPosLimit() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402SetMaxVelLimit( axis, 100000000 );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402SetMaxVelLimit() error %d \n", ret ); goto _ERR; }

	RtPrintf("Start move\n");
	
	counts = 10;
	for( i = 0; i < counts; i++ )
	{
		ret = NEC_CoE402PtpA( axis, OPT_WMC | OPT_REL, 500000, 1000000, 10000000, 100000000 );
		if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402PtpA() error %d \n", ret ); goto _ERR; }
		
		ret = NEC_CoE402PtpA( axis, OPT_WMC | OPT_REL, -500000, 1000000, 10000000, 100000000 );
		if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402PtpA() error %d \n", ret ); goto _ERR; }
	}

_ERR:
// Close process...

	if( ret != ECERR_SUCCESS )
		RtPrintf( "[Error] " );
	else
		RtPrintf( "[Normal] " );

	// Normally Master already stopped here...
	// add check code here...
	RtPrintf( "Master going to stopped.\n" );

	ret = NEC_CoE402ServoOn( axis, 0 );  // 0:ServoOff, 1:ServoOn
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_CoE402ServoOn() error %d \n", ret ); }

	ret = NEC_RtStopMaster( masterId );
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_RtStopMaster() error %d \n", ret ); }

	ret = NEC_RtUnregisterClient( masterId, &clientParam );
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_RtUnregisterClient() error %d \n", ret ); }

	ret = NEC_CoE402Close();
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_CoE402Close() error %d \n", ret ); }

	ret = NEC_RtCloseMaster( masterId ); 
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_RtCloseMaster() error %d \n", ret ); }

    ExitProcess(0);
}


void __RtCyclicCallback( void *UserDataPtr )
{
	USER_DAT      *pData = (USER_DAT *)UserDataPtr;
	U16_T          state;

	NEC_RtGetMasterState( pData->masterId, &state );
	switch( state )
	{
	case ECM_STA_OPERATION:
		NEC_CoE402CyclicProcess();
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
	//RTN_ERR ret;
	USER_DAT *pData = (USER_DAT *)UserDataPtr;

	RtPrintf( "\n\n\n ********************************************************************** \n" );
	RtPrintf( "[x] ERROR!! __RtErrorCallback() ErrorCode = %d \n", ErrorCode );
	RtPrintf( "    Stop master!!\n" );
	RtPrintf( "********************************************************************** \n\n\n" );

	/*
	ret = NEC_RtStopMasterCb( pData->masterId );

	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "__RtErrorCallback:NEC_RtStopMasterCb() error %d \n", ret );
		return;
	}
	*/

}