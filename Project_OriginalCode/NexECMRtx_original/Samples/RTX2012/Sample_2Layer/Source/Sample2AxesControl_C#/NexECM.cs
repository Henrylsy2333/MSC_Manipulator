using System;
using System.Collections;
using System.Text;
using System.Runtime.InteropServices;

namespace Sample2AexsControl
{
    class NexECM
    {
        public const string ECM_DLL = "NexEcm.dll";

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetVersion")]
        public static extern uint NEC_GetVersion();

        [DllImport(ECM_DLL, EntryPoint = "NEC_StartDriver")]
        public static extern int NEC_StartDriver();

        [DllImport(ECM_DLL, EntryPoint = "NEC_StopDriver")]
        public static extern int NEC_StopDriver();

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetAvailableDriverCount")]
        public static extern ushort NEC_GetAvailableDriverCount();

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetMasterType")]
        public static extern ushort NEC_GetMasterType(ushort MasterId, ref ushort Type);

        [DllImport(ECM_DLL, EntryPoint = "NEC_SetParameter")]
        public static extern int NEC_SetParameter(ushort MasterId, ushort ParaNum, UInt32 ParaData);
        
        [DllImport(ECM_DLL, EntryPoint = "NEC_GetParameter")]
        public static extern int NEC_GetParameter(ushort MasterId, ushort ParaNum, ref UInt32 ParaData);

        //
        [DllImport(ECM_DLL, EntryPoint = "NEC_StartNetwork")]
        public static extern int NEC_StartNetwork(ushort MasterId, string ConfigurationFile, int TimeoutMs);

        [DllImport(ECM_DLL, EntryPoint = "NEC_StartNetworkEx")]
        public static extern int NEC_StartNetworkEx(ushort MasterId, string ConfigurationFile, int Option, int TimeoutMs);

        [DllImport(ECM_DLL, EntryPoint = "NEC_StopNetwork")]
        public static extern int NEC_StopNetwork(ushort MasterId, int TimeoutMs);

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetSlaveCount")]
        public static extern int NEC_GetSlaveCount(ushort MasterId, ref uint Count);

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetNetworkState")]
        public static extern int NEC_GetNetworkState(ushort MasterId, ref ushort State);

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetSlaveState")]
        public static extern int NEC_GetSlaveState(ushort MasterId, ushort SlaveIndex, byte[] StateArr, ref ushort ArrLen);

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetStateError")]
        public static extern int NEC_GetStateError(ushort MasterId, ref int Code);// Return error code.
        [DllImport(ECM_DLL, EntryPoint = "NEC_GetErrorMsg")]
        public static extern int NEC_GetErrorMsg(ushort MasterId, StringBuilder ErrMsg_128_len); // Return error message when state error.

        //*** Application functions ****
        // <<< non-synchronized DIO functions, set DO value to memory only. >>> 
        [DllImport(ECM_DLL, EntryPoint = "NEC_SetDo")]
        public static extern int NEC_SetDo(ushort MasterId, ushort SlaveAddr, ushort Offset, ushort SizeByte, byte[] DoData);
        [DllImport(ECM_DLL, EntryPoint = "NEC_GetDo")]
        public static extern int NEC_GetDo(ushort MasterId, ushort SlaveAddr, ushort Offset, ushort SizeByte, byte[] DoData);
        [DllImport(ECM_DLL, EntryPoint = "NEC_GetDi")]
        public static extern int NEC_GetDi(ushort MasterId, ushort SlaveAddr, ushort Offset, ushort SizeByte, byte[] DoData);

        // <<< synchronized DIO functions, set DO value to memory and wait master accepted. >>>
        [DllImport(ECM_DLL, EntryPoint = "NEC_SetDo_s")]
        public static extern int NEC_SetDo_s(ushort MasterId, ushort SlaveAddr, ushort Offset, ushort SizeByte, byte[] DoData);


        [DllImport(ECM_DLL, EntryPoint = "NEC_SDODownloadEx")]
        public static extern int NEC_SDODownloadEx(ushort MasterId, ushort SlaveIndex,
                                                 ushort Index
                                                , byte SubIndex     // [i]   Objec sub-index
                                                , byte CtrlFlag     // [i]   Control flag, bit 0: Complete access
                                                , uint DataLenByte  // [i/o] Lengh of input or output data. 
                                                , byte[] DataPtr      // [i/o] point ot input or output data.
                                                , ref UInt32 AbortCode);    // [o]   SDO abort code*/

        [DllImport(ECM_DLL, EntryPoint = "NEC_SDOUploadEx")]
        public static extern int NEC_SDOUploadEx(ushort MasterId, ushort SlaveIndex,
                                                 ushort Index
                                                , byte SubIndex     // [i]   Objec sub-index
                                                , byte CtrlFlag     // [i]   Control flag, bit 0: Complete access
                                                , uint DataLenByte  // [i/o] Lengh of input or output data. 
                                                , byte[] DataPtr      // [i/o] point ot input or output data.
                                                , ref UInt32 AbortCode);    // [o]   SDO abort code*/

        [DllImport(ECM_DLL, EntryPoint = "NEC_RWProcessImage")]
        public static extern int NEC_RWProcessImage(ushort MasterId, ushort RW, ushort Offset, byte[] Data, ushort Size);
        [DllImport(ECM_DLL, EntryPoint = "NEC_GetProcessImageSize")]
        public static extern int NEC_GetProcessImageSize(ushort MasterId, ref ushort SizeOfInputByte, ref ushort SizeOfOutputByte);
        [DllImport(ECM_DLL, EntryPoint = "NEC_RWSlaveProcessImage")]
        public static extern int NEC_RWSlaveProcessImage(ushort MasterId, ushort SlaveIndex, ushort RW, ushort Offset, byte[] Data, ushort Size);
        
        //*************************************
        //*** API for realtime applications ***
        //*************************************
        [DllImport(ECM_DLL, EntryPoint = "NEC_GetRtMasterId")]
        unsafe public static extern int NEC_GetRtMasterId(ref ushort MasterId);

        [DllImport(ECM_DLL, EntryPoint = "NEC_ResetEcMaster")]
        unsafe public static extern int NEC_ResetEcMaster(ushort MasterId);

        [DllImport(ECM_DLL, EntryPoint = "NEC_LoadRtxApp")]
        public static extern int NEC_LoadRtxApp(string RtxFileName);

        [DllImport(ECM_DLL, EntryPoint = "NEC_KillRtxApp")]
        public static extern int NEC_KillRtxApp(uint ProcessId);

        [DllImport(ECM_DLL, EntryPoint = "NEC_LoadNetworkConfig")]
        public static extern int NEC_LoadNetworkConfig(ushort MasterId, string ConfigurationFile, uint Option); // Load ENI file 

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetRtMasterPorcessId")]
        public static extern int NEC_GetRtMasterPorcessId(ushort MasterId, ref uint pProcessID);

        [DllImport(ECM_DLL, EntryPoint = "NEC_GetRtMasterVersion")]
        public static extern int NEC_GetRtMasterVersion(ushort MasterId, ref uint pVersion);


    }
}