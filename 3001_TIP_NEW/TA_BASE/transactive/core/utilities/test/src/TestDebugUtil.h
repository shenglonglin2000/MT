/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestDebugUtil.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#ifndef CPP_UNIT_TESTDEBUGUTIL_H
#define CPP_UNIT_TESTDEBUGUTIL_H

#include <string>
#include <stdarg.h>
#include "TestCase.h"
#include "TestFramework.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/GenericLogType.h"

namespace CU = TA_Base_Core;

class TestDebugUtil : public TestCase
{
public:

	struct DebugTypeStruct
	{
		CU::DebugUtil::EDebugType type;
		const char* name;
	};
	

    TestSuite * suite();

    TestDebugUtil ( const std::string & name )
        : TestCase ( name ), m_setFileCount(0)
        {
        }

    ~TestDebugUtil()
        {
        }

	void TestGetInstance();
    
	void TestSetFileWithExistingFile();
	void TestSetFileWithNotExistingFile();

	void TestGetStringDebugLevelWithAllLevels();
    void TestGetDebugLevelFromStringWithAllLevels();
	void TestGetDebugLevelFromStringWithNonExistingLevel();

	void TestLogWithEmptyFilename();
	void TestLogWithLineEqualsZero();
	
	void TestLogWithPreNoArgs();
	void TestLogWithPreArgEmptyStr();
	void TestLogWithPreExcessArgs();
	void TestLogWithPreFormatStrWithArg();
	void TestLogWithPreCorrectArg();
	void TestLogWithGenFirstArgNotLevel();
	void TestLogWithGenArgEmptyStr();
	void TestLogWithGenArgNull();
	void TestLogWithGenFormatStrNoArg();
	void TestLogWithGenExcessArgs();
	void TestLogWithGenCorrectArg();
	
	void TestLogWithDebugLevelFatal();
	void TestLogWithDebugLevelError();
	void TestLogWithDebugLevelWarn();
	void TestLogWithDebugLevelInfo();
	void TestLogWithDebugLevelDebug();

	void TestLogMoreWithNoArgs();
	void TestLogMoreWithArgNull();
	void TestLogMoreWithFormatStrNoArg();
	void TestLogMoreWithExcessArgs();
	void TestLogMoreWithCorrectArgs();
	void TestLogMoreWithPlainStr();
	void TestLogMoreWithNotCallingLog();
	void TestLogMoreWithCallingLogFirst();

    void testLOGWithSwapFile();

    void testLogLocking();
	
    virtual void setUp( const std::string & INFile, const std::string & OUTFile );
    virtual void tearDown( const std::string & OUTFile );

    virtual void setUpSuite ( const std::string & INFile );
    virtual void tearDownSuite();

private:

	int m_setFileCount;

    std::string createFilename( std::string filename, int count );
    int countLines( std::string filename );

    void RemoveFile( const std::string& filename );

    void RemoveFile( int fileHandle, const std::string& filename );
};


#endif // CPP_UNIT_TESTDEBUGUTIL_H

