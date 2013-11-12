/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestGenericLogType.cpp $
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
#include "TestGenericLogType.h"
#include <assert.h>


// Initialises variables at the beginning of a test suite
void TestGenericLogType::setUpSuite ( std::string const & INFile )
{
    // Use the INFile string to read in data,
    // this can change according the config file.
}


// Initialises variables at the end of a test suite
void TestGenericLogType::tearDownSuite ()
{


}



void TestGenericLogType::setUp ( const std::string & INFile , const std::string & OUTFile)
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}



void TestGenericLogType::tearDown ( const std::string & OUTFile )
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}


// Test
void TestGenericLogType::TestConstructor ()
{
	std::cout << "TestConstructor() ... "; 

	try
	{
		CU::GenericLogType genericLogType;
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
    Assert ( true );
}

void TestGenericLogType::TestGetCompleteLogMessageWithEmptyFilename()
{
	std::cout << "TestGetCompleteLogMessageWithEmptyFilename() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugDebug;

	CU::GenericLogType genericLogType;
		
	// Empty Filename
	try
	{
		std::string mesg = VaListGetCompleteMsg ( genericLogType, "", __LINE__, level, format, arg );
		
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
    Assert( true );
}

void TestGenericLogType::TestGetCompleteLogMessageWithLineEqualsZero()
{
	std::cout << "TestGetCompleteLogMessageWithLineEqualsZero() ... ";

    char* format = "This is a test %d";
	int arg = 1;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugDebug;

	CU::GenericLogType genericLogType;
		
	// Line == 0
	try
	{
		std::string mesg = VaListGetCompleteMsg ( genericLogType, __FILE__, 0, level, format, arg );

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
    Assert( true );
}

void TestGenericLogType::TestGetCompleteLogMessageWithNoArgs()
{
	std::cout << "TestGetCompleteLogMessageWithNoArgs() ... ";

	CU::GenericLogType genericLogType;

	// No args
	try
	{
		// An exception will be throw for this case because it expects the first
		// arg to be a debug level and will check if the first value is a valid level
		std::string mesg = VaListGetCompleteMsg ( genericLogType, __FILE__, __LINE__ );
		
		std::cout << "Failed on No Args" << std::endl;
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
    Assert( true );
}

void TestGenericLogType::TestGetCompleteLogMessageWithFirstArgNotLevel()
{
	std::cout << "TestGetCompleteLogMessageWithFirstArgNotLevel() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	
	CU::GenericLogType genericLogType;
		
	// 1st arg is not level
	try
	{
		std::string mesg = VaListGetCompleteMsg ( genericLogType, __FILE__, __LINE__, format, arg );
	
		std::cout << "Failed on 1st arg not Level" << std::endl;
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
    Assert( true );
}

void TestGenericLogType::TestGetCompleteLogMessageWithSecondArgNotString()
{
	std::cout << "TestGetCompleteLogMessageWithSecondArgNotString() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	int arg = 1;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugDebug;

	CU::GenericLogType genericLogType;
		
	// 1st arg is level, 2nd arg not string
	try
	{
		std::string mesg = VaListGetCompleteMsg ( genericLogType, __FILE__, __LINE__, level, arg );
		
		std::cout << "Failed on 2nd arg not string" << std::endl;
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

void TestGenericLogType::TestGetCompleteLogMessageWithExcessArgs()
{
	std::cout << "TestGetCompleteLogMessageWithExcessArgs() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugDebug;

	CU::GenericLogType genericLogType;
		
	// Excess arguments
	try
	{
		std::string mesg = VaListGetCompleteMsg ( genericLogType, __FILE__, __LINE__, level, format, arg, 2, 3 );
		
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

void TestGenericLogType::TestGetCompleteLogMessageWithLargeFormatString()
{
	std::cout << "TestGetCompleteLogMessageWithLargeFormatString() ... ";

	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugDebug;

	CU::GenericLogType genericLogType;
		
	// Format string too large
	try
	{
		std::string longArg ( "" );
		for ( unsigned int i = 0; i < MAXLOGMESGSIZE + 5; ++i )
		{
			longArg += "a";
		}
		longArg += "z";

		std::string mesg = VaListGetCompleteMsg ( genericLogType, __FILE__, __LINE__, level, longArg.c_str() );

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
	std::cout << "Passed" << std::endl;
}

void TestGenericLogType::TestGetCompleteLogMessageWithCorrectArgs()
{
	std::cout << "TestGetCompleteLogMessageWithCorrectArgs() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugDebug;

	CU::GenericLogType genericLogType;
		
	// Correct arguments
	try
	{
		std::string mesg = VaListGetCompleteMsg ( genericLogType, __FILE__, __LINE__, level, format, arg );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}
	std::cout << "Passed" << std::endl;
	Assert ( true );
}


void TestGenericLogType::TestConstructMessageWithEmptyFilename()
{
	std::cout << "TestConstructMessageWithEmptyFilename() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::GenericLogType genericLogType;
		
	// Empty Filename
	try
	{
		std::string mesg = genericLogType.constructMessage ( "", __LINE__, level, message );
		
		std::cout << "Failed" << std::endl;
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

void TestGenericLogType::TestConstructMessageWithNullFilename()
{
	std::cout << "TestConstructMessageWithNullFilename() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::GenericLogType genericLogType;
		
	// NULL Filename
	try
	{
		std::string mesg = genericLogType.constructMessage ( NULL, __LINE__, level, message );
		
		std::cout << "Failed" << std::endl;
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

void TestGenericLogType::TestConstructMessageWithLineEqualsZero()
{
	std::cout << "TestConstructMessageWithLineEqualsZero() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::GenericLogType genericLogType;
		
	// Line == 0
	try
	{
		std::string mesg = genericLogType.constructMessage ( __FILE__, 0, level, message );

		std::cout << "Failed" << std::endl;
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

void TestGenericLogType::TestConstructMessageWithLineLessThanZero()
{
	std::cout << "TestConstructMessageWithLineLessThanZero() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::GenericLogType genericLogType;
		
	// Line < 0
	try
	{
		std::string mesg = genericLogType.constructMessage ( __FILE__, -2, level, message );
		
		std::cout << "Failed" << std::endl;
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

void TestGenericLogType::TestConstructMessageWithEmptyLevel()
{
	std::cout << "TestConstructMessageWithEmptyLevel() ... ";

	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::GenericLogType genericLogType;
		
	// Empty Level
	try
	{
		std::string mesg = genericLogType.constructMessage ( __FILE__, 0, "", message );

		std::cout << "Failed" << std::endl;
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

void TestGenericLogType::TestConstructMessageWithEmptyMessage()
{
	std::cout << "TestConstructMessageWithEmptyMessage() ... ";

	std::string level = "DEBUG";
	
	CU::GenericLogType genericLogType;
		
	// Empty Message
	try
	{
		std::string mesg = genericLogType.constructMessage ( __FILE__, 0, level, "" );
	
		std::cout << "Failed" << std::endl;
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

void TestGenericLogType::TestConstructMessageWithCorrectArgs()
{
	std::cout << "TestConstructMessageWithCorrectArgs() ... ";

	std::string level = "DEBUG";
	std::string message = "Testing GenericLogType::ConstructMessage";
	
	CU::GenericLogType genericLogType;
		
	// Correct Args
	try
	{
		std::string mesg = genericLogType.constructMessage ( __FILE__, __LINE__, level, message );
		
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}
   
	std::cout << "Passed" << std::endl;
    Assert ( true );
}


void TestGenericLogType::TestGetSimpleMessageWithNoArgs()
{
	std::cout << "TestGetSimpleMessageWithNoArgs() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	CU::GenericLogType genericLogType;
	int pholder = 0;
		
	// No args
	try
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		std::string mesg = VaListGetSimpleMsg ( genericLogType, pholder );
		Assert ( true );	
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );

	}
#endif

	std::cout << "Passed" << std::endl;
}

void TestGenericLogType::TestGetSimpleMessageWithFirstArgNotString()
{
	std::cout << "TestGetSimpleMessageWithFirstArgNotString() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	char* format = "This is a test %d";
	int arg = 1;
	
	CU::GenericLogType genericLogType;
	int pholder = 0;
		
	// 1st arg not string
	try
	{
		//std::string mesg = VaListGetSimpleMsg ( genericLogType, CU::DebugUtil::DebugDebug, format, arg );
		std::string mesg = VaListGetSimpleMsg ( genericLogType, pholder, arg, format );

		std::cout << "Failed" << std::endl;
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

void TestGenericLogType::TestGetSimpleMessageWithExcessArgs()
{
	std::cout << "TestGetSimpleMessageWithExcessArgs() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	
	CU::GenericLogType genericLogType;
	int pholder = 0;
		
	// Excess arguments
	try
	{
		std::string mesg = VaListGetSimpleMsg ( genericLogType, pholder, format, arg, 2, 3 );
		
		Assert ( true );
	}
	catch ( ... )
	{
		// An exception should not be thrown if there are too many args, the 
		// excess args will just be ignored. It is up to the caller to get
		// it right.
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}
	std::cout << "Passed" << std::endl;
    Assert ( true );
}

void TestGenericLogType::TestGetSimpleMessageWithCorrectArgs()
{
	std::cout << "TestGetSimpleMessageWithCorrectArgs() ... ";

	char* format = "This is a test %d";
	int arg = 1;
	
	CU::GenericLogType genericLogType;
	int pholder = 0;
		
	// Correct arguments
	try
	{
		std::string mesg = VaListGetSimpleMsg ( genericLogType, pholder, format, arg );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}
	std::cout << "Passed" << std::endl;
    Assert ( true );
}

void TestGenericLogType::TestGetSimpleMessageWithStdStringInsteadOfCharStar()
{
	std::cout << "TestGetSimpleMessageWithStdStringInsteadOfCharStar() ... ";

// Only run this test on windows as the solaris compiler will
// pick up the problem - won't let you pass in a std::string
// to ...
#if defined ( WIN32 )
	std::string format( "This is a test %d" );
	int arg = 1;
	
	CU::GenericLogType genericLogType;
	int pholder = 0;
		
	// Passing in a std::string instead of a char *
	try
	{
		std::string mesg = VaListGetSimpleMsg ( genericLogType, pholder, format, arg );
		std::cout << "Failed" << std::endl;
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
#endif // defined WIN32

	std::cout << "Passed" << std::endl;   
}


// The suite method. Returns list of methods.

TestSuite* TestGenericLogType::suite ()
{
    // Must have same name as test class.
    TestSuite * testSuite = new TestSuite( "TestGenericLogType" );

    testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructor", &TestGenericLogType::TestConstructor, this ) );
   
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithEmptyFilename", &TestGenericLogType::TestGetCompleteLogMessageWithEmptyFilename, this ) );
    testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithLineEqualsZero", &TestGenericLogType::TestGetCompleteLogMessageWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithNoArgs", &TestGenericLogType::TestGetCompleteLogMessageWithNoArgs, this ) );
    testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithFirstArgNotLevel", &TestGenericLogType::TestGetCompleteLogMessageWithFirstArgNotLevel, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithSecondArgNotString", &TestGenericLogType::TestGetCompleteLogMessageWithSecondArgNotString, this ) );
    testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithExcessArgs", &TestGenericLogType::TestGetCompleteLogMessageWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithLargeFormatString", &TestGenericLogType::TestGetCompleteLogMessageWithLargeFormatString, this ) );
    testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetCompleteLogMessageWithCorrectArgs", &TestGenericLogType::TestGetCompleteLogMessageWithCorrectArgs, this ) );

	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructMessageWithEmptyFilename", &TestGenericLogType::TestConstructMessageWithEmptyFilename, this ) );
    testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructMessageWithNullFilename", &TestGenericLogType::TestConstructMessageWithNullFilename, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructMessageWithLineEqualsZero", &TestGenericLogType::TestConstructMessageWithLineEqualsZero, this ) );
    testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructMessageWithLineLessThanZero", &TestGenericLogType::TestConstructMessageWithLineLessThanZero, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructMessageWithEmptyLevel", &TestGenericLogType::TestConstructMessageWithEmptyLevel, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructMessageWithEmptyMessage", &TestGenericLogType::TestConstructMessageWithEmptyMessage, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestConstructMessageWithCorrectArgs", &TestGenericLogType::TestConstructMessageWithCorrectArgs, this ) );

	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetSimpleMessageWithNoArgs", &TestGenericLogType::TestGetSimpleMessageWithNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetSimpleMessageWithFirstArgNotString", &TestGenericLogType::TestGetSimpleMessageWithFirstArgNotString, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetSimpleMessageWithExcessArgs", &TestGenericLogType::TestGetSimpleMessageWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetSimpleMessageWithCorrectArgs", &TestGenericLogType::TestGetSimpleMessageWithCorrectArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestGenericLogType> (
            "TestGetSimpleMessageWithStdStringInsteadOfCharStar", &TestGenericLogType::TestGetSimpleMessageWithStdStringInsteadOfCharStar, this ) );

    return testSuite;
}


std::string TestGenericLogType::VaListGetCompleteMsg ( CU::GenericLogType& genericLog, const std::string& file, int line, ...  )
{
	va_list args;
	va_start ( args, line );

	return genericLog.getCompleteLogMessage ( file, line, args );
}


//std::string TestGenericLogType::VaListGetSimpleMsg ( CU::GenericLogType& genericLog, ... )
std::string TestGenericLogType::VaListGetSimpleMsg ( CU::GenericLogType& genericLog, int pholder, ... )
{
	va_list args;
	va_end ( args );
	va_start ( args, pholder );

	return genericLog.getSimpleMessage ( args );
}
