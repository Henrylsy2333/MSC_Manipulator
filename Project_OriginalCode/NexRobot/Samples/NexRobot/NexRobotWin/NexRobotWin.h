/******************************************************************************
	Building The Digital Infrastructure 
	(C) 2015 NEXCOM International Co., Ltd. All Rights Reserved.

    This header is the interface of Nexcom Robot Controller. It can be used only
	in Microsoft windows system (win32 user mode).
      
*******************************************************************************/

#ifndef __NEX_ROBOT_H
#define __NEX_ROBOT_H

#define FNTYPE __declspec(dllexport) __stdcall

#include "nex_type.h"

#ifdef __cplusplus
  extern "C" {
#endif 

typedef struct 
{
	I32_T Axis_actpos[7];  // Robot joint data(encoder cnt)	
	I32_T Axis_actvel[7];  // Robot joint data(encoder cnt/s)	
	F64_T Axis_Data[7];    // Robot joint data(deg)	
	F64_T Axis_Vel[7];     // Robot joint velocity(deg/s)	
	F64_T Tcp[6];
	U16_T Servo_Status[7]; // Robot joint servo status
}NexRobotPos;

//#ifdef WIN32
//U32_T FNTYPE NexR_GetDllVersion();  
//#endif

/*** Functions related to Robot Control***/
 
int  FNTYPE NexR_LinktoRobotKernel(void);
void FNTYPE NexR_GetRobotKernelStatus(int &ret);
int  FNTYPE NexR_CloseRobotKernel(void);

// Get Robot Position(mm), Orientation(Euler ZYX,deg) and joint data(deg);
 void FNTYPE NexR_GetRobotPosition(NexRobotPos &Robot_Pos);

 int FNTYPE NexR_RobotServoON(void);
 int FNTYPE NexR_RobotServoOFF(void);
 
 // type 1 : MoveJoint, type 2 : MoveTCP
 int FNTYPE NexR_MovePtp(U16_T  type, 
	                     F64_T *target_data,
						 F64_T *max_vel,
						 F64_T *acc); 
 
 int FNTYPE NexR_GetCmdDone(void);

 int FNTYPE NexR_ReSetDriveError(void);

 int FNTYPE NexR_GetMasteringData(F64_T *masteringdata, U8_T *IsReverseMotor);

 int FNTYPE NexR_SetMasteringData(F64_T *masteringdata, U8_T *IsReverseMotor);

 int FNTYPE NexR_SetDO(unsigned int DO_Index,unsigned int *output_data);

 int FNTYPE NexR_GetDI(unsigned int DI_Index,unsigned int *input_data);

 int FNTYPE NexR_GetDIOCount(unsigned int &DIO_Cnt);
 
 int FNTYPE NexR_GetDIOSize(unsigned int DIO_Index,unsigned &inputinbyte,unsigned &outputinbyte);

 int FNTYPE NexR_EmgStop(void);

 int FNTYPE NexR_ResetSafetyAlarm(void);

 int FNTYPE NexR_UserDefined(void);

 int FNTYPE NexR_ChangePTPVel(U8_T speed_ratio);

 int FNTYPE NexR_ChangeOpMode(U8_T mode);

 int FNTYPE NexR_ReInitializeDriverParameters(void);

 int FNTYPE NexR_Robot_MoveLine(U8_T u8CmdType, F64_T *target_data,F64_T max_vel,F64_T acc);
 
#ifdef __cplusplus
  }
#endif 

#endif

