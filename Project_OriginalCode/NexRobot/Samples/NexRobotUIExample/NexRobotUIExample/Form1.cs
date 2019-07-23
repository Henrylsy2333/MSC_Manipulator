using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Source;
using NexECM;
using System.Runtime.InteropServices;
using Microsoft.VisualBasic.PowerPacks;

namespace NexRobotUIExample
{
    public struct NEXROBOT_DO
    {
        public uint outputsizeinbyte;
        
        //[MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public uint[] outdata;
    }

    public partial class Form1 : Form
    {
        #region IniFile
        private string Tag_Path_ENI = "PATH_ENI";
        private string Tag_Path_NexECMRtx = "PATH_NEXECMRTX_DRIVER";
        private string Tag_Path_UserApp = "PATH_USER_APP";
        private string Key_Path = "PATH";
        private string Ini_Path = "C:\\Program Files\\Nexcom\\NexECMRtx\\tools\\x32\\NexECMRtxConfig.ini";

        private string EniPath = "C:\\ENI_NexCAT_Export.xml"; //default
        private string NexECMPath = "C:\\Program Files\\NEXCOM\\NexECMRtx\\Lib\\NexECMRtx\\x32\\NexECMRtx.rtss";//default
        private string UserAPPPath = "C:\\Users\\Weihan\\Desktop\\Controller\\Weihan\\0211\\RTSSDebug\\UserRTApp.rtss";//default

        private StringBuilder retString = new StringBuilder(255);
        #endregion

        private Setting Setting_new_Form;
        private bool is_closing;
        private bool u1AxisRdButtonChecked = true;

        public Form1()
        {
            InitializeComponent();

            #region LoadIniFile
            var eniPath = new StringBuilder(255);
            int ret = NexECMPaser.GetPrivateProfileString(Tag_Path_ENI, Key_Path, null, retString, 255, Ini_Path);
            if (ret != 0) { EniPath = retString.ToString(); }

            ret = NexECMPaser.GetPrivateProfileString(Tag_Path_NexECMRtx, Key_Path, null, retString, 255, Ini_Path);
            if (ret != 0) { NexECMPath = retString.ToString(); }

            ret = NexECMPaser.GetPrivateProfileString(Tag_Path_UserApp, Key_Path, null, retString, 255, Ini_Path);
            if (ret != 0) { UserAPPPath = retString.ToString(); }
            #endregion

            button2.Enabled = false;
            button3.Enabled = false;
            button4.Enabled = false;
            button5.Enabled = false;
            button6.Enabled = false;
            button7.Enabled = false;
            button8.Enabled = false;
            button9.Enabled = false;
            button10.Enabled = false;

            Global_Var.Max_PTP_Vel = 30.0; // deg/sec
            Global_Var.PTP_Acc     = 15.0; // deg/sec^2

            Global_Var.Max_LINE_CIRCLE_Vel = 30.0; // mm/sec
            Global_Var.LINE_CIRCLE_Acc     = 15.0; // mm/sec^2

            Setting_new_Form = new Setting();
            is_closing = true;

            #region DIO Ini
            DO0.FillColor = Color.White;
            DO0.FillStyle = FillStyle.Solid;
            DO1.FillColor = Color.White;
            DO1.FillStyle = FillStyle.Solid;
            DO2.FillColor = Color.White;
            DO2.FillStyle = FillStyle.Solid;
            DO3.FillColor = Color.White;
            DO3.FillStyle = FillStyle.Solid;
            DO4.FillColor = Color.White;
            DO4.FillStyle = FillStyle.Solid;
            DO5.FillColor = Color.White;
            DO5.FillStyle = FillStyle.Solid;
            DO6.FillColor = Color.White;
            DO6.FillStyle = FillStyle.Solid;
            DO7.FillColor = Color.White;
            DO7.FillStyle = FillStyle.Solid;
            DO8.FillColor = Color.White;
            DO8.FillStyle = FillStyle.Solid;
            DO9.FillColor = Color.White;
            DO9.FillStyle = FillStyle.Solid;
            DO10.FillColor = Color.White;
            DO10.FillStyle = FillStyle.Solid;
            DO11.FillColor = Color.White;
            DO11.FillStyle = FillStyle.Solid;
            DO12.FillColor = Color.White;
            DO12.FillStyle = FillStyle.Solid;
            DO13.FillColor = Color.White;
            DO13.FillStyle = FillStyle.Solid;
            DO14.FillColor = Color.White;
            DO14.FillStyle = FillStyle.Solid;
            DO15.FillColor = Color.White;
            DO15.FillStyle = FillStyle.Solid;
            DI0.FillColor = Color.White;
            DI0.FillStyle = FillStyle.Solid;
            DI1.FillColor = Color.White;
            DI1.FillStyle = FillStyle.Solid;
            DI2.FillColor = Color.White;
            DI2.FillStyle = FillStyle.Solid;
            DI3.FillColor = Color.White;
            DI3.FillStyle = FillStyle.Solid;
            DI4.FillColor = Color.White;
            DI4.FillStyle = FillStyle.Solid;
            DI5.FillColor = Color.White;
            DI5.FillStyle = FillStyle.Solid;
            DI6.FillColor = Color.White;
            DI6.FillStyle = FillStyle.Solid;
            DI7.FillColor = Color.White;
            DI7.FillStyle = FillStyle.Solid;
            DI8.FillColor = Color.White;
            DI8.FillStyle = FillStyle.Solid;
            DI9.FillColor = Color.White;
            DI9.FillStyle = FillStyle.Solid;
            DI10.FillColor = Color.White;
            DI10.FillStyle = FillStyle.Solid;
            DI11.FillColor = Color.White;
            DI11.FillStyle = FillStyle.Solid;
            DI12.FillColor = Color.White;
            DI12.FillStyle = FillStyle.Solid;
            DI13.FillColor = Color.White;
            DI13.FillStyle = FillStyle.Solid;
            DI14.FillColor = Color.White;
            DI14.FillStyle = FillStyle.Solid;
            DI15.FillColor = Color.White;
            DI15.FillStyle = FillStyle.Solid;
            #endregion

            #region ModeOP Combo Ini
            OPModecomboBox.Items.Add("CSP");
            OPModecomboBox.Items.Add("CSV");
            OPModecomboBox.Items.Add("CST");
            OPModecomboBox.SelectedIndex = 0; // set select item to "CSP"
            #endregion
        }

