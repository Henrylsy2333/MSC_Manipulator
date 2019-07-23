//////////////////////////////////////////////////////////////////
//
// SampleNexECMRtx.c - C file
//
// This file was generated using the RTX Application Wizard 
// for Visual Studio.  
//
//////////////////////////////////////////////////////////////////
    
#include "SampleNexECMRtxCSP.h"

/*
	This sample demostrate NexECMRtx as an EtherCAT master communication with two YASKAWA Sigma5 EtherCAT slave devices.
	Action: Executing positive move for a time under CSP(refer to CIA402) mode.
	Notice: You may need change a little part of code for your drive.
*/

#define MAX_SM_AXES 8

#pragma pack(push, 1)

typedef struct
{
	U16_T  StatusWord;
	U32_T  ActualPosition;
}PROC_IN, *PPROC_IN;

typedef struct
{
	U16_T  ControlWord;
	U32_T  TargetPosition;
}PROC_OUT, *PPROC_OUT;


typedef struct
{
	PROC_IN  *pProcIn;
	PROC_OUT *pProcOut;
	U32_T     ProcIntSize;
	U32_T     ProcOutSize;
}TSLAVE, *PTSLAVE;

typedef struct
{
	U16_T     masterId;
	TSLAVE    slave[MAX_SM_AXES]; 
	U16_T     startFlag;
	U32_T     runTimes;
	U16_T     startAxis;
	U16_T     lastAxis;
	U32_T     inc_dis;
}USER_DATA;

#pragma pack( pop )

void __RtCyclicCallback( void *UserDataPtr );
void __RtEventCallback( void *UserDataPtr, U32_T EventCode ); 
void __RtErrorCallback( void *UserDataPtr, I32_T ErrorCode );


#define START_AXIS 0
#define LAST_AXIS  1

#define FAULT_RESET_402        128
#define READY_TO_SWITCH_ON_402 6
#define SWITCH_ON_402          7
#define OPERATION_ENABLE_402   15
#define CSP_MODE_402           8
#define HOME_MODE_402          6

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
	USER_DATA   data;
	U8_T        value[4];
	TSDO        sdo;
	I32_T		baseTime = 500;
	U32_T       runSec   = 30;    //time for running.
	U32_T       baseSpeed = 100000; //please refer to your drive resolution
	I32_T       cycleTime = 1000; //microsecond

	F64_T       run_times = ( runSec * 1000000 ) / cycleTime;
	F64_T       inc_dis   = ( baseSpeed * cycleTime ) / baseTime;

	U16_T       i = 0;

	RtPrintf("cycle time:%d\n", cycleTime );

	data.runTimes = (U32_T)run_times;
	RtPrintf( "run times:%d\n", data.runTimes );

	data.inc_dis = (U32_T)inc_dis;
	RtPrintf( "increase distance:%d\n", data.inc_dis );

	data.startAxis = START_AXIS;
	data.lastAxis  = LAST_AXIS;

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

	//Config user data
	data.masterId = masterId;
	data.startFlag = 0;

	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		ret = NEC_RtGetSlaveProcessDataPtr( masterId
		    , i
			, (U8_T **)&data.slave[i].pProcIn
			, &data.slave[i].ProcIntSize
			, (U8_T **)&data.slave[i].pProcOut
			, &data.slave[i].ProcOutSize );

		if( ret != ECERR_SUCCESS )
		{
			RtPrintf( "NEC_RtGetProcessDataPtr() error %d \n", ret );
			return;
		}
	}
	
	//Register client
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

	ret = NEC_RtSetMasterStateWait( masterId, ECM_STA_OPERATION, 10000 );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtSetMasterState() error %d \n", ret );
		goto _FAIL;
	}

	//Change operation to Homd mode and set the mode to 35.
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		memset(value, 0, sizeof(value));
		value[0] = HOME_MODE_402; 

		sdo.index       = 0x6060;
		sdo.subIndex    = 0;
		sdo.dataLenByte = 1;
		sdo.dataPtr     = value;
		sdo.ctrlFlag    = 0;
		sdo.abortCode   = 0;
		sdo.status      = 0;

		ret = NEC_RtSDODownload( masterId, i, &sdo );	
		if( ( ret != ECERR_SUCCESS ) || ( sdo.abortCode != ECERR_SUCCESS ) )
		{
			if( ret != ECERR_SUCCESS )
				RtPrintf( "NEC_RtSDODownload() error %d \n", ret );
			if( sdo.abortCode != ECERR_SUCCESS )
				RtPrintf( "NEC_RtSDODownload() abort error %d \n", sdo.abortCode );

			goto _FAIL;
		}

		memset(value, 0, sizeof(value));
		value[0] = 35; 
		
		sdo.index       = 0x6098;
		sdo.subIndex    = 0;
		sdo.dataLenByte = 1;
		sdo.dataPtr     = value;
		sdo.ctrlFlag    = 0;
		sdo.abortCode   = 0;
		sdo.status      = 0;
		
		ret = NEC_RtSDODownload( masterId, i, &sdo );	
		if( ( ret != ECERR_SUCCESS ) || ( sdo.abortCode != ECERR_SUCCESS ) )
		{
			if( ret != ECERR_SUCCESS )
				RtPrintf( "NEC_RtSDODownload() error %d \n", ret );
			if( sdo.abortCode != ECERR_SUCCESS )
				RtPrintf( "NEC_RtSDODownload() abort error %d \n", sdo.abortCode );

			goto _FAIL;
		}
	}
	
	//Clear driver fault
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		data.slave[i].pProcOut->ControlWord = 0;
		Sleep(100);
		data.slave[i].pProcOut->ControlWord = FAULT_RESET_402;
		Sleep(100);
	}

	//switch 402 state machine to Ready-to-SwitchOn
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		data.slave[i].pProcOut->ControlWord = READY_TO_SWITCH_ON_402;
		while(1)
		{
			if( ( ( data.slave[i].pProcIn->StatusWord >> 0 ) & 0x01 ) == 0x01 ) 
				break;

			RtPrintf("Wait <<<ready to Switch On>>>\n");

			Sleep(10);
		}
	}

	//switch 402 state machine to SWITCH_ON_402
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		data.slave[i].pProcOut->ControlWord = SWITCH_ON_402;
		while(1)
		{
			if( ( ( ( data.slave[i].pProcIn->StatusWord >> 0 ) & 0x01 ) == 0x01 ) && 
				( ( ( data.slave[i].pProcIn->StatusWord >> 1 ) & 0x01 ) == 0x01 ) )
			break;

			RtPrintf("Wait <<<Switch on>>>\n");

			Sleep(10);
		}
	}

	//switch 402 state machine to Operation-Enabled
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		data.slave[i].pProcOut->ControlWord = OPERATION_ENABLE_402;
		while(1)
		{
			if( ( ( ( data.slave[i].pProcIn->StatusWord >> 0 ) & 0x01 ) == 0x01 ) && 
				( ( ( data.slave[i].pProcIn->StatusWord >> 1 ) & 0x01 ) == 0x01 ) && 
				( ( ( data.slave[i].pProcIn->StatusWord >> 2 ) & 0x01 ) == 0x01) )
				break;

			RtPrintf("Wait <<<Operation Enabled>>>\n");

			Sleep(10);
		}
	}
	
	//Executing home mode 35 to clear actual position of drive.
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		data.slave[i].pProcOut->ControlWord = 31;
	}
	Sleep(10);
	
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		data.slave[i].pProcOut->ControlWord = 15;
	}
	Sleep(10);

	//Change operation to csp
	for( i = data.startAxis; i <= data.lastAxis; ++i )
	{
		memset(value, 0, sizeof(value));
		value[0] = CSP_MODE_402; 

		sdo.index       = 0x6060;
		sdo.subIndex    = 0;
		sdo.dataLenByte = 1;
		sdo.dataPtr     = value;
		sdo.ctrlFlag    = 0;
		sdo.abortCode   = 0;
		sdo.status      = 0;

		ret = NEC_RtSDODownload( masterId, i, &sdo );	
		if( ( ret != ECERR_SUCCESS ) || ( sdo.abortCode != ECERR_SUCCESS ) )
		{
			if( ret != ECERR_SUCCESS )
				RtPrintf( "NEC_RtSDODownload() error %d \n", ret );
			if( sdo.abortCode != ECERR_SUCCESS )
				RtPrintf( "NEC_RtSDODownload() abort error %d \n", sdo.abortCode );

			goto _FAIL;
		}
	}
	
	data.startFlag = 1;
	
	RtPrintf( " blocked until user stop master... \n" );
	ret = NEC_RtWaitMasterStop( masterId ); 
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtWaitMasterStop() error %d \n", ret );
		goto _FAIL;;
	}

	//Normally Master already stopped here...
	//add check code here...
	RtPrintf( " User stop the master \n" );

	ret = NEC_RtUnregisterClient( masterId, &clientParam );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtUnregisterClient() error %d \n", ret );
		goto _FAIL;
	}

	ret = NEC_RtCloseMaster( masterId ); 
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtCloseMaster() error %d \n", ret );
		return;
	}

	ExitProcess(0);

