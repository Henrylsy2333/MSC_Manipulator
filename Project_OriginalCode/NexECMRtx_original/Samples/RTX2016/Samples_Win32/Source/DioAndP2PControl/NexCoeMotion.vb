Imports System.Runtime.InteropServices
Public Class NexCoeMotion

    ' CiA402 object index
    Const INDEX_MODE_OF_OPERATION = &H6060
    Const INDEX_MODE_OF_OPERATION_DISPLAY = &H6061
    Const INDEX_MAX_PROFILE_VELOCITY = &H607F ' U32_T, PP, PV
    Const INDEX_PROFILE_VELOCITY = &H6081 'U32_T, PP
    Const INDEX_PROFILE_ACCELERATION = &H6083 'U32_T, PP, PV 
    Const INDEX_PROFILE_DECELERATION = &H6084 ' U32_T, PP, PV 
    Const INDEX_QUICK_STOP_DEC = &H6085 ' U32_T, PP, PV
    Const INDEX_TARGET_VELOCITY = &H60FF ' I32_T, PV

    Const INDEX_HOME_OFFSET = &H607C
    Const INDEX_HOME_METHOD = &H6098
    Const INDEX_HOME_SPEED = &H6099 ' SubIndex = 1
    Const INDEX_HOME_ZERO_SPEED = &H6099 ' SubIndex = 2
    Const INDEX_HOME_ACC = &H609A

    'PDO Type
    Const TYPE_RXPDO = (0)  ' Type of RxPDO
    Const TYPE_TXPDO = (1)  ' Type of TxPDO

    'Type of CiA402 Axis
    Const EC_CIA402_SERVO_DRIVE = (0)  ' For Most standard EtherCAT CoE servo drive, Only ref SlaveAddr, 
    Const EC_MULTIPLE_CIA402_SLAVE = (1)  ' For multiple slots/channel EtherCAT slave 


    Public Structure EcCiA402AxisMapInfo_T

        Dim TypeOfSlave As UShort
        Dim SlaveAddr As UShort
        Dim SlaveSlotNum As UShort
        Dim Reserved As UShort
        Dim CoeObjectOffset As UShort
        Dim pdoMapOffset As UShort
        Dim MinRxPdoIndex As UShort
        Dim MaxRxPdoIndex As UShort
        Dim MinTxPdoIndex As UShort
        Dim MaxTxPdoIndex As UShort

    End Structure

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402Reset() As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402Close() As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetAxisId(ByVal MasterId As UShort, ByVal SlaveAddr As UShort, ByRef pAxis As UInteger) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetDefaultMapInfo(ByVal TypeOfSlave As UShort, ByVal SlaveAddr As UShort, ByRef pMapInfo As EcCiA402AxisMapInfo_T) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetAxisIdEx(ByVal MasterId As UShort, ByRef pMapInfo As EcCiA402AxisMapInfo_T, ByRef pAxis As IntPtr) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402ResetPdoMapping(ByVal pAxis As UInteger) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402UpdatePdoMapping(ByVal pAxis As UInteger) As Integer
    End Function

    'State control functions
    '<DllImport("NexEcm")>
    'Public Shared Function NEC_CoE402CyclicProcess() As Integer
    'End Function

    '<DllImport("NexEcm")>
    'Public Shared Function NEC_CoE402SetSlaveProcessCountPreCycle(ByVal AxisCount As UShort) As Integer
    'End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetCtrlWord(ByVal pAxis As UInteger, ByVal CtrlInBit As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetCtrlWord(ByVal pAxis As UInteger, ByRef CtrlInBit As UShort) As Integer
    End Function


    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetStatusWord(ByVal pAxis As UInteger, ByRef StatusInBit As UShort) As Integer
    End Function

    Const COE_STA_DISABLE = (0) 'ServoOff
    Const COE_STA_READY_TO_SWITCH_ON = (1)
    Const COE_STA_SWITCH_ON = (2)
    Const COE_STA_OPERATION_ENABLE = (3)  ' ServoOn
    Const COE_STA_QUICK_STOP_ACTIVE = (4)
    Const COE_STA_FAULT = (5)  ' Error, Servo Internal
    Const COE_STA_FAULT_REACTION_ACTIVE = (6) ' Error, Servo Internal
    Const MAX_COE_STA = (7)
    Const COE_STA_UNKNOWN = &HFF

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402ChangeState(ByVal pAxis As UInteger, ByVal TargetState As UShort, ByVal TimeoutMs As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetState(ByVal pAxis As UInteger, ByVal State As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetState(ByVal pAxis As UInteger, ByRef State As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402FaultReset(ByVal pAxis As UInteger, ByVal TimeoutMs As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402ServoOn(ByVal pAxis As UInteger, ByVal OnOff As UShort) As Integer
    End Function

    'CoE Mode of operation
    Const CiA402_OP_MODE_PROFILE_POSITION = (1)
    Const CiA402_OP_MODE_PROFILE_VELOCITY = (3)
    Const CiA402_OP_MODE_TORQUE_PROFILE = (2)
    Const CiA402_OP_MODE_HOMING = (6)
    Const CiA402_OP_MODE_INTERPOLATED_POSITION = (7)
    Const CiA402_OP_MODE_CYCLIC_POSITION = (8)
    Const CiA402_OP_MODE_CYCLIC_VELOCITY = (9)
    Const CiA402_OP_MODE_CYCLIC_TORQUE = (10)

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetOperationMode(ByVal pAxis As UInteger, ByVal OnOff As Byte, ByVal CheckTimeoutMs As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetOperationModeDisplay(ByVal pAxis As UInteger, ByRef MotionMode As Byte) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetParameter(ByVal pAxis As UInteger, ByVal Index As UShort, ByVal SubIndex As Byte, ByVal LenOfByte As Byte, ByVal Value As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetParameter(ByVal pAxis As UInteger, ByVal Index As UShort, ByVal SubIndex As Byte, ByVal LenOfByte As Byte, ByVal Value As Integer) As Integer
    End Function

    'For CSP operation mode
    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetActualPosition(ByVal pAxis As UInteger, ByRef Position As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetTargetPosition(ByVal pAxis As UInteger, ByVal TargetPos As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetTargetPosition(ByVal pAxis As UInteger, ByRef TargetPos As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetQuickStopDec(ByVal pAxis As UInteger, ByVal QuickStopDec As UInteger) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetSoftPosLimit(ByVal pAxis As UInteger, ByVal MinPositionLimit As Integer, ByVal MaxPositionLimit As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetMaxVelLimit(ByVal pAxis As UInteger, ByVal MaxVelocityLimit As UInteger) As Integer
    End Function

    'Operation mode: Profile Position mode
    Const OPT_ABS = &H0        'Absolution position
    Const OPT_REL = &H40       'Releative distance
    Const OPT_WMC = &H10000    'Wait move complete
    Const OPT_IMV = &H10000000 'Ignore MaxVel
    Const OPT_IAC = &H20000000 'Ignore Acc
    Const OPT_IDC = &H40000000 'Ignore Dec

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402Ptp(ByVal pAxis As UInteger, ByVal Opt As UInteger, ByVal TargetPos As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402PtpV(ByVal pAxis As UInteger, ByVal Opt As UInteger, ByVal TargetPos As Integer, ByVal MaxVel As UInteger) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402PtpA(ByVal pAxis As UInteger, ByVal Opt As UInteger, ByVal TargetPos As Integer, ByVal MaxVel As UInteger, ByVal Acc As UInteger, ByVal Dec As UInteger) As Integer
    End Function

    'Operation mode: Profile Velocity mode
    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402Jog(ByVal pAxis As UInteger, ByVal Opt As UInteger, ByVal MaxVel As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402JogA(ByVal pAxis As UInteger, ByVal Opt As UInteger, ByVal MaxVel As Integer, ByVal Acc As Integer, ByVal Dec As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402Halt(ByVal pAxis As UInteger, ByVal OnOff As UInteger) As Integer
    End Function

    'Operation mode: Homing
    Const OPT_MTD = &H8000000  'Ignore Method
    Const OPT_IZV = &H40000000 'Ignore ZeroVel
    Const OPT_IOF = &H80000000 'Ignore Offset

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402Home(ByVal pAxis As UInteger, ByVal Opt As UInteger) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402HomeEx(ByVal pAxis As UInteger, ByVal Opt As UInteger, ByVal Method As Byte, ByVal Offset As UInteger, ByVal MaxVel As UInteger, ByVal ZeroVel As UInteger, ByVal Acc As UInteger) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402WaitHomeFinished(ByVal pAxis As UInteger) As Integer
    End Function

    'Operation mode: Profile Torque Mode /Cyclic Sync Torque mode
    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetTargetTorque(ByVal pAxis As UInteger, ByVal TargetTorque As Short) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetTargetTorque(ByVal pAxis As UInteger, ByRef TargetTorque As Short) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402GetActualTorque(ByVal pAxis As UInteger, ByRef TorqueActualValue As Short) As Integer
    End Function

    'Operation mode: Profile Torque Mode
    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402SetTorqueProfile(ByVal pAxis As UInteger, ByVal TargetTorque As Short, ByVal TorqueSlope As UInteger) As Integer
    End Function

    'Profile position move
    Const CW_HALT = &H100  ' Halt
    ' Profile position move
    Const CW_PP_ABSOLUTE = &H0
    Const CW_PP_RELATIVE = &H40
    Const CW_PP_START_IMMEDIATELY = &H20
    Const O_WT = &H10000 ' Wait target reach

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402ProfilePositionMove(ByVal pAxis As UInteger, ByVal TargetPos As Integer, ByVal CtrlWord_B4_15 As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402ProfileVelocityMove(ByVal pAxis As UInteger, ByVal TargetVel As Integer, ByVal CtrlWord_B4_15 As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402ProfileVelocityMoveAcc(ByVal pAxis As UInteger, ByVal TargetVel As Integer, ByVal Acceleration As UInteger, ByVal Deceleration As UInteger, ByVal CtrlWord_B4_15 As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_CoE402Homing(ByVal pAxis As UInteger, ByVal CtrlWord_B4_15 As UShort) As Integer
    End Function

End Class