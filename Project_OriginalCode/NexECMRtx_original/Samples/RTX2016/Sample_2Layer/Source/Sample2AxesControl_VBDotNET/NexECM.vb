Imports System.Runtime.InteropServices

Public Class NexECM

    '*** StartNetworkEx() Option define.	  
    Const START_NETWORK_OPT_NIC_PORT_USING_PARAMETER = (1)

    Const MAX_CONFIG_FILE_NAME_LEN = (248)

    ' Master type
    Const MASTER_TYPE_WIN32 = (0)
    Const MASTER_TYPE_RTX = (1)
    Const MASTER_TYPE_CARD = (2)

    '*** Network state definition ***
    Const STATE_STOPPED = (0) ' Networking is stopped.
    Const STATE_OPERATIONAL = (1) ' Networking is in operation state.(EtherCAT in OP state)
    Const STATE_ERROR = (2) ' Networking / slaves errors, and stopped.
    Const STATE_SLAVE_RETRY = (3) ' Networking / slaves errors, and try to re-connect.

    '***********************
    '*** API list below ***
    '***********************

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetVersion() As UInteger
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_StartDriver() As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_StopDriver() As Integer
    End Function

    '<DllImport("NexEcm")>
    'Public Shared Function NEC_GetAvailableDriverCount() As UShort
    'End Function

    '<DllImport("NexEcm")>
    'Public Shared Function NEC_GetMasterType(ByVal MasterId As UShort, ByRef Type As UShort) As UShort
    'End Function



    <DllImport("NexEcm")>
    Public Shared Function NEC_SetParameter(ByVal MasterId As UShort, ByVal ParaNum As UShort, ByVal ParaData As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetParameter(ByVal MasterId As UShort, ByVal ParaNum As UShort, ByRef ParaData As UShort) As Integer
    End Function

    ' TimeoutMs: wait state to operation state. if value = -1 no wait, just start communication and you can check state by call NEC_GetNetworkState()
    <DllImport("NexEcm")>
    Public Shared Function NEC_StartNetwork(ByVal MasterId As UShort, ByVal ConfigurationFile As String, ByVal TimeoutMs As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_StartNetworkEx(ByVal MasterId As UShort, ByVal ConfigurationFile As String, ByVal Opt As Integer, ByVal TimeoutMs As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_StopNetwork(ByVal MasterId As UShort, ByVal TimeoutMs As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetSlaveCount(ByVal MasterId As UShort, ByRef Count As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetNetworkState(ByVal MasterId As UShort, ByRef State As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetSlaveState(ByVal MasterId As UShort, ByVal SlaveIndex As UShort, ByRef StateArr As Byte, ByRef ArrLen As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetStateError(ByVal MasterId As UShort, ByRef Code As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetErrorMsg(ByVal MasterId As UShort, ByRef ErrMsg_128_len As String) As Integer
    End Function

    '*** Application functions ****
    '<<< non-synchronized DIO functions, set DO value to memory only. >>> 
    <DllImport("NexEcm")>
    Public Shared Function NEC_SetDo(ByVal MasterId As UShort, ByVal SlaveAddr As UShort, ByVal Offset As UShort, ByVal SizeByte As UShort, ByRef DoData As Byte) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetDo(ByVal MasterId As UShort, ByVal SlaveAddr As UShort, ByVal Offset As UShort, ByVal SizeByte As UShort, ByRef DoData As Byte) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetDi(ByVal MasterId As UShort, ByVal SlaveAddr As UShort, ByVal Offset As UShort, ByVal SizeByte As UShort, ByRef DoData As Byte) As Integer
    End Function

    '<<< synchronized DIO functions, set DO value to memory and wait master accepted. >>>
    '<DllImport("NexEcm")>
    'Public Shared Function NEC_SetDo_s(ByVal MasterId As UShort _
    '                                   , ByVal SlaveAddr As UShort _
    '                                   , ByVal Offset As UShort _
    '                                   , ByVal SizeByte As UShort _
    '                                   , ByRef DoData As Byte _
    '                                   ) As Integer
    'End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_SDODownloadEx(ByVal MasterId As UShort _
                                             , ByVal SlaveAddr As UShort _
                                             , ByVal Index As UShort _
                                             , ByVal SubIndex As Byte _
                                             , ByVal CtrlFlag As Byte _
                                             , ByRef DataLenByte As UInteger _
                                             , ByVal DataPtr() As Byte _
                                             , ByRef AbortCode As UInteger _
                                             ) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_SDOUploadEx(ByVal MasterId As UShort _
                                           , ByVal SlaveAddr As UShort _
                                           , ByVal Index As UShort _
                                           , ByVal SubIndex As Byte _
                                           , ByVal CtrlFlag As Byte _
                                           , ByRef DataLenByte As UInteger _
                                           , ByRef DataPtr As Byte _
                                           , ByRef AbortCode As UInteger _
                                           ) As Integer
    End Function

    Const READ_PI = (0)   ' Read ProcessImage (PDI)
    Const WRITE_PI = (1)   ' Write ProcessImage (PDO)
    Const READ_PDO = (2)  ' Read ProcessImage (PDO)

    <DllImport("NexEcm")>
    Public Shared Function NEC_RWProcessImage(ByVal MasterId As UShort, ByVal RW As UShort, ByVal Offset As UShort, ByRef Data As Byte, ByVal Size As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetProcessImageSize(ByVal MasterId As UShort, ByRef SizeOfInputByte As UShort, ByRef SizeOfOutputByte As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_RWSlaveProcessImage(ByVal MasterId As UShort, ByVal SlaveAddr As UShort, ByVal RW As UShort, ByVal offset As UShort, ByRef Data As Byte, ByVal Size As UShort) As Integer
    End Function

    '//*************************************
    '//*** API for realtime applications ***
    '//*************************************

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetRtMasterId(ByRef pMasterId As UShort) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_ResetEcMaster(ByVal MasterId As UShort) As Integer
    End Function

    Const MAX_RTX_FILE_NAME = 256
    <DllImport("NexEcm")>
    Public Shared Function NEC_LoadRtxApp(ByVal a As String) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_KillRtxApp(ByVal ProcessId As UInteger) As Integer
    End Function

    Const MAX_ENI_FILE_NAME = 248

    <DllImport("NexEcm")>
    Public Shared Function NEC_LoadNetworkConfig(ByVal MasterId As UShort, ByVal ConfigurationFile As String, ByVal Opt As Integer) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetRtMasterPorcessId(ByVal MasterId As UShort, ByRef pProcessID As UInteger) As Integer
    End Function

    <DllImport("NexEcm")>
    Public Shared Function NEC_GetRtMasterVersion(ByVal MasterId As UShort, ByRef pVersion As UInteger) As Integer
    End Function

End Class