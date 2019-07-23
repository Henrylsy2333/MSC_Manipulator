/******************************************************************************
	Building The Digital Infrastructure 
	(C) 2015 NEXCOM International Co., Ltd. All Rights Reserved.

    @author  WeihanWang
    @date    2015/01/06
    @dllversion 1.0 beta   
	
	@description
	This cpp file is the interface(dll defines) between win32 user application and NexRobot Controller.
      

*******************************************************************************/

// NexRobotWin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NexRobotWin.h"
#include "NexSharedMemory.h"
#include <Rtapi.h>
#include <ShellAPI.h>

/* global variable */
_NER_SHAREDMEM         *SharedData      = NULL;
static HANDLE			hDatamem		= NULL;
DWORD                   TimeOut         = 1000;// (1s)

/* local function */
int m_WaitUntil_CmdRdy(void);

int FNTYPE NexR_LinktoRobotKernel(void)
{
	/* Open SharedMemory */
	if (hDatamem == NULL) 
	{
		if ((hDatamem = RtOpenSharedMemory(SHM_MAP_WRITE, FALSE, "NER_Shared_Space", (void **)&SharedData)) == NULL)
		{
			RtPrintf("Open Shared Memory Failed\n");			
			return -1;
		}
	}

	return 0;
}

int FNTYPE NexR_CloseRobotKernel(void)
{		
	// Initialize parameters
	SharedData->b_rec_cmd = FALSE;
	SharedData->cmd_type  = NER_CLOSE_ROBOT_KERNEL;

	// send command
	SharedData->b_send_cmd = TRUE;

	// check cmd is ready
	if(0 == m_WaitUntil_CmdRdy()){return 0;}

	// Timeout
	return -1;
}

void FNTYPE NexR_GetRobotKernelStatus(int &ret)
{
	if(hDatamem != NULL)
	{
		ret = SharedData->b_robot_kernal_ready;
	}
	else
		ret = FALSE;
}

void FNTYPE NexR_GetRobotPosition( NexRobotPos &Robot_Pos)
{
	int i = 0;
	for( i = 0; i < 6; i++)
	{
		Robot_Pos.Axis_actpos[i]  = SharedData->robot_data.robot_axis[i].actual_position;	
		Robot_Pos.Axis_actvel[i]  = SharedData->robot_data.robot_axis[i].actual_velocity;	
		Robot_Pos.Axis_Data[i]    = SharedData->robot_data.robot_axis[i].robot_deg;
		Robot_Pos.Axis_Vel[i]    = SharedData->robot_data.robot_axis[i].robot_vel;
		Robot_Pos.Servo_Status[i] = SharedData->robot_data.robot_axis[i].state;
		Robot_Pos.Tcp[i]          = SharedData->robot_data.tcp_data[i];		
	}
}

int FNTYPE NexR_RobotServoON(void)
{
	// Initialize parameters
	SharedData->b_rec_cmd = FALSE;
	SharedData->cmd_type  = NER_SERVO_ON_ALL;

	// send command
	SharedData->b_send_cmd = TRUE;

	// check cmd is ready
	if(0 == m_WaitUntil_CmdRdy()){return 0;}

	// Timeout
	return -1;
}

int FNTYPE NexR_RobotServoOFF(void)
 {
	 // Initialize parameters
	 SharedData->b_rec_cmd = FALSE;
	 SharedData->cmd_type  = NER_SERVO_OFF_ALL;

	 // send command
	 SharedData->b_send_cmd = TRUE;

	 // check cmd is ready
	 if(0 == m_WaitUntil_CmdRdy()){return 0;}

	 // Timeout
	 return -1;
 }

