// SampleGetAliasAddr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Nexecm.h"
#include "nex_type.h"
#include "EcErrors.h"
#include <Windows.h>

#include <assert.h>
#define __ASSERT assert

#define XML_FILE  "C:\\ENI_NexCAT_Export.xml"

int _tmain(int argc, _TCHAR* argv[])
{
	U16_T  id;
	RTN_ERR ret;
	U32_T   cnt;
	U32_T   i;
	U16_T   data;
	U16_T   state;

	ret = NEC_StartDriver();
	__ASSERT( ret == ECERR_SUCCESS );	
	
	ret = NEC_GetRtMasterId(&id);
	__ASSERT( ret == ECERR_SUCCESS );

	ret = NEC_SetParameter( id, NEC_PARA_S_ECM_CYCLETIMEUS, 1000 );  // 1 ms
	__ASSERT( ret == ECERR_SUCCESS );

	ret = NEC_StartNetworkEx( id, XML_FILE, START_NETWORK_OPT_MASK_NIC_PORT, 5000 ); 
	__ASSERT( ret == ECERR_SUCCESS );

	ret = NEC_GetNetworkState( id, &state );
	__ASSERT( ret == ECERR_SUCCESS );

	Sleep( 1000 );

	ret = NEC_GetSlaveCount( id, &cnt );
	__ASSERT( ret == ECERR_SUCCESS );

	for( i = 0; i < cnt; ++i )
	{
		ret = NEC_GetAliasAddress( id, i, &data );
		__ASSERT( ret == ECERR_SUCCESS );
		printf(" SlaveIndex:%d aliasAddr:0x%x. \n", i, data );
	}
	
	ret = NEC_StopNetwork( id, 5000 );
	__ASSERT( ret == ECERR_SUCCESS );

	NEC_StopDriver();

}

