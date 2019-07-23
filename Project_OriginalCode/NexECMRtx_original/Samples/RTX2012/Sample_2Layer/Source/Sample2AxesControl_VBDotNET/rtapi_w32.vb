Imports System.Runtime.InteropServices

Public Class rtapi_w32

    <DllImport("rtapi_w32.dll")> _
    Public Shared Function RtOpenEvent(ByVal dwDesiredAccess As Integer, _
                                       ByVal bInheritHandle As Integer, _
                                       ByVal lpName As String) As IntPtr
    End Function

    <DllImport("rtapi_w32.dll")> _
    Public Shared Function RtSetEvent(ByVal hEvent As IntPtr) As IntPtr
    End Function

    <DllImport("rtapi_w32.dll")> _
    Public Shared Function RtOpenSharedMemory(ByVal DesiredAccess As Integer, _
                                              ByVal bInheritHandle As Integer, _
                                              ByVal lpName As String, _
                                              ByRef addr As IntPtr) As IntPtr
    End Function

End Class