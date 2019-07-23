//////////////////////////////////////////////////////////////////
//
// RwDioNexECMRtx.c - C file
//
// This file was generated using the RTX Application Wizard 
// for Visual Studio.  
//////////////////////////////////////////////////////////////////
    


/*
	This sample demostrate NexECMRtx as an EtherCAT master communication with an EtherCAT slave I/O device (eg. AXE-9200 16DI-16DO )
	Action: change all bits(bit0~bit15) from 0 to 1 sequentially
*/

#include "RwDioNexECMRtx.h"
#include "NexECMRtx.h"
#include "nex_type.h"
#include "EcErrors.h"

void 
_cdecl
wmain(
       int     argc,
       wchar_t **argv,
       wchar_t **envp
     )

{
    //
    // TO DO:  your program code here
    //
	RTN_ERR     ret;
	U16_T       masterId = 0;
	U16_T       i = 0;
	
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

	ret = NEC_RtStartMaster( masterId );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtStartMaster() error %d \n", ret );
		return;
	}

	ret = NEC_RtChangeStateToOP( masterId, 10000 );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtChangeStateToOP() error %d \n", ret );
		return;
	}

	for( i = 0; i < 15; ++i )
	{
		U16_T data = 1 << i;
		NEC_RtSetSlaveProcessDataOutput( masterId, 0, 0, (U8_T *)&data, sizeof(data));
		Sleep(1000);
	}

	ret = NEC_RtCloseMaster( masterId ); 
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtCloseMaster() error %d \n", ret );
		return;
	}

    ExitProcess(0);
}
