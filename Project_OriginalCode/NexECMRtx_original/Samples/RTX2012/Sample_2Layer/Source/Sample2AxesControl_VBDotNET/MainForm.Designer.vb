<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainForm
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.Button_Start = New System.Windows.Forms.Button()
        Me.TextBox_master_state = New System.Windows.Forms.TextBox()
        Me.TextBox_slave_state = New System.Windows.Forms.TextBox()
        Me.TextBox_actual_pos = New System.Windows.Forms.TextBox()
        Me.TextBox_target_pos = New System.Windows.Forms.TextBox()
        Me.TextBox_v = New System.Windows.Forms.TextBox()
        Me.TextBox_a = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.TextBox_slave_state1 = New System.Windows.Forms.TextBox()
        Me.TextBox_actual_pos1 = New System.Windows.Forms.TextBox()
        Me.TextBox_target_pos1 = New System.Windows.Forms.TextBox()
        Me.TextBox_v1 = New System.Windows.Forms.TextBox()
        Me.TextBox_a1 = New System.Windows.Forms.TextBox()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Button_exit = New System.Windows.Forms.Button()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.SuspendLayout()
        '
        'Button_Start
        '
        Me.Button_Start.Location = New System.Drawing.Point(144, 12)
        Me.Button_Start.Name = "Button_Start"
        Me.Button_Start.Size = New System.Drawing.Size(145, 30)
        Me.Button_Start.TabIndex = 0
        Me.Button_Start.Text = "Cycle Start"
        Me.Button_Start.UseVisualStyleBackColor = True
        '
        'TextBox_master_state
        '
        Me.TextBox_master_state.Location = New System.Drawing.Point(96, 18)
        Me.TextBox_master_state.Name = "TextBox_master_state"
        Me.TextBox_master_state.ReadOnly = True
        Me.TextBox_master_state.Size = New System.Drawing.Size(33, 22)
        Me.TextBox_master_state.TabIndex = 1
        '
        'TextBox_slave_state
        '
        Me.TextBox_slave_state.Location = New System.Drawing.Point(95, 22)
        Me.TextBox_slave_state.Name = "TextBox_slave_state"
        Me.TextBox_slave_state.ReadOnly = True
        Me.TextBox_slave_state.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_slave_state.TabIndex = 1
        '
        'TextBox_actual_pos
        '
        Me.TextBox_actual_pos.Location = New System.Drawing.Point(95, 58)
        Me.TextBox_actual_pos.Name = "TextBox_actual_pos"
        Me.TextBox_actual_pos.ReadOnly = True
        Me.TextBox_actual_pos.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_actual_pos.TabIndex = 1
        '
        'TextBox_target_pos
        '
        Me.TextBox_target_pos.Location = New System.Drawing.Point(95, 94)
        Me.TextBox_target_pos.Name = "TextBox_target_pos"
        Me.TextBox_target_pos.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_target_pos.TabIndex = 1
        '
        'TextBox_v
        '
        Me.TextBox_v.Location = New System.Drawing.Point(95, 133)
        Me.TextBox_v.Name = "TextBox_v"
        Me.TextBox_v.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_v.TabIndex = 1
        '
        'TextBox_a
        '
        Me.TextBox_a.Location = New System.Drawing.Point(95, 173)
        Me.TextBox_a.Name = "TextBox_a"
        Me.TextBox_a.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_a.TabIndex = 1
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(18, 21)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(61, 12)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "Master State"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(14, 25)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(55, 12)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Slave State"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(14, 61)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(75, 12)
        Me.Label3.TabIndex = 2
        Me.Label3.Text = "Actual Position"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(14, 97)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(75, 12)
        Me.Label4.TabIndex = 2
        Me.Label4.Text = "Target Position"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(14, 136)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(68, 12)
        Me.Label5.TabIndex = 2
        Me.Label5.Text = "Axis Velocity"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(14, 176)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(68, 12)
        Me.Label6.TabIndex = 2
        Me.Label6.Text = "Axis Acc/Dec"
        '
        'TextBox_slave_state1
        '
        Me.TextBox_slave_state1.Location = New System.Drawing.Point(93, 22)
        Me.TextBox_slave_state1.Name = "TextBox_slave_state1"
        Me.TextBox_slave_state1.ReadOnly = True
        Me.TextBox_slave_state1.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_slave_state1.TabIndex = 1
        '
        'TextBox_actual_pos1
        '
        Me.TextBox_actual_pos1.Location = New System.Drawing.Point(93, 58)
        Me.TextBox_actual_pos1.Name = "TextBox_actual_pos1"
        Me.TextBox_actual_pos1.ReadOnly = True
        Me.TextBox_actual_pos1.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_actual_pos1.TabIndex = 1
        '
        'TextBox_target_pos1
        '
        Me.TextBox_target_pos1.Location = New System.Drawing.Point(93, 94)
        Me.TextBox_target_pos1.Name = "TextBox_target_pos1"
        Me.TextBox_target_pos1.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_target_pos1.TabIndex = 1
        '
        'TextBox_v1
        '
        Me.TextBox_v1.Location = New System.Drawing.Point(93, 133)
        Me.TextBox_v1.Name = "TextBox_v1"
        Me.TextBox_v1.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_v1.TabIndex = 1
        '
        'TextBox_a1
        '
        Me.TextBox_a1.Location = New System.Drawing.Point(93, 173)
        Me.TextBox_a1.Name = "TextBox_a1"
        Me.TextBox_a1.Size = New System.Drawing.Size(83, 22)
        Me.TextBox_a1.TabIndex = 1
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(12, 25)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(55, 12)
        Me.Label7.TabIndex = 2
        Me.Label7.Text = "Slave State"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(12, 61)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(75, 12)
        Me.Label8.TabIndex = 2
        Me.Label8.Text = "Actual Position"
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(12, 97)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(75, 12)
        Me.Label9.TabIndex = 2
        Me.Label9.Text = "Target Position"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(12, 136)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(68, 12)
        Me.Label10.TabIndex = 2
        Me.Label10.Text = "Axis Velocity"
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(12, 176)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(68, 12)
        Me.Label11.TabIndex = 2
        Me.Label11.Text = "Axis Acc/Dec"
        '
        'Timer1
        '
        '
        'Button_exit
        '
        Me.Button_exit.Location = New System.Drawing.Point(310, 12)
        Me.Button_exit.Name = "Button_exit"
        Me.Button_exit.Size = New System.Drawing.Size(83, 30)
        Me.Button_exit.TabIndex = 3
        Me.Button_exit.Text = "Exit"
        Me.Button_exit.UseVisualStyleBackColor = True
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Label6)
        Me.GroupBox1.Controls.Add(Me.Label5)
        Me.GroupBox1.Controls.Add(Me.Label4)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.TextBox_a)
        Me.GroupBox1.Controls.Add(Me.TextBox_v)
        Me.GroupBox1.Controls.Add(Me.TextBox_target_pos)
        Me.GroupBox1.Controls.Add(Me.TextBox_actual_pos)
        Me.GroupBox1.Controls.Add(Me.TextBox_slave_state)
        Me.GroupBox1.Location = New System.Drawing.Point(7, 55)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(206, 208)
        Me.GroupBox1.TabIndex = 4
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Axis 1"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Label11)
        Me.GroupBox2.Controls.Add(Me.Label10)
        Me.GroupBox2.Controls.Add(Me.Label9)
        Me.GroupBox2.Controls.Add(Me.Label8)
        Me.GroupBox2.Controls.Add(Me.Label7)
        Me.GroupBox2.Controls.Add(Me.TextBox_a1)
        Me.GroupBox2.Controls.Add(Me.TextBox_v1)
        Me.GroupBox2.Controls.Add(Me.TextBox_target_pos1)
        Me.GroupBox2.Controls.Add(Me.TextBox_actual_pos1)
        Me.GroupBox2.Controls.Add(Me.TextBox_slave_state1)
        Me.GroupBox2.Location = New System.Drawing.Point(236, 55)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(201, 208)
        Me.GroupBox2.TabIndex = 5
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Axis 2"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(465, 286)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.Button_exit)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.TextBox_master_state)
        Me.Controls.Add(Me.Button_Start)
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.Text = "Sample2AexsControl"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Button_Start As System.Windows.Forms.Button
    Friend WithEvents TextBox_master_state As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_slave_state As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_actual_pos As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_target_pos As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_v As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_a As System.Windows.Forms.TextBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents TextBox_slave_state1 As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_actual_pos1 As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_target_pos1 As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_v1 As System.Windows.Forms.TextBox
    Friend WithEvents TextBox_a1 As System.Windows.Forms.TextBox
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Button_exit As System.Windows.Forms.Button
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox

End Class
