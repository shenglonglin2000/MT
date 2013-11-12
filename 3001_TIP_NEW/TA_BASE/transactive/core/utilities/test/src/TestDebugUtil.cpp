/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestDebugUtil.cpp $
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
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "TestDebugUtil.h"
#include "core/utilities/src/DebugUtil.h"

TestDebugUtil::DebugTypeStruct debugtypes[] = 
{
	{CU::DebugUtil::ProgramExecution, "ProgramExecution"},
	{CU::DebugUtil::ProgramEnd, "ProgramEnd"},
	{CU::DebugUtil::FunctionEntry, "FunctionEntry"},
	{CU::DebugUtil::FunctionExit, "FunctionExit"},
	{CU::DebugUtil::ExceptionConstruction, "ExceptionConstruction"},
	{CU::DebugUtil::ExceptionCatch, "ExceptionCatch"},
	{CU::DebugUtil::ThreadCreate, "ThreadCreate"},
	{CU::DebugUtil::ThreadBegin, "ThreadBegin"},
	{CU::DebugUtil::ThreadEnd, "ThreadEnd"},
	{CU::DebugUtil::GenProcessCreate, "GenProcessCreate"},
	{CU::DebugUtil::GenProcessDestroy, "GenProcessDestroy"},
	{CU::DebugUtil::MandConfParam, "MandConfParam"},
	{CU::DebugUtil::OptConfParam, "OptConfParam"},
	{CU::DebugUtil::DatabaseProblem, "DatabaseProblem"},
	{CU::DebugUtil::SubmitAlarmMessage, "SubmitAlarmMessage"},
	{CU::DebugUtil::GenericLog, NULL}
};


// Initialises variables at the beginning of a test suite
void TestDebugUtil::setUpSuite ( std::string const & INFile )
{
    // Use the INFile string to read in data,
    // this can change according the config file.
}


// Initialises variables at the end of a test suite
void TestDebugUtil::tearDownSuite ()
{
    RemoveFile ( "removeMe.*" );
}


void TestDebugUtil::setUp ( const std::string & INFile , const std::string & OUTFile)
{
   // Use the INFile string to read in data,
    // this can change according the config file.
}


void TestDebugUtil::tearDown ( const std::string & OUTFile )
{
   // Use the INFile string to read in data,
    // this can change according the config file.
}


///////////////////////////////////////
// Test getInstance
///////////////////////////////////////

