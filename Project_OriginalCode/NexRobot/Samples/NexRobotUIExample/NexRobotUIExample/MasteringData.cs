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
    public partial class MasteringData : Form
    {
        public MasteringData()
        {
            InitializeComponent();
        }

        private void MasteringData_Load(object sender, EventArgs e)
        {
            double[] mastering_data = new double[6];
            byte[] isReverseMotor = new byte[6];

            if (0 == NexRobotPaser.NexR_GetMasteringData(mastering_data, isReverseMotor))
            {
                A1_textBox.Text = mastering_data[0].ToString("00.0000");
                A2_textBox.Text = mastering_data[1].ToString("00.0000");
                A3_textBox.Text = mastering_data[2].ToString("00.0000");
                A4_textBox.Text = mastering_data[3].ToString("00.0000");
                A5_textBox.Text = mastering_data[4].ToString("00.0000");
                A6_textBox.Text = mastering_data[5].ToString("00.0000");

                if (isReverseMotor[0] == 1) checkBox1_reverseDir.Checked = true; else checkBox1_reverseDir.Checked = false;
                if (isReverseMotor[1] == 1) checkBox2_reverseDir.Checked = true; else checkBox2_reverseDir.Checked = false;
                if (isReverseMotor[2] == 1) checkBox3_reverseDir.Checked = true; else checkBox3_reverseDir.Checked = false;
                if (isReverseMotor[3] == 1) checkBox4_reverseDir.Checked = true; else checkBox4_reverseDir.Checked = false;
                if (isReverseMotor[4] == 1) checkBox5_reverseDir.Checked = true; else checkBox5_reverseDir.Checked = false;
                if (isReverseMotor[5] == 1) checkBox6_reverseDir.Checked = true; else checkBox6_reverseDir.Checked = false;
            }
        }

        private void button_OK_Click(object sender, EventArgs e)
        {
            double[] mastering_data = new double[6];
            byte[] isReverseMotor = new byte[6];

            mastering_data[0] = double.Parse(A1_textBox.Text);
            mastering_data[1] = double.Parse(A2_textBox.Text);
            mastering_data[2] = double.Parse(A3_textBox.Text);
            mastering_data[3] = double.Parse(A4_textBox.Text);
            mastering_data[4] = double.Parse(A5_textBox.Text);
            mastering_data[5] = double.Parse(A6_textBox.Text);

            if (checkBox1_reverseDir.Checked) isReverseMotor[0] = 1; else isReverseMotor[0] = 0;
            if (checkBox2_reverseDir.Checked) isReverseMotor[1] = 1; else isReverseMotor[1] = 0;
            if (checkBox3_reverseDir.Checked) isReverseMotor[2] = 1; else isReverseMotor[2] = 0;
            if (checkBox4_reverseDir.Checked) isReverseMotor[3] = 1; else isReverseMotor[3] = 0;
            if (checkBox5_reverseDir.Checked) isReverseMotor[4] = 1; else isReverseMotor[4] = 0;
            if (checkBox6_reverseDir.Checked) isReverseMotor[5] = 1; else isReverseMotor[5] = 0;

            if (0 != NexRobotPaser.NexR_SetMasteringData(mastering_data, isReverseMotor))
            {
                string MsgBox_Title = "SetMasteringData Failed!!";
                DialogResult dialog_result = MessageBox.Show(MsgBox_Title, "Error!!", MessageBoxButtons.OK);                                
            }

            if (0 == NexRobotPaser.NexR_GetMasteringData(mastering_data, isReverseMotor))
            {
                A1_textBox.Text = mastering_data[0].ToString("00.0000");
                A2_textBox.Text = mastering_data[1].ToString("00.0000");
                A3_textBox.Text = mastering_data[2].ToString("00.0000");
                A4_textBox.Text = mastering_data[3].ToString("00.0000");
                A5_textBox.Text = mastering_data[4].ToString("00.0000");
                A6_textBox.Text = mastering_data[5].ToString("00.0000");

                if (isReverseMotor[0] == 1) checkBox1_reverseDir.Checked = true; else checkBox1_reverseDir.Checked = false;
                if (isReverseMotor[1] == 1) checkBox2_reverseDir.Checked = true; else checkBox2_reverseDir.Checked = false;
                if (isReverseMotor[2] == 1) checkBox3_reverseDir.Checked = true; else checkBox3_reverseDir.Checked = false;
                if (isReverseMotor[3] == 1) checkBox4_reverseDir.Checked = true; else checkBox4_reverseDir.Checked = false;
                if (isReverseMotor[4] == 1) checkBox5_reverseDir.Checked = true; else checkBox5_reverseDir.Checked = false;
                if (isReverseMotor[5] == 1) checkBox6_reverseDir.Checked = true; else checkBox6_reverseDir.Checked = false;
            }
        }

        
    }
}
