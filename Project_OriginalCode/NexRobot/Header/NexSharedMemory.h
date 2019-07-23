#ifndef __NEX_SHAREDMEM_H
#define __NEX_SHAREDMEM_H

#ifdef __cplusplus
  extern "C" {
#endif 

#include "NexRobotKernel.h"

typedef enum
{
    NER_CMD_NONE            =  0x00,
	NER_CLOSE_ROBOT_KERNEL  =  0x01,
	NER_SERVO_ON_ALL        =  0x02, 
	NER_SERVO_OFF_ALL       =  0x03, 
    NER_MOVE_JOINT          =  0x04,
    NER_MOVE_TCP            =  0x05,
	NER_RESET_DRIVE_ERROR   =  0x06,
    NER_SET_MASTERING_DATA  =  0x07,
    NER_GET_MASTERING_DATA  =  0x08,
	NER_SET_DO_DATA         =  0x09,
	NER_EMG_STOP            =  0x0A,
	NER_RESET_SAFETY_ALARM  =  0x0B,	
	NER_USER_DEFINE         =  0x0C,
	NER_PTP_CHANGE_SPEED    =  0x0D,
	NER_CHANGE_OP_MODE      =  0x0E,
	NER_INITIALIZE_PARAS    =  0x0F,
	NER_MOVE_LINE           =  0x10,
}_NER_ROBOT_CMD;	  

typedef enum
{
	NER_OP_MODE_CYCLIC_POSITION  = 8,
	NER_OP_MODE_CYCLIC_VELOCITY  = 9,
	NER_OP_MODE_CYCLIC_TORQUE    = 10,
}_NER_OP_MODE;


typedef struct
{
    F64_T        target_data[6];
    F64_T        max_vel[6];
    F64_T        acc[6];
    U32_T        cmd_dio_index;
    DIO_Command  Output[32]; // currently only support 32 out	

	U8_T         line_data_type;
	F64_T        line_vel;
	F64_T        line_acc;
}_NER_ROBOT_CMD_DATA;

typedef struct 
{
	int                  b_robot_kernal_ready;
	BOOL                 b_send_cmd;
	BOOL                 b_rec_cmd;
	BOOL                 b_cmd_done;
	_NER_ROBOT_CMD       cmd_type;    
    _NER_ROBOT_CMD_DATA  cmd_data;
	_NER_ROBOT_DATA      robot_data;
	U32_T                dio_count;   
	_NER_ROBOT_DIO       dio_data[64]; // currently only support max 64 DIO slaves	
	U8_T                 ptp_speed_ratio;
	U8_T                 desire_OP_mode;

	

}_NER_SHAREDMEM;


#ifdef __cplusplus
  }
#endif 

#endif