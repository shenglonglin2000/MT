/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/main.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This file contains the 'main' method for testing
  * the TA_Synchonisation library.
  *
  */

#include "Test_TA_Synchronisation.h"

#include "SemaphoreTest.h"
#include "ConditionTest.h"
#include "ThreadGuardTest.h"
#include "ThreadReadGuardTest.h"
#include "ThreadLockableHolderVerifierTest.h"
#include "NonReEntrantThreadLockableTest.h"
#include "ReEntrantThreadLockableTest.h"
#include "ReadWriteThreadLockableTest.h"
#include "WriteReadThreadLockableTest.h"

int main()
{
    // Set the debug information so we don't get the debug to standard output.
    TA_Base_Core::DebugUtil::getInstance().setLevel(TA_Base_Core::DebugUtil::DebugDebug);
    TA_Base_Core::DebugUtil::getInstance().setFile("./TA_Synchronisation_Test.log");
    
    TestRunner runner;

    SemaphoreTest testcase1("SemaphoreTest");
	runner.addSuite( testcase1.suite() );
    ConditionTest testcase2("ConditionTest");
	runner.addSuite( testcase2.suite() );
    ThreadReadGuardTest testcase3("ThreadReadGuardTest");
	runner.addSuite( testcase3.suite() );
    ThreadGuardTest testcase4("ThreadGuardTest");
	runner.addSuite( testcase4.suite() );
    ThreadLockableHolderVerifierTest testcase5("ThreadLockableHolderVerifierTest");
	runner.addSuite( testcase5.suite() );
    NonReEntrantThreadLockableTest testcase6("NonReEntrantThreadLockableTest");
	runner.addSuite( testcase6.suite() );
    ReEntrantThreadLockableTest testcase7("ReEntrantThreadLockableTest");
	runner.addSuite( testcase7.suite() );
    ReadWriteThreadLockableTest testcase8("ReadWriteThreadLockableTest");
	runner.addSuite( testcase8.suite() );
    WriteReadThreadLockableTest testcase9("WriteReadThreadLockableTest");
	runner.addSuite( testcase9.suite() );
    
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
