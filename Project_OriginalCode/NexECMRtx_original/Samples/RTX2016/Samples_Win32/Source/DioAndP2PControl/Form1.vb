'Public NotInheritable Class OpenFileDialog
'End Class
Public Class Form1

    Dim ret, cnt As Integer
    Dim Master_Id As UShort = 1
    Dim P As IntPtr
    Dim DI_1 As IntPtr
    Dim DI_2 As IntPtr
    Dim AxisId As IntPtr
    Dim SlaveCnt As IntPtr
    Dim TargetPos As Integer = 0
    Dim Velocity As Integer = 0
    Dim Acc As Integer = 0
    Dim SlaveCheckNum As Integer
    Dim DioSlaveAddr As Int16 = 0
    Dim DoOffset As Int16 = 0
    Dim DiOffset As Int16 = 1
    Dim DioSizeByte As Int16 = 1

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ret = NexECM.NEC_LoadRtxApp("C:\\Program Files\\NEXCOM\\NexECMRtx\\Lib\\NexECMRtx\\x32\\NexECMRtx.rtss")
        If ret <> 0 Then
            MessageBox.Show("NEC_LoadRtxApp faile" + ret.ToString)
            Return
        End If

        tb_targetPos.Text = TargetPos
        tb_velocity.Text = Velocity
        tb_acc.Text = Acc

    End Sub

    Dim motion As Integer = 0

    Private Sub btn_startMove_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btn_startMove.Click

        If SlaveCheckNum < 2 Then
            Return
        End If

        If motion = 0 Then

            ret = NexCoeMotion.NEC_CoE402SetOperationMode(AxisId, 1, 5000)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402SetOperationMode faile" + ret.ToString)
                Return
            End If

            ret = NexCoeMotion.NEC_CoE402ServoOn(AxisId, 1)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402ServoOn faile" + ret.ToString)
                Return
            End If

            ret = NexCoeMotion.NEC_CoE402Halt(AxisId, 0)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402Halt faile" + ret.ToString)
                Return
            End If



            btn_startMove.Text = "Servo off"
            motion = 1
        Else

            btn_startMove.Text = "Servo on"
            motion = 0
            btn_Move.Text = "Move"
            movecheck = 0
            ret = NexCoeMotion.NEC_CoE402ServoOn(AxisId, 0)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402ServoOn faile" + ret.ToString)
                Return
            End If

        End If



    End Sub

    Dim NetCtr As Integer = 0
    Private Sub btn_startNetwork_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btn_startNetwork.Click

        SlaveCheckNum = 0
        SlaveCheck()

        If LoadENI = 0 Then
            MessageBox.Show("Load ENI first")
            Return
        End If


        If NetCtr = 0 Then
            ret = NexECM.NEC_StartDriver()
            If ret <> 0 Then
                MessageBox.Show("NEC_StartDriver faile" + ret.ToString)
                Return
            End If

            ret = NexECM.NEC_ResetEcMaster(Master_Id)
            If ret <> 0 Then
                MessageBox.Show("NEC_ResetEcMaster faile" + ret.ToString)
                Return
            End If

            ret = NexECM.NEC_SetParameter(Master_Id, 0, 1000)
            If ret <> 0 Then
                MessageBox.Show("NEC_SetParameter faile" + ret.ToString)
                Return
            End If

            ret = NexCoeMotion.NEC_CoE402Reset()
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402Reset faile" + ret.ToString)
                Return
            End If

            If SlaveCheckNum = 0 Then
                MessageBox.Show("Please check slave !")
                Return
            End If

            ret = NexECM.NEC_StartNetworkEx(Master_Id, ENIPath, 1, 5000)
            If ret <> 0 Then
                MessageBox.Show("NEC_StartNetworkEx faile" + ret.ToString)
                Return
            End If

            btn_startNetwork.BackColor = Color.YellowGreen

            ret = NexECM.NEC_GetSlaveCount(Master_Id, SlaveCnt)
            If ret <> 0 Then
                MessageBox.Show("NEC_GetSlaveCount faile" + ret.ToString)
                Return
            End If

            Timer1.Enabled = True
            btn_startNetwork.Text = "Stop Network"
            NetCtr = 1

            If SlaveCheckNum < 2 Then
                Return
            End If

            Dim SlaveNum As Integer

            SlaveNum = SlaveCnt

            If SlaveNum < 2 Then
                SlaveCheckNum = 1
                MessageBox.Show("Please check your slave ")
                Return
            End If

            ret = NexCoeMotion.NEC_CoE402GetAxisId(Master_Id, 1, AxisId)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402GetAxisId faile" + ret.ToString)
                Return
            End If

            ret = NexCoeMotion.NEC_CoE402UpdatePdoMapping(AxisId)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402UpdatePdoMapping faile" + ret.ToString)
                Return
            End If

            ret = NexCoeMotion.NEC_CoE402FaultReset(AxisId, 5000)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402FaultReset faile" + ret.ToString)
                Return
            End If



        Else
            btn_startNetwork.BackColor = Color.WhiteSmoke
            Timer1.Enabled = False

            ret = NexECM.NEC_StopNetwork(Master_Id, 5000)
            If ret <> 0 Then
                MessageBox.Show("NEC_StopNetwork faile" + ret.ToString)
                Return
            End If

            ret = NexECM.NEC_StopDriver()
            If ret <> 0 Then
                MessageBox.Show("NEC_StopDriver faile" + ret.ToString)
                Return
            End If
            btn_startNetwork.Text = "Start Network"
            NetCtr = 0
        End If
    End Sub

    Private Sub btn_Exit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btn_Exit.Click

        Timer1.Enabled = False
        ret = 0

        If LoadENI = 0 Then
            Me.Close()
        ElseIf NetCtr = 0 Then
            LoadENI = 0
            Me.Close()
        Else
            ret = NexECM.NEC_StopNetwork(Master_Id, 5000)
            If ret <> 0 Then
                MessageBox.Show("NEC_StopNetwork faile" + ret.ToString)
                Return
            End If

            ret = NexECM.NEC_StopDriver()
            If ret <> 0 Then
                MessageBox.Show("NEC_StopDriver faile" + ret.ToString)
                Return
            End If
            LoadENI = 0
            NetCtr = 0
            Me.Close()
        End If
    End Sub

    Dim ENIPath As String

    Dim LoadENI As Integer = 0

    Private Sub btn_browse_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btn_browse.Click
        Dim openFileDialog1 As New OpenFileDialog()
        openFileDialog1.Filter = "ENI Files|*.xml"
        openFileDialog1.Title = "Select a ENI Files"

        If openFileDialog1.ShowDialog() = System.Windows.Forms.DialogResult.OK Then
            Dim sr As New System.IO.StreamReader(openFileDialog1.FileName)
            tb_eniPath.Text = openFileDialog1.FileName
            ENIPath = openFileDialog1.FileName
            LoadENI = 1
        End If


    End Sub


   

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick

        Dim pos_act As IntPtr
        Dim state_act As IntPtr
        

        DOCtrl()

        DICtrl()

        If SlaveCheckNum < 2 Then
            Return
        End If

        ret = NexCoeMotion.NEC_CoE402GetActualPosition(AxisId, pos_act)
        If ret <> 0 Then
            MessageBox.Show("NEC_CoE402GetActualPosition faile" + ret.ToString)
            Return
        End If

        ret = NexCoeMotion.NEC_CoE402GetState(AxisId, state_act)
        If ret <> 0 Then
            MessageBox.Show("NEC_CoE402GetActualPosition faile" + ret.ToString)
            Return
        End If

        tb_actualPos.Text = Convert.ToString(pos_act)
        tb_slaveState.Text = Convert.ToString(state_act)

    End Sub



    Private Sub SlaveCheck()

        If CheckBox_DIO.Checked = True Then
            SlaveCheckNum = SlaveCheckNum + 1
        End If

        If CheckBox_AXIS.Checked = True Then
            SlaveCheckNum = SlaveCheckNum + 2
        End If

    End Sub


    Private Sub DICtrl()
        Dim CalDI_1 As Integer
        Dim CalDI_2 As Integer
        DiOffset = 0
        ret = NexECM.NEC_GetDi(Master_Id, DioSlaveAddr, DiOffset, DioSizeByte, DI_1)

        DiOffset = 1
        ret = NexECM.NEC_GetDi(Master_Id, DioSlaveAddr, DiOffset, DioSizeByte, DI_2)

        CalDI_1 = DI_1
        CalDI_2 = DI_2

        If (CalDI_1 And 1) = 1 Then
            tb_di0.BackColor = Color.GreenYellow
        Else
            tb_di0.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_1 And 2) = 2 Then
            tb_di1.BackColor = Color.GreenYellow
        Else
            tb_di1.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_1 And 4) = 4 Then
            tb_di2.BackColor = Color.GreenYellow
        Else
            tb_di2.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_1 And 8) = 8 Then
            tb_di3.BackColor = Color.GreenYellow
        Else
            tb_di3.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_1 And 16) = 16 Then
            tb_di4.BackColor = Color.GreenYellow
        Else
            tb_di4.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_1 And 32) = 32 Then
            tb_di5.BackColor = Color.GreenYellow
        Else
            tb_di5.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_1 And 64) = 64 Then
            tb_di6.BackColor = Color.GreenYellow
        Else
            tb_di6.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_1 And 128) = 128 Then
            tb_di7.BackColor = Color.GreenYellow
        Else
            tb_di7.BackColor = Color.WhiteSmoke
        End If
        '''''''''''''''''''''''''''''''''''''
        If (CalDI_2 And 1) = 1 Then
            tb_di8.BackColor = Color.GreenYellow
        Else
            tb_di8.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_2 And 2) = 2 Then
            tb_di9.BackColor = Color.GreenYellow
        Else
            tb_di9.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_2 And 4) = 4 Then
            tb_di10.BackColor = Color.GreenYellow
        Else
            tb_di10.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_2 And 8) = 8 Then
            tb_di11.BackColor = Color.GreenYellow
        Else
            tb_di11.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_2 And 16) = 16 Then
            tb_di12.BackColor = Color.GreenYellow
        Else
            tb_di12.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_2 And 32) = 32 Then
            tb_di13.BackColor = Color.GreenYellow
        Else
            tb_di13.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_2 And 64) = 64 Then
            tb_di14.BackColor = Color.GreenYellow
        Else
            tb_di14.BackColor = Color.WhiteSmoke
        End If

        If (CalDI_2 And 128) = 128 Then
            tb_di15.BackColor = Color.GreenYellow
        Else
            tb_di15.BackColor = Color.WhiteSmoke
        End If



    End Sub

    Private Sub DOCtrl()
        Dim cal As Integer
        DoOffset = 0
        If cb_do0.Checked = True Then
            cal = cal Or 1
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 254
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do1.Checked = True Then
            cal = cal Or 2
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 253
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do2.Checked = True Then
            cal = cal Or 4
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 251
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do3.Checked = True Then
            cal = cal Or 8
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 247
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do4.Checked = True Then
            cal = cal Or 16
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 239
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do5.Checked = True Then
            cal = cal Or 32
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 223
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do6.Checked = True Then
            cal = cal Or 64
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 191
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If


        If cb_do7.Checked = True Then
            cal = cal Or 128
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 127
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If
        ''''''''''''''''''''''''''''''''''''''''
        DoOffset = 1

        If cb_do8.Checked = True Then
            cal = cal Or 1
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 254
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do9.Checked = True Then
            cal = cal Or 2
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 253
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do10.Checked = True Then
            cal = cal Or 4
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 251
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do11.Checked = True Then
            cal = cal Or 8
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 247
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do12.Checked = True Then
            cal = cal Or 16
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 239
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do13.Checked = True Then
            cal = cal Or 32
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 223
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

        If cb_do14.Checked = True Then
            cal = cal Or 64
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 191
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If


        If cb_do15.Checked = True Then
            cal = cal Or 128
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        Else
            cal = cal And 127
            P = cal
            ret = NexECM.NEC_SetDo(Master_Id, DioSlaveAddr, DoOffset, DioSizeByte, P)
        End If

  

    End Sub

    Dim movecheck As Integer = 0

    Private Sub btn_Move_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btn_Move.Click

        If SlaveCheckNum < 2 Then
            Return
        End If

        If motion = 0 Then
            Return
        End If

        TargetPos = Convert.ToInt32(tb_targetPos.Text)
        Velocity = Convert.ToInt32(tb_velocity.Text)
        Acc = Convert.ToInt32(tb_acc.Text)

        If movecheck = 0 Then

            ret = NexCoeMotion.NEC_CoE402Halt(AxisId, 0)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402Halt faile" + ret.ToString)
                Return
            End If

            ret = NexCoeMotion.NEC_CoE402PtpA(AxisId, 0, TargetPos, Velocity, Acc, Acc)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402PtpA faile" + ret.ToString)
                Return
            End If

            btn_Move.Text = "Stop"
            movecheck = 1
        Else
            btn_Move.Text = "Move"
            movecheck = 0

            ret = NexCoeMotion.NEC_CoE402Halt(AxisId, 1)
            If ret <> 0 Then
                MessageBox.Show("NEC_CoE402Halt faile" + ret.ToString)
                Return
            End If
        End If
    End Sub

    Private Sub Form1_Closed(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles MyBase.FormClosed
        If LoadENI <> 0 Then
            ret = NexECM.NEC_StopNetwork(Master_Id, 5000)
            If ret <> 0 Then
                MessageBox.Show("NEC_StopNetwork faile" + ret.ToString)
                Return
            End If

            ret = NexECM.NEC_StopDriver()
            If ret <> 0 Then
                MessageBox.Show("NEC_StopDriver faile" + ret.ToString)
                Return
            End If
        End If
    End Sub

End Class
