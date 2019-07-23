//////////////////////////////////////////////////////////////////
//
// UserRTApp.c - C file
//
// This file was generated using the RTX Application Wizard 
// for Visual Studio.  
//////////////////////////////////////////////////////////////////
    
#include "UserRTApp.h"
#include <windows.h>
#include <wchar.h>
#include <rtapi.h>
#include <stdio.h>
#include "NexRobotKernel.h"
#include "NexSharedMemory.h"
#include "NexRobotErrors.h"

/* global variables */
_NER_SHAREDMEM         *SharedData       = NULL;
static HANDLE			hDatamem		 = NULL;
bool                    g_terminate      = false;
bool                    g_run_userdefined = false;
int                     g_userdefinedcnt  = 0;
F64_T                   g_userdefinedPos  = 0;
F64_T                   g_userCmdVel      = 0; // deg/s
F64_T                   g_userdefinedVel  = 0; // deg/s
F64_T                   g_userdefinedaccT = 0; // s
I16_T                   g_UserTorque      = 0;


/* Local Function */
void __RtUserCyclicCallback( void *UserDataPtr );
void __ProcessNERCommand(void);
void __PrintfAlarm(int cnt);


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

	/* create shared memory */
	hDatamem = RtCreateSharedMemory(PAGE_READWRITE, 0, sizeof(_NER_SHAREDMEM), "NER_Shared_Space", (void**)&SharedData);
	if(hDatamem == NULL)
	{
		RtPrintf("RtCreateSharedMemory Failed\n");
		return;
	}	

	/* initialize */
	SharedData->b_robot_kernal_ready = FALSE;		


	/* Start NexRobotKernel */
	if(FALSE == NER_StartNexRobotKernel(__RtUserCyclicCallback
		                                ,NER_CYCLIC_POSITION // NER_CYCLIC_POSITION,NER_CYCLIC_VELOCITY,NER_CYCLIC_TORQUE
										,NER_DEBUG_MSG_LEVEL::NER_DEBUG_MSG_HIGH)
										) 
	{
		RtPrintf("NER_StartNexRobotKernel error\n");

		if(FALSE == NER_CloseNexRobotKernel())
			RtPrintf("NER_CloseNexRobotKernel error\n");
	    else 
			RtPrintf("NER_CloseNexRobotKernel succed\n");
	
    ExitProcess(0);
	}
	
	/* Read DIO data */	
	SharedData->dio_count = NER_Get_DIO_count();
	if(!NER_Get_DIO_Info(SharedData->dio_data)){RtPrintf("No DIO found in this procedure...\n");}
	else
	{
		RtPrintf("dio_count=%d,InSizeInByte=%d,\n",SharedData->dio_count,SharedData->dio_data[0].InSizeInByte);
		RtPrintf("dio_count=%d,OutSizeInByte=%d,\n",SharedData->dio_count,SharedData->dio_data[0].OutSizeInByte);

		if(SharedData->dio_count == 2)
		{
			RtPrintf("dio_count=%d,InSizeInByte=%d,\n",SharedData->dio_count,SharedData->dio_data[1].InSizeInByte);
		    RtPrintf("dio_count=%d,OutSizeInByte=%d,\n",SharedData->dio_count,SharedData->dio_data[1].OutSizeInByte);
		}
	}

	/* Read Robot Mastering Data, only work after calling NER_StartNexRobotKernel */
	double Mastering_data[6]; // currently only support 6R
    BOOL_T IsReverseMotordata[6] = {FALSE}; // currently only support 6R
	NER_ROBOT_TYPE now_type;
	NER_GetRobotMasteringData(Mastering_data, IsReverseMotordata, now_type);
	switch(now_type)
	{
	case NER_6R:
		for( int i=0; i < 6; i++)
		{
			SharedData->robot_data.robot_axis[i].mastering_data = Mastering_data[i];
            SharedData->robot_data.robot_axis[i].isReverseMotor = IsReverseMotordata[i];
			//RtPrintf("A%d = %d.%d\n",i+1,int(SharedData->robot_data.robot_axis[i].mastering_data),int((SharedData->robot_data.robot_axis[i].mastering_data-int(SharedData->robot_data.robot_axis[i].mastering_data))*1000.0));
		}
		break;
	}

	SharedData->b_robot_kernal_ready = TRUE;

	while(!g_terminate)
	{
		if(SharedData->b_send_cmd == TRUE) //receive cmd from win32 system
		{			
			// Reset
			SharedData->b_send_cmd = FALSE;

			// Process Receive Command Here
		    __ProcessNERCommand();

		    // Set receive command flag to true
		    SharedData->b_rec_cmd = TRUE;
		}

		Sleep(4); // cmd polling cycle set as 4ms
		
	}
	
	SharedData->b_robot_kernal_ready = FALSE;
	
	if(FALSE == NER_CloseNexRobotKernel())
		RtPrintf("NER_CloseNexRobotKernel error\n");
	else 
		RtPrintf("NER_CloseNexRobotKernel succed\n");
	
    ExitProcess(0);
}

