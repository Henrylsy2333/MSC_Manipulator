using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Source;
namespace NexRobotUIExample
{
    public partial class Setting : Form
    {
        
        public Setting()
        {
            InitializeComponent();
        }
        public Form1 _Form1;
        int ret = 0;
        private void button_Servo_Click(object sender, EventArgs e)
        {
            if (Global_Var.servo == 1)
            {
                ret = NexRobotPaser.NexR_RobotServoOFF();
                Global_Var.servo = 0;
                button_Servo.Text  = "Servo On";
            }
            else 
            {
                ret = NexRobotPaser.NexR_RobotServoON();
                Global_Var.servo = 1;
                button_Servo.Text = "Servo Off";
            }

            
        }

        private void button_Reset_Click(object sender, EventArgs e)
        {
            int ret = 0;
            if (Global_Var.servo == 1)
            {
                ret = NexRobotPaser.NexR_RobotServoOFF();
                Global_Var.servo = 0;
            }
            NexRobotPaser.NexR_ReSetDriveError();

            //ret = NexRobotPaser.NexR_RobotServoON();
            //Global_Var.servo = 1;
        }

        private void button_OK_Click(object sender, EventArgs e)
        {
            //if (VEL_textBox.Text == "" || double.Parse(VEL_textBox.Text) > 50 || double.Parse(VEL_textBox.Text) <1 )
            //{
            //    VEL_textBox.Text = "30";
            //    string MsgBox_Title = "Velocity value is out of range!!.";
            //    DialogResult dialog_result = MessageBox.Show(MsgBox_Title, "Error!!", MessageBoxButtons.OK);

            //}

            //if (ACC_textBox.Text == "" || double.Parse(ACC_textBox.Text) > 20 || double.Parse(ACC_textBox.Text) < 1)
            //{
            //    ACC_textBox.Text = "15";
            //    string MsgBox_Title = "Acceleration value is out of range!!";
            //    DialogResult dialog_result = MessageBox.Show(MsgBox_Title, "Error!!", MessageBoxButtons.OK);

            //}
            if (double.Parse(VEL_textBox.Text) > 360) // unit:deg/s
                Global_Var.Max_PTP_Vel = 360;
            else
                Global_Var.Max_PTP_Vel = double.Parse(VEL_textBox.Text);

            Global_Var.PTP_Acc = double.Parse(ACC_textBox.Text);

            VEL_textBox.Text = Global_Var.Max_PTP_Vel.ToString("00.000");
            ACC_textBox.Text = Global_Var.PTP_Acc.ToString("00.000");
        }

        private void Setting_Load(object sender, EventArgs e)
        {
            VEL_textBox.Text = Global_Var.Max_PTP_Vel.ToString("00.000");
            ACC_textBox.Text = Global_Var.PTP_Acc.ToString("00.000");

            LineCircle_VELtextBox.Text = Global_Var.Max_LINE_CIRCLE_Vel.ToString("00.000");
            LineCircle_ACCtextBox.Text = Global_Var.LINE_CIRCLE_Acc.ToString("00.000");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MasteringData form = new MasteringData();
            form.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            NexRobotPaser.NexR_NER_ReInitializeDriverParameters();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Global_Var.Max_LINE_CIRCLE_Vel = double.Parse(LineCircle_VELtextBox.Text);
            Global_Var.LINE_CIRCLE_Acc = double.Parse(LineCircle_ACCtextBox.Text);

            LineCircle_VELtextBox.Text = Global_Var.Max_LINE_CIRCLE_Vel.ToString("00.000");
            LineCircle_ACCtextBox.Text = Global_Var.LINE_CIRCLE_Acc.ToString("00.000");
        }
    }
}
