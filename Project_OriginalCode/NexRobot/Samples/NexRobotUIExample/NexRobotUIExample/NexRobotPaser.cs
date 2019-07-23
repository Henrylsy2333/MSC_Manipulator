/******************************************************************************
	Building The Digital Infrastructure 
	(C) 2015 NEXCOM International Co., Ltd. All Rights Reserved.

    This file is the example of how to import NexRobot Interface C++ dll, and make 
    API for Using int C# Enviroment. It can be used only in Microsoft windows 
    system (win32 user mode).
      
*******************************************************************************/

using System;
using System.Collections;
using System.Text;
using System.Runtime.InteropServices;

namespace Source
{
    //=============================== internal used struct define ==================
    public struct NexRobotPos
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public int[] Axis_actpos;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public int[] Axis_actvel;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public double[] Axis_Data;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public double[] Axis_Vel;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public double[] Tcp;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public ushort[] Servo_Status;

    }


    class NexRobotPaser
    {
#if DEBUG
        public const string ROBOT_DLL = "NexRobotWind.dll";
        public const string ECM_DLL = "NexEcm.dll";        
        
#else
        public const string ROBOT_DLL = "NexRobotWin.dll";
        public const string ECM_DLL = "NexEcm.dll";
#endif

        //*******************************************************************************
        //  NexRobot-APIs define here
        //*******************************************************************************
        [DllImport(ROBOT_DLL, EntryPoint = "NexR_GetRobotPosition", CallingConvention = CallingConvention.StdCall)]
        public static extern void NexR_GetRobotPosition(ref NexRobotPos Robot_Pos);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_LinktoRobotKernel", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_LinktoRobotKernel();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_CloseRobotKernel", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_CloseRobotKernel();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_GetRobotKernelStatus", CallingConvention = CallingConvention.StdCall)]
        public static extern void NexR_GetRobotKernelStatus(ref int ret);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_RobotServoON", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_RobotServoON();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_RobotServoOFF", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_RobotServoOFF();        

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_MovePtp", CallingConvention = CallingConvention.StdCall)]
        public static extern void NexR_MovePtp(ushort type, double[] target_data, double[] max_vel, double[] acc);

        [DllImport(ECM_DLL, EntryPoint = "NEC_KillRtxApp")]
        public static extern int NEC_KillRtxApp(uint ProcessId);

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetRtMasterPorcessId")]
        public static extern int NEC_GetRtMasterPorcessId(ushort MasterId, ref uint pProcessID);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_GetCmdDone", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_GetCmdDone();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_ReSetDriveError", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_ReSetDriveError();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_GetMasteringData", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_GetMasteringData(double[] mastering_data, byte[] isReverseMotor);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_SetMasteringData", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_SetMasteringData(double[] mastering_data,byte[] isReverseMotor);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_SetDO", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_SetDIO(uint DO_Index, uint[] output_data);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_GetDI", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_GetDIO(uint DI_Index, uint[] input_data);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_GetDIOCount", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_GetDIOCount(ref uint DIO_Cnt);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_GetDIOSize", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_GetDIOSize(uint DIO_Index, ref uint inputinbyte, ref uint outputinbyte);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_EmgStop", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_EmgStop();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_ResetSafetyAlarm", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_ResetSafetyAlarm();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_UserDefined", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_UserDefined();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_ChangePTPVel", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_ChangePTPVel(byte speed_ratio);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_ChangeOpMode", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_ChangeOpMode(byte mode);

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_ReInitializeDriverParameters", CallingConvention = CallingConvention.StdCall)]
        public static extern int NexR_NER_ReInitializeDriverParameters();

        [DllImport(ROBOT_DLL, EntryPoint = "NexR_Robot_MoveLine", CallingConvention = CallingConvention.StdCall)]
        public static extern  int NexR_Robot_MoveLine(byte u8CmdType, double[] target_data,double max_vel,double acc);       
    }
}
