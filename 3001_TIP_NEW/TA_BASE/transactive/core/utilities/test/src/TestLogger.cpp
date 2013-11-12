/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestLogger.cpp $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#if defined ( WIN32 )
#include <io.h>
#else
#include <unistd.h>
#endif

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "TestLogger.h"
#include "core/utilities/src/PreformattedLogType.h"
#include "core/utilities/src/GenericLogType.h"
#include "core/utilities/src/DebugUtil.h"



// Initialises variables at the beginning of a test suite
void TestLogger::setUpSuite ( std::string const & INFile )
{
    // Use the INFile string to read in data,
    // this can change according the config file.
}


// Initialises variables at the end of a test suite
void TestLogger::tearDownSuite ()
{


}



void TestLogger::setUp ( const std::string & INFile , const std::string & OUTFile)
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}



void TestLogger::tearDown ( const std::string & OUTFile )
{

    // Use the INFile string to read in data,
    // this can change according the config file.
}


// TestConstructor
void TestLogger::testConstructor ()
{
	std::cout << "testConstructor() ... "; 

	try
	{
		CU::Logger logger;
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
    Assert ( true );
}


///////////////////////////////
// TestAddLoggType
///////////////////////////////

// TestAddLogTypeWithGenericLogType
void TestLogger::testAddLogTypeWithGenericLogType()
{
	std::cout << "testAddLogTypeWithGenericLogType() ... ";
	
	CU::GenericLogType* genType;
	CU::Logger logger;
			
	// Generic Log Type
	try
	{
		genType = new CU::GenericLogType(); 
		logger.addLogType ( *genType );

		delete genType;

		//Assert ( false );
	}
	catch ( ... )
	{
		delete genType;
		std::cout << "Failed on Add Generic Log" << std::endl;

		Assert ( true );
	}

	std::cout << "Passed" << std::endl;
}


// TestAddLogTypeWithPreformattedLogType
void TestLogger::testAddLogTypeWithPreformattedLogType()
{
	std::cout << "testAddLogTypeWithPreformattedLogType() ... ";
	
	CU::PreformattedLogType* logType;
	CU::Logger logger;
		
	// Preformatted Log Type
	try
	{
		logType = new CU::PreformattedLogType ( CU::DebugUtil::ProgramExecution, CU::DebugUtil::DebugDebug, "Format String" ); 
		logger.addLogType ( *logType );

		delete logType;

		//Assert ( false );
	}
	catch ( ... )
	{
		delete logType;

		std::cout << "Failed on Add Preformatted Log" << std::endl;
		Assert ( true );
	}

	std::cout << "Passed" << std::endl;
}


///////////////////////////////
// TestAddLogType - Full Log
///////////////////////////////

// TestAddToCacheFullLogWithEmptyFilename
void TestLogger::testAddToCacheFullLogWithEmptyFilename()
{
	std::cout << "testAddToCacheFullLogWithEmptyFilename() ... ";
	
	bool simpleLog = false;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
		
	// Empty filename
	try
	{
		vaListAddToCache ( type, logger, "", __LINE__, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );
		
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
}

// TestAddToCacheFullLogWithLineEqualsZero
void TestLogger::testAddToCacheFullLogWithLineEqualsZero()
{
	std::cout << "TestAddToCacheFullLogWithLineEqualsZero() ... ";
	
	bool simpleLog = false;
	int arg = 10;
	std::string format ( "Testing %d" );
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Line == 0
	try
	{
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );
		
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
}

// TestAddToCacheFullLogWithGenLogNoArgs
void TestLogger::testAddToCacheFullLogWithGenLogNoArgs()
{
	std::cout << "testAddToCacheFullLogWithGenLogNoArgs() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )

	bool simpleLog = false;
	std::string format ( "Testing %d" );
	
	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// No Args - allowed for GenericLog
	try
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		vaListAddToCache ( CU::DebugUtil::GenericLog, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugWarn );
		Assert ( true );
	}
	catch ( ... )
	{
		// Should not because the arg will be converted to a char* for
		// the format string.
		std::cout << "Failed on GenericLog No Args" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed" << std::endl;
}

// TestAddToCacheFullLogWithPreLogNoArgs
void TestLogger::testAddToCacheFullLogWithPreLogNoArgs()
{
	std::cout << "testAddToCacheFullLogWithPreLogNoArgs() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )	
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// No Args - allowed for PreformattedLog
	try
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog );
		
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on PreformattedLog No Args" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed" << std::endl;
}

// TestAddToCacheFullLogWithFirstArgNotStr
void TestLogger::testAddToCacheFullLogWithFirstArgNotStr()
{
	std::cout << "testAddToCacheFullLogWithFirstArgNotStr() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = false;
	int arg = 1;
	CU::DebugUtil::EDebugType type1 = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugType type2 = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );


	// 1st arg not string - Generic
	try
	{
		vaListAddToCache (type1, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, arg );

		std::cout << "Failed on 1st Arg not string - Generic" << std::endl;
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );		
	}

	// 1st arg not string - Preformatted
	try
	{
		vaListAddToCache (type2, logger, __FILE__, __LINE__, simpleLog, arg );
		
		// This should fail as the message constructor will be expecting a
		// string (into the existing format string but does not do any 
		// conversions before passing in the argument
		std::cout << "Failed on 1st Arg not string - Preformatted" << std::endl;
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
}

