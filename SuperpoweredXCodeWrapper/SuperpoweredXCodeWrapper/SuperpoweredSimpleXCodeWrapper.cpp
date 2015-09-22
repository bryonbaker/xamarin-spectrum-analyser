//
//  SuperpoweredSimpleXCodeWrapper.cpp
//  SuperpoweredXCodeWrapper
//
//  Created by Bryon on 6/09/2015.
//  Copyright (c) 2015 Bryon Baker. All rights reserved.
//

#include "SuperpoweredWrapperUtilities.h"
#include "SuperpoweredSimpleXCodeWrapper.h"

void SuperpoweredSimple_SuperpoweredInterleave(float left[], float right[], float output[], unsigned int numberOfSamples)
{
    try
    {        
        // Number of samples must be divisible by 4.
        if( numberOfSamples % 4 != 0 )
        {
            WriteErrorToSyslog( "ERROR: numberOfSamples must be divisible by 4 in SuperpoweredSimple_SuperpoweredInterleave()\n" );
            
            return;
        }
        
        SuperpoweredInterleave(left, right, output, numberOfSamples);
        
        return;
    }
    catch ( ... ) // You cannot allow an exception to propagate from unmanaged code into managed code.
    
    {
        WriteErrorToSyslog( "Exception thrown in unmanaged code SuperpoweredSimple_SuperpoweredInterleave().\n" );
    }

    return;
}