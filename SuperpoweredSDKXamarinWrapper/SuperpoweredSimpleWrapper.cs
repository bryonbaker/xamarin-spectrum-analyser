using System;
using System.Runtime.InteropServices;

namespace SuperpoweredSDKXamarinWrapper
{
	public static class SuperpoweredSimpleWrapper
	{
		[DllImport("__Internal", EntryPoint = "SuperpoweredSimple_SuperpoweredInterleave")]
		public static extern IntPtr SuperpoweredInterleave(float[] left, float[] right, float[] output, uint numberOfSamples);
	}
}

