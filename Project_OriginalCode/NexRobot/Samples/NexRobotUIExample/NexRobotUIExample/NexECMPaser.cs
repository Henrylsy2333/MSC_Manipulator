using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace NexECM
{
    class NexECMPaser
    {
        #region ImportNEXECM dll
        public const string NEXECM_DLL = "C:\\Windows\\System32\\NexEcm.dll";

        //*******************************************************************************
        //  NexEcm-APIs define here
        //*******************************************************************************
        [DllImport(NEXECM_DLL, EntryPoint = "NEC_StartDriver", CallingConvention = CallingConvention.StdCall)]
        public static extern int NEC_StartDriver();
        
        [DllImport(NEXECM_DLL, EntryPoint = "NEC_GetAvailableDriverCount", CallingConvention = CallingConvention.StdCall)]
        public static extern UInt16 NEC_GetAvailableDriverCount();

        [DllImport(NEXECM_DLL, EntryPoint = "NEC_GetMasterType", CallingConvention = CallingConvention.StdCall)]
        public static extern ushort NEC_GetMasterType(ushort MasterId, ref ushort Type);

        [DllImport(NEXECM_DLL, EntryPoint = "NEC_GetRtMasterId", CallingConvention = CallingConvention.StdCall)]
        public static extern int NEC_GetRtMasterId(ref ushort pMasterId);

        [DllImport(NEXECM_DLL, EntryPoint = "NEC_ResetEcMaster", CallingConvention = CallingConvention.StdCall)]
        public static extern int NEC_ResetEcMaster(ushort pMasterId);

        [DllImport(NEXECM_DLL, EntryPoint = "NEC_LoadRtxApp", CallingConvention = CallingConvention.StdCall)]
        public static extern int NEC_LoadRtxApp(string RtxFileName); 
        
        [DllImport(NEXECM_DLL, EntryPoint = "NEC_LoadNetworkConfig", CallingConvention = CallingConvention.StdCall)]
        public static extern int NEC_LoadNetworkConfig(ushort MasterId, string ConfigurationFile, uint Option); // Load ENI file 
        #endregion

        #region kernel32 dll
        [DllImport("C:\\Windows\\System32\\kernel32.dll", EntryPoint = "GetPrivateProfileString", CallingConvention = CallingConvention.StdCall)]
        public static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);        
        #endregion

        public static void ShowECMErrorMessage(int Error_code)
        {
            switch (Error_code)
            {
                case -10: // File not found or File open failed.
                    {
                        string MsgBox_Title = "路徑或檔名錯誤";
                        DialogResult dialog_result = MessageBox.Show(MsgBox_Title, "Error!!", MessageBoxButtons.OK);
                    }
                    break;
                default:
                    {
                        string MsgBox_Title = "尚未定義錯誤代碼";
                        DialogResult dialog_result = MessageBox.Show(MsgBox_Title, "Error!!", MessageBoxButtons.OK);
                    }
                    break;
            }
        }

    }
}
