/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/main.cpp $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#include "TestGenericLogType.h"
#include "TestPreformattedLogType.h"
#include "TestLogger.h"
#include "TestDebugUtil.h"
#include "TestDebugUtilLogMacros.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/DebugUtil.h"

int main(int argc, char** argv)
{
    // Set a RunParams parameter so DebugUtil knows 
    // which types of exceptions to throw

    TA_Base_Core::RunParams::getInstance().set("Testing", "");
    TA_Base_Core::DebugUtil::getInstance().setLevel(TA_Base_Core::DebugUtil::DebugTrace);

    TestRunner* runner = new TestRunner();

    TestGenericLogType		* testcase1 = new TestGenericLogType		("TestGenericLogType");
    TestPreformattedLogType * testcase2 = new TestPreformattedLogType   ("TestPreformattedLogType");
	TestLogger			    * testcase3 = new TestLogger			    ("TestLogger");
	TestDebugUtil			* testcase4 = new TestDebugUtil			    ("TestDebugUtil");
	TestDebugUtilLogMacros	* testcase5 = new TestDebugUtilLogMacros	("TestDebugUtilLogMacros");

    runner->addSuite( testcase1->suite () );                // Adds all test methods to the framework
    runner->addSuite( testcase2->suite () );                // Adds all test methods to the framework
	runner->addSuite( testcase3->suite () );                // Adds all test methods to the framework
	runner->addSuite( testcase4->suite () );                // Adds all test methods to the framework
	runner->addSuite( testcase5->suite () );                // Adds all test methods to the framework

    // Default, ie no parameters passed
    if (argc == 1)
    {
        // Run config file. Make sure it is in your WINNT directory.
#ifdef WIN32
		runner->begin( "./config.ini" );
#else
		runner->begin( "./config.solaris.ini" );
#endif // WIN32
    }
    else
    {
        runner->begin ( argv[1] );

    }

    delete testcase1;
    delete testcase2;
	delete testcase3;
	delete testcase4;
	delete testcase5;

    delete runner;


    return 0;

}