int FNTYPE NexR_MovePtp(U16_T  type, 
	                      F64_T *target_data,
						  F64_T *max_vel,
						  F64_T *acc)
 {	 
	 // Initialize parameters
	 SharedData->b_rec_cmd  = FALSE;
	 SharedData->b_cmd_done = FALSE;
	 // assign cmd
	 if( type == 1)       SharedData->cmd_type = NER_MOVE_JOINT;
	 else if ( type == 2) SharedData->cmd_type = NER_MOVE_TCP;
	 else                 return -1;

	 // assign data
	 memcpy(SharedData->cmd_data.target_data,target_data,sizeof(F64_T)*6);
	 memcpy(SharedData->cmd_data.max_vel,max_vel,sizeof(F64_T)*6);
	 memcpy(SharedData->cmd_data.acc,acc,sizeof(F64_T)*6);

	 // send command
	 SharedData->b_send_cmd = TRUE;

	 // check cmd is ready
	 if(0 == m_WaitUntil_CmdRdy()){return 0;}

	 // Timeout
	 return -1;	 
 }

 int FNTYPE NexR_GetCmdDone(void)
 {
	return SharedData->b_cmd_done;
 }

 int FNTYPE NexR_ReSetDriveError(void)
 {
	 // Initialize parameters
	 SharedData->b_rec_cmd = FALSE;
	 SharedData->cmd_type  = NER_RESET_DRIVE_ERROR;

	 // send command
	 SharedData->b_send_cmd = TRUE;

	 // check cmd is ready
	 if(0 == m_WaitUntil_CmdRdy()){return 0;}

	 // Timeout
	 return -1;

 }

 int FNTYPE NexR_GetMasteringData(F64_T *masteringdata, U8_T *IsReverseMotor)
 {
	 // Initialize parameters
	 SharedData->b_rec_cmd = FALSE;
	 SharedData->cmd_type  = NER_GET_MASTERING_DATA;

	 // send command
	 SharedData->b_send_cmd = TRUE;

	 // check cmd is ready
	 if(0 == m_WaitUntil_CmdRdy())
	 {
		 for(int i=0; i<6;i++)
		 {
			 masteringdata[i] = SharedData->robot_data.robot_axis[i].mastering_data;
             if( SharedData->robot_data.robot_axis[i].isReverseMotor )
                 IsReverseMotor[i] = 1;
             else
                 IsReverseMotor[i] = 0;
		 }
		 return 0;
	 }

	 // Timeout
	 return -1;	 	  	  
 }

 int FNTYPE NexR_SetMasteringData(F64_T *masteringdata, U8_T *IsReverseMotor)
 {
	 for(int i=0; i<6;i++)
	 {
		 SharedData->robot_data.robot_axis[i].mastering_data = masteringdata[i];
         if( IsReverseMotor[i] == 1 )
             SharedData->robot_data.robot_axis[i].isReverseMotor = TRUE;
         else
             SharedData->robot_data.robot_axis[i].isReverseMotor = FALSE;
	 }	

	 // Initialize parameters
	 SharedData->b_rec_cmd = FALSE;
	 SharedData->cmd_type  = NER_SET_MASTERING_DATA;

	 // send command
	 SharedData->b_send_cmd = TRUE;

	 // check cmd is ready
	if(0 == m_WaitUntil_CmdRdy()){return 0;}

	 // Timeout
	 return -1;
 }

 int FNTYPE NexR_GetDIOSize(unsigned int DIO_Index,unsigned &inputinbyte,unsigned &outputinbyte)
 {
	 // check
	 if(DIO_Index >= SharedData->dio_count)
		 return -1;
	  
	 outputinbyte =  SharedData->dio_data[DIO_Index].OutSizeInByte;
	 inputinbyte  =  SharedData->dio_data[DIO_Index].InSizeInByte;

	 return 0;
 }

 int FNTYPE NexR_GetDIOCount(unsigned int &DIO_Cnt)
 {
	 DIO_Cnt = SharedData->dio_count;
	 return 0;
 }

 int FNTYPE NexR_SetDO(unsigned int DO_Index,unsigned int *output_data)
 {
	 //assign data
	 SharedData->cmd_data.cmd_dio_index = DO_Index;
	 SharedData->b_cmd_done = FALSE;
	 
	 for(int i=0;i<32;i++)
	 {
		 SharedData->cmd_data.Output[i] = (DIO_Command)output_data[i];
	 }
	 
	 // Initialize parameters
	 SharedData->b_rec_cmd = FALSE;
	 SharedData->cmd_type  = NER_SET_DO_DATA;
	  
	 // send command
	 SharedData->b_send_cmd = TRUE;
	  
	 // check cmd is ready
	 if(0 == m_WaitUntil_CmdRdy()){SharedData->b_cmd_done = TRUE;return 0;}

	 // Timeout
	 SharedData->b_cmd_done = TRUE;	
	 return -1;

	  
 }

 int FNTYPE NexR_GetDI(unsigned int DI_Index,unsigned int *input_data)
 {
	 // check
	 if(DI_Index >= SharedData->dio_count)
		 return -1;

	 memcpy(input_data, SharedData->dio_data[DI_Index].Input, sizeof(DIO_Command)*SharedData->dio_data[DI_Index].InSizeInByte*8);
	 
	 return 0;
 }

 int FNTYPE NexR_EmgStop(void)
 {	
	// Initialize parameters
	SharedData->b_rec_cmd = FALSE;
	SharedData->cmd_type  = NER_EMG_STOP;
	  
	// send command
	SharedData->b_send_cmd = TRUE;
	  
	// check cmd is ready
	if(0 == m_WaitUntil_CmdRdy()){return 0;}

	// Timeout
	SharedData->b_cmd_done = TRUE;	
	return -1;
 }

 int FNTYPE NexR_ResetSafetyAlarm(void)
 {
	 // Initialize parameters
	SharedData->b_rec_cmd = FALSE;
	SharedData->cmd_type  = NER_RESET_SAFETY_ALARM;
	  
	// send command
	SharedData->b_send_cmd = TRUE;
	  
	// check cmd is ready
	if(0 == m_WaitUntil_CmdRdy()){return 0;}

	// Timeout
	SharedData->b_cmd_done = TRUE;	
	return -1;
 }

 int FNTYPE NexR_UserDefined(void)
 {	
	// Initialize parameters	
	SharedData->cmd_type  = NER_USER_DEFINE;	  
	
	// send command
	SharedData->b_send_cmd = TRUE;
	
	return 0;
 }

  int FNTYPE NexR_ChangePTPVel(U8_T speed_ratio)
  {
	  // Initialize parameters	
	  SharedData->cmd_type  = NER_PTP_CHANGE_SPEED;	  
	
	  // Set data
	  SharedData->ptp_speed_ratio = speed_ratio;
	  
	  // send command
	  SharedData->b_send_cmd = TRUE;
	
	  return 0;
  }

  int FNTYPE NexR_ChangeOpMode(U8_T mode)
  {
	   // Initialize parameters	
	  SharedData->cmd_type  = NER_CHANGE_OP_MODE;	  
	
	  // Set data
	  SharedData->desire_OP_mode = mode;
	  
	  // send command
	  SharedData->b_send_cmd = TRUE;
	
	  return 0;
  }

  int FNTYPE NexR_ReInitializeDriverParameters(void)
  {
	   // Initialize parameters	
	  SharedData->cmd_type  = NER_INITIALIZE_PARAS;	  
	
	  // send command
	  SharedData->b_send_cmd = TRUE;
	
	  return 0;
  }

  int FNTYPE NexR_Robot_MoveLine(U8_T u8CmdType, F64_T *target_data,F64_T max_vel,F64_T acc)
  {
	  // Initialize parameters	
	  SharedData->cmd_type = NER_MOVE_LINE;
	  
	  // Set data
	  SharedData->cmd_data.line_data_type = u8CmdType;
	  memcpy(SharedData->cmd_data.target_data,target_data,sizeof(F64_T)*6);
	  SharedData->cmd_data.line_vel = max_vel;
	  SharedData->cmd_data.line_acc = acc;

	  // send command
	  SharedData->b_send_cmd = TRUE;
	
	  return 0;
  }

 /* local function */

 int m_WaitUntil_CmdRdy(void)
 {
	  int start_cnt = GetTickCount();
	  while((GetTickCount()-start_cnt)<=TimeOut)
	  {
		  if(SharedData->b_rec_cmd == TRUE)
		  {		
			  return 0;				 
		  }
		  Sleep(10);
	  }

	  // timeout
	  return -1;
 }