_FAIL:
	NEC_RtStopMaster( masterId );
	NEC_RtUnregisterClient( masterId, &clientParam );
	NEC_RtCloseMaster( masterId ); 
    
	ExitProcess(0);
}



void __RtCyclicCallback( void *UserDataPtr )
{
	#define PRINT_COUNT 5000

	USER_DATA     *pData = (USER_DATA *)UserDataPtr;
	U16_T          state;
	static I32_T   cnt = 0;
	int i;

	NEC_RtGetMasterState( pData->masterId, &state );

	if( cnt == pData->runTimes ) 
	{
		NEC_RtStopMasterCb(pData->masterId);
		return;
	}

	if( state == ECM_STA_OPERATION )
	{
		if( pData->startFlag )
		{
			if( ++cnt == pData->runTimes )
			{
				for( i = pData->startAxis; i < pData->lastAxis; ++i )
				{
					pData->slave[i].pProcOut->ControlWord = 0;
					pData->startFlag = 0;
					RtPrintf("Stop master from call back.\n");
				}
			}
			else
			{
				if( ( cnt % PRINT_COUNT ) == 0 )
				{
					for( i = pData->startAxis; i <= pData->lastAxis; ++i )
					{ 
						RtPrintf("Axis:%d Actual position:%d, TargetPosition:%d\n", i, pData->slave[i].pProcIn->ActualPosition, pData->slave[i].pProcOut->TargetPosition );
					}
				}

				for( i = pData->startAxis; i <= pData->lastAxis; ++i )
				{
					pData->slave[i].pProcOut->TargetPosition = pData->slave[i].pProcIn->ActualPosition + pData->inc_dis;
				}

			}
		}
	}

}


void __RtEventCallback( void *UserDataPtr, U32_T EventCode )
{
	RTN_ERR ret;
	USER_DATA *pData = (USER_DATA *)UserDataPtr;
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
	USER_DATA *pData = (USER_DATA *)UserDataPtr;

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