//////////////////////////////////////////////////////////////////
//
// RwDriveParamNexECMRtx.c - C file
//
// This file was generated using the RTX Application Wizard 
// for Visual Studio.  
//////////////////////////////////////////////////////////////////
    


/*
	This sample demostrate NexECMRtx as an EtherCAT master communication with an EtherCAT slave drive device (eg. Hiwin D2 drive )
	Action: write value to profile velocity object(0x6081), and read come back.
*/

#include "RwDriveParamNexECMRtx.h"
#include "NexECMRtx.h"
#include "NexCoeMotion.h"
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
	U16_T       coeAxisAddr = 0;
	I32_T       wdata = 0;
	I32_T       rdata = 0;
	CANAxis_T   axis;
	
	ret = NEC_RtInitMaster( masterId );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtInitMaster() error %d \n", ret ); goto _ERR; }
	
	ret = NEC_CoE402Reset();
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_CoE402Reset() error %d \n", ret ); goto _ERR; }

	ret = NEC_CoE402GetAxisId( masterId, coeAxisAddr, &axis );
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_CoEGetAxisId() error %d \n", ret ); goto _ERR; }

	ret = NEC_RtSetParameter( masterId, 0, 1000 );  // Set master cycle time = 1 ms
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtSetParameter() error %d \n", ret ); goto _ERR; }

	ret = NEC_RtStartMaster( masterId );
	if( ret != ECERR_SUCCESS ){ RtPrintf( "NEC_RtStartMaster() error %d \n", ret ); goto _ERR; }

	ret = NEC_RtChangeStateToOP( masterId, 10000 );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_RtChangeStateToOP() error %d \n", ret );
		goto _ERR;
	}

	wdata = 10000;
	ret = NEC_CoE402SetParameter( axis, INDEX_PROFILE_VELOCITY, 0, 2, wdata );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_CoE402SetParameter() error %d \n", ret );
		goto _ERR;
	}
	RtPrintf("Write INDEX_PROFILE_VELOCITY, value:%d\n", wdata);
	
	rdata = 0;
	ret = NEC_CoE402GetParameter( axis, INDEX_PROFILE_VELOCITY, 0, 2, &rdata );
	if( ret != ECERR_SUCCESS )
	{
		RtPrintf( "NEC_CoE402GetParameter() error %d \n", ret );
		goto _ERR;
	}

	RtPrintf("Read INDEX_PROFILE_VELOCITY, value:%d\n", rdata);
		
	if( wdata != rdata )
	{
		RtPrintf("Write-Read INDEX_PROFILE_VELOCITY failed.\n");
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

	ret = NEC_RtStopMaster( masterId );
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_RtStopMaster() error %d \n", ret ); }

	ret = NEC_CoE402Close();
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_CoE402Close() error %d \n", ret ); }

	ret = NEC_RtCloseMaster( masterId ); 
	if( ret != ECERR_SUCCESS ) { RtPrintf( "NEC_RtCloseMaster() error %d \n", ret ); }

    ExitProcess(0);
}
