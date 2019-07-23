#include <Windows.h>
#include <stdio.h>

#include "Nexecm.h"
#include "NexCoeMotion.h"
#include "EcErrors.h"

#define TOTAL_AXES        (1)
#define FIRST_AXIS_ADDR   (0)
#define DISTANCE          (500000)

int main()
{
	RTN_ERR ret;
	U16_T   masterId;
	CANAxis_T axes[TOTAL_AXES]; 

	ret = NEC_StartDriver();
	if( ret != ECERR_SUCCESS ){ printf( "NEC_StartDriver return %d \n", ret ); goto ERR; }

	ret = NEC_GetRtMasterId( &masterId );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_GetRtMasterId return %d \n", ret ); goto ERR; }

	NEC_StopNetwork( masterId, 5000 );

	ret = NEC_ResetEcMaster( masterId );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_ResetEcMaster return %d \n", ret ); goto ERR; }

	ret = NEC_SetParameter( masterId, NEC_PARA_S_ECM_CYCLETIMEUS, 2000 );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_SetParameter return %d \n", ret ); goto ERR; }

	ret = NEC_CoE402Reset();
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402Reset return %d \n", ret ); goto ERR; }

	// ENI file can be general by NexCAT utility
	ret = NEC_StartNetworkEx( masterId, "c:\\ENI_NexCAT_Export.xml", 1, 10000 );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_StartNetworkEx return %d \n", ret ); goto ERR; }

	for( int i = 0; i < TOTAL_AXES; i++ )
	{
		ret = NEC_CoE402GetAxisId( masterId, FIRST_AXIS_ADDR + i, &axes[i] );
		if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402GetAxisId return %d \n", ret ); goto ERR; }
	}

	ret = NEC_CoE402UpdatePdoMapping( CAN_ALL_AXES );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402UpdatePdoMapping return %d \n", ret ); goto ERR; }

	// Change first axis to Profile position mode
	ret = NEC_CoE402SetOperationMode( axes[0], CiA402_OP_MODE_PROFILE_POSITION, 1000 );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402SetOperationMode return %d \n", ret ); goto ERR; }

	ret = NEC_CoE402FaultReset( CAN_ALL_AXES,  1000 ); 
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402UpdatePdoMapping return %d \n", ret ); goto ERR; }

	printf( "All axes servo on! \n" );
	ret = NEC_CoE402ServoOn( CAN_ALL_AXES, 1 ); 
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402ServoOn return %d \n", ret ); goto ERR; }

	printf( "First axis positive move! \n" );
	ret = NEC_CoE402PtpA( axes[0], OPT_REL | OPT_WMC, DISTANCE, 100000, 1000000, 1000000 );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402PtpA return %d \n", ret ); goto ERR; }

	printf( "First axis negative move! \n" );
	ret = NEC_CoE402Ptp( axes[0], OPT_REL | OPT_WMC, -DISTANCE );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402Ptp return %d \n", ret ); goto ERR; }
	
	ret = NEC_CoE402ServoOn( CAN_ALL_AXES, 0 ); 
	if( ret != ECERR_SUCCESS ){ printf( "NEC_CoE402ServoOn return %d \n", ret ); goto ERR; }

ERR:
	ret = NEC_StopNetwork( masterId, 5000 );
	if( ret != ECERR_SUCCESS ){ printf( "NEC_StopNetwork return %d \n", ret ); }

	 NEC_StopDriver();

	system( "pause" );
	return 0;
}