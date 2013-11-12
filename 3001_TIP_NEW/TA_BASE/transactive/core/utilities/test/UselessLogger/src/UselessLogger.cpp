/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/UselessLogger/src/UselessLogger.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This is just a small program that will produce a log file that can be
  * for errors.
  *
  */

#include "UselessClass.h"
#include "core/utilities/src/RunParams.h"
#include <fstream>
#ifdef SOLARIS
#include <unistd.h>
#endif
UselessClass UselessClass::uselessInstance;

/**
 * This is where all the fireworks start from. (Program start)
 */
int main()
{
    // Remove the file
#ifdef WIN32
    _unlink( "Useless.1.log" );
#else
    unlink( "Useless.1.log" );
#endif

    // Setup the stuff.
    try
    {
        TA_Base_Core::DebugUtil::getInstance().setLevel( TA_Base_Core::DebugUtil::DebugTrace );
        TA_Base_Core::DebugUtil::getInstance().setFile( "Useless.log" );
    }
    catch( ... )
    {
        return 1;
    }

    // Make the useless call.
    UselessClass::uselessInstance.uselessMethod();

    return 0;
}