        private void get_dio()
        {
            int ret = 0;
            uint dio_cnt = 10;
            Global_Var.DO_List.Clear();

            ret = NexRobotPaser.NexR_GetDIOCount(ref dio_cnt);

            for (uint i = 0; i < dio_cnt; i++)
            {
                uint inputsizeinbyte = 0;
                uint outputsizeinbyte = 0;

                ret = NexRobotPaser.NexR_GetDIOSize(i, ref inputsizeinbyte, ref outputsizeinbyte);

                //error handle
                if (ret != 0)
                {
                }

                if (outputsizeinbyte != 0)
                {
                    NEXROBOT_DO do_size = new NEXROBOT_DO();
                    do_size.outputsizeinbyte = outputsizeinbyte;
                    do_size.outdata = new uint[outputsizeinbyte * 8];
                    for (int j = 0; j < (outputsizeinbyte * 8); j++)
                        do_size.outdata[j] = 0;

                    Global_Var.DO_List.Add(do_size);
                }
                else
                {
                }
            }// end for (uint i = 0; i < dio_cnt; i++)
        }

        private void button1_Click(object sender, EventArgs e)
        {                        
            int ret = 0;
            ushort Master_ID = 0;

            ret = NexECMPaser.NEC_GetRtMasterId(ref Master_ID);
            if (ret != 0)
            {
                // don't exist ECM, start ECM right now                 
                ret = NexECMPaser.NEC_LoadRtxApp(NexECMPath);
                if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); return; }

