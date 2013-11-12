/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestPreformattedLogType.cpp $
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
#include "TestPreformattedLogType.h"
#include <assert.h>


// Initialises variables at the beginning of a test suite
void TestPreformattedLogType::setUpSuite ( std::string const & INFile )
{
    // Use the INFile string to read in data,
    // this can change according the config file.
}


// Initialises variables at the end of a test suite
void TestPreformattedLogType::tearDownSuite ()
{


}



void TestPreformattedLogType::setUp ( const std::string & INFile , const std::string & OUTFile)
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}



void TestPreformattedLogType::tearDown ( const std::string & OUTFile )
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}


// Test
void TestPreformattedLogType::TestConstructorWithEmptyFormatStr()
{
	std::cout << "TestConstructorWithEmptyFormatStr() ... "; 

	std::string format ( "Test Message" );

	// Empty format string
	try
	{
		CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "" );
		
		std::cout << "Failed on Empty Format String" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}

	std::cout << "Passed" << std::endl;
    Assert ( true );
}

void TestPreformattedLogType::TestConstructorWithCorrectArgs()
{
	std::cout << "TestConstructorWithCorrectArgs() ... "; 

	std::string format ( "Test Message" );

	// Correct Args
	try
	{
		CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, format);
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
    Assert ( true );
}


void TestPreformattedLogType::TestGetCompleteLogMessageWithEmptyFilename()
{
	std::cout << "TestGetCompleteLogMessageWithEmptyFilename() ... ";

	char* arg = "Test";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );
		
	// Empty Filename
	try
	{
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, "", __LINE__, arg );
		
		std::cout << "Failed on Empty Filename" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestGetCompleteLogMessageWithLineEqualsZero()
{
	std::cout << "TestGetCompleteLogMessageWithLineEqualsZero() ... ";

	char* arg = "Test";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );
		
	// Line == 0
	try
	{
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, __FILE__, 0, arg );
		
		std::cout << "Failed on Line == 0" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestGetCompleteLogMessageWithNoArgs()
{
	std::cout << "TestGetCompleteLogMessageWithNoArgs() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );
		
	// No args
	try
	{
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, __FILE__, __LINE__ );
		
		Assert ( true );
	}
	catch ( ... )
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		std::cout << "Failed on No Args" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestGetCompleteLogMessageWithArgEmptyString()
{
	std::cout << "TestGetCompleteLogMessageWithArgEmptyString() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) throws a bus error
// if the created string is too large for the buffer... 
#if defined ( WIN32 )
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );
		
	// Arg is empty string
	try
	{
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, __FILE__, __LINE__, "" );
		
		Assert ( true );
	}
	catch ( ... )
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		std::cout << "Failed on Empty Arg String" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestGetCompleteLogMessageWithArgNull()
{
	std::cout << "TestGetCompleteLogMessageWithArgNull() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
    CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );
		
	// Arg is NULL
	try
	{
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, __FILE__, __LINE__, NULL );
		
		Assert ( true );
	}
	catch ( ... )
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		std::cout << "Failed on Arg is NULL" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestGetCompleteLogMessageWithExcessArgs()
{
	std::cout << "TestGetCompleteLogMessageWithExcessArgs() ... ";

	char* arg = "Test";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );
		
	// Excess args
	try
	{
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, __FILE__, __LINE__, arg, 2, 3, 4 );
		
		Assert ( true );
	}
	catch ( ... )
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If there are excess arguments, the excess will be
		// ignored.
		std::cout << "Failed on Excess arguments" << std::endl;
		Assert ( false );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestGetCompleteLogMessageWithLargeString()
{
	std::cout << "TestGetCompleteLogMessageWithLargeString() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) throws a bus error
// if the created string is too large for the buffer... 
//#if defined ( WIN32 )
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );
		
	// Format string too large
	try
	{
		std::string longArg ( "" );
		for ( int i = 0; i < MAXLOGMESGSIZE + 10; ++i )
		{
			longArg += "a";
		}
		longArg += "z";
		
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, __FILE__, __LINE__, longArg.c_str() );

		std::cout << "Failed on Format string too large" << std::endl;
		Assert ( false );
	}
	catch ( TA_Base_Core::DebugMsgConstructionException& )
	{
		Assert ( true );
	}
    catch ( ... )
    {
        std::cout << "Failed on Format string too large" << std::endl;
        Assert ( false );
    }
