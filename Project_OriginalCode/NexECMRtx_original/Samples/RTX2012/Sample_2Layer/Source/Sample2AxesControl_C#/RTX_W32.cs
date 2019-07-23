using System;
using System.Collections;
using System.Text;
using System.Runtime.InteropServices;

namespace Sample2AexsControl
{
    class rtapi
    {
        public const string RTX_DLL = "rtapi_w32.dll";
        [DllImport(RTX_DLL, EntryPoint = "RtOpenEvent")]
        public static extern System.IntPtr RtOpenEvent(
            int dwDesiredAccess,
            int bInheritHandle,
            string lpName);
        [DllImport(RTX_DLL, EntryPoint = "RtSetEvent")]
        public static extern bool RtSetEvent(System.IntPtr hEvent);

        [DllImport(RTX_DLL, EntryPoint = "RtOpenSharedMemory")]
        unsafe public static extern System.IntPtr RtOpenSharedMemory(
             int DesiredAccess,
             int bInheritHandle,
             string lpName,
             ref IntPtr addr);
    }
}