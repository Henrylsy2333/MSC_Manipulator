//////////////////////////////////////////////////////////////////
//
// Sample2Layer_RTX.c - c file
//
// This file was generated using the RTX 2016 SDK 12.0.0.1324
// RTX Application Template.
//
// Created: 5/20/2016 2:36:18 PM 
// User: NET3640
//
//////////////////////////////////////////////////////////////////

#include "Sample2Layer_RTX.h"
   

#define EVN_NAME "EventHandle"
#define EVN_NAME2 "EventHandle2"
#define EVN_NAME3 "EventHandle3"
#define SHM_NAME "MemoryHandle"

typedef	struct
{
	int master;
	int x;
	int y;
	int ans;
}USER_DAT;

static  PVOID  location;

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
	int ret = 0;
	HANDLE sHhandle = NULL;
	HANDLE oBhandle = NULL;
	HANDLE oBhandle2 = NULL;
	HANDLE oBhandle3 = NULL;
	USER_DAT  *pData;

	RtPrintf("RtxLayer.rtss is opened ! \n");

	sHhandle = RtCreateSharedMemory((DWORD)PAGE_READWRITE, (DWORD)0, (DWORD) sizeof(USER_DAT), SHM_NAME, &location);
	if (sHhandle == NULL) { RtPrintf("RtCreateSharedMemory failed.\n"); ExitProcess(0); }

	pData = (USER_DAT *)(location);
	pData->master = 5;

	oBhandle = RtCreateEvent(NULL, 0, FALSE, EVN_NAME);
	if (oBhandle == NULL) { RtPrintf("RtCreateEvent 1 failed.\n"); ExitProcess(0); }

	oBhandle2 = RtCreateEvent(NULL, 0, FALSE, EVN_NAME2);
	if (oBhandle2 == NULL) { RtPrintf("RtCreateEvent 2 failed.\n"); ExitProcess(0); }

	oBhandle3 = RtCreateEvent(NULL, 0, FALSE, EVN_NAME3);
	if (oBhandle3 == NULL) { RtPrintf("RtCreateEvent 3 failed.\n"); ExitProcess(0); }

	while (1)
	{
		ret = RtWaitForSingleObject(oBhandle, 3);
		if (ret == 0) { pData->ans = Addition(pData->x, pData->y); RtPrintf("(A) x = %d, y = %d, ans = %d \n", pData->x, pData->y, pData->ans); }

		ret = RtWaitForSingleObject(oBhandle2, 3);
		if (ret == 0) { pData->ans = Multiplication(pData->x, pData->y); RtPrintf("(B) x = %d, y = %d, ans = %d \n", pData->x, pData->y, pData->ans); }

		ret = RtWaitForSingleObject(oBhandle3, 3);
		if (ret == 0) 
		{
			RtPrintf("Rtss app going to close!!");

			RtCloseHandle(sHhandle);
			RtCloseHandle(oBhandle);
			RtCloseHandle(oBhandle2);
			RtCloseHandle(oBhandle3);

			ExitProcess(0);
		}
	}

}

int Addition(int x, int y)
{
	return (x + y);
}

int Multiplication(int x, int y)
{
	return (x * y);
}