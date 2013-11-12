/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/AssertBreak/src/main.cpp $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * A simple test to check that TA_ASSERT_FAIL=BREAK functions
  * as desired whilst debugging.
  *
  */

#define TA_ASSERT_FAIL BREAK

#include <iostream>
#include "core/exceptions/src/AssertException.h"
#include "core/threads/src/Thread.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

/**
 * Look, its a loop!
 *
 * Just here to make test look more complex ;)
 */
void loop()
{
    for ( int i=0; i<10; i++ )
    {
        TA_Base_Core::Thread::sleep(10);
    }
}

/**
 * Debugger should break inside this function.
 */
void breakpoint()
{
    // The debugger should break on this line!
    TA_ASSERT( false, "I should cause the debugger to break!" );
}

/**
 * An exception should be throw, however debugger should not break.
 */
void exception1()
{
    TA_DEBUG_ASSERT( false, "TA_DEBUG_ASSERT: exception1" );
}

/**
 * An exception should be throw, however debugger should not break.
 */
void exception2()
{
    TA_THROW( TA_Base_Core::AssertException( "TA_THROW: exception2" ) );
}

/**
 * A simple function to test if the debugger will break when an assertion
 * is generated and TA_ASSERT_FAIL=BREAK.
 */
int main()
{
    // Should have no worries
    loop();

    // Should get an exception, but no break.
    try
    {
        exception1();
    }
    catch ( TA_Base_Core::AssertException& ex )
    {
        std::cout << "Exception = {" << std::endl << ex.what() << std::endl << "}" << std::endl;
    }

    // Should get an exception, but no break.
    try
    {
        exception2();
    }
    catch ( TA_Base_Core::AssertException& ex )
    {
        std::cout << "Exception = {" << std::endl << ex.what() << std::endl << "}" << std::endl;
    }
    
    // Should get a break occurring inside this function.
    breakpoint();

    return 0;
}