void __RtUserCyclicCallback( void *UserDataPtr )
{
	static int        swCnt           = 0;
	static I16_T      torque          = 0;
	int               i               = 0;
	//_NER_ROBOT_AXIS  *Robot_Axis      = (_NER_ROBOT_AXIS *)UserDataPtr;
	_NER_ROBOT_DATA   *Robot_Data     = (_NER_ROBOT_DATA*)UserDataPtr;
	BOOL              IS_ALL_SERVO_ON = FALSE;
	NER_ROBOT_AXIS_CONTROL_MODE mode;

	// Read Servo Status
	IS_ALL_SERVO_ON = NER_RobotServoOnReady();
	
	for( i=0; i<6; i++)
	{
		// Update actual position,robot deg and tcp to sharedmemory 
		SharedData->robot_data.robot_axis[i].actual_position = Robot_Data->robot_axis[i].actual_position;
		SharedData->robot_data.robot_axis[i].actual_velocity = Robot_Data->robot_axis[i].actual_velocity;
		SharedData->robot_data.robot_axis[i].robot_deg       = Robot_Data->robot_axis[i].robot_deg;
		SharedData->robot_data.robot_axis[i].robot_vel       = Robot_Data->robot_axis[i].robot_vel;
		SharedData->robot_data.tcp_data[i]                   = Robot_Data->tcp_data[i];
		
		//Update Servo Status to sharedmemory    
		if(IS_ALL_SERVO_ON==TRUE){SharedData->robot_data.robot_axis[i].state  = servo_on;}
		else                     {SharedData->robot_data.robot_axis[i].state  = servo_off;}   
	}

	// Update DI data
	NER_GetDI(0, SharedData->dio_data[0].Input);

	// Read cmdDone status
	SharedData->b_cmd_done = NER_Robot_MotDone();

	// Printf Alarm
	__PrintfAlarm(swCnt);

	/* if servo on */
	if(TRUE == IS_ALL_SERVO_ON)
	{
		if(g_run_userdefined)
		{			
			NER_GetCurrentCtrlMode(mode);
			switch(mode)
			{
			case NER_CYCLIC_POSITION:
				{
					F64_T TarPos = g_userdefinedPos + F64_T(g_userdefinedcnt)*0.001;
					NER_SetTargetPosition(0,TarPos);
					//NER_SetTargetPosition(5,0);

					/*if(swCnt%500==0)
					{
						RtPrintf("TarPos=%d.%d,g_userdefinedcnt=%d\n",int(TarPos),int((TarPos-int(TarPos))*1000),g_userdefinedcnt);					
					}*/

					if(g_userdefinedcnt > 1000)
						g_run_userdefined = false;
				}
				break;
			case NER_CYCLIC_VELOCITY:

				// acc
				if(g_userdefinedcnt <= int(g_userdefinedaccT*1.0*1000.0))
				{
					g_userCmdVel = 0 + (F64_T(g_userdefinedcnt)*0.001)*g_userdefinedVel/g_userdefinedaccT;
				}
				// constant velocity 
				else if(g_userdefinedcnt <= int(g_userdefinedaccT*2.0*1000.0))
				{
					g_userCmdVel = g_userdefinedVel;
				}
				// dec
				else if(g_userdefinedcnt <= int(g_userdefinedaccT*3.0*1000.0))
				{
					g_userCmdVel = g_userdefinedVel - ((F64_T(g_userdefinedcnt)*0.001)-g_userdefinedaccT*2.0)*g_userdefinedVel/g_userdefinedaccT;				
				}

				if(swCnt%500==0)
				{
					RtPrintf("g_userCmdVel=%d,g_userdefinedcnt=%d,swCnt=%d\n",g_userCmdVel,g_userdefinedcnt,swCnt);					
				}

				NER_SetTargetVelocity(0,g_userCmdVel);

				if(g_userdefinedcnt > int(g_userdefinedaccT*3.0*1000.0))
				{					
					g_run_userdefined = false;
				}

				break;
			case NER_CYCLIC_TORQUE:
				NER_SetTargetTorque(0,g_UserTorque);
				//NER_SetTargetTorque(1,g_UserTorque);
				//NER_SetTargetTorque(2,g_UserTorque);
				//NER_SetTargetTorque(3,g_UserTorque);
				//NER_SetTargetTorque(4,g_UserTorque);
				//NER_SetTargetTorque(5,g_UserTorque);

				if(swCnt%500==0)
					RtPrintf("Set Torque = %d\n",g_UserTorque);
				
				if(g_userdefinedcnt > 10000)
				{				
					g_run_userdefined = false;
					NER_SetTargetTorque(0,0);
					NER_SetTargetTorque(1,0);
					NER_SetTargetTorque(2,0);
					NER_SetTargetTorque(3,0);
					NER_SetTargetTorque(4,0);
					NER_SetTargetTorque(5,0);					
				}
				break;
			}
			g_userdefinedcnt++;
		}// end if(g_run_userdefined)
			  

		//NER_SetTargetTorque(0,torque);

		//if(swCnt%1000==0)
		//{
			//RtPrintf("actual_position=%d,torque=%d\n",Robot_Data->robot_axis[0].actual_position,torque);					
		//}
		/*if(swCnt%50==0)
		torque++;*/		
	}
	

	swCnt++;
}
void __ProcessNERCommand(void)
{
	F64_T vel_value[6];
	I16_T tor_value[6];

	//RtPrintf("SharedData->cmd_type=%d\n",SharedData->cmd_type);

	switch(SharedData->cmd_type)
	{
	case NER_CLOSE_ROBOT_KERNEL:
		g_terminate = true;
		break;
	case NER_SERVO_ON_ALL:
		NER_ActivateServoOn();
		break;
    case NER_SERVO_OFF_ALL:
		NER_ActivateServoOff();
		break;
	case NER_MOVE_JOINT:
	case NER_MOVE_TCP:
		NER_Robot_MovePTP((U8_T)SharedData->cmd_type, SharedData->cmd_data.target_data,SharedData->cmd_data.max_vel,SharedData->cmd_data.acc);
		break;
	case NER_RESET_DRIVE_ERROR:
		NER_Robot_ReSet_Drive_Error();
		break;
	case NER_SET_MASTERING_DATA:
		{
			F64_T MasteringData[6];
            BOOL_T IsReverseMotordata[6] = {FALSE}; // currently only support 6R
			for(int i=0;i<6;i++)
			{
				MasteringData[i] = SharedData->robot_data.robot_axis[i].mastering_data;
                IsReverseMotordata[i] = SharedData->robot_data.robot_axis[i].isReverseMotor;
			}
			NER_SetRobotMasteringData(MasteringData, IsReverseMotordata);
		}
		break;
	case NER_GET_MASTERING_DATA:
		{
			F64_T MasteringData[6];
            BOOL_T IsReverseMotordata[6] = {FALSE}; // currently only support 6R
			NER_ROBOT_TYPE type;
			NER_GetRobotMasteringData(MasteringData, IsReverseMotordata, type);

			for(int i=0;i<6;i++)
			{
				SharedData->robot_data.robot_axis[i].mastering_data = MasteringData[i];
                SharedData->robot_data.robot_axis[i].isReverseMotor = IsReverseMotordata[i];
            }
		}
		break;
	case NER_SET_DO_DATA:
		{
			if(!NER_SetDO(SharedData->cmd_data.cmd_dio_index,SharedData->cmd_data.Output))
				RtPrintf("NER_SetDO failed\n");
		}
		break;
	case NER_EMG_STOP:
		{
			NER_Robot_EmergencyStop();
		}
		break;
	case NER_RESET_SAFETY_ALARM:
		{
			if(FALSE == NER_ResetSafetyAlarm())
				RtPrintf("Reset Safety Alarm Failed!!!\n");
		}
		break;	
	case NER_USER_DEFINE:
		{			
			if(g_run_userdefined == true)
			{
				RtPrintf("Already Running User Define Command..\n");
				break;
			}

			// Initialize
			g_userdefinedcnt  = 0;

			// CSP example			
			g_userdefinedPos  = SharedData->robot_data.robot_axis[0].robot_deg;
			
			// CSV example			
			g_userCmdVel      =   0.0;  // deg/s
			g_userdefinedVel  =  20.0;  // deg/s
            g_userdefinedaccT =   0.5;  //   s

			// CST example
			g_UserTorque      =  100;  // 0.1% (The Motor rated torque is 100%)
	
			
			// Rdy for user defined command
			g_run_userdefined = true;

			//RtPrintf("NER_USER_DEFINE\n");
		}
		break;
	case NER_PTP_CHANGE_SPEED:
		NER_Robot_ChangeSpdRatio(SharedData->ptp_speed_ratio);
		break;
	case NER_CHANGE_OP_MODE:
		switch(SharedData->desire_OP_mode)
		{
		case NER_OP_MODE_CYCLIC_POSITION:
			RtPrintf("Change To CSP mode\n");
			NER_Robot_Change_To_CSP_Mode();
			break;
		case NER_OP_MODE_CYCLIC_VELOCITY:			
			for(int i=0;i<6;i++)
				vel_value[i] = 0;
			RtPrintf("Change To CSV mode\n");
			NER_Robot_Change_To_CSV_Mode(vel_value);
			break;
		case NER_OP_MODE_CYCLIC_TORQUE:
			for(int i=0;i<6;i++)
				tor_value[i] = 0;
			RtPrintf("Change To CST mode\n");
			NER_Robot_Change_To_CST_Mode(tor_value);
			break;
		}
		break;
	case NER_INITIALIZE_PARAS:
		NER_ReInitializeDriverParameters();
		break;
	case NER_MOVE_LINE:
		NER_Robot_MoveLine(SharedData->cmd_data.line_data_type,SharedData->cmd_data.target_data,SharedData->cmd_data.line_vel,SharedData->cmd_data.line_acc);
		break;
	default:
		RtPrintf("Undefine Command\n");
	}
}
void __PrintfAlarm(int cnt)
{
	I32_T i             = 0;
	I32_T ret           = NER_ERR_NOERR;
	U8_T  Err_Driver_NO = 0;

	// Get Robot Alarm Code
	ret = NER_Robot_GetAlarmCode();

	if(NER_ERR_DRIVER_HAS_ALARM == ret) // at least one driver has fault
	{
		if(cnt%500==0)
			RtPrintf("NER_ERR_DRIVER_HAS_ALARM\n");

		NER_Robot_Get_Error_Driver_NO(Err_Driver_NO);
		for( i = 0 ; i < 6; i++ )
		{
			U32_T temp = 0;
			temp = Err_Driver_NO >> i;
			if(temp & 1)
			{
				if(cnt%500==0)
					RtPrintf("Axis %d has fault\n",i+1);
			}
		}
	}
	else if(NER_ERR_EMG_STOP == ret) // EMG STOP
	{
		if(cnt%500==0)
			RtPrintf("NER_ERR_EMG_STOP\n");
	}
	else if(NER_ERR_NOERR == ret)
	{
		// no error
		/*if(cnt%500==0)
			RtPrintf("NER_ERR_NOERR\n");*/		
	}

}