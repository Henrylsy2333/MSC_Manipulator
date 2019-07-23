//////////////////////////////////////////////////////////////////
//
// Sample2AxesControl_RTX.c - c file
//
// This file was generated using the RTX 2016 SDK 12.0.0.1324
// RTX Application Template.
//
// Created: 5/20/2016 2:30:58 PM 
// User: NET3640
//
//////////////////////////////////////////////////////////////////

#include "Sample2AxesControl_RTX.h"
   
#include "nex_type.h"
#include "NexECMRtx.h"
#include "nex_type.h"
#include "EcErrors.h"
#include "NexCoeMotion.h"
#define EVN_NAME "Event"
#define SHM_NAME "Memory"
typedef	struct
{
	CANAxis_T mAxis_1;
	CANAxis_T mAxis_2;
	U16_T masterId;
	I32_T ActualPos_1;
	I32_T ActualPos_2;
	I32_T TargetPos_1;
	I32_T TargetPos_2;
	U16_T MasterState;
	U16_T SlaveState_1;
	U16_T SlaveState_2;
	U8_T  Move_Type_1;
	U8_T  Move_Type_2;
	U32_T ACC_DEC_1;
	U32_T ACC_DEC_2;
	U32_T Velocity_1;
	U32_T Velocity_2;

}USER_DAT;

void __RtCyclicCallback(void *UserDataPtr);
void __RtEventCallback(void *UserDataPtr, U32_T EventCode);
void __RtErrorCallback(void *UserDataPtr, I32_T ErrorCode);

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
	HANDLE shHandle = NULL;
	HANDLE obHandle = NULL;
	USER_DAT  *pData;
	RTN_ERR     ret;
	U16_T       masterId = 0;
	TClintParam clientParam;
	U16_T       coeAxisAddr = 0;
	U16_T       slaveCnt;
	shHandle = RtCreateSharedMemory((DWORD)PAGE_READWRITE, (DWORD)0, (DWORD) sizeof(USER_DAT), SHM_NAME, &location);
	if (shHandle == NULL)
	{
		RtPrintf("RtCreateSharedMemory failed.\n");
		ExitProcess(0);
	}
	pData = (USER_DAT *)(location);
	obHandle = RtCreateEvent(NULL, 0, FALSE, EVN_NAME);
	if (obHandle == NULL)
	{
		RtPrintf("RtCreateEvent failed.\n");
		ExitProcess(0);
	}
	while (1)
	{
		ret = RtWaitForSingleObject(obHandle, -3);
		if (ret == 0)
		{
			RtPrintf("this event is opened.\n");

			ret = NEC_RtInitMaster(masterId);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtInitMaster() error %d \n", ret); return; }

			ret = NEC_CoE402Reset();
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402Reset() error %d \n", ret); return; }

			ret = NEC_RtGetSlaveCount(masterId, &slaveCnt);
			RtPrintf(" \n\nEni slave count = %d \n", slaveCnt);

			ret = NEC_CoE402GetAxisId(masterId, 0, &pData->mAxis_1);
			if (ret != 0) { RtPrintf("NEC_CoE402GetAxisId failed!"); return; }

			ret = NEC_CoE402GetAxisId(masterId, 1, &pData->mAxis_2);
			if (ret != 0) { RtPrintf("NEC_CoE402GetAxisId failed!"); return; }

			ret = NEC_RtSetParameter(masterId, NEC_PARA_S_ECM_CYCLETIMEUS, 1000);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtSetParameter() error %d \n", ret); return; }

			RtPrintf("start master!.\n");

			// Register client
			clientParam.version = NEC_RtRetVer();
			clientParam.userDataPtr = pData;
			clientParam.cyclicCallback = __RtCyclicCallback;
			clientParam.eventCallback = __RtEventCallback;
			clientParam.errorCallback = __RtErrorCallback;

			ret = NEC_RtRegisterClient(masterId, &clientParam);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtRegisterClient() error %d \n", ret); return; }
			ret = NEC_RtStartMaster(masterId);

			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtStartMaster() error %d \n", ret); return; }
			ret = NEC_RtSetMasterStateWait(masterId, ECM_STA_SAFEOP, 5000);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtSetMasterStateWait() error %d \n", ret); }

			ret = NEC_CoE402FaultReset(pData->mAxis_1, 5000);
			if (ret != 0) { RtPrintf("NEC_CoE402FaultReset failed!%d \n", ret); return; }
			ret = NEC_CoE402FaultReset(pData->mAxis_2, 5000);
			if (ret != 0) { RtPrintf("NEC_CoE402FaultReset failed!%d \n", ret); return; }

			ret = NEC_CoE402UpdatePdoMapping(pData->mAxis_1);
			if (ret != 0) { RtPrintf("NEC_CoE402UpdatePdoMapping failed! %d \n", ret); return; }
			ret = NEC_CoE402UpdatePdoMapping(pData->mAxis_2);
			if (ret != 0) { RtPrintf("NEC_CoE402UpdatePdoMapping failed!"); return; }

			ret = NEC_CoE402FaultReset(pData->mAxis_1, 5000);
			if (ret != 0) { RtPrintf("NEC_CoE402FaultReset failed!%d \n", ret); return; }
			ret = NEC_CoE402FaultReset(pData->mAxis_2, 5000);
			if (ret != 0) { RtPrintf("NEC_CoE402FaultReset failed!"); return; }

			ret = NEC_RtChangeStateToOP(masterId, 5000);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtChangeStateToOP() error %d \n", ret); }

			RtPrintf("Change state to op, going to set mode of operation\n");

			ret = NEC_CoE402SetOperationMode(pData->mAxis_1, CiA402_OP_MODE_PROFILE_POSITION, 5000);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402SetOperationMode() error %d \n", ret); }
			ret = NEC_CoE402SetOperationMode(pData->mAxis_2, CiA402_OP_MODE_PROFILE_POSITION, 5000);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402SetOperationMode() error %d \n", ret); }

			ret = NEC_CoE402ServoOn(pData->mAxis_1, 1);  // 0:ServoOff, 1:ServoOn
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402ServoOn() error %d \n", ret); }
			ret = NEC_CoE402ServoOn(pData->mAxis_2, 1);  // 0:ServoOff, 1:ServoOn
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402ServoOn() error %d \n", ret); }

			Sleep(2000);
			ret = NEC_CoE402Halt(pData->mAxis_1, 0);
			ret = NEC_CoE402Halt(pData->mAxis_2, 0);
			Sleep(2000);
			ret = NEC_CoE402PtpA(pData->mAxis_1, OPT_ABS | OPT_WMC, pData->TargetPos_1, pData->Velocity_1, pData->ACC_DEC_1, pData->ACC_DEC_1);
			if (ret != 0) { RtPrintf("NEC_CoE402PtpA failed!%d \n", ret); }
			ret = NEC_CoE402PtpA(pData->mAxis_2, OPT_ABS | OPT_WMC, pData->TargetPos_2, pData->Velocity_2, pData->ACC_DEC_2, pData->ACC_DEC_2);
			if (ret != 0) { RtPrintf("NEC_CoE402PtpA failed!"); }

			Sleep(1000);

			RtPrintf("Servo Off.\n");
			ret = NEC_CoE402ServoOn(pData->mAxis_1, 0);  // 0:ServoOff, 1:ServoOn
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402ServoOn() error %d \n", ret); }
			ret = NEC_CoE402ServoOn(pData->mAxis_2, 0);  // 0:ServoOff, 1:ServoOn
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402ServoOn() error %d \n", ret); }

			RtPrintf("Master going to stopped.\n");

			ret = NEC_CoE402ServoOn(pData->mAxis_1, 0);  // 0:ServoOff, 1:ServoOn
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402ServoOn() error %d \n", ret); }
			ret = NEC_CoE402ServoOn(pData->mAxis_2, 0);  // 0:ServoOff, 1:ServoOn
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402ServoOn() error %d \n", ret); }

			NEC_CoE402SetCtrlWord(pData->mAxis_1, 0);
			NEC_CoE402SetCtrlWord(pData->mAxis_2, 0);

			ret = NEC_RtStopMaster(masterId);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtStopMaster() error %d \n", ret); }

			ret = NEC_RtUnregisterClient(masterId, &clientParam);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtUnregisterClient() error %d \n", ret); }

			ret = NEC_CoE402Close();
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_CoE402Close() error %d \n", ret); }

			ret = NEC_RtCloseMaster(masterId);
			if (ret != ECERR_SUCCESS) { RtPrintf("NEC_RtCloseMaster() error %d \n", ret); }

			RtCloseHandle(obHandle);
			RtCloseHandle(shHandle);
			ExitProcess(0);
		}
	}
}

void __RtCyclicCallback(void *UserDataPtr)
{
	USER_DAT      *pData = (USER_DAT *)UserDataPtr;
	U16_T          state;
	int i = 0;
	RTN_ERR ret;
	I32_T   pos, pos2;
	U16_T SlaveState, SlaveState2;
	NEC_RtGetMasterState(pData->masterId, &state);

	pData->MasterState = state;
	switch (state)
	{
	case ECM_STA_OPERATION:
		NEC_CoE402CyclicProcess();
		break;
	}
	ret = NEC_CoE402GetActualPosition(pData->mAxis_1, &pos);
	if (ret == 0)
	{
		pData->ActualPos_1 = pos;
	}
	ret = NEC_CoE402GetActualPosition(pData->mAxis_2, &pos2);
	if (ret == 0)
	{
		pData->ActualPos_2 = pos2;
	}
	NEC_CoE402GetState(pData->mAxis_1, &SlaveState);
	pData->SlaveState_1 = SlaveState;

	NEC_CoE402GetState(pData->mAxis_2, &SlaveState2);
	pData->SlaveState_2 = SlaveState2;
}
void __RtEventCallback(void *UserDataPtr, U32_T EventCode)
{
	RTN_ERR ret;
	USER_DAT *pData = (USER_DAT *)UserDataPtr;
	U16_T state;

	switch (EventCode)
	{
	case EVENT_ECM_STATE_CHANGE:
		ret = NEC_RtGetMasterState(pData->masterId, &state);
		RtPrintf("State change event! state change to: %d \n", state);
		break;
	}
}

void __RtErrorCallback(void *UserDataPtr, I32_T ErrorCode)
{
	//RTN_ERR ret;
	USER_DAT *pData = (USER_DAT *)UserDataPtr;

	RtPrintf("\n\n\n ********************************************************************** \n");
	RtPrintf("[x] ERROR!! __RtErrorCallback() ErrorCode = %d \n", ErrorCode);
	RtPrintf("    Stop master!!\n");
	RtPrintf("********************************************************************** \n\n\n");
	/*
	ret = NEC_RtStopMasterCb( pData->masterId );

	if( ret != ECERR_SUCCESS )
	{
	RtPrintf( "__RtErrorCallback:NEC_RtStopMasterCb() error %d \n", ret );
	return;
	}
	*/

}


