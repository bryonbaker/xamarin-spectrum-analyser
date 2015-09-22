//
//  SuperpoweredSimpleXCodeWrapper.h
//  SuperpoweredXCodeWrapper
//
//  Created by Bryon on 6/09/2015.
//  Copyright (c) 2015 Bryon Baker. All rights reserved.
//

#ifndef __SuperpoweredXCodeWrapper__SuperpoweredSimpleXCodeWrapper__
#define __SuperpoweredXCodeWrapper__SuperpoweredSimpleXCodeWrapper__

#include "SuperpoweredSimple.h"

/**
 @fn SuperpoweredInterleave(float *left, float *right, float *output, unsigned int numberOfSamples);
 @brief Makes an interleaved output from two input channels.
 
 @param left Input for left channel.
 @param right Input for right channel.
 @param output Interleaved output.
 @param numberOfSamples The number of samples to process. Should be 4 minimum, must be exactly divisible with 4.
 */
extern "C" void SuperpoweredSimple_SuperpoweredInterleave(float left[], float right[], float output[], unsigned int numberOfSamples);

#endif /* defined(__SuperpoweredXCodeWrapper__SuperpoweredSimpleXCodeWrapper__) */