void TestDebugUtil::TestGetInstance ()
{
	std::cout << "TestGetInstance() ... "; 

    //
	// Test: An instance of DebugUtil is constructed properly
    // Expected: Success
    // Preconditions: None
    //
	try
	{
		CU::DebugUtil::getInstance();

		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


///////////////////////////////////////
// Test setFile
///////////////////////////////////////

// TestSetFileWithExistingFile
void TestDebugUtil::TestSetFileWithExistingFile()
{
	std::cout << "TestSetFileWithExistingFile() ... ";

	std::string filename ( "TestSetFileWithExistingFile.txt" );
    std::string buffer = this->createFilename( filename, ++m_setFileCount );

    FILE *fp = fopen( buffer.c_str(), "w" );
    fclose( fp );

    //
	// Test: An existing file can be assigned as the new log file
    // Expected: Success
    // Preconditions: The file already exists
    //
	try
	{
		CU::DebugUtil::getInstance().setFile ( filename.c_str() );
	}
	catch ( ... )
	{
		// Remove File
        RemoveFile ( buffer );
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

    RemoveFile ( buffer );
	std::cout << "Passed" << std::endl;
}


// TestSetFileWithNotExistingFile
void TestDebugUtil::TestSetFileWithNotExistingFile()
{
	std::cout << "TestSetFileWithNotExistingFile() ... ";

	std::string filename ( "TestSetFileWithNotExistingFile.txt" );
    std::string buffer = this->createFilename( filename, ++m_setFileCount );

    //
	// Test: Assign a file that doesn't exist as the new log file
    // Expected: Success
    // Preconditions: The file does not exist
    //
	try
	{
		CU::DebugUtil::getInstance().setFile ( filename.c_str() );
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	RemoveFile ( buffer );
	std::cout << "Passed" << std::endl;
}


///////////////////////////////////////
// TestGetStringDebugLevel
///////////////////////////////////////

// TestGetStringDebugLevelWithAllLevels
void TestDebugUtil::TestGetStringDebugLevelWithAllLevels()
{
	std::cout << "TestGetStringDebugLevelWithAllLevels() ... ";

	//
	// Test: Get the string equivalent of the Fatal debug level
    // Expected: Success
    // Preconditions: None
    //
	try
	{
		std::string level = CU::DebugUtil::getInstance().getStringDebugLevel( CU::DebugUtil::DebugFatal );
		Assert ( level == "FATAL" );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Error
	try
	{
		std::string level = CU::DebugUtil::getInstance().getStringDebugLevel( CU::DebugUtil::DebugError );
		Assert ( level == "ERROR" );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Warn
	try
	{
		std::string level = CU::DebugUtil::getInstance().getStringDebugLevel( CU::DebugUtil::DebugWarn );
		Assert ( level == "WARN" );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Norm
	try
	{
		std::string level = CU::DebugUtil::getInstance().getStringDebugLevel( CU::DebugUtil::DebugNorm );
		Assert ( level == "NORM" );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Info
	try
	{
		std::string level = CU::DebugUtil::getInstance().getStringDebugLevel( CU::DebugUtil::DebugInfo );
		Assert ( level == "INFO" );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Debug
	try
	{
		std::string level = CU::DebugUtil::getInstance().getStringDebugLevel( CU::DebugUtil::DebugDebug );
		Assert ( level == "DEBUG" );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


///////////////////////////////////////
// TestGetDebugLevelFromString
///////////////////////////////////////

// TestGetDebugLevelFromStringWithAllLevels
void TestDebugUtil::TestGetDebugLevelFromStringWithAllLevels()
{
	std::cout << "TestGetDebugLevelFromStringWithAllLevels() ... ";

	// Fatal
	try
	{
		CU::DebugUtil::EDebugLevel level = CU::DebugUtil::getInstance().getDebugLevelFromString( "FATAL" );
		Assert ( level == CU::DebugUtil::DebugFatal );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Error
	try
	{
		CU::DebugUtil::EDebugLevel level = CU::DebugUtil::getInstance().getDebugLevelFromString( "ERROR" );
		Assert ( level == CU::DebugUtil::DebugError );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Warn
	try
	{
		CU::DebugUtil::EDebugLevel level = CU::DebugUtil::getInstance().getDebugLevelFromString( "WARN" );
		Assert ( level == CU::DebugUtil::DebugWarn );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Norm
	try
	{
		CU::DebugUtil::EDebugLevel level = CU::DebugUtil::getInstance().getDebugLevelFromString( "NORM" );
		Assert ( level == CU::DebugUtil::DebugNorm );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Info
	try
	{
		CU::DebugUtil::EDebugLevel level = CU::DebugUtil::getInstance().getDebugLevelFromString( "INFO" );
		Assert ( level == CU::DebugUtil::DebugInfo );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	// Debug
	try
	{
		CU::DebugUtil::EDebugLevel level = CU::DebugUtil::getInstance().getDebugLevelFromString( "DEBUG" );
		Assert ( level == CU::DebugUtil::DebugDebug );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestGetDebugLevelFromStringWithNonExistingLevel
void TestDebugUtil::TestGetDebugLevelFromStringWithNonExistingLevel()
{
	std::cout << "TestGetDebugLevelFromStringWithNonExistingLevel() ... ";

	try
	{
		CU::DebugUtil::getInstance().getDebugLevelFromString( "UNKNOWN" );
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
}


///////////////////////////////////////
// TestLog
///////////////////////////////////////

// TestLogWithEmptyFilename
void TestDebugUtil::TestLogWithEmptyFilename()
{
	std::cout << "TestLogWithEmptyFilename() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugFatal;
	std::string logMsg ( "TestLogWithEmptyFilename" );

	try
	{
		CU::DebugUtil::getInstance().log ( "", __LINE__, type, level, logMsg.c_str() );
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
}


// TestLogWithLineEqualsZero
void TestDebugUtil::TestLogWithLineEqualsZero()
{
	std::cout << "TestLogWithLineEqualsZero() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugFatal;
	std::string logMsg ( "TestLogWithLineEqualsZero" );

	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, 0, type, level, logMsg.c_str() );
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
}


// TestLogWithPreNoArgs
void TestDebugUtil::TestLogWithPreNoArgs()
{
	std::cout << "TestLogWithPreNoArgs() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )
	
	// Test all the Preformatted types
	DebugTypeStruct* dts = debugtypes;
	while ( dts->name != NULL )
	{
		CU::DebugUtil::EDebugType type = dts->type;
		try
		{
			// An exception should not be thrown because it is up to the caller to provide
			// the correct arguments. If the correct args are not provided the message
			// string will not be as expected.
			CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type );
            Assert ( true );		
		}
        //catch ( AssertionFailedError & )
		//{    
		//	throw;
		//}
		catch ( ... )
		{
            std::cout << "Failed on " << dts->name << std::endl;
			Assert ( false );			
		}
		++dts;
	}
#endif
	std::cout << "Passed" << std::endl;
}



// TestLogWithPreArgEmptyStr
void TestDebugUtil::TestLogWithPreArgEmptyStr()
{
	std::cout << "TestLogWithPreArgEmptyStr() ... ";

	// Test all the Preformatted types
	DebugTypeStruct* dts = debugtypes;
	while ( dts->name != NULL )
	{
		CU::DebugUtil::EDebugType type = dts->type;
		try
		{
			CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, "" );
            std::cout << "Failed on " << dts->name << std::endl;
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
		++dts;
	}

	std::cout << "Passed" << std::endl;
}


// TestLogWithPreExcessArgs
void TestDebugUtil::TestLogWithPreExcessArgs()
{
	std::cout << "TestLogWithPreExcessArgs() ... ";

	std::string arg ( "TestLogWithPreExcessArgs" );

	// Program Execution
	CU::DebugUtil::EDebugType type = CU::DebugUtil::ProgramExecution;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ProgramExecution" << std::endl;
		Assert ( false );
	}

	// Program End
	type = CU::DebugUtil::ProgramEnd;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ProgramEnd" << std::endl;
		Assert ( false );
	}

	// Function Entry
	type = CU::DebugUtil::FunctionEntry;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionEntry" << std::endl;
		Assert ( false );
	}

	// Function Exit
	type = CU::DebugUtil::FunctionExit;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionExit" << std::endl;
		Assert ( false );
	}

	// Exception Construction
	type = CU::DebugUtil::ExceptionConstruction;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ExceptionConstruction" << std::endl;
		Assert ( false );
	}

	// Exception Catch
	type = CU::DebugUtil::ExceptionCatch;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ExceptionCatch" << std::endl;
		Assert ( false );
	}

	// Thread Create
	type = CU::DebugUtil::ThreadCreate;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ThreadCreate" << std::endl;
		Assert ( false );
	}

	// Thread Begin
	type = CU::DebugUtil::ThreadBegin;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ThreadBegin" << std::endl;
		Assert ( false );
	}

	// Thread End
	type = CU::DebugUtil::ThreadEnd;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ThreadEnd" << std::endl;
		Assert ( false );
	}

	// GenProcessCreate
	type = CU::DebugUtil::GenProcessCreate;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on GenProcessCreate" << std::endl;
		Assert ( false );
	}

	// GenProcessDestroy
	type = CU::DebugUtil::GenProcessDestroy;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on GenProcessDestroy" << std::endl;
		Assert ( false );
	}

	// MandConfParam
	type = CU::DebugUtil::MandConfParam;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on MandConfParam" << std::endl;
		Assert ( false );
	}

	// OptConfParam
	type = CU::DebugUtil::OptConfParam;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on OptConfParam" << std::endl;
		Assert ( false );
	}

	// DatabaseProblem
	type = CU::DebugUtil::DatabaseProblem;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on DatabaseProblem" << std::endl;
		Assert ( false );
	}

	// SubmitAlarmMessage
	type = CU::DebugUtil::SubmitAlarmMessage;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on SubmitAlarmMessage" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogWithPreFormatStrWithArg
void TestDebugUtil::TestLogWithPreFormatStrWithArg()
{
	std::cout << "TestLogWithPreFormatStrWithArg() ... ";

	std::string logMsg ( "TestLogWithPreFormatStrWithArg: %s" );
	std::string arg ( "" );

	// Test all the Preformatted types
	DebugTypeStruct* dts = debugtypes;
	while ( dts->name != NULL )
	{
		CU::DebugUtil::EDebugType type = dts->type;
		arg = dts->name;
		try
		{
			CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, logMsg.c_str(), arg.c_str() );
			Assert ( true );
			
		}
		catch ( ... )
		{
			std::cout << "Failed on " << dts->name << std::endl;
			Assert ( false );
		}
		++dts;
	}

	std::cout << "Passed" << std::endl;
}


// TestLogWithPreCorrectArg
void TestDebugUtil::TestLogWithPreCorrectArg()
{
	std::cout << "TestLogWithPreCorrectArg() ... ";

	std::string arg ( "TestLogWithPreCorrectArg" );

	// Program Execution
	CU::DebugUtil::EDebugType type = CU::DebugUtil::ProgramExecution;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ProgramExecution" << std::endl;
		Assert ( false );
	}

	// Program End
	type = CU::DebugUtil::ProgramEnd;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ProgramEnd" << std::endl;
		Assert ( false );
	}

	// Function Entry
	type = CU::DebugUtil::FunctionEntry;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionEntry" << std::endl;
		Assert ( false );
	}

	// Function Exit
	type = CU::DebugUtil::FunctionExit;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on FunctionExit" << std::endl;
		Assert ( false );
	}

	// Exception Construction
	type = CU::DebugUtil::ExceptionConstruction;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ExceptionConstruction" << std::endl;
		Assert ( false );
	}

	// Exception Catch
	type = CU::DebugUtil::ExceptionCatch;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ExceptionCatch" << std::endl;
		Assert ( false );
	}

	// Thread Create
	type = CU::DebugUtil::ThreadCreate;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ThreadCreate" << std::endl;
		Assert ( false );
	}

	// Thread Begin
	type = CU::DebugUtil::ThreadBegin;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ThreadBegin" << std::endl;
		Assert ( false );
	}

	// Thread End
	type = CU::DebugUtil::ThreadEnd;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on ThreadEnd" << std::endl;
		Assert ( false );
	}

	// GenProcessCreate
	type = CU::DebugUtil::GenProcessCreate;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on GenProcessCreate" << std::endl;
		Assert ( false );
	}

	// GenProcessDestroy
	type = CU::DebugUtil::GenProcessDestroy;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on GenProcessDestroy" << std::endl;
		Assert ( false );
	}

	// MandConfParam
	type = CU::DebugUtil::MandConfParam;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on MandConfParam" << std::endl;
		Assert ( false );
	}

	// OptConfParam
	type = CU::DebugUtil::OptConfParam;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on OptConfParam" << std::endl;
		Assert ( false );
	}

	// DatabaseProblem
	type = CU::DebugUtil::DatabaseProblem;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on DatabaseProblem" << std::endl;
		Assert ( false );
	}

	// SubmitAlarmMessage
	type = CU::DebugUtil::SubmitAlarmMessage;
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on SubmitAlarmMessage" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogWithGenFirstArgNotLevel
void TestDebugUtil::TestLogWithGenFirstArgNotLevel()
{
	std::cout << "TestLogWithGenFirstArgNotLevel() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type );
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
}


