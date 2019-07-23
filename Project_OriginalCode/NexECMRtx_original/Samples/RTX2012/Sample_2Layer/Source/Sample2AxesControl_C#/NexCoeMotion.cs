using System;
using System.Collections;
using System.Text;
using System.Runtime.InteropServices;

namespace Source
{    
    class NexCoeMotion
    {         
        //typedef void* CANAxis_T; 
        //#define CAN_ALL_AXES     ((CANAxis_T)(-1))
        
        public const string ECM_DLL = "NexEcm.dll";      

        //
        // CoE CANOpen Profile 402 for servo control

        [StructLayout(LayoutKind.Explicit, CharSet = CharSet.Ansi)]
        public struct EcCiA402AxisMapInfo_T
        {
            [FieldOffset(0), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort TypeOfSlave;
            [FieldOffset(2), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort SlaveAddr;
            [FieldOffset(4), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort SlaveSlotNum;
            [FieldOffset(6), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort Reserved;
            [FieldOffset(8), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort CoeObjectOffset;
            [FieldOffset(10), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort pdoMapOffset;
            [FieldOffset(12), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort MinRxPdoIndex;
            [FieldOffset(14), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort MaxRxPdoIndex;
            [FieldOffset(16), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort MinTxPdoIndex;
            [FieldOffset(18), MarshalAs(UnmanagedType.U2, SizeConst = 2)]
            public ushort MaxTxPdoIndex;
        }

        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402Reset")]
        public static extern int NEC_CoE402Reset();
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402lose")]
        public static extern int NEC_CoE402Close();
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetAxisId")]
        public static extern int NEC_CoE402GetAxisId( ushort MasterId, ushort SlaveAddr, ref uint pAxis );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetAxisIdEx")]
        public static extern int NEC_CoE402GetAxisIdEx(ushort MasterId, ref EcCiA402AxisMapInfo_T pInfo, ref uint pAxis);
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetDefaultMapInfo")]
        public static extern int NEC_CoE402GetDefaultMapInfo(ushort TypeOfSlave, ushort SlaveAddr, ref EcCiA402AxisMapInfo_T pInfo);

        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402ResetPdoMapping")]
        public static extern int NEC_CoE402ResetPdoMapping(uint Axis );  // support CAN_ALL_AXES
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402AddPdoMapping")]
        public static extern int NEC_CoE402AddPdoMapping(uint Axis, ushort Type, ushort CANIndex, byte CANSubIndex, byte OffsetOfByte, byte LenOfByte );  // support CAN_ALL_AXES
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402UpdatePdoMapping")]
        public static extern int NEC_CoE402UpdatePdoMapping(uint Axis );  // support CAN_ALL_AXES
        // State control functions
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402CyclicProcess")]
        public static extern int NEC_CoE402CyclicProcess(); // Callback 
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetSlaveProcessCountPreCycle")]
        public static extern int NEC_CoE402SetSlaveProcessCountPreCycle( ushort SlaveCount );    // Callback ok
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetCtrlWord")]
        public static extern int NEC_CoE402SetCtrlWord(uint Axis, ushort CtrlInBit );      // Callback ok (PDO mapped only)
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetCtrlWord")]
        public static extern int NEC_CoE402GetCtrlWord(uint Axis, ref ushort CtrlInBit);     // Callback ok (PDO mapped only)
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetStatusWord")]
        public static extern int NEC_CoE402GetStatusWord(uint Axis, ref ushort StatusInBit ); // Callback ok (PDO mapped only)

        // State for CiA402 
        public static int COE_STA_DISABLE =               (0);  // ServoOff
        public static int OE_STA_READY_TO_SWITCH_ON =     (1);
        public static int COE_STA_SWITCH_ON =             (2);
        public static int COE_STA_OPERATION_ENABLE =      (3);  // ServoOn
        public static int COE_STA_QUICK_STOP_ACTIVE =     (4);  
        public static int COE_STA_FAULT =                 (5);  // Error, Servo Internal
        public static int COE_STA_FAULT_REACTION_ACTIVE = (6);  // Error, Servo Internal
        public static int MAX_COE_STA =                   (7);
        public static int COE_STA_UNKNOWN =               (0xFF);

        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402ChangeState")]
        public static extern int NEC_CoE402ChangeState(uint Axis, ushort TargetState, int TimeoutMs ); // CAN_ALL_AXES support
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetState")]
        public static extern int NEC_CoE402SetState(uint Axis, ushort State );                         // Callback ok,  CAN_ALL_AXES support
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetState")]
        public static extern int NEC_CoE402GetState(uint Axis, ref ushort State );                     // Callback ok
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402FaultReset")]
        public static extern int NEC_CoE402FaultReset(uint Axis, int TimeoutMs );                 // CAN_ALL_AXES support
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402ServoOn")]
        public static extern int NEC_CoE402ServoOn(uint Axis, ushort OnOff );                         // 0:ServoOff, 1:ServoOn; CAN_ALL_AXES support
        
        // CoE Mode of operation
        public static int CiA402_OP_MODE_PROFILE_POSITION =      (1);
        public static int CiA402_OP_MODE_PROFILE_VELOCITY =      (3);
        public static int CiA402_OP_MODE_TORQUE_PROFILE  =       (4);
        public static int CiA402_OP_MODE_HOMING =                (6);
        public static int CiA402_OP_MODE_INTERPOLATED_POSITION = (7);
        public static int CiA402_OP_MODE_CYCLIC_POSITION =       (8);
        public static int CiA402_OP_MODE_CYCLIC_VELOCITY =       (9);
        public static int CiA402_OP_MODE_CYCLIC_TORQUE =         (10);

        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetOperationMode")]
        public static extern int NEC_CoE402SetOperationMode(uint Axis , char MotionMode, int CheckTimeoutMs );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetOperationModeDisplay")]
        public static extern int NEC_CoE402GetOperationModeDisplay(uint Axis, ref char MotionMode );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetParameter")]
        public static extern int NEC_CoE402SetParameter(uint Axis, ushort Index, byte SubIndex, byte LenOfByte, int Value ); 
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetParameter")]
        public static extern int NEC_CoE402GetParameter(uint Axis, ushort Index, byte SubIndex, byte LenOfByte, ref uint pRetValue );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetActualPosition")]
        public static extern int NEC_CoE402GetActualPosition( uint Axis, ref int Position );  // Return motor actual position (0x6064)
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetTargetPosition")]
        public static extern int NEC_CoE402SetTargetPosition( uint Axis, int TargetPos );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402GetTargetPosition")]
        public static extern int NEC_CoE402GetTargetPosition( uint Axis, ref int TargetPos );

        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetQuickStopDec")]
        public static extern int NEC_CoE402SetQuickStopDec(uint Axis, uint QuickStopDec );    // (0x6085)
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetSoftPosLimit")]
        public static extern int NEC_CoE402SetSoftPosLimit(uint Axis, uint MinPeteeositionLimit, int MaxPositionLimit); // (0x607D) 
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402SetMaxVelLimit")]
        public static extern int NEC_CoE402SetMaxVelLimit(uint Axis, uint MaxVelocityLimit ); // (0x607F)

        // Operation mode: Profile Position mode
        public static uint OPT_ABS = 0x00000000; // Absolution position
        public static uint OPT_REL = 0x00000040; // Releative distance
        public static uint OPT_WMC = 0x00010000; // Wait move complete
        public static uint OPT_IMV = 0x10000000; // Ignore MaxVel
        public static uint OPT_IAC = 0x20000000; // Ignore Acc
        public static uint OPT_IDC = 0x40000000; // Ignore Dec
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402Ptp")]
        public static extern int NEC_CoE402Ptp(uint Axis, uint Option, int TargetPos );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402PtpV")]
        public static extern int NEC_CoE402PtpV(uint Axis, uint Option, int TargetPos, uint MaxVel );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402PtpA")]
        public static extern int NEC_CoE402PtpA(uint Axis, uint Option, int TargetPos, uint MaxVel, uint Acc, uint Dec );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402WaitTargetReached")]
        public static extern int NEC_CoE402WaitTargetReached(int Axis );

        // Operation mode: Profile Velocity mode
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402Jog")]
        public static extern int NEC_CoE402Jog(uint Axis, uint Option, int MaxVel );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402JogA")]
        public static extern int NEC_CoE402JogA(uint Axis, uint Option, int MaxVel, uint Acc, uint Dec );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402Halt")]
        public static extern int NEC_CoE402Halt(uint Axis, uint OnOff  );

        // Operation mode: Homing
        public static uint OPT_MTD = 0x08000000;  // Ignore Method
        // #define OPT_IMV 0x10000000 // Ignore MaxVel
        // #define OPT_IAC 0x20000000 // Ignore Acc
        public static uint OPT_IZV = 0x40000000;  // Ignore ZeroVel
        public static uint OPT_IOF = 0x80000000;  // Ignore Offset
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402Home")]
        public static extern int NEC_CoE402Home( int Axis, uint Option ); // Start home move
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402HomeEx")]
        public static extern int NEC_CoE402HomeEx( uint Axis, uint Option, char Method, int Offset, uint MaxVel, uint ZeroVel, uint Acc );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402WaitHomeFinished")]
        public static extern int NEC_CoE402WaitHomeFinished(int Axis ); 

        //*******************************************************************************
        // Reserved functions.
        //********************************************************************************
        public static uint CW_HALT =                 0x0100;  // Halt
        // Profile position move
        public static uint CW_PP_ABSOLUTE =          0x0000;
        public static uint CW_PP_RELATIVE =          0x0040;
        public static uint CW_PP_START_IMMEDIATELY = 0x0020;
        public static uint O_WTR = 0x10000; // Wait target reach
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402ProfilePositionMove")]
        public static extern int NEC_CoE402ProfilePositionMove( int Axis, int TargetPos, ushort CtrlWord_B4_15 );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402ProfileVelocityMove")]
        public static extern int NEC_CoE402ProfileVelocityMove( int Axis, int TargetVel, ushort CtrlWord_B4_15 );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402ProfileVelocityMoveAcc")]
        public static extern int NEC_CoE402ProfileVelocityMoveAcc( int Axis, int TargetVel, ushort Acceleration, uint Deceleration, ushort CtrlWord_B4_15 );
        [DllImport(ECM_DLL, EntryPoint = "NEC_CoE402Homing")]
        public static extern int NEC_CoE402Homing( int Axis, ushort CtrlWord_B4_15 );
    }
}