//#endif

	std::cout << "Passed" << std::endl;
}

void TestPreformattedLogType::TestGetCompleteLogMessageWithCorrectArgs()
{
	std::cout << "TestGetCompleteLogMessageWithCorrectArgs() ... ";

	char* arg = "Test";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %s" );

	// Correct arguments
	try
	{
		std::string mesg = VaListGetCompleteMsg ( preformattedLogType, __FILE__, __LINE__, arg );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct arguments" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestConstructMessageWithFilenameEmpty()
{
	std::cout << "TestConstructMessageWithFilenameEmpty() ... ";
    std::cout.flush();

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %d" );
		
	// Empty Filename
	try
	{
		std::string mesg = preformattedLogType.constructMessage ( "", __LINE__, level, message );
		
		std::cout << "Failed on Empty Filename" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestConstructMessageWithFilenameNull()
{
	std::cout << "TestConstructMessageWithFilenameNull() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %d" );
		
	// NULL Filename
	try
	{
		std::string mesg = preformattedLogType.constructMessage ( NULL, __LINE__, level, message );

		std::cout << "Failed on Empty Filename" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
#endif

	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestConstructMessageWithLineEqualsZero()
{
	std::cout << "TestConstructMessageWithLineEqualsZero() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %d" );
		
	// Line == 0
	try
	{
		std::string mesg = preformattedLogType.constructMessage ( __FILE__, 0, level, message );
		
		std::cout << "Failed on Line == 0" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestConstructMessageWithLineLessThanZero()
{
	std::cout << "TestConstructMessageWithLineLessThanZero() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %d" );
		
	// Line < 0
	try
	{
		std::string mesg = preformattedLogType.constructMessage ( __FILE__, -2, level, message );
		
		std::cout << "Failed on Line < 0" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestConstructMessageWithEmptyLevel()
{
	std::cout << "TestConstructMessageWithEmptyLevel() ... ";

	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %d" );
		
	// Empty Level
	try
	{
		std::string mesg = preformattedLogType.constructMessage ( __FILE__, 0, "", message );
		
		std::cout << "Failed on Empty Level" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestConstructMessageWithEmptyMessage()
{
	std::cout << "TestConstructMessage() ... ";

	std::string level = "DEBUG";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %d" );
		
	// Empty Message
	try
	{
		std::string mesg = preformattedLogType.constructMessage ( __FILE__, 0, level, "" );

		std::cout << "Failed on Empty Message" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}

void TestPreformattedLogType::TestConstructMessageWithCorrectArgs()
{
	std::cout << "TestConstructMessageWithCorrectArgs() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::PreformattedLogType preformattedLogType(CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Test Message %d" );
		
	// Correct Args
	try
	{
		std::string mesg = preformattedLogType.constructMessage ( __FILE__, __LINE__, level, message );
		
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct Args" << std::endl;
		Assert ( false );
	}
   
	std::cout << "Passed" << std::endl;
    Assert ( true );
}


void TestPreformattedLogType::TestGetSimpleMessageWithNoArgs()
{
	std::cout << "TestGetSimpleMessageWithNoArgs() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	char* format = "This is a test %d";
	
	CU::PreformattedLogType preformattedLogType ( CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, format );
	int pholder = 0;
	
	// No args
	try
	{
		std::string mesg = VaListGetSimpleMsg ( preformattedLogType, pholder );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on No Args" << std::endl;
		Assert ( false );

	}
#endif

	std::cout << "Passed" << std::endl;
    Assert ( true );
}

void TestPreformattedLogType::TestGetSimpleMessageWithFirstArgNotString()
{
	std::cout << "TestGetSimpleMessageWithFirstArgNotString() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	char* format = "This is a test %d";
	CU::PreformattedLogType preformattedLogType ( CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, format );
	int pholder = 0; 
	int arg = 1;

	// 1st arg not string
	try
	{
		std::string mesg = VaListGetSimpleMsg ( preformattedLogType, pholder, CU::DebugUtil::DebugDebug, format, arg );
		
		std::cout << "Failed on 1st Arg not String" << std::endl;
		Assert ( false );
	}
	catch ( AssertionFailedError & )
	{
		throw;
	}
	catch ( ... )
	{
		Assert ( true );
	}
#endif

	std::cout << "Passed" << std::endl;
    Assert( true );
}

void TestPreformattedLogType::TestGetSimpleMessageWithExcessArgs()
{
	std::cout << "TestGetSimpleMessageWithExcessArgs() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	
	CU::PreformattedLogType preformattedLogType ( CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, format );
	int pholder = 0;

	// Excess arguments
	try
	{
		std::string mesg = VaListGetSimpleMsg ( preformattedLogType, pholder, format, arg, 2, 3 );
		
		Assert ( true );
	}
	catch ( ... )
	{
		// An exception should not be thrown if there are too many args, the 
		// excess args will just be ignored. It is up to the caller to get
		// it right.
		std::cout << "Failed on Format args wrong type" << std::endl;
		Assert ( false );
	}
	std::cout << "Passed" << std::endl;
    Assert( true );
}

void TestPreformattedLogType::TestGetSimpleMessageWithCorrectArgs()
{
	std::cout << "TestGetSimpleMessage() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	
	CU::PreformattedLogType preformattedLogType ( CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, format );
	int pholder = 0;

	// Correct arguments
	try
	{
		std::string mesg = VaListGetSimpleMsg ( preformattedLogType, pholder, format, arg );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct arguments" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
    Assert( true );
}




// The suite method. Returns list of methods.

TestSuite* TestPreformattedLogType::suite ()
{
    // Must have same name as test class.
    TestSuite * testSuite = new TestSuite( "TestPreformattedLogType" );

    testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructorWithEmptyFormatStr", &TestPreformattedLogType::TestConstructorWithEmptyFormatStr, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructorWithCorrectArgs", &TestPreformattedLogType::TestConstructorWithCorrectArgs, this ) );
    
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithEmptyFilename", &TestPreformattedLogType::TestGetCompleteLogMessageWithEmptyFilename, this ) );
    testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithLineEqualsZero", &TestPreformattedLogType::TestGetCompleteLogMessageWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithNoArgs", &TestPreformattedLogType::TestGetCompleteLogMessageWithNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithArgEmptyString", &TestPreformattedLogType::TestGetCompleteLogMessageWithArgEmptyString, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithArgNull", &TestPreformattedLogType::TestGetCompleteLogMessageWithArgNull, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithExcessArgs", &TestPreformattedLogType::TestGetCompleteLogMessageWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithLargeString", &TestPreformattedLogType::TestGetCompleteLogMessageWithLargeString, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetCompleteLogMessageWithCorrectArgs", &TestPreformattedLogType::TestGetCompleteLogMessageWithCorrectArgs, this ) );

	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructMessageWithFilenameEmpty", &TestPreformattedLogType::TestConstructMessageWithFilenameEmpty, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructMessageWithFilenameNull", &TestPreformattedLogType::TestConstructMessageWithFilenameNull, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructMessageWithLineEqualsZero", &TestPreformattedLogType::TestConstructMessageWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructMessageWithLineLessThanZero", &TestPreformattedLogType::TestConstructMessageWithLineLessThanZero, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructMessageWithEmptyLevel", &TestPreformattedLogType::TestConstructMessageWithEmptyLevel, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructMessageWithEmptyMessage", &TestPreformattedLogType::TestConstructMessageWithEmptyMessage, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestConstructMessageWithCorrectArgs", &TestPreformattedLogType::TestConstructMessageWithEmptyMessage, this ) );

	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetSimpleMessageWithNoArgs", &TestPreformattedLogType::TestGetSimpleMessageWithNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetSimpleMessageWithFirstArgNotString", &TestPreformattedLogType::TestGetSimpleMessageWithFirstArgNotString, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetSimpleMessageWithExcessArgs", &TestPreformattedLogType::TestGetSimpleMessageWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestPreformattedLogType> (
            "TestGetSimpleMessageWithCorrectArgs", &TestPreformattedLogType::TestGetSimpleMessageWithCorrectArgs, this ) );

    return testSuite;
}


std::string TestPreformattedLogType::VaListGetCompleteMsg ( CU::PreformattedLogType& preformattedLog, const std::string& file, int line, ...  )
{
	va_list args;
	va_start ( args, line );

	return preformattedLog.getCompleteLogMessage ( file, line, args );
}


std::string TestPreformattedLogType::VaListGetSimpleMsg ( CU::PreformattedLogType& preformattedLog, int pholder, ... )
{
	va_list args;
	va_start ( args, pholder );

	return preformattedLog.getSimpleMessage ( args );
}