// TestLogWithGenArgEmptyStr
void TestDebugUtil::TestLogWithGenArgEmptyStr()
{
	std::cout << "TestLogWithGenArgEmptyStr() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugFatal;
	
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, level, "" );
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
}


// TestLogWithGenArgNull
void TestDebugUtil::TestLogWithGenArgNull()
{
	std::cout << "TestLogWithGenArgNull() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugFatal;

	// If run under Windows, log() will be executed without any
	// problems even if NULL is passed as a parameter. va_arg()		
	// will still try to retrieve an argument even if it is NULL.
//#if defined ( WIN32 )
//	try
//	{
//		CU::DebugUtil::getInstance().log ( filename, line, type, level, NULL );
//		std::cout << "Failed" << std::endl;
//		Assert ( false );
//	}
//	catch ( AssertionFailedError & )
//	{    
//		throw;
//	}
//	catch ( ... )
//	{
//		Assert ( true );
//	}
	// If run under Solaris, va_arg() will throw an exception when
	// trying to retrieve an argument that is NULL. Since log()
	// catches all exceptions, an error will be written to stdout
	// and log should finish execution without throwing any
	// exceptions
//#else
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, level );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}
//#endif

	std::cout << "Passed" << std::endl;
}


// TestLogWithGenFormatStrNoArg - this test is redundant I think.
// Already have a test "TestLogWithPreNoArgs" for no variable args.
// Up to caller to provide correct args if a format string has been
// provided
void TestDebugUtil::TestLogWithGenFormatStrNoArg()
{
	std::cout << "TestLogWithGenFormatStrNoArg() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )
	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugFatal;
	std::string format ( "Running test: %s" );
	
	try
	{
		// An exception should not be thrown because it is up to the caller to provide
		// the correct arguments. If the correct args are not provided the message
		// string will not be as expected.
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, level, format.c_str() );
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


// TestLogWithGenExcessArgs
void TestDebugUtil::TestLogWithGenExcessArgs()
{
	std::cout << "TestLogWithGenExcessArgs() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugFatal;
	std::string format ( "Running test: %s" );
	std::string arg ( "TestLogWithGenExcessArgs" );
	
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, level, format.c_str(), arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on format string" << std::endl;
		Assert ( false );
	}

	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, level, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on plain string" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogWithGenCorrectArg
void TestDebugUtil::TestLogWithGenCorrectArg()
{
	std::cout << "TestLogWithGenCorrectArg() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;
	CU::DebugUtil::EDebugLevel level = CU::DebugUtil::DebugFatal;
	std::string format ( "Running test: %s" );
	std::string arg ( "TestLogWithGenFormatStrNoArg" );
	
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, level, format.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogWithDebugLevelFatal
void TestDebugUtil::TestLogWithDebugLevelFatal()
{
	std::cout << "TestLogWithDebugLevelFatal() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

    // Set the required strings
	std::string format ( "Running test: TestLogWithDebugLevelFatal" );
	std::string logfile ( "TestLogWithDebugLevelFatal.txt" );
    std::string buffer = this->createFilename( logfile, ++m_setFileCount );

	// Set the file
	CU::DebugUtil::getInstance().setFile ( logfile.c_str() );
	
	// Set level to Fatal
	CU::DebugUtil::getInstance().setLevel ( CU::DebugUtil::DebugFatal );

	// Log some lower level messages
	try
	{
		// These messages should all be cached
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugDebug, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugInfo, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugWarn, format.c_str() );

        // We should have no lines in the log.
		Assert ( 0 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log a FATAL message
	try
	{
		// All Cached messages should be written to the file along with the following message
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugFatal, format.c_str() );
		
        // We should have 3 cached + 1 above lines in the log.
        Assert ( 4 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	RemoveFile ( buffer );
	std::cout << "Passed" << std::endl;
}


// TestLogWithDebugLevelError
void TestDebugUtil::TestLogWithDebugLevelError()
{
	std::cout << "TestLogWithDebugLevelError() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

    // Set the required strings.
	std::string format ( "Running test: TestLogWithDebugLevelError" );
	std::string logfile ( "TestLogWithDebugLevelError.txt" );	
    std::string buffer = this->createFilename( logfile, ++m_setFileCount );

    // Set the file
	CU::DebugUtil::getInstance().setFile ( logfile.c_str() );
	
	// Set level to Fatal
	CU::DebugUtil::getInstance().setLevel ( CU::DebugUtil::DebugError );

	// Log some lower level messages
	try
	{
		// These messages should all be cached
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugDebug, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugInfo, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugWarn, format.c_str() );

        // We should have no lines in the log.
        Assert( 0 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log an ERROR message
	try
	{
		// All Cached messages should be written to the file along with the following message
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugError, format.c_str() );
		
        // We should have 1 above and 3 cached lines in the log.
		Assert ( 4 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log some lower level messages
	try
	{
		// These messages should all be cached
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugDebug, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugInfo, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugWarn, format.c_str() );
		
        // We should still have 4 lines in the log.
		Assert ( 4 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log a FATAL message
	try
	{
		// All Cached messages should be written to the file along with the following message
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugFatal, format.c_str() );
		
		// We should now have 4 orig + 3 cached + 1 above lines in the log.
		Assert ( 8 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	RemoveFile ( buffer );
	std::cout << "Passed" << std::endl;
}


// TestLogWithDebugLevelWarn
void TestDebugUtil::TestLogWithDebugLevelWarn()
{
	std::cout << "TestLogWithDebugLevelWarn() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

    // Set the required strings
	std::string format ( "Running test: TestLogWithDebugLevelWarn" );
	std::string logfile ( "TestLogWithDebugLevelWarn.txt" );
    std::string buffer = this->createFilename( logfile, ++m_setFileCount );
	
	// Set the file
	CU::DebugUtil::getInstance().setFile ( logfile.c_str() );
	
	// Set level to Fatal
	CU::DebugUtil::getInstance().setLevel ( CU::DebugUtil::DebugWarn );

	// Log some lower level messages
	try
	{
		// These messages should not be printed
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugDebug, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugInfo, format.c_str() );
		
        // We should have no lines in the log.
		Assert ( 0 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log WARN message
	try
	{
		// These messages should be printed
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugWarn, format.c_str() );
		
        // We should have the above line in the log.
		Assert ( 1 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log higher level messages
	try
	{
		// These messages should be printed
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugError, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugFatal, format.c_str() );
		
        // We should have the above 2 + 1 original lines in the log.
		Assert ( 3 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile ( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile ( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	RemoveFile ( buffer );
	std::cout << "Passed" << std::endl;
}


// TestLogWithDebugLevelInfo
void TestDebugUtil::TestLogWithDebugLevelInfo()
{
	std::cout << "TestLogWithDebugLevelInfo() ... ";

	CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

    // Set the required strings
	std::string format ( "Running test: TestLogWithDebugLevelInfo" );
	std::string logfile ( "TestLogWithDebugLevelInfo.txt" );	
    std::string buffer = this->createFilename( logfile, ++m_setFileCount );
					
	// Set the file
	CU::DebugUtil::getInstance().setFile ( logfile.c_str() );
	
	// Set level to Info
	CU::DebugUtil::getInstance().setLevel ( CU::DebugUtil::DebugInfo );

	// Log some lower level messages
	try
	{
		// These messages should not be printed
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugDebug, format.c_str() );
		
        // We should have no lines in the log.
		Assert ( 0 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log INFO message
	try
	{
		// These messages should not be printed
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugInfo, format.c_str() );
		
        // We should now have the above line in the log.
		Assert ( 1 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	// Log higher level messages
	try
	{
		// These messages should be printed
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugWarn, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugError, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugFatal, format.c_str() );
		
        // We should now have the above 3 lines + the line already in the log.
		Assert ( 4 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
		std::cout << "Failed" << std::endl;
		RemoveFile( buffer );
		throw;
	}
	catch ( ... )
	{
		RemoveFile( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

    RemoveFile( buffer );
	std::cout << "Passed" << std::endl;
}


// TestLogWithDebugLevelDebug
void TestDebugUtil::TestLogWithDebugLevelDebug()
{
	std::cout << "TestLogWithDebugLevelDebug() ... ";

    CU::DebugUtil::EDebugType type = CU::DebugUtil::GenericLog;

    // Set the required strings
	std::string format ( "Running test: TestLogWithDebugLevelDebug" );
	std::string logfile ( "TestLogWithDebugLevelDebug.txt" );	
    std::string buffer = this->createFilename( logfile, ++m_setFileCount );

	// Set the file
	CU::DebugUtil::getInstance().setFile ( logfile.c_str() );
	
	// Set level to Debug
	CU::DebugUtil::getInstance().setLevel ( CU::DebugUtil::DebugDebug );

	// Log all level messages
	try
	{
		// These messages should be printed
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugDebug, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugInfo, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugWarn, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugError, format.c_str() );
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, type, CU::DebugUtil::DebugFatal, format.c_str() );

        // We should now have the above 5 lines in the log.
		Assert ( 5 == this->countLines( buffer ) );
	}
	catch ( AssertionFailedError & )
	{
        this->RemoveFile( buffer );
		std::cout << "Failed" << std::endl;
		throw;
	}
	catch ( ... )
	{
        this->RemoveFile( buffer );
		std::cout << "Test did not complete..." << std::endl;
		Assert ( false );
	}

	this->RemoveFile( buffer );
    std::cout << "Passed" << std::endl;
}


///////////////////////////////////////
// TestLogMore
///////////////////////////////////////

// TestLogMoreWithNoArgs
void TestDebugUtil::TestLogMoreWithNoArgs()
{
	std::cout << "TestLogMoreWithNoArgs() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )
	
	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__ );
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


// TestLogMoreWithArgNull
void TestDebugUtil::TestLogMoreWithArgNull()
{
	std::cout << "TestLogMoreWithArgNull() ... ";

	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, NULL );
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
}


// TestLogMoreWithFormatStrNoArg
void TestDebugUtil::TestLogMoreWithFormatStrNoArg()
{
	std::cout << "TestLogMoreWithFormatStrNoArg() ... ";

// Cannot run this test under Solaris as vsprintf (called in
// PreformattedLogType and GenericLogType) segfaults if
// no args are supplied... I still can't figure out how to
// determine whether args are provided or not...
#if defined ( WIN32 )
	std::string format ( "This is testing: %s" );
	
	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
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


// TestLogMoreWithExcessArgs
void TestDebugUtil::TestLogMoreWithExcessArgs()
{
	std::cout << "TestLogMoreWithExcessArgs() ... ";

	std::string format ( "This is testing: %s" );
	std::string arg ( "TestLogMoreWithExcessArgs" );
	
	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str(), arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on format string" << std::endl;
		Assert ( false );
	}

	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, arg.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed on plain string" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogMoreWithCorrectArgs
void TestDebugUtil::TestLogMoreWithCorrectArgs()
{
	std::cout << "TestLogMoreWithCorrectArgs() ... ";

	std::string format ( "This is testing: %s" );
	std::string arg ( "TestLogMoreWithCorrectArgs" );
	
	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str(), arg.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogMoreWithPlainStr
void TestDebugUtil::TestLogMoreWithPlainStr()
{
	std::cout << "TestLogMoreWithPlainStr() ... ";

	std::string format ( "This is testing: TestLogMoreWithPlainStr" );
	
	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogMoreWithNotCallingLog
void TestDebugUtil::TestLogMoreWithNotCallingLog()
{
	std::cout << "TestLogMoreWithNotCallingLog() ... ";

	std::string format ( "This is testing: TestLogMoreWithNotCallingLog" );
	
	try
	{
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


// TestLogMoreWithCallingLogFirst
void TestDebugUtil::TestLogMoreWithCallingLogFirst()
{
	std::cout << "TestLogMoreWithCallingLogFirst() ... ";

	std::string format ( "This is testing: TestLogMoreWithCallingLogFirst" );
	
	try
	{
		CU::DebugUtil::getInstance().log ( __FILE__, __LINE__, CU::DebugUtil::GenericLog, CU::DebugUtil::DebugFatal, format.c_str() );
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
		CU::DebugUtil::getInstance().logMore ( __FILE__, __LINE__, format.c_str() );
		Assert ( true );
	}
	catch ( ... )
	{
		std::cout << "Failed" << std::endl;
		Assert ( false );
	}

	std::cout << "Passed" << std::endl;
}


void TestDebugUtil::testLOGWithSwapFile()
{
	std::cout << "testLOGWithSwapFiles() ... ";

    CU::DebugUtil::getInstance().setFile("TestDebugUtilSwapFile");
    CU::DebugUtil::getInstance().setLevel(CU::DebugUtil::DebugDebug);
    CU::DebugUtil::getInstance().setMaxSize(100);
    CU::DebugUtil::getInstance().setMaxFiles(3);

    std::string msgOf100Bytes("");
    for(int i=0; i<99; ++i)
    {
        msgOf100Bytes += "A";
    }
    msgOf100Bytes += "\n";

    for(int j=0; j<5; ++j)
    {
	    try
	    {
		    LOG ( SourceInfo, CU::DebugUtil::GenericLog, CU::DebugUtil::DebugDebug, "%s", msgOf100Bytes.c_str() ); 
		    Assert ( true );
	    }
	    catch ( ... )
	    {
            RemoveFile ( "TestDebugUtilSwapFile.*" );
		    std::cout << "Failed" << std::endl;
		    Assert ( false );
	    }
    }

    RemoveFile ( "TestDebugUtilSwapFile.*" );
	std::cout << "Passed" << std::endl;
}


// The suite method. Returns list of methods.

TestSuite* TestDebugUtil::suite ()
{
    // Must have same name as test class.
    TestSuite * testSuite = new TestSuite( "TestDebugUtil" );

    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestGetInstance", &TestDebugUtil::TestGetInstance, this ) );
    
	////////////// TestGetString

	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestGetStringDebugLevelWithAllLevels", &TestDebugUtil::TestGetStringDebugLevelWithAllLevels, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestGetDebugLevelFromStringWithAllLevels", &TestDebugUtil::TestGetDebugLevelFromStringWithAllLevels, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestGetDebugLevelFromStringWithNonExistingLevel", &TestDebugUtil::TestGetDebugLevelFromStringWithNonExistingLevel, this ) );

	////////////// TestSetFile

	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestSetFileWithExistingFile", &TestDebugUtil::TestSetFileWithExistingFile, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestSetFileWithNotExistingFile", &TestDebugUtil::TestSetFileWithNotExistingFile, this ) );

	////////////// TestLog

	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithEmptyFilename", &TestDebugUtil::TestLogWithEmptyFilename, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithLineEqualsZero", &TestDebugUtil::TestLogWithLineEqualsZero, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithPreNoArgs", &TestDebugUtil::TestLogWithPreNoArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithPreArgEmptyStr", &TestDebugUtil::TestLogWithPreArgEmptyStr, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithPreExcessArgs", &TestDebugUtil::TestLogWithPreExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithPreCorrectArg", &TestDebugUtil::TestLogWithPreCorrectArg, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithPreFormatStrWithArg", &TestDebugUtil::TestLogWithPreFormatStrWithArg, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithGenFirstArgNotLevel", &TestDebugUtil::TestLogWithGenFirstArgNotLevel, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithGenArgEmptyStr", &TestDebugUtil::TestLogWithGenArgEmptyStr, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithGenArgNull", &TestDebugUtil::TestLogWithGenArgNull, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithGenFormatStrNoArg", &TestDebugUtil::TestLogWithGenFormatStrNoArg, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithGenExcessArgs", &TestDebugUtil::TestLogWithGenExcessArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithGenCorrectArg", &TestDebugUtil::TestLogWithGenCorrectArg, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithDebugLevelFatal", &TestDebugUtil::TestLogWithDebugLevelFatal, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithDebugLevelError", &TestDebugUtil::TestLogWithDebugLevelError, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithDebugLevelWarn", &TestDebugUtil::TestLogWithDebugLevelWarn, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithDebugLevelInfo", &TestDebugUtil::TestLogWithDebugLevelInfo, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogWithDebugLevelDebug", &TestDebugUtil::TestLogWithDebugLevelDebug, this ) );

	////////////// TestLogMore

	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithNoArgs", &TestDebugUtil::TestLogMoreWithNoArgs, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithArgNull", &TestDebugUtil::TestLogMoreWithArgNull, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithFormatStrNoArg", &TestDebugUtil::TestLogMoreWithFormatStrNoArg, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithExcessArgs", &TestDebugUtil::TestLogMoreWithExcessArgs, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithCorrectArgs", &TestDebugUtil::TestLogMoreWithCorrectArgs, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithPlainStr", &TestDebugUtil::TestLogMoreWithPlainStr, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithNotCallingLog", &TestDebugUtil::TestLogMoreWithNotCallingLog, this ) );
	testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "TestLogMoreWithCallingLogFirst", &TestDebugUtil::TestLogMoreWithCallingLogFirst, this ) );

    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "testLOGWithSwapFile", &TestDebugUtil::testLOGWithSwapFile, this ) );
    testSuite->addTest (
        new TestCaller <TestDebugUtil> (
            "testLogLocking", &TestDebugUtil::testLogLocking, this ) );
     
    return testSuite;
}


/** 
  * TestDebugUtil::createFilename
  *
  * Copy and paste from DebugUtil::createFilename to ensure that the files being
  * checked are correct!
  *
  * @param filename - The original file name to mangle.
  * @param fileNum  - The number to incorporate into the final name.
  *
  * @return std::string - The new filename.
  *
  */
std::string TestDebugUtil::createFilename( std::string filename, int fileNum )
{
    std::ostringstream stringstream;
    
    // Find where the extension in the filename starts
    // (ie look for the last '.').
    int dotPos = filename.rfind('.');

    if (dotPos != std::string::npos)
    {
        // Found a '.'. Take a copy of what's after it.
        std::string extension = filename.substr(dotPos + 1, filename.length());

        if (atoi(extension.c_str()) == 0 && extension != "0")
        {
            // Extension is a normal string, not a number.
            // (This is most likely the case for Windows.)

            // Add everything before the '.' to the filename.
            stringstream << filename.substr(0, dotPos);
    
            // Add the '.' and the number.
            stringstream << "." << fileNum;

            // Add the extension.
            stringstream << "." << extension;
        }
        else
        {
            // Extension is a number. (Most likely Solaris)
            // Just add the log number to the end.   
            stringstream << filename << "." << fileNum;
        }
    }
    else
    {
        // No extension at all. Add the log number to the end.
        stringstream << filename << "." << fileNum;
    }

    return stringstream.str();
}

/** 
  * TestDebugUtil::countLines
  *
  * Opens the specified file and counts the number of lines it contains.
  *
  * @param filename - The file to count the number of lines in.
  *
  * @return int - The number of lines in the file.
  */
int TestDebugUtil::countLines( std::string filename )
{
    // Open the file.
    FILE *fp = fopen( filename.c_str(), "r" );

    if ( fp == NULL )
    {
        return 0;
    }

    // Count the number of new lines
    char TmpStr[5];
    int Tmp=1, TmpCount=0;
    while ( Tmp )
    {
        Tmp = fread( TmpStr, 1, 1, fp ) ;
        if ( Tmp && ( TmpStr[0] == 0x0A ) )
        {
            TmpCount++;
        }
    }

    fclose( fp );

    return TmpCount;
}


void TestDebugUtil::RemoveFile( const std::string& filename )
{

    
#if defined ( SOLARIS )

	remove ( filename.c_str() );

#else

    // Set the log file to another file to remove the handle
    ++m_setFileCount;
    CU::DebugUtil::getInstance().setFile ( "removeMe" );

    std::string cmd ( "cmd /c\"RemoveFile.bat " );
    cmd += filename + "\"";

    system ( cmd.c_str() );

#endif    
}


void TestDebugUtil::RemoveFile( int fileHandle, const std::string& filename )
{
#if defined ( SOLARIS )
    close ( fileHandle );
#else
    _close ( fileHandle );
#endif

    RemoveFile ( filename );
}


void TestDebugUtil::testLogLocking()
{
    //
    // Test: This tests to see if the DebugUtil is locked properly.
    // Expected: No exceptions and a log file to be created.
    // Preconditions: No log file called "Useless.1.log".
    //

    // This test to see that the DebugUtil instantiates the it's static
    // critical section lock correctly to fix TD2689.  Because behaviour is
    // unpredictable if this lock is not instantiated correctly (as in it
    // causes the entire process to die due to memory access violation which
    // has different behaviours in different OSes), a separate program was
    // made called UselessLogger.  This is executed and checked that it did
    // not crash and that a log file of the correct size is created.

    // Return value of child.  Should be 0 for success.
    unsigned long childReturnVal = 1;

#ifdef WIN32

    std::string commandline;

    // Construct the WIN32 start process information
	int pid = 0;
    STARTUPINFO         sInfo;
    sInfo.cb              = sizeof(STARTUPINFO);
    sInfo.lpReserved      = NULL;
    sInfo.lpReserved2     = NULL;
    sInfo.cbReserved2     = 0;
    sInfo.lpDesktop       = NULL;
    sInfo.lpTitle         = NULL;
    sInfo.dwFlags         = 0;
    sInfo.dwX             = 0;
    sInfo.dwY             = 0;
    sInfo.dwFillAttribute = 0;
    sInfo.wShowWindow     = SW_SHOW;

    PROCESS_INFORMATION pi;

    // The lovely call to create process!
    CreateProcess( "..//..//..//..//..//test//testutils//win32_nd//UselessLogger.exe",
                        (char*)commandline.c_str(),
                        NULL,
                        NULL,
                        TRUE,
                        CREATE_NEW_CONSOLE,
                        NULL,
                        NULL,
                        &sInfo,
                        &pi);
    pid = pi.dwProcessId;               

    // Did the process get spawned?
    if( pid == 0 )
    {
        Assert( false );
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Get the exit code of the child.
    GetExitCodeProcess( pi.hProcess, &childReturnVal );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
#else
    char**  argv = new char*[1];
    argv[0] = NULL;

    pid_t pid = 0;
    switch (pid = vfork())
	{
        case -1:	// Error
            Assert( false );
            break;
		case 0:		// Child
            //	Change to the required user & group IDs.
            {
                struct rlimit limit;

                if (getrlimit(RLIMIT_NOFILE, &limit) != 0)
                {
                    printf("getrlimit error for RLIMIT_NOFILE");
                }

                // Close all open file descriptors for the child
                for (unsigned int i = 3; i <= limit.rlim_cur; i++)
                {
                    close(i);
                }
		    
                //	Run the executable.
				
			    if (execv("../../testutils/SOLARIS_nd/UselessLogger", argv) == -1)
			    {
                    _exit(1);
			    }
                _exit(0);
            }
			break;
		default:	// Parent
			break;
	}
    delete [] argv;
    // check the pid exists, if not make the return pid = 0
/*    if( kill(pid, 0) != 0)
    {
        Assert( false );
    }
*/
    // Get the return value of the child.
    int returnVal = -1;
    wait( &returnVal );

    childReturnVal = returnVal;

#endif //#ifdef WIN32

    // Now we need to check that the process ran correctly.
    Assert( 1 != childReturnVal );


    // Check that the log file is as we want it.
    int fileSize = -1;
    try
    {
        std::ifstream file( "Useless.1.log" );

        if( !file )
        {
            Assert( false );
        }
        else
        {
            while( !file.eof() )
            {
                char input;
                file.get(input);
                if( input == 0x0A )
                {
                    fileSize++;
                }
            }
        }
        file.close();

    }
    catch( ... )
    {
        Assert( false );
    }

    // Remove the file
#ifdef WIN32
    _unlink( "Useless.1.log" );
#else
    unlink( "Useless.1.log" );
#endif

    // Check that the fileSize is what we think it should be.  In this
    // case it is 4, which indicates that the file existed and it has the
    // right number of lines (4 lines).
    std::cout << "File size reported was: " << fileSize << "\n";
    Assert( 4 == fileSize );
}
