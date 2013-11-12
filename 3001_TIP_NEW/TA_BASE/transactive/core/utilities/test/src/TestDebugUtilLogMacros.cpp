/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestDebugUtilLogMacros.cpp $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#include <string>
#include <algorithm>
#include "TestDebugUtilLogMacros.h"
#include "ThreadThatCallsLog.h"
#include "core/threads/src/Thread.h"

using namespace TA_Base_Core;

// Initialises variables at the beginning of a test suite
void TestDebugUtilLogMacros::setUpSuite ( std::string const & INFile )
{
    // Use the INFile string to read in data,
    // this can change according the config file.
}


// Initialises variables at the end of a test suite
void TestDebugUtilLogMacros::tearDownSuite ()
{


}



void TestDebugUtilLogMacros::setUp ( const std::string & INFile , const std::string & OUTFile)
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}



void TestDebugUtilLogMacros::tearDown ( const std::string & OUTFile )
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}



void TestDebugUtilLogMacros::testLOGWithGenericLog()
{
	std::cout << "TestLOGWithGenericLog() ... " << std::endl; 

	// Calling Generic Log
	try
	{
		LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugFatal, "Testing LOG with Generic Log at FATAL level" ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}
 

void TestDebugUtilLogMacros::testLOGWithPreformattedLog()
{
	std::cout << "testLOGWithPreformattedLog() ... " << std::endl; 

	// Calling a Preformatted Log
	try
	{
		LOG ( SourceInfo, DebugUtil::FunctionEntry, "testLOGWithPreformattedLog" ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


void TestDebugUtilLogMacros::testLOGWithMultipleLOGs()
{
	std::cout << "testLOGWithMulipleLOGs() ... " << std::endl; 

	// Calling a Preformatted Log - Function Entry
	try
	{
		LOG ( SourceInfo, DebugUtil::FunctionEntry, "testLOGWithMulipleLOGs" ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionEntry" << std::endl;
		Assert ( false );
	}

	// Calling a number of Generic Logs
	try
	{
		int count = 0;
		char * level = "DEBUG";
		LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "MultipleLOG: %d: Generic Log at %s level", ++count, level ); 
		level = "INFO";
		LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "MultipleLOG: %d: Generic Log at %s level", ++count, level ); 
		level = "WARN";
		LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugWarn, "MultipleLOG: %d: Generic Log at %s level", ++count, level ); 
		level = "ERROR";
		LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugError, "MultipleLOG: %d: Generic Log at %s level", ++count, level ); 
		level = "FATAL";
		LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugFatal, "MultipleLOG: %d: Generic Log at %s level", ++count, level ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Generic Logs" << std::endl;
		Assert ( false );
	}

	// Calling a Preformatted Log - Function Exit
	try
	{
		LOG ( SourceInfo, DebugUtil::FunctionExit, "testLOGWithMulipleLOGs" ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionExit" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


void TestDebugUtilLogMacros::testLOGWithMultipleLOGsInDiffFunctions()
{
	std::cout << "testLOGWithMutilpleLOGsInDiffFunctions() ... " << std::endl; 

	// Calling a Preformatted Log - Function Entry
	try
	{
		LOG ( SourceInfo, DebugUtil::FunctionEntry, "testLOGWithMulipleLOGs" ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionEntry" << std::endl;
		Assert ( false );
	}

	// Calling method that calls LOG with Generic Log
	try
	{
		callingLOGWithGenericLog();	
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on callingLOGWithGenericLog" << std::endl;
		Assert ( false );
	}

	// Calling method that calls LOG with Preformatted Log
	try
	{
		callingLOGWithPreformattedLog();	
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on callingLOGWithPreformattedLog" << std::endl;
		Assert ( false );
	}

	// Calling a Preformatted Log - Function Exit
	try
	{
		LOG ( SourceInfo, DebugUtil::FunctionExit, "testLOGWithMulipleLOGs" ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionExit" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


void TestDebugUtilLogMacros::testLOGWithMultipleThreads()
{
	std::cout << "testLOGWithMulitpleThreads() ... " << std::endl; 

	ThreadThatCallsLog* logThread1 = new ThreadThatCallsLog ( ThreadThatCallsLog::Log );
	ThreadThatCallsLog* logThread2 = new ThreadThatCallsLog ( ThreadThatCallsLog::Log );
	ThreadThatCallsLog* logThread3 = new ThreadThatCallsLog ( ThreadThatCallsLog::Log );

	// Start the threads
	try
	{
		logThread1->start();
		logThread2->start();
		logThread3->start();

		int timeInMilliSecs = 500;
		Thread::sleep(timeInMilliSecs);

		logThread1->terminateAndWait();
		logThread2->terminateAndWait();
		logThread3->terminateAndWait();
	}
	catch ( ... )
	{
		delete logThread1;
		delete logThread2;
		delete logThread3;

		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	delete logThread1;
	delete logThread2;
	delete logThread3;

	std::cout << "Passed" << std::endl;
}


void TestDebugUtilLogMacros::testLOGMOREWithMultipleLOGMOREs()
{
	std::cout << "testLOGMOREWithMultipleLOGMOREs() ... " << std::endl; 

	// Calling a number of LOGMOREs
	try
	{
		int count = 0;
		LOGMORE ( SourceInfo, "MultipleLOG: %d: Generic Log", ++count ); 
		LOGMORE ( SourceInfo, "MultipleLOG: %d: Generic Log", ++count ); 
		LOGMORE ( SourceInfo, "MultipleLOG: %d: Generic Log", ++count ); 
		LOGMORE ( SourceInfo, "MultipleLOG: %d: Generic Log", ++count ); 
		LOGMORE ( SourceInfo, "MultipleLOG: %d: Generic Log", ++count ); 
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Generic Logs" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


void TestDebugUtilLogMacros::testLOGMOREWithMultipleThreads()
{
	std::cout << "testLOGMOREWithMultipleThreads() ... " << std::endl; 

	ThreadThatCallsLog* logThread1 = new ThreadThatCallsLog ( ThreadThatCallsLog::LogMore );
	ThreadThatCallsLog* logThread2 = new ThreadThatCallsLog ( ThreadThatCallsLog::LogMore );
	ThreadThatCallsLog* logThread3 = new ThreadThatCallsLog ( ThreadThatCallsLog::LogMore );

	// Start the threads
	try
	{
		logThread1->start();
		logThread2->start();
		logThread3->start();

		int timeInMilliSecs = 500;
		Thread::sleep(timeInMilliSecs);

		logThread1->terminateAndWait();
		logThread2->terminateAndWait();
		logThread3->terminateAndWait();
	}
	catch ( ... )
	{
		delete logThread1;
		delete logThread2;
		delete logThread3;

		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	delete logThread1;
	delete logThread2;
	delete logThread3;

	std::cout << "Passed" << std::endl;
}

void TestDebugUtilLogMacros::testLOGAndLOGMOREWithMultipleThreads()
{
	std::cout << "testLOGAndLOGMOREWithMultipleThreads() ... " << std::endl; 

	ThreadThatCallsLog* logThread1 = new ThreadThatCallsLog ( ThreadThatCallsLog::Mix );
	ThreadThatCallsLog* logThread2 = new ThreadThatCallsLog ( ThreadThatCallsLog::Mix );
	ThreadThatCallsLog* logThread3 = new ThreadThatCallsLog ( ThreadThatCallsLog::Mix );

	// Start the threads
	try
	{
		logThread1->start();
		logThread2->start();
		logThread3->start();

		int timeInMilliSecs = 500;
		Thread::sleep(timeInMilliSecs);

		logThread1->terminateAndWait();
		logThread2->terminateAndWait();
		logThread3->terminateAndWait();
	}
	catch ( ... )
	{
		delete logThread1;
		delete logThread2;
		delete logThread3;

		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	delete logThread1;
	delete logThread2;
	delete logThread3;

	std::cout << "Passed" << std::endl;
}


// The suite method. Returns list of methods.

TestSuite* TestDebugUtilLogMacros::suite ()
{
    // Must have same name as test class.
    TestSuite * testSuite = new TestSuite( "TestDebugUtilLogMacros" );

    testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGWithGenericLog", &TestDebugUtilLogMacros::testLOGWithGenericLog, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGWithPreformattedLog", &TestDebugUtilLogMacros::testLOGWithPreformattedLog, this ) );

	testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGWithMultipleLOGs", &TestDebugUtilLogMacros::testLOGWithMultipleLOGs, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGWithMultipleLOGsInDiffFunctions", &TestDebugUtilLogMacros::testLOGWithMultipleLOGsInDiffFunctions, this ) );
	/*
	testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGWithMultipleThreads", &TestDebugUtilLogMacros::testLOGWithMultipleThreads, this ) );
    */
	testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGMOREWithMultipleLOGMOREs", &TestDebugUtilLogMacros::testLOGMOREWithMultipleLOGMOREs, this ) );
	  
	testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGMOREWithMultipleThreads", &TestDebugUtilLogMacros::testLOGMOREWithMultipleThreads, this ) );
   
	testSuite->addTest (
        new TestCaller <TestDebugUtilLogMacros> (
            "testLOGAndLOGMOREWithMultipleThreads", &TestDebugUtilLogMacros::testLOGAndLOGMOREWithMultipleThreads, this ) );
   
    return testSuite;
}


void TestDebugUtilLogMacros::callingLOGWithGenericLog()
{
	LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugError, "Private Helper Function 'callingLOGWithGenericLog' called" );
}

void TestDebugUtilLogMacros::callingLOGWithPreformattedLog()
{
	LOG ( SourceInfo, DebugUtil::FunctionEntry, "callingLOGWithPreformattedLog" );
	LOG ( SourceInfo, DebugUtil::FunctionExit, "callingLOGWithPreformattedLog" );
}
