/******************************************************************************
	Building The Digital Infrastructure 
	(C) 2015 NEXCOM International Co., Ltd. All Rights Reserved.

    This header is the API of NexROBO. It can be used only in RTX 2012.
      
*******************************************************************************/

#ifndef __NEXROBOT_H
#define __NEXROBOT_H

#ifdef __cplusplus
  extern "C" {
#endif 

#include <Windows.h>
#include "nex_type.h"

struct _RT_WAIT_Cmd
{
	BOOL wait_dio;
	F64_T sec;
	U8_T DI_No;
	BOOL DI_Status;
	U32_T wait_time_count;
};

typedef enum _NER_SERVO_STATE
{
    servo_on         = 0x00,
    servo_off        = 0x01,
	servo_error      = 0x02,
} NER_SERVO_STATE;

typedef enum _NER_ROBOT_TYPE
{
    NER_6R		= 0x00,
    NER_DELTA3	= 0x01,
	NER_DELTA4	= 0x02,
	NER_SCARA	= 0x03,
} NER_ROBOT_TYPE;

typedef enum _NER_MACHINE_TYPE
{
	NER_EDU		= 0x04,
} NER_MACHINE_TYPE;

typedef enum _NER_ROBOT_AXIS_CONTROL_MODE
{
	NER_CYCLIC_POSITION   = 0x08,
	NER_CYCLIC_VELOCITY   = 0x09,
	NER_CYCLIC_TORQUE     = 0x0A,    
}NER_ROBOT_AXIS_CONTROL_MODE;

typedef enum _NER_DEBUG_MSG_LEVEL
{
	NER_DEBUG_MSG_LOW    = 0x00,
	NER_DEBUG_MSG_NORMAL = 0x01,
	NER_DEBUG_MSG_HIGH   = 0x02,    
}NER_DEBUG_MSG_LEVEL;

typedef enum _DIO_Command
{
	NER_DIO_OFF    = 0,
	NER_DIO_ON     = 1,
} DIO_Command;

typedef struct 
{
	_NER_SERVO_STATE state;
	I32_T            actual_position;	
	I32_T            actual_velocity;
	I16_T            actual_torque;
	F64_T            robot_deg;
	F64_T            robot_vel;
	F64_T            mastering_data;
    BOOL_T           isReverseMotor;
}_NER_ROBOT_AXIS;

typedef struct 
{
	U32_T            InSizeInByte;
	U32_T            OutSizeInByte;
	DIO_Command      Input[32];  // currently only support 32 in
	DIO_Command      Output[32]; // currently only support 32 out	
}_NER_ROBOT_DIO;

typedef struct 
{
	U32_T            InSizeInByte;
	U32_T            OutSizeInByte;
	I16_T			 Input[8];  // currently only support 8 channel
	U16_T			 Output[8]; // currently only support 8 channel
	U8_T			 Channel_Num; //total channel number in a slave
}_NER_ROBOT_AIO;

typedef struct
{
	U8_T	StatusByte;
	U16_T	CountValue;
	U8_T	DIG_INPUT;
	U16_T	LatchValue;
}MODULE_750631_IN;
typedef struct
{
	U8_T	ControlByte;
	U16_T	SetpointValue;
}MODULE_750631_OUT;
typedef struct 
{
	MODULE_750631_IN	In;
	MODULE_750631_OUT	Out;
}MODULE_750631;

typedef struct
{
	MODULE_750631		Module_750631[2];
}_NER_ROBOT_WAGO;

typedef struct 
{
	_NER_ROBOT_AXIS  robot_axis[6];
	F64_T            tcp_data[6];	
	U32_T            DIO_Count;
	U32_T            AIO_Count;
	BOOL_T			 DIO_IsWago;
	_NER_ROBOT_DIO	 dIO[64];
	_NER_ROBOT_AIO	 aIO[64];
	_NER_ROBOT_WAGO	 Wago[64];//currently support 750-631
}_NER_ROBOT_DATA;

// For RT application
// Realtime callback functions define
typedef void (*NER_RtCyclicCallback)( void *UserDataPtr );	// For EtherCAT cyclic process.


//*************************************
//*** Initialization Functions ***
//*************************************
// current only support torque mode
BOOL NER_StartNexRobotKernel(NER_RtCyclicCallback        __UserCyclicCallback,	                         
							 NER_ROBOT_AXIS_CONTROL_MODE ctrl_mode,
							 NER_DEBUG_MSG_LEVEL         debug_level = NER_DEBUG_MSG_HIGH);

BOOL NER_CloseNexRobotKernel();
BOOL NER_GetRobotMasteringData(F64_T *MasteringData, BOOL_T *IsReverseMotor, NER_ROBOT_TYPE &type);
BOOL NER_SetRobotMasteringData(F64_T *MasteringData, BOOL_T *IsReverseMotor);
U32_T NER_GetNexRobotKernelVersion();
BOOL  NER_ReInitializeDriverParameters();

//*********************************************
//*** Robot Servo Basic Operation Functions ***
//*********************************************
BOOL NER_ActivateServoOn();           // Activate to ServoOn  state of all robot axis (the external axis will not be activated to ServoOn  state)
BOOL NER_ActivateServoOff();          // Activate to ServoOff state of all robot axis (the external axis will not be activated to ServoOff state)

BOOL NER_RobotServoOnReady(); /* returns:
								 TRUE  - all robot axis are at ServoOn state, 
                                 False - at least one of robot axis is not at ServoOn state ( ServoOff or ServoError )
							  */
BOOL NER_Robot_ReSet_Drive_Error();
BOOL NER_Robot_Get_Error_Driver_NO(U8_T &AXIS_Number);


//***************************************
//*** Robot Basic Operation Functions ***
//***************************************
BOOL     NER_Robot_MovePTP(U8_T u8CmdType, F64_T *target_data,F64_T *max_vel,F64_T *acc);
BOOL     NER_Robot_ChangeSpdRatio(U8_T speed_ratio);
RTN_ERR  NER_Robot_MoveLine(U8_T u8CmdType, F64_T *target_data,F64_T max_vel,F64_T acc);
BOOL     NER_Robot_EmergencyStop();
BOOL     NER_Robot_MotDone();
I32_T    NER_Robot_GetAlarmCode();

//*************************************
//*** User Mode Operation Functions ***
//*************************************
BOOL NER_SetTargetPosition(U16_T Robot_Axis_ind,F64_T t_Position);
BOOL NER_SetTargetVelocity(U16_T Robot_Axis_ind,F64_T t_Veloicty);
BOOL NER_SetTargetTorque(U16_T Robot_Axis_ind,I16_T t_Torque);
BOOL NER_ResetSafetyAlarm();
BOOL NER_GetCurrentCtrlMode(NER_ROBOT_AXIS_CONTROL_MODE &mode);
BOOL NER_Robot_Change_To_CSP_Mode();
BOOL NER_Robot_Change_To_CSV_Mode(F64_T *vel_value); // vel_value : Initial velocity while changing to CSV mode (unit : deg/s)
BOOL NER_Robot_Change_To_CST_Mode(I16_T *tor_value); // vel_value : Initial velocity while changing to CSV mode (unit : 0.1% of rated torque)

//***************************************
//*** Digital I/O Operation Functions ***
//***************************************
U32_T NER_Get_DIO_count();
BOOL  NER_Get_DIO_Info(_NER_ROBOT_DIO *dio_data);
BOOL  NER_SetDO(U32_T DO_index,DIO_Command *Output_data);
BOOL  NER_GetDI(U32_T DI_index,DIO_Command *Input_data);

//***************************************
//*** Analog I/O Operation Functions ***
//***************************************
U32_T NER_Get_AIO_count();
BOOL  NER_Get_AIO_Info(_NER_ROBOT_AIO *aio_data);


#ifdef __cplusplus
  }
#endif 

#endif