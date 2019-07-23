using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Sample2AexsControl
{
    public partial class MainForm : Form
    {
        ushort Master_Id;
        string EVN_NAME = "Event";
        string SHN_NAME = "Memory";
        System.IntPtr PVOID;
        System.IntPtr obHandle;
        System.IntPtr shHandle;

        public MainForm()
        {
            InitializeComponent();
            textBox_target_pos.Text = "5000";
            textBox_target_pos1.Text = "5000";
            textBox_v.Text = "10000";
            textBox_v1.Text = "10000";
            textBox_a.Text = "100000";
            textBox_a1.Text = "100000";
            int ret = 0;
            ret = NexECM.NEC_LoadRtxApp("C:\\Program Files\\NEXCOM\\NexECMRtx\\Lib\\NexECMRtx\\x32\\NexECMRtx.rtss");
            if (ret != 0) { MessageBox.Show("NEC_LoadRtxApp failed! error = " + Convert.ToInt32(ret).ToString()); return; }

        }

        unsafe public struct WIN32_DAT
        {
            public int mAxis1;
            public int mAxis2;
            public ushort masterId;
            public int ActualPos1;
            public int ActualPos2;
            public int TargetPos1;
            public int TargetPos2;
            public ushort MasterState;
            public ushort SlaveState1;
            public ushort SlaveState2;
            public byte Move_Type1;
            public byte Move_Type2;
            public int ACC_DEC1;
            public int ACC_DEC2;
            public int Velocity1;
            public int Velocity2;
        }

        unsafe WIN32_DAT* abc;

        unsafe private void button_start_Click(object sender, EventArgs e)
        {
            int ret = 0;
            Master_Id = 1;

            ret = NexECM.NEC_StartDriver();
            if (ret != 0) { MessageBox.Show("NEC_StartDriver failed! error = " + Convert.ToInt32(ret).ToString()); NexECM.NEC_StopDriver(); this.Close(); return; }

            ret = NexECM.NEC_ResetEcMaster(Master_Id);
            if (ret != 0) { MessageBox.Show("NEC_ResetEcMaster failed! error = " + Convert.ToInt32(ret).ToString()); NexECM.NEC_StopDriver(); this.Close(); return; }

            ret = NexECM.NEC_LoadNetworkConfig(Master_Id, "C:\\ENI_NexCAT_Export.xml", 1);
            if (ret != 0) { MessageBox.Show("NEC_LoadNetworkConfig failed! error = " + Convert.ToInt32(ret).ToString()); NexECM.NEC_StopDriver(); this.Close(); return; }

            ret = NexECM.NEC_StopDriver();
            if (ret != 0) { MessageBox.Show("NEC_StopDriver failed! error = " + Convert.ToInt32(ret).ToString()); NexECM.NEC_StopDriver(); this.Close(); return; }

            ret = NexECM.NEC_LoadRtxApp("C:\\Program Files\\NEXCOM\\NexECMRtx\\Samples\\RTX2012\\Sample_2Layer\\VS2010\\Sample2AxesControl_C#\\RTSSDebug\\RtxApp.rtss");
            if (ret != 0) { MessageBox.Show("NEC_LoadRtxApp failed! error = " + Convert.ToInt32(ret).ToString()); return; }
          
            shHandle = Sample2AexsControl.rtapi.RtOpenSharedMemory(3, 0, SHN_NAME, ref PVOID);
            
            abc = (WIN32_DAT*)PVOID;

            abc->TargetPos1 = Convert.ToInt32(textBox_target_pos.Text);
            abc->TargetPos2 = Convert.ToInt32(textBox_target_pos1.Text);
            abc->ACC_DEC1 = Convert.ToInt32(textBox_a.Text);
            abc->ACC_DEC2 = Convert.ToInt32(textBox_a1.Text);
            abc->Velocity1 = Convert.ToInt32(textBox_v.Text);
            abc->Velocity2 = Convert.ToInt32(textBox_v1.Text);
            
            obHandle = Sample2AexsControl.rtapi.RtOpenEvent(0, 0, EVN_NAME);

            Sample2AexsControl.rtapi.RtSetEvent(obHandle);

            timer1.Enabled = true;
        }

        unsafe private void timer1_Tick(object sender, EventArgs e)
        {
            abc = (WIN32_DAT*)PVOID;
            textBox_actual_pos.Text = abc->ActualPos1.ToString();
            textBox_actual_pos1.Text = abc->ActualPos2.ToString();
            textBox_master_state.Text = abc->MasterState.ToString();
            textBox_slave_state.Text = abc->SlaveState1.ToString();
            textBox_slave_state1.Text = abc->SlaveState2.ToString();
        }

        private void button_exit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