                // Start NexECM Driver
                ret = NexECMPaser.NEC_StartDriver();
                if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); return; }

                // Get ECMaster ID
                ret = NexECMPaser.NEC_GetRtMasterId(ref Master_ID);
                if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); return; }

                // Reset ECMaster
                ret = NexECMPaser.NEC_ResetEcMaster(Master_ID);
                if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); return; }

                // Start NexECM Driver
                ret = NexECMPaser.NEC_LoadNetworkConfig(Master_ID, EniPath, 1);
                if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); return; }

                //NexECM is Ready, now start NexRobot
                ret = NexECMPaser.NEC_LoadRtxApp(UserAPPPath);
                //if error, show error message and return
                if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); return; }

                // Robottimer.Enabled = true;
            }

            ret = NexRobotPaser.NexR_LinktoRobotKernel();

            if (ret != 0) // not ready, which means sharedmemory in dll open failed....
            {
                string MsgBox_Title = "NexRobot Kernel is Not Ready.....";
                DialogResult dialog_result = MessageBox.Show(MsgBox_Title, "Error!!", MessageBoxButtons.OK);
                button1.Enabled = false;
                return;
            }

            // wait status to op
            int timeoutcnt = 30;
            int now_cnt = 0;
            while (true)
            {
                NexRobotPaser.NexR_GetRobotKernelStatus(ref ret);
                if (ret == 1)
                {
                    // unkown bug ....need to delay some time to get dio count
                    System.Threading.Thread.Sleep(500);

                    get_dio();
                    //ret = NexRobotPaser.NexR_RobotServoON();
                    //Global_Var.servo = 1;
                    break;
                }

                if (now_cnt > timeoutcnt)
                {
                    string MsgBox_Title = "Wait GetRobotKernelStatus Timeout";
                    DialogResult dialog_result = MessageBox.Show(MsgBox_Title, "Error!!", MessageBoxButtons.OK);
                    button1.Enabled = false;
                    return;
                }

                System.Threading.Thread.Sleep(300);

                is_closing = false;

            }//end while

            // assign initialize Axis data to TextBox
            NexRobotPos Robot_Pos = new NexRobotPos();
            NexRobotPaser.NexR_GetRobotPosition(ref Robot_Pos);
            Update_Robot_Pos_Info(Robot_Pos);

            if (radioButtonTCP.Checked == true)
            {
                textBox1.Text = Robot_Pos.Tcp[0].ToString("00.000");
                textBox2.Text = Robot_Pos.Tcp[1].ToString("00.000");
                textBox3.Text = Robot_Pos.Tcp[2].ToString("00.000");
                textBox4.Text = Robot_Pos.Tcp[3].ToString("00.000");
                textBox5.Text = Robot_Pos.Tcp[4].ToString("00.000");
                textBox6.Text = Robot_Pos.Tcp[5].ToString("00.000");
                u1AxisRdButtonChecked = false;
            }
            else //if (radioButtonAxis.Checked == true)
            {
                textBox1.Text = Robot_Pos.Axis_Data[0].ToString("00.000");
                textBox2.Text = Robot_Pos.Axis_Data[1].ToString("00.000");
                textBox3.Text = Robot_Pos.Axis_Data[2].ToString("00.000");
                textBox4.Text = Robot_Pos.Axis_Data[3].ToString("00.000");
                textBox5.Text = Robot_Pos.Axis_Data[4].ToString("00.000");
                textBox6.Text = Robot_Pos.Axis_Data[5].ToString("00.000");
                u1AxisRdButtonChecked = true;
            }
       
            //initialize buttons
            button1.Enabled  = false; // start
            button8.Enabled  = false; // safety reset
            button9.Enabled  = true;  // start reset            
            button10.Enabled = true;  // BK ON/OFF            
            timer1.Enabled = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int ret = 0;

            if (Global_Var.servo == 1)
            {
                ret = NexRobotPaser.NexR_RobotServoOFF();
                Global_Var.servo = 0;
                button3.Text = "Servo ON";
                button4.Enabled = false;
                button7.Enabled = false;
            }
            else 
            {
                ret = NexRobotPaser.NexR_RobotServoON();
                Global_Var.servo = 1;
                button3.Text = "Servo OFF";
                button4.Enabled = true;
                button7.Enabled = true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int ret = NexRobotPaser.NexR_RobotServoOFF();
            if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); }

            ret = NexRobotPaser.NexR_CloseRobotKernel();

            is_closing = true;

            this.Close();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (is_closing)
                return;

            int ret = NexRobotPaser.NexR_RobotServoOFF();
            if (ret != 0) { NexECMPaser.ShowECMErrorMessage(ret); }

            ret = NexRobotPaser.NexR_CloseRobotKernel();            
        }

        public void ShowDI(uint[] DI_Data)
        {
            // Display DI dialog
            if (DI_Data[0] == 1)
                DI0.FillColor = Color.Red;
            else if (DI_Data[0] == 0)
                DI0.FillColor = Color.White;

            if (DI_Data[1] == 1)
                DI1.FillColor = Color.Red;
            else if (DI_Data[1] == 0)
                DI1.FillColor = Color.White;

            if (DI_Data[2] == 1)
                DI2.FillColor = Color.Red;
            else if (DI_Data[2] == 0)
                DI2.FillColor = Color.White;

            if (DI_Data[3] == 1)
                DI3.FillColor = Color.Red;
            else if (DI_Data[3] == 0)
                DI3.FillColor = Color.White;

            if (DI_Data[4] == 1)
                DI4.FillColor = Color.Red;
            else if (DI_Data[4] == 0)
                DI4.FillColor = Color.White;

            if (DI_Data[5] == 1)
                DI5.FillColor = Color.Red;
            else if (DI_Data[5] == 0)
                DI5.FillColor = Color.White;

            if (DI_Data[6] == 1)
                DI6.FillColor = Color.Red;
            else if (DI_Data[6] == 0)
                DI6.FillColor = Color.White;

            if (DI_Data[7] == 1)
                DI7.FillColor = Color.Red;
            else if (DI_Data[7] == 0)
                DI7.FillColor = Color.White;

            if (DI_Data[8] == 1)
                DI8.FillColor = Color.Red;
            else if (DI_Data[8] == 0)
                DI8.FillColor = Color.White;

            if (DI_Data[9] == 1)
                DI9.FillColor = Color.Red;
            else if (DI_Data[9] == 0)
                DI9.FillColor = Color.White;

            if (DI_Data[10] == 1)
                DI10.FillColor = Color.Red;
            else if (DI_Data[10] == 0)
                DI10.FillColor = Color.White;

            if (DI_Data[11] == 1)
                DI11.FillColor = Color.Red;
            else if (DI_Data[11] == 0)
                DI11.FillColor = Color.White;

            if (DI_Data[12] == 1)
                DI12.FillColor = Color.Red;
            else if (DI_Data[12] == 0)
                DI12.FillColor = Color.White;

            if (DI_Data[13] == 1)
                DI13.FillColor = Color.Red;
            else if (DI_Data[13] == 0)
                DI13.FillColor = Color.White;

            if (DI_Data[14] == 1)
                DI14.FillColor = Color.Red;
            else if (DI_Data[14] == 0)
                DI14.FillColor = Color.White;

            if (DI_Data[15] == 1)
                DI15.FillColor = Color.Red;
            else if (DI_Data[15] == 0)
                DI15.FillColor = Color.White;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int status = 0;
            NexRobotPaser.NexR_GetRobotKernelStatus(ref status);
            NexRobotPos Robot_Pos = new NexRobotPos();
            Robot_Pos.Axis_actpos = new int[7];
            Robot_Pos.Axis_actvel = new int[7];
            Robot_Pos.Axis_Data = new double[7];
            Robot_Pos.Axis_Vel = new double[7];
            Robot_Pos.Servo_Status = new ushort[7];
            Robot_Pos.Tcp = new double[6];
            uint[] DI_Data = new uint[16];
            
            if (status == 1) // TRUE
            {
                // Refresh Robot Pos
                NexRobotPaser.NexR_GetRobotPosition(ref Robot_Pos);
                Update_Robot_Pos_Info(Robot_Pos);
                UpdatePtpLabelTxtInfo(Robot_Pos);

                // Get DI
                NexRobotPaser.NexR_GetDIO(0, DI_Data);
                ShowDI(DI_Data);
            }

        }

        public void Update_Robot_Pos_Info(NexRobotPos pos)
        {
            label18.Text = pos.Axis_Data[0].ToString("00.000");
            label17.Text = pos.Axis_Data[1].ToString("00.000");
            label16.Text = pos.Axis_Data[2].ToString("00.000");
            label15.Text = pos.Axis_Data[3].ToString("00.000");
            label14.Text = pos.Axis_Data[4].ToString("00.000");
            label13.Text = pos.Axis_Data[5].ToString("00.000");
            label3.Text  = pos.Tcp[0].ToString("00.000");
            label4.Text  = pos.Tcp[1].ToString("00.000");
            label7.Text  = pos.Tcp[2].ToString("00.000");
            label12.Text = pos.Tcp[3].ToString("00.000");
            label11.Text = pos.Tcp[4].ToString("00.000");
            label8.Text = pos.Tcp[5].ToString("00.000"); 
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
           
            if (Global_Var.DO_List.Count() > 0)
            {
                if (Global_Var.DO_List[0].outdata[1] == 0)
                {
                    DialogResult dialog_result = MessageBox.Show("BK not OFF", "Error!!", MessageBoxButtons.OK);
                    return; 
                }
            }

            double[] target_data = new double[6];
            double[] vel = new double[6];
            double[] acc = new double[6];

            m_Get_Current_Pos_Vel_Acc_data(target_data, vel, acc);

            target_data[0] = double.Parse(textBox1.Text);
            target_data[1] = double.Parse(textBox2.Text);
            target_data[2] = double.Parse(textBox3.Text);
            target_data[3] = double.Parse(textBox4.Text);
            target_data[4] = double.Parse(textBox5.Text);
            target_data[5] = double.Parse(textBox6.Text);

            // PTP
            if ((radioButtonTCP.Checked == true) && (radioButtonPTP.Checked == true))
                NexRobotPaser.NexR_MovePtp(2, target_data, vel, acc);
            else if ((radioButtonAxis.Checked == true) && (radioButtonPTP.Checked == true))
                NexRobotPaser.NexR_MovePtp(1, target_data, vel, acc);

            // LINE
            else if ((radioButtonTCP.Checked == true) && (radioButtonLINE.Checked == true))
                NexRobotPaser.NexR_Robot_MoveLine(1, target_data, Global_Var.Max_LINE_CIRCLE_Vel, Global_Var.LINE_CIRCLE_Acc);
            else
                NexRobotPaser.NexR_Robot_MoveLine(0, target_data, Global_Var.Max_LINE_CIRCLE_Vel, Global_Var.LINE_CIRCLE_Acc);

            Global_Var.speed_ratio = 100;
            Speed_Ratio_Label.Text = Global_Var.speed_ratio.ToString();

            button5.Enabled = true;
           
        }

        public void m_Get_Current_Pos_Vel_Acc_data(double[] target_data, double[] vel, double[] acc)
        {

            NexRobotPos Robot_Pos = new NexRobotPos();
            NexRobotPaser.NexR_GetRobotPosition(ref Robot_Pos);

            target_data[0] = Robot_Pos.Axis_Data[0];
            target_data[1] = Robot_Pos.Axis_Data[1];
            target_data[2] = Robot_Pos.Axis_Data[2];
            target_data[3] = Robot_Pos.Axis_Data[3];
            target_data[4] = Robot_Pos.Axis_Data[4];
            target_data[5] = Robot_Pos.Axis_Data[5];

            vel[0] = Global_Var.Max_PTP_Vel;
            vel[1] = Global_Var.Max_PTP_Vel;
            vel[2] = Global_Var.Max_PTP_Vel;
            vel[3] = Global_Var.Max_PTP_Vel;
            vel[4] = Global_Var.Max_PTP_Vel;
            vel[5] = Global_Var.Max_PTP_Vel;

            acc[0] = Global_Var.PTP_Acc;
            acc[1] = Global_Var.PTP_Acc;
            acc[2] = Global_Var.PTP_Acc;
            acc[3] = Global_Var.PTP_Acc;
            acc[4] = Global_Var.PTP_Acc;
            acc[5] = Global_Var.PTP_Acc;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            NexRobotPaser.NexR_EmgStop();
            button5.Enabled = false;
        }

        private void Form1_Leave(object sender, EventArgs e)
        {
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Setting_new_Form.ShowDialog(this);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            NexRobotPaser.NexR_UserDefined();
           
        }

        private void button8_Click(object sender, EventArgs e)
        {
            NexRobotPaser.NexR_ResetSafetyAlarm();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            uint Start_Reset = 0;

            if (Global_Var.DO_List.Count() != 0)
            {
                if (Global_Var.DO_List[0].outdata[Start_Reset] == 0)
                {
                    Global_Var.DO_List[0].outdata[Start_Reset] = 1;
                    NexRobotPaser.NexR_SetDIO(0, Global_Var.DO_List[0].outdata);
                    DO0.FillColor = Color.Red;
                    //button9.Enabled = false;                    
                }                
            }

            // enable buttons
            button2.Enabled = true; // exit
            button3.Enabled = true; // servo on/off
            button6.Enabled = true; // setting
            button8.Enabled = true; // safety alarm
        }

        private void button10_Click(object sender, EventArgs e)
        {
            uint BK_index = 1;

            if (Global_Var.DO_List.Count() != 0)
            {
                if (Global_Var.DO_List[0].outdata[BK_index] == 0)
                {
                    Global_Var.DO_List[0].outdata[BK_index] = 1;
                    NexRobotPaser.NexR_SetDIO(0, Global_Var.DO_List[0].outdata);
                    DO1.FillColor = Color.Red;
                    button10.Text = "BK ON";
                }
                else 
                {
                    Global_Var.DO_List[0].outdata[BK_index] = 0;
                    NexRobotPaser.NexR_SetDIO(0, Global_Var.DO_List[0].outdata);
                    DO1.FillColor = Color.White;
                    button10.Text = "BK OFF";
                }
            }
        }

        private void UpdatePtpLabelTxtInfo(NexRobotPos tInPos)
        {
            // Update label info
            if (radioButtonTCP.Checked == true)
            {
                label25.Text = "C";
                label26.Text = "B";
                label27.Text = "A";
                label28.Text = "Z";
                label29.Text = "Y";
                label30.Text = "X";
            }
            else //if (radioButtonAxis.Checked == true)
            {
                label25.Text = "A6";
                label26.Text = "A5";
                label27.Text = "A4";
                label28.Text = "A3";
                label29.Text = "A2";
                label30.Text = "A1";
            }

            // Update input parameter if mode setting is changed
            if (u1AxisRdButtonChecked != radioButtonAxis.Checked)
            {
                if (u1AxisRdButtonChecked == true)
                {
                    textBox1.Text = tInPos.Tcp[0].ToString("00.000");
                    textBox2.Text = tInPos.Tcp[1].ToString("00.000");
                    textBox3.Text = tInPos.Tcp[2].ToString("00.000");
                    textBox4.Text = tInPos.Tcp[3].ToString("00.000");
                    textBox5.Text = tInPos.Tcp[4].ToString("00.000");
                    textBox6.Text = tInPos.Tcp[5].ToString("00.000");
                }
                else
                {
                    textBox1.Text = tInPos.Axis_Data[0].ToString("00.000");
                    textBox2.Text = tInPos.Axis_Data[1].ToString("00.000");
                    textBox3.Text = tInPos.Axis_Data[2].ToString("00.000");
                    textBox4.Text = tInPos.Axis_Data[3].ToString("00.000");
                    textBox5.Text = tInPos.Axis_Data[4].ToString("00.000");
                    textBox6.Text = tInPos.Axis_Data[5].ToString("00.000");
                }

                u1AxisRdButtonChecked = radioButtonAxis.Checked;
            }
        }

        private void label66_Click(object sender, EventArgs e)
        {
         
        }

        private void Speed_Ratio_Plus_button_Click(object sender, EventArgs e)
        {
            Global_Var.speed_ratio = Global_Var.speed_ratio + 10;
            if (Global_Var.speed_ratio > 100)
                Global_Var.speed_ratio = 100;

            Speed_Ratio_Label.Text = Global_Var.speed_ratio.ToString();

            NexRobotPaser.NexR_ChangePTPVel((byte)Global_Var.speed_ratio);            
        }

        private void Speed_Ratio_Minus_button_Click(object sender, EventArgs e)
        {
            Global_Var.speed_ratio = Global_Var.speed_ratio - 10;
            if (Global_Var.speed_ratio < 0)
                Global_Var.speed_ratio = 0;

            Speed_Ratio_Label.Text = Global_Var.speed_ratio.ToString();

            NexRobotPaser.NexR_ChangePTPVel((byte)Global_Var.speed_ratio);
        }

        private void SET_OP_Mode_button_Click(object sender, EventArgs e)
        {
            switch (OPModecomboBox.SelectedIndex)
            {
                case 0: // CSP
                    NexRobotPaser.NexR_ChangeOpMode(8);
                    break;
                case 1: // CSV
                    NexRobotPaser.NexR_ChangeOpMode(9);
                    break;
                case 2: // CST
                    NexRobotPaser.NexR_ChangeOpMode(10);
                    break;
            }
        }

        private void radioButtonAxis_CheckedChanged(object sender, EventArgs e)
        {

        }
    }

    public class Global_Var
    {
        public static double Max_PTP_Vel;
        public static double PTP_Acc;
        public static double Max_LINE_CIRCLE_Vel;
        public static double LINE_CIRCLE_Acc;
        public static List<NEXROBOT_DO> DO_List = new List<NEXROBOT_DO>();
        public static int servo;
        public static int speed_ratio = 100;
        //public static uint[] DO_Data = new uint[16];
    }
}
