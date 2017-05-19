using Foundation;

namespace SuperpoweredXCodeWrapper
{
	// @interface SuperpoweredFrequencies : NSObject
	[BaseType (typeof(NSObject))]
	interface SuperpoweredFrequencies
	{
		// -(void)getFrequencies:(float *)freqs;
		[Export ("getFrequencies:")]
		unsafe void GetFrequencies (float* freqs);
	}
}
