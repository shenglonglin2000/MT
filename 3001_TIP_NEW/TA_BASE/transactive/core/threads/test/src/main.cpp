/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/threads/test/src/main.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This file contains the 'main' method for testing
  * the TA_Thread library.
  *
  */

#include "Test_TA_Thread.h"

#include "ThreadTest.h"

int main()
{
    // Set the debug information so we don't get the debug to standard output.
    TA_Base_Core::DebugUtil::getInstance().setLevel(TA_Base_Core::DebugUtil::DebugDebug);
    TA_Base_Core::DebugUtil::getInstance().setFile("./TA_Thread_Test.log");
    
    TestRunner runner;

    ThreadTest testcase("ThreadTest");
	runner.addSuite( testcase.suite() );
    
    try
    {
        // Run config file. Make sure it is in the cfg directory.
        runner.begin( "./cfg/config.ini" );
    }
    catch (...)
    {
		std::cout << "Caught an unhandled exception" << std::endl;
	}

 

    return 0;
}
