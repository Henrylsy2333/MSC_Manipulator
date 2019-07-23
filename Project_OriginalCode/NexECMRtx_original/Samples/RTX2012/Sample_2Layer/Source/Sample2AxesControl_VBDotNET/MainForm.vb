Imports System.Runtime.InteropServices

Public Class MainForm

    Dim EVN_NAME, SHN_NAME As String
    Dim obhandle, PVOID As IntPtr
    Dim ret As Integer

    Public Structure WIN32_DAT

        Dim mAxis1 As Integer
        Dim mAxis2 As Integer
        Dim masterId As UShort
        Dim ActualPos1 As Integer
        Dim ActualPos2 As Integer
        Dim TargetPos1 As Integer
        Dim TargetPos2 As Integer
        Dim MasterState As UShort
        Dim SlaveState1 As UShort
        Dim SlaveState2 As UShort
        Dim ACC_DEC1 As Integer
        Dim ACC_DEC2 As Integer
        Dim Velocity1 As Integer
        Dim Velocity2 As Integer

    End Structure

    Private Sub Button_Start_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Start.Click

        Dim data As WIN32_DAT
        Dim Master_Id As UShort

        EVN_NAME = "Event"
        SHN_NAME = "Memory"

        ret = NexECM.NEC_StartDriver()
        If ret <> 0 Then
            MessageBox.Show("NEC_StartDriver failed, ret = " + ret.ToString)
            Me.Close()
            Return
        End If

        ret = NexECM.NEC_ResetEcMaster(Master_Id)
        If ret <> 0 Then
            MessageBox.Show("NEC_StartDriver failed, ret = " + ret.ToString)
            NexECM.NEC_StopDriver()
            Me.Close()
            Return
        End If

        ret = NexECM.NEC_LoadNetworkConfig(Master_Id, "C:\\ENI_NexCAT_Export.xml", 1)
        If ret <> 0 Then
            MessageBox.Show("NEC_StartDriver failed, ret = " + ret.ToString)
            NexECM.NEC_StopDriver()
            Me.Close()
            Return
        End If

        ret = NexECM.NEC_StopDriver()
        If ret <> 0 Then
            MessageBox.Show("NEC_StartDriver failed, ret = " + ret.ToString)
            NexECM.NEC_StopDriver()
            Me.Close()
            Return
        End If

        Master_Id = 1

        ret = NexECM.NEC_LoadRtxApp("C:\\Program Files\\NEXCOM\\NexECMRtx\\Samples\\RTX2012\\Sample_2Layer\\VS2010\\Sample2AxesControl_VBDotNET\\RTSSDebug\\RtxApp.rtss")
        If ret <> 0 Then
            MessageBox.Show("NEC_LoadRtxApp failed, ret = " + ret.ToString)
            Me.Close()
            Return
        End If

        obhandle = rtapi_w32.RtOpenSharedMemory(3, 0, SHN_NAME, PVOID)

        data.TargetPos1 = Convert.ToInt32(TextBox_target_pos.Text)
        data.TargetPos2 = Convert.ToInt32(TextBox_target_pos1.Text)
        data.Velocity1 = Convert.ToInt32(TextBox_v.Text)
        data.Velocity2 = Convert.ToInt32(TextBox_v1.Text)
        data.ACC_DEC1 = Convert.ToInt32(TextBox_a.Text)
        data.ACC_DEC2 = Convert.ToInt32(TextBox_a1.Text)

        Marshal.StructureToPtr(data, PVOID, True)

        obhandle = rtapi_w32.RtOpenEvent(0, 0, EVN_NAME)

        rtapi_w32.RtSetEvent(obhandle)

        Timer1.Enabled = True


    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        ret = NexECM.NEC_LoadRtxApp("C:\\Program Files\\NEXCOM\\NexECMRtx\\Lib\\NexECMRtx\\x32\\NexECMRtx.rtss")
        If ret <> 0 Then
            MessageBox.Show("NEC_LoadRtxApp failed, ret = " + ret.ToString)
            Return
        End If

        TextBox_target_pos.Text = 5000
        TextBox_target_pos1.Text = 5000
        TextBox_v.Text = 10000
        TextBox_v1.Text = 10000
        TextBox_a.Text = 100000
        TextBox_a1.Text = 100000

    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick

        Dim data As WIN32_DAT
        data = CType(Marshal.PtrToStructure(PVOID, GetType(WIN32_DAT)), WIN32_DAT)

        TextBox_actual_pos.Text = data.ActualPos1
        TextBox_actual_pos1.Text = data.ActualPos2
        TextBox_master_state.Text = data.MasterState
        TextBox_slave_state.Text = data.SlaveState1
        TextBox_slave_state1.Text = data.SlaveState2

    End Sub

    Private Sub Button_exit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_exit.Click

        Me.Close()

    End Sub
End Class