// TestAddToCacheFullLogWithArgEmptyStr
void TestLogger::testAddToCacheFullLogWithArgEmptyStr()
{
	std::cout << "testAddToCacheFullLogWithArgEmptyStr() ... ";
	
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type1 = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugType type2 = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// Arg is empty string - Generic
	try
	{
		vaListAddToCache (type1, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, "" );
		std::cout << "Failed on Empty Arg String - Generic" << std::endl;		
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );
	}
	
	// Arg is empty string - Preformatted
	try
	{
		vaListAddToCache (type2, logger, __FILE__, __LINE__, simpleLog, "" );
				
		Assert ( true );
	}
	catch ( ... )
	{
		// An exception should not be thrown because a format string already exists
		// and it is up to the caller to provide the correct arguments. 
		// If the correct args are not provided the message
		// string will not be as expected.
		std::cout << "Failed on Empty Arg String - Preformatted" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestAddToCacheFullLogWithArgIsNull
void TestLogger::testAddToCacheFullLogWithArgIsNull()
{
	std::cout << "TestAddToCacheFullLogWithArgIsNull() ... ";
	
// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type1 = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugType type2 = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// Arg is NULL - GEneric
	try
	{
		vaListAddToCache (type1, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, NULL );
	
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		std::cout << "Failed on Arg is NULL - Generic" << std::endl;
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );
	}

	// Arg is NULL - Preformatted
	try
	{
		vaListAddToCache (type2, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, NULL );
	
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		std::cout << "Failed on Arg is NULL - Preformatted" << std::endl;
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );
	}
#endif

	std::cout << "Passed" << std::endl;
}

// TestAddToCacheFullLogWithArgWrongType
void TestLogger::testAddToCacheFullLogWithArgWrongType()
{
	std::cout << "testAddToCacheFullLogWithArgWrongType() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
	
	// Arg is wrong type
	try
	{
		vaListAddToCache (type, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, 10 );
		
		std::cout << "Failed on Arg wrong type" << std::endl;
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
}

// TestAddToCacheFullLogWithExcessArgs
void TestLogger::testAddToCacheFullLogWithExcessArgs()
{
	std::cout << "testAddToCacheFullLogWithExcessArgs() ... ";
	
	bool simpleLog = false;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type1 = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugType type2 = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
		
	// Excess args - Generic
	try
	{
		vaListAddToCache (type1, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg, 2, 3 );		
		Assert ( true );	
	}
	catch ( ... )
	{
		// It is up to the caller to supply the correct number of args
		std::cout << "Failed on Excess arguments" << std::endl;
		Assert ( false );
	}

	// Excess args - Preformatted
	try
	{
		vaListAddToCache (type2, logger, __FILE__, __LINE__, simpleLog, format.c_str(), arg );		
		Assert ( true );	
	}
	catch ( ... )
	{
		// It is up to the caller to supply the correct number of args
		std::cout << "Failed on Excess arguments" << std::endl;
		Assert ( false );

	}

	std::cout << "Passed" << std::endl;
}

// TestAddToCacheFullLogWithFormatStrTooLarge
void TestLogger::testAddToCacheFullLogWithFormatStrTooLarge()
{
	std::cout << "TestAddToCacheFullLogWithFormatStrTooLarge() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
//#if defined ( WIN32 )
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
		
	// Format string too large
	try
	{
		std::string longArg ( "" );
		for ( int i = 0; i < MAXLOGMESGSIZE + 1; ++i )
		{
			longArg += "a";
		}
		longArg += "z";

		std::string newFormat ( "Testing %s" );

		vaListAddToCache (type, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, newFormat.c_str(), longArg.c_str() );
		
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

// TestAddToCacheFullLogWithCorrectArgs
void TestLogger::testAddToCacheFullLogWithCorrectArgs()
{
	std::cout << "testAddToCacheFullLogWithCorrectArgs() ... ";
	
	bool simpleLog = false;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type1 = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugType type2 = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// Correct arguments for Generic
	try
	{
		vaListAddToCache ( type1, logger, __FILE__, __LINE__, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );

		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct arguments - Generic" << std::endl;
		Assert ( false );
	}
		
	// Correct arguments for Preformatted
	try
	{
		vaListAddToCache ( type2, logger, __FILE__, __LINE__, simpleLog, "TestProgram" );

		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct arguments - Preformatted" << std::endl;
		Assert ( false );
	}

	


	std::cout << "Passed" << std::endl;
}

///////////////////////////////
// TestAddLogType - Simple Log
///////////////////////////////

// TestAddToCacheSimpleLogWithEmptyFilename
void TestLogger::testAddToCacheSimpleLogWithEmptyFilename()
{
	std::cout << "testAddToCacheSimpleLogWithEmptyFilename() ... ";
	
	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Empty filename 
	try
	{
		vaListAddToCache ( type, logger, "", __LINE__, simpleLog, format.c_str(), arg );
		
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Empty Filename" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestAddToCacheSimpleLogWithLineEqualsZero
void TestLogger::testAddToCacheSimpleLogWithLineEqualsZero()
{
	std::cout << "testAddToCacheSimpleLogWithLineEqualsZero() ... ";
	std::cout.flush();

	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Line == 0
	try
	{
		vaListAddToCache ( type, logger, __FILE__, 0, simpleLog, format.c_str(), arg );
		
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Line == 0" << std::endl;
		std::cout.flush();
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
	std::cout.flush();
}

// TestAddToCacheSimpleLogWithNoArgs
void TestLogger::testAddToCacheSimpleLogWithNoArgs()
{
	std::cout << "testAddToCacheSimpleLogWithNoArgs() ... ";
	std::cout.flush();
	
// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )	
	std::string filename ( "C:/testFile.txt" );
	int line = 10;
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type1 = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugType type2 = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// No Args - Generic
	try
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		vaListAddToCache (type1, logger, __FILE__, __LINE__, simpleLog );
		Assert ( true );
	}
	catch ( ... )
	{
		// Should not because the arg will be converted to a char* for
		// the format string.
		std::cout << "Failed on GenericLog No Args" << std::endl;
		Assert ( false );
	}

	// No Args - Preformatted
	try
	{
		vaListAddToCache (type2, logger, __FILE__, __LINE__, simpleLog );
		Assert ( true );
	}
	catch ( ... )
	{
		// Should not because the arg will be converted to a char* for
		// the format string.
		std::cout << "Failed on Preformatted No Args" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed A" << std::endl;
	std::cout.flush();
}

// TestAddToCacheSimpleLogWithFirstArgNotStr
void TestLogger::testAddToCacheSimpleLogWithFirstArgNotStr()
{
	std::cout << "testAddToCacheSimpleLogWithFirstArgNotStr() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = true;
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// 1st arg not string
	try
	{
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, arg );
		
		std::cout << "Failed on 1st Arg not string" << std::endl;
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

// TestAddToCacheSimpleLogWithWithArgEmptyStr
void TestLogger::testAddToCacheSimpleLogWithArgEmptyStr()
{
	std::cout << "testAddToCacheSimpleLogWithArgEmptyStr() ... ";
    std::cout.flush();
	
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );
	
	// Arg is empty string
	try
	{
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, "" );
		std::cout << "Failed on Empty Arg String" << std::endl;
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
}

// TestAddToCacheSimpleLogWithArgIsNull
void TestLogger::testAddToCacheSimpleLogWithArgIsNull()
{
	std::cout << "testAddToCacheSimpleLogWithArgIsNull() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )	
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Arg is NULL
	try
	{
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, NULL );
		std::cout << "Failed on Arg is NULL" << std::endl;
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );
	}
#endif
	std::cout << "Passed" << std::endl;
}

// TestAddToCacheSimpleLogWithArgWrongType
void TestLogger::testAddToCacheSimpleLogWithArgWrongType()
{
	std::cout << "testAddToCacheSimpleLogWithArgWrongType() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )	
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Arg is wrong type
	try
	{
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, 10 );
		
		std::cout << "Failed on Arg wrong type" << std::endl;
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
}

// TestAddToCacheSimpleLogWithExcessArgs
void TestLogger::testAddToCacheSimpleLogWithExcessArgs()
{
	std::cout << "testAddToCacheSimpleLogWithExcessArgs() ... ";
	
	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Excess args
	try
	{
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, format.c_str(), arg, 2, 3, 4 );
		
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
}

// TestAddToCacheSimpleLogWithFormatStrTooLarge
void TestLogger::testAddToCacheSimpleLogWithFormatStrTooLarge()
{
	std::cout << "testAddToCacheSimpleLogWithFormatStrTooLarge() ... ";
	
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );


	// Format string too large
	try
	{
		std::string longArg ( "" );
		for ( unsigned int i = 0; i < MAXLOGMESGSIZE + 1; ++i )
		{
			longArg += "a";
		}
		longArg += "z";

		std::string newFormat ( "Testing %s" );

		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, newFormat.c_str(), longArg.c_str() );
		
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

// TestAddToCacheSimpleLogWithCorrectArgs
void TestLogger::testAddToCacheSimpleLogWithCorrectArgs()
{
	std::cout << "testAddToCacheSimpleLogWithCorrectArgs() ... ";
	
	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Correct arguments
	try
	{
		vaListAddToCache ( type, logger, __FILE__, __LINE__, simpleLog, format.c_str(), arg );

		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct arguments" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

///////////////////////////////
// TestGetLevel
///////////////////////////////

// TestGetLevelWithoutLogTypesLoaded
void TestLogger::testGetLevelWithoutLogTypesLoaded()
{
	std::cout << "testGetLevelWithoutLogTypesLoaded() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::ProgramExecution;
	CU::Logger logger;

	// Before Load
	// Try to get level before loading log types
	try
	{
		logger.getLevel ( type );

		std::cout << "Failed on Before Load" << std::endl;
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
}

// TestGetLevelWithLogTypesLoaded
void TestLogger::testGetLevelWithLogTypesLoaded()
{
	std::cout << "testGetLevelWithLogTypesLoaded() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::ProgramExecution;
	CU::Logger logger;

	// Load log types
	setUpTestLevel ( logger );

	// Try to get level after loading log types
	try
	{
		logger.getLevel ( type );

		Assert ( true );		
	}
	catch ( ... )
	{	
		std::cout << "Failed on Before Load" << std::endl;
		Assert ( false );
	}
	
	std::cout << "Passed" << std::endl;
    Assert ( true );
}


///////////////////////////////
// TestLogCache
///////////////////////////////

// TestLogCacheWithLogTypesNotLoaded
void TestLogger::testLogCacheWithLogTypesNotLoaded()
{
	std::cout << "testLogCacheWithLogTypesNotLoaded() ... ";

	CU::Logger logger;

	// Empty Cache
	// Try to print cache when it is empty
	try
	{
		int numPrinted = logger.logCache ( std::cout );
		
		Assert ( numPrinted == 0 );
	}
	catch ( ... )
	{	
		// Should not throw any exceptions as it is acceptable to attempt
		// to print messages in the cache when it is empty. It should
		// just return 0.
		std::cout << "Failed on Before Load" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogCacheWithCout
void TestLogger::testLogCacheWithCout()
{
	std::cout << "testLogCacheWithCout() ... ";

	CU::Logger logger;

	// Load messages
	std::string format ( "Testing %d" );
	int arg = 1;
	unsigned int numMsgs = 3;
	setUpTestLogCache ( logger, numMsgs, format.c_str(), arg );

	char buff[100];
	sprintf ( buff, format.c_str(), arg );
	std::string msg ( buff );
	msg = "    " + msg + "\n";

	// Log Cache to cout
	try
	{
		unsigned int numPrinted = logger.logCache ( std::cout );

		Assert ( numPrinted == msg.size() * numMsgs );		
	}
	catch ( ... )
	{	
		std::cout << "Failed on Log Cache With Cout" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogCacheWithBadFile
void TestLogger::testLogCacheWithBadFile()
{
	std::cout << "testLogCacheWithBadFile() ... ";

	std::fstream outFile;
//#if defined ( WIN32 )
//	std::string filename ( "C:\\Bogus\\BogusFileThatDoesNotExist.txt" );
//#else
//	std::string filename ( ".//BogusFileThatDoesNotExist.txt" );
//#endif
	CU::Logger logger;

	// Try to open the file - it should fail and set the error flag
	//outFile.open ( filename.c_str() );
	outFile.clear(std::ios::failbit);

	// For this test to run, the error flag must be set
	Assert ( outFile.fail() );

	// Load messages
	std::string format ( "Testing %d" );
	int arg = 1;
	int numMsgs = 3;
	char buff[100];
	
	sprintf ( buff, format.c_str(), arg );
	std::string msg ( buff );
	msg = "    " + msg + "\n";
	setUpTestLogCache ( logger, numMsgs, format.c_str(), arg );
 
	// Log Cache to bad file
	try
	{
		// An exception shouldn't be thrown. Instead an error is logged
		// to stderr and the messages are logged to stdout from now on.
		logger.logCache ( outFile );
		outFile.clear();
		Assert ( true );	
	}
	catch ( ... )
	{	
		std::cout << "Failed on Log to Bad File" << std::endl;
		Assert ( false );	

	}

	outFile.clear();
	std::cout << "Passed" << std::endl;
}

// TestLogCacheWithGoodFile
void TestLogger::testLogCacheWithGoodFile()
{
	std::cout << "testLogCacheWithGoodFile() ... ";
	
	std::fstream outFile;
	std::string filename ( "TestLogCacheWithGoodFile.txt" );
	CU::Logger logger;

	// Create a file
	int fh;
#if defined ( SOLARIS )
	fh = creat( filename.c_str(), S_IREAD | S_IWRITE );
#else
	fh = _creat( filename.c_str(), _S_IREAD | _S_IWRITE );
#endif
	Assert ( fh != -1 );

	// Load messages
	std::string format ( "Testing %d" );
	int arg = 1;
	int numMsgs = 3;
	char buff[100];

	sprintf ( buff, format.c_str(), arg );
	std::string msg ( buff );
	msg = "    " + msg + "\n";
	setUpTestLogCache ( logger, numMsgs, format.c_str(), arg );

	// Try to open the file
	outFile.open ( filename.c_str(),std::ios::out|std::ios::app );
	
	// For this test to run, the error flag must not be set
	Assert ( !outFile.fail() );
	
	// Log Cache to good file
	try
	{
		logger.logCache ( outFile );
		Assert ( true );
	}
	catch ( ... )
	{	
		// remove file
		outFile.close();
		RemoveFile ( filename.c_str() );
		std::cout << "Failed on Log to Bad File" << std::endl;
		Assert ( false );		
	}

	// remove file
	outFile.close();
	RemoveFile ( filename.c_str() );
	std::cout << "Passed" << std::endl;
}


///////////////////////////////
// TestLog
///////////////////////////////

// TestLogFullLogWithEmptyFilename
void TestLogger::testLogFullLogWithEmptyFilename()
{
	std::cout << "testLogFullLogWithEmptyFilename() ... ";
	
	bool simpleLog = false;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
		
	// Empty filename
	try
	{
		vaListLog ( type, logger, "", __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );
		
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
}

// TestLogFullLogWithLineEqualsZero
void TestLogger::testLogFullLogWithLineEqualsZero()
{
	std::cout << "testLogFullLogWithLineEqualsZero() ... ";
	
	bool simpleLog = false;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Line == 0
	try
	{
		vaListLog ( type, logger, __FILE__, 0, std::cout, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );
		
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
}

// TestLogFullLogWithGenLogNoArgs
void TestLogger::testLogFullLogWithGenLogNoArgs()
{
	std::cout << "testLogFullLogWithGenLogNoArgs() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )	
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// No Args - allowed for GenericLog
	try
	{
		vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug );
		Assert ( true );
	}
	catch ( ... )
	{
		
		std::cout << "Failed on GenericLog No Args" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed A" << std::endl;
}

// TestLogFullLogWithPreLogNoArgs
void TestLogger::testLogFullLogWithPreLogNoArgs()
{
	std::cout << "testLogFullLogWithPreLogNoArgs() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )	
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::ProgramExecution;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// No Args - allowed for PreformattedLog
	try
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog );
		
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on GenericLog No Args" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed A" << std::endl;
}

// TestLogFullLogWithFirstArgNotStr
void TestLogger::testLogFullLogWithFirstArgNotStr()
{
	std::cout << "testLogFullLogWithFirstArgNotStr() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = false;
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
	
	// 1st arg not string
	try
	{
		vaListLog (type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, arg );
		
		std::cout << "Failed on 1st Arg not string" << std::endl;
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
}

// TestLogFullLogWithArgEmptyStr
void TestLogger::testLogFullLogWithArgEmptyStr()
{
	std::cout << "testLogFullLogWithArgEmptyStr() ... ";
	
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
	
	// Arg is empty string
	try
	{
		vaListLog (type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, "" );
		std::cout << "Failed on Empty Arg String" << std::endl;
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogFullLogWithArgIsNull
void TestLogger::testLogFullLogWithArgIsNull()
{
	std::cout << "testLogFullLogWithArgIsNull() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );

	// Arg is NULL
	try
	{
		vaListLog (type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, NULL );
		std::cout << "Failed on Arg is NULL" << std::endl;
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );
	}
#endif

	std::cout << "Passed" << std::endl;
}

// TestLogFullLogWithArgWrongType
void TestLogger::testLogFullLogWithArgWrongType()
{
	std::cout << "testLogFullLogWithArgWrongType() ... ";
	
// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
	
	// Arg is wrong type
	try
	{
		vaListLog (type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, 10 );
		
		std::cout << "Failed on Arg wrong type" << std::endl;
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
}

// TestLogFullLogWithExcessArgs
void TestLogger::testLogFullLogWithExcessArgs()
{
	std::cout << "testLogFullLogWithExcessArgs() ... ";
	
	bool simpleLog = false;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
		
	// Excess args
	try
	{
		unsigned int numPrinted = vaListLog (type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg, 2, 3 );
		
		Assert ( numPrinted > format.size() );
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
}

// TestLogFullLogWithFormatStrTooLarge
void TestLogger::testLogFullLogWithFormatStrTooLarge()
{
	std::cout << "testLogFullLogWithFormatStrTooLarge() ... ";
	
	bool simpleLog = false;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
		
	// Format string too large
	try
	{
		std::string longArg ( "" );
		for ( unsigned int i = 0; i < MAXLOGMESGSIZE + 1; ++i )
		{
			longArg += "a";
		}
		longArg += "z";

		std::string newFormat ( "Testing %s" );

		vaListLog (type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, newFormat.c_str(), longArg.c_str() );
		
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

// TestLogFullLogWithCorrectArgs
void TestLogger::testLogFullLogWithCorrectArgs()
{
	std::cout << "testLogFullLogWithCorrectArgs() ... ";
	
	bool simpleLog = false;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;

	// Load log types into cache
	setUpTestLevel ( logger );
		
	// Correct arguments
	try
	{
		unsigned int numPrinted = vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );

		Assert ( numPrinted > format.size() );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct arguments" << std::endl;
		Assert ( false );
	}


	std::cout << "Passed" << std::endl;
}

// TestLogSimpleLogWithEmptyFilename
void TestLogger::testLogSimpleLogWithEmptyFilename()
{
	std::cout << "testLogSimpleLogWithEmptyFilename() ... ";
	
	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Empty filename 
	try
	{
		unsigned int numPrinted = vaListLog ( type, logger, "", __LINE__, std::cout, simpleLog, format.c_str(), arg );
		
		Assert ( numPrinted > format.size() );
	}
	catch ( ... )
	{
		std::cout << "Failed on Empty Filename" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogSimpleLogWithLineEqualsZero
void TestLogger::testLogSimpleLogWithLineEqualsZero()
{
	std::cout << "testLogSimpleLogWithLineEqualsZero() ... ";
	
	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Line == 0
	try
	{
		unsigned int numPrinted = vaListLog ( type, logger, __FILE__, 0, std::cout, simpleLog, format.c_str(), arg );
		
		Assert ( numPrinted > format.size() );
	}
	catch ( ... )
	{
		std::cout << "Failed on Line == 0" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogSimpleLogWithNoArgs
void TestLogger::testLogSimpleLogWithNoArgs()
{
	std::cout << "testLogSimpleLogWithNoArgs() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// No Args
	try
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		vaListLog (type, logger, __FILE__, __LINE__, std::cout, simpleLog );	
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on No Args" << std::endl;
		Assert ( false );
	}
#endif

	std::cout << "Passed" << std::endl;
}

// TestLogSimpleLogWithFirstArgNotStr
void TestLogger::testLogSimpleLogWithFirstArgNotStr()
{
	std::cout << "testLogSimpleLogWithFirstArgNotStr() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = true;
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// 1st arg not string
	try
	{
		vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, arg );
		
		std::cout << "Failed on 1st Arg not string" << std::endl;
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

// TestLogSimpleLogWithWithArgEmptyStr
void TestLogger::testLogSimpleLogWithArgEmptyStr()
{
	std::cout << "testLogSimpleLogWithArgEmptyStr() ... ";
	
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );
	
	// Arg is empty string
	try
	{
		vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, "" );
		std::cout << "Failed on Empty Arg String" << std::endl;
		Assert ( false );		
	}
	catch ( ... )
	{
		Assert ( true );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogSimpleLogWithArgIsNull
void TestLogger::testLogSimpleLogWithArgIsNull()
{
	std::cout << "testLogSimpleLogWithArgIsNull() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Arg is NULL
	try
	{
		int numPrinted = vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, NULL );
		std::cout << "Failed on Arg is NULL" << std::endl;
		Assert ( false );
	}
	catch ( ... )
	{
		Assert ( true );
	}
#endif

	std::cout << "Passed" << std::endl;
}

// TestLogSimpleLogWithArgWrongType
void TestLogger::testLogSimpleLogWithArgWrongType()
{
	std::cout << "testLogSimpleLogWithArgWrongType() ... ";

// Cannot run this test under Solaris as it runs through
// format = va_arg ( args, char* ); but seg faults when it
// tries to use 'format'. Don't know how to ensure that a
// char * is passed through (...) as there are checks that
// 'format' is not equal to "" or NULL and it passes both.
#if defined ( WIN32 )
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Arg is wrong type
	try
	{
		vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, 10 );
				
		std::cout << "Failed on Arg wrong type" << std::endl;
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
}

// TestLogSimpleLogWithExcessArgs
void TestLogger::testLogSimpleLogWithExcessArgs()
{
	std::cout << "testLogSimpleLogWithExcessArgs() ... ";
	
	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Excess args
	try
	{
		unsigned int numPrinted = vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, format.c_str(), arg, 2, 3, 4 );
		
		Assert ( numPrinted > format.size() );
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
}

// TestLogSimpleLogWithFormatStrTooLarge
void TestLogger::testLogSimpleLogWithFormatStrTooLarge()
{
	std::cout << "testLogSimpleLogWithFormatStrTooLarge() ... ";
	
	bool simpleLog = true;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );


	// Format string too large
	try
	{
		std::string longArg ( "" );
		for ( unsigned int i = 0; i < MAXLOGMESGSIZE + 1; ++i )
		{
			longArg += "a";
		}
		longArg += "z";

		std::string newFormat ( "Testing %s" );

		vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, newFormat.c_str(), longArg.c_str() );
	
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

// TestLogSimpleLogWithCorrectArgs
void TestLogger::testLogSimpleLogWithCorrectArgs()
{
	std::cout << "testLogSimpleLogWithCorrectArgs() ... ";
	
	bool simpleLog = true;
	std::string format ( "Testing %d" );
	int arg = 1;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

	CU::Logger logger;
		
	// Load log types into cache
	setUpTestLevel ( logger );

	// Correct arguments
	try
	{
		unsigned int numPrinted = vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, format.c_str(), arg );

		Assert ( numPrinted > format.size() );
	}
	catch ( ... )
	{
		std::cout << "Failed on Correct arguments" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogWithCout
void TestLogger::testLogWithCout()
{
	std::cout << "testLogWithCout() ... ";

	bool simpleLog ( false );
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::Logger logger;

	// Load messages
	std::string format ( "Testing %d" );
	int arg = 1;
	int numMsgs = 3;
	char buff[100];
	
	sprintf ( buff, format.c_str(), arg );
	std::string msg ( buff );
	msg = "    " + msg + "\n";
	setUpTestLogCache ( logger, numMsgs, format.c_str(), arg );

	// Log to cout
	try
	{
		unsigned int numPrinted = vaListLog ( type, logger, __FILE__, __LINE__, std::cout, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );

		Assert ( numPrinted > msg.size() );
	}
	catch ( ... )
	{	
		std::cout << "Failed on Log Cache With Cout" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}

// TestLogCacheWithBadFile
void TestLogger::testLogWithBadFile()
{
	std::cout << "testLogCacheWithBadFile() ... ";

	std::fstream outFile;
	bool simpleLog ( false );
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::Logger logger;

	// Set the fail bit
	outFile.clear ( std::ios::failbit );

	// Error flag for file needs to be set for this test to run
	Assert ( outFile.fail() );

	// Load messages
	std::string format ( "Testing %d" );
	int arg = 1;
	int numMsgs = 3;
	setUpTestLogCache ( logger, numMsgs, format.c_str(), arg );

	char buff[100];
	sprintf ( buff, format.c_str(), arg );
	std::string msg ( buff );
	msg = "    " + msg + "\n";

	// Log to bad file
	try
	{
		// Shouldn't throw exception as it will just log to stdout if there
		// are problems writing to file
		vaListLog ( type, logger, __FILE__, __LINE__, outFile, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );
		outFile.clear();
		Assert ( true );
	}
	catch ( ... )
	{	
		std::cout << "Failed on Log to Bad File" << std::endl;
		Assert ( false );
	}

	outFile.clear();
	std::cout << "Passed" << std::endl;
}

// TestLogWithGoodFile
void TestLogger::testLogWithGoodFile()
{
	std::cout << "testLogWithGoodFile() ... ";
	
	std::fstream outFile;
	bool simpleLog ( false );
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	std::string filename ( "TestLogWithGoodFile.txt" );
	CU::Logger logger;

	// Create a file
	int fh;
#if defined ( SOLARIS )
	fh = creat( filename.c_str(), S_IREAD | S_IWRITE );
#else
	fh = _creat( filename.c_str(), _S_IREAD | _S_IWRITE );
#endif
	Assert ( fh != -1 );

	// Try to open the file
	outFile.open ( filename.c_str(),std::ios::out|std::ios::app );
	
	// Error flag must not be set for this test to run
	Assert ( !outFile.fail() );
	
	// Load messages
	std::string format ( "Testing %d" );
	int arg = 1;
	int numMsgs = 3;
	char buff[100];

	sprintf ( buff, format.c_str(), arg );
	std::string msg ( buff );
	msg = "    " + msg + "\n";
	setUpTestLogCache ( logger, numMsgs, format.c_str(), arg );

	// Log to good file
	try
	{
		vaListLog ( type, logger, __FILE__, __LINE__, outFile, simpleLog, CU::DebugUtil::DebugDebug, format.c_str(), arg );
		
		Assert ( true );
	}
	catch ( ... )
	{	
		// remove file
		outFile.close();
		RemoveFile ( fh, filename.c_str() );
		std::cout << "Failed on Log to Bad File" << std::endl;
		Assert ( false );		
	}

	// remove file
	outFile.close();
	RemoveFile ( fh, filename.c_str() );
	std::cout << "Passed" << std::endl;
}


// The suite method. Returns list of methods.

TestSuite* TestLogger::suite ()
{
    // Must have same name as test class.
    TestSuite * testSuite = new TestSuite( "TestLogger" );

    testSuite->addTest (
        new TestCaller <TestLogger> (
            "testConstructor", &TestLogger::testConstructor, this ) );
    
	/////////////////// AddToCache - Full Log

	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithEmptyFilename", &TestLogger::testAddToCacheFullLogWithEmptyFilename, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithLineEqualsZero", &TestLogger::testAddToCacheFullLogWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithGenLogNoArgs", &TestLogger::testAddToCacheFullLogWithGenLogNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithPreLogNoArgs", &TestLogger::testAddToCacheFullLogWithPreLogNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithFirstArgNotStr", &TestLogger::testAddToCacheFullLogWithFirstArgNotStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithArgEmptyStr", &TestLogger::testAddToCacheFullLogWithArgEmptyStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithArgIsNull", &TestLogger::testAddToCacheFullLogWithArgIsNull, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithArgWrongType", &TestLogger::testAddToCacheFullLogWithArgWrongType, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithExcessArgs", &TestLogger::testAddToCacheFullLogWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithFormatStrTooLarge", &TestLogger::testAddToCacheFullLogWithFormatStrTooLarge, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheFullLogWithCorrectArgs", &TestLogger::testAddToCacheFullLogWithCorrectArgs, this ) );

	/////////////////// AddToCache - Simple Log

	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithEmptyFilename", &TestLogger::testAddToCacheSimpleLogWithEmptyFilename, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithLineEqualsZero", &TestLogger::testAddToCacheSimpleLogWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithNoArgs", &TestLogger::testAddToCacheSimpleLogWithNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithFirstArgNotStr", &TestLogger::testAddToCacheSimpleLogWithFirstArgNotStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithArgEmptyStr", &TestLogger::testAddToCacheSimpleLogWithArgEmptyStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithArgIsNull", &TestLogger::testAddToCacheSimpleLogWithArgIsNull, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithArgWrongType", &TestLogger::testAddToCacheSimpleLogWithArgWrongType, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithExcessArgs", &TestLogger::testAddToCacheSimpleLogWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithFormatStrTooLarge", &TestLogger::testAddToCacheSimpleLogWithFormatStrTooLarge, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testAddToCacheSimpleLogWithCorrectArgs", &TestLogger::testAddToCacheSimpleLogWithCorrectArgs, this ) );
	
	/////////////////// AddLogType

	testSuite->addTest (
        new TestCaller <TestLogger> (
			"testAddLogTypeWithPreformattedLogType", &TestLogger::testAddLogTypeWithPreformattedLogType, this ) );
	testSuite->addTest (
		new TestCaller <TestLogger> (
			"testAddLogTypeWithGenericLogType", &TestLogger::testAddLogTypeWithGenericLogType, this ) );

	////////////////// GetLevel

	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testGetLevelWithLogTypesLoaded", &TestLogger::testGetLevelWithLogTypesLoaded, this ) );
    testSuite->addTest (
        new TestCaller <TestLogger> (
            "testGetLevelWithoutLogTypesLoaded", &TestLogger::testGetLevelWithoutLogTypesLoaded, this ) );

	////////////////// LogCache

	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogCacheWithLogTypesNotLoaded", &TestLogger::testLogCacheWithLogTypesNotLoaded, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogCacheWithCout", &TestLogger::testLogCacheWithCout, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogCacheWithBadFile", &TestLogger::testLogCacheWithBadFile, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogCacheWithGoodFile", &TestLogger::testLogCacheWithGoodFile, this ) );

	////////////////// Log

	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithEmptyFilename", &TestLogger::testLogFullLogWithEmptyFilename, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithLineEqualsZero", &TestLogger::testLogFullLogWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithGenLogNoArgs", &TestLogger::testLogFullLogWithGenLogNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithPreLogNoArgs", &TestLogger::testLogFullLogWithPreLogNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithFirstArgNotStr", &TestLogger::testLogFullLogWithFirstArgNotStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithArgEmptyStr", &TestLogger::testLogFullLogWithArgEmptyStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithArgIsNull", &TestLogger::testLogFullLogWithArgIsNull, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithArgWrongType", &TestLogger::testLogFullLogWithArgWrongType, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithExcessArgs", &TestLogger::testLogFullLogWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithFormatStrTooLarge", &TestLogger::testLogFullLogWithFormatStrTooLarge, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogFullLogWithCorrectArgs", &TestLogger::testLogFullLogWithCorrectArgs, this ) );

	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithEmptyFilename", &TestLogger::testLogSimpleLogWithEmptyFilename, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithLineEqualsZero", &TestLogger::testLogSimpleLogWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithNoArgs", &TestLogger::testLogSimpleLogWithNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithFirstArgNotStr", &TestLogger::testLogSimpleLogWithFirstArgNotStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithArgEmptyStr", &TestLogger::testLogSimpleLogWithArgEmptyStr, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithArgIsNull", &TestLogger::testLogSimpleLogWithArgIsNull, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithArgWrongType", &TestLogger::testLogSimpleLogWithArgWrongType, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithExcessArgs", &TestLogger::testLogSimpleLogWithExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithFormatStrTooLarge", &TestLogger::testLogSimpleLogWithFormatStrTooLarge, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogSimpleLogWithCorrectArgs", &TestLogger::testLogSimpleLogWithCorrectArgs, this ) );
	
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogWithCout", &TestLogger::testLogWithCout, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogWithBadFile", &TestLogger::testLogWithBadFile, this ) );
	testSuite->addTest (
        new TestCaller <TestLogger> (
            "testLogWithGoodFile", &TestLogger::testLogWithGoodFile, this ) );

    return testSuite;
}


void TestLogger::vaListAddToCache(CU::DebugUtil::EDebugType type, CU::Logger& logger, const std::string& file, int line, bool simpleLog, ...)
{
	va_list arg;
	va_start ( arg, simpleLog );

	logger.addToCache ( type, file, line, arg, simpleLog );
}


void TestLogger::setUpTestLevel(CU::Logger& logger)
{
	CU::DebugUtil::DebugTypeData DebugTypeInfo[] = 	
	{
		{CU::DebugUtil::ProgramExecution,     CU::DebugUtil::DebugDebug, "Program Executed: %s"},
		{CU::DebugUtil::ProgramEnd,		      CU::DebugUtil::DebugDebug, "Program Ended: %s"},
		{CU::DebugUtil::FunctionEntry,	      CU::DebugUtil::DebugTrace, "Function Entered: %s"},
		{CU::DebugUtil::FunctionExit,	      CU::DebugUtil::DebugTrace, "Function Exited: %s"},
		{CU::DebugUtil::ExceptionConstruction, CU::DebugUtil::DebugError, "TA Exception Constructed: %s: %s"},
		{CU::DebugUtil::ExceptionDetails,	  CU::DebugUtil::DebugError, "TA Exception Details: %s: %s"},
		{CU::DebugUtil::ExceptionCatch,	      CU::DebugUtil::DebugError, "Exception Caught: %s: %s"},
		{CU::DebugUtil::ThreadCreate,	      CU::DebugUtil::DebugDebug, "Thread Created: %s"},
		{CU::DebugUtil::ThreadBegin,	      CU::DebugUtil::DebugDebug, "Thread Started: %s"},
		{CU::DebugUtil::ThreadEnd,		      CU::DebugUtil::DebugDebug, "Thread Ended: %s"},
		{CU::DebugUtil::AssertFailed,		  CU::DebugUtil::DebugError, "ASSERT Failed:\n\tFile: %s\n\tLine: %d\n\tFailed Condition: %s\n\tDescription: %s"},
		{CU::DebugUtil::GenProcessCreate,     CU::DebugUtil::DebugDebug, "Generic Process Created: %s"},
		{CU::DebugUtil::GenProcessDestroy,    CU::DebugUtil::DebugDebug, "Generic Process Destroyed: %s"},
		{CU::DebugUtil::MandConfParam,	      CU::DebugUtil::DebugFatal, "Mandatory Configuration Parameter: %s: %s"},
		{CU::DebugUtil::OptConfParam,	      CU::DebugUtil::DebugWarn,  "Optional Configuration Parameter: %s: %s"},
		{CU::DebugUtil::DatabaseProblem,      CU::DebugUtil::DebugError, "Database Connection Problem: %s"},
		{CU::DebugUtil::SubmitAlarmMessage,   CU::DebugUtil::DebugError, "Could not submit %s: %s"},

		// This one (GenericLog) always remains at the end
		{CU::DebugUtil::GenericLog, CU::DebugUtil::DebugWarn, NULL},
	};

	// Load GenericLog type
	CU::GenericLogType* glogType = new CU::GenericLogType;
	logger.addLogType ( *glogType );
	
	// Load Preformatted types
	CU::DebugUtil::DebugTypeData* dtd = DebugTypeInfo;
	while ( dtd->debugType != CU::DebugUtil::GenericLog )
	{
		CU::DebugUtil::EDebugType debugType = dtd->debugType;
		CU::DebugUtil::EDebugLevel debugLevel = dtd->debugLevel;
		std::string debugFormat( dtd->formatString );
		
		++dtd;

		CU::PreformattedLogType* plogType = new CU::PreformattedLogType( debugType, debugLevel, debugFormat );
		logger.addLogType ( *plogType );
	}
}


void TestLogger::setUpTestLogCache(CU::Logger& logger, int numMsgs, ...)
{
	bool simpleLog = true;
	std::string file ( "" );
	int line = 0;
	CU::DebugUtil::EDebugType type = CU::DebugUtil::ProgramExecution;

	va_list args;
	va_start ( args, numMsgs );

	// Load log types
	setUpTestLevel ( logger );

	// Add messages into the cache
	for ( int i = 0; i < numMsgs; ++i )
	{
		logger.addToCache ( type, file, line, args, simpleLog );
	}
}


int TestLogger::vaListLog(CU::DebugUtil::EDebugType type, CU::Logger& logger, const std::string& file, int line, std::ostream& outfile, bool simpleLog, ...)
{
	va_list arg;
	va_start ( arg, simpleLog );

	return logger.log ( type, file, line, arg, outfile, simpleLog );
}

void TestLogger::RemoveFile( const std::string& filename )
{

    // Set the log file to another file to remove the handle
    //++m_setFileCount;
    //CU::DebugUtil::getInstance().setFile ( "removeMe" );

#if defined ( SOLARIS )

	remove ( filename.c_str() );

#else

    std::string cmd ( "cmd /c\"RemoveFile.bat " );
    cmd += filename + "\"";

    system ( cmd.c_str() );

#endif    
}


void TestLogger::RemoveFile( int fileHandle, const std::string& filename )
{
#if defined ( SOLARIS )
    close ( fileHandle );
#else
    _close ( fileHandle );
#endif
    RemoveFile ( filename );
}
