/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestLogger.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#ifndef CPP_UNIT_TESTLOGGER_H
#define CPP_UNIT_TESTLOGGER_H

#include <string>
#include <stdarg.h>
#include "TestCase.h"
#include "TestFramework.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/Logger.h"

namespace CU = TA_Base_Core;

class TestLogger : public TestCase
{
public:

    TestSuite * suite();

    TestLogger ( const std::string & name )
        : TestCase ( name )
        {
        }

    ~TestLogger()
        {
        }

	void testConstructor();
    
    void testAddToCacheFullLogWithEmptyFilename();
	void testAddToCacheFullLogWithLineEqualsZero();
	void testAddToCacheFullLogWithGenLogNoArgs();
	void testAddToCacheFullLogWithPreLogNoArgs();
	void testAddToCacheFullLogWithFirstArgNotStr();
	void testAddToCacheFullLogWithArgEmptyStr();
	void testAddToCacheFullLogWithArgIsNull();
	void testAddToCacheFullLogWithArgWrongType();
	void testAddToCacheFullLogWithExcessArgs();
	void testAddToCacheFullLogWithFormatStrTooLarge();
	void testAddToCacheFullLogWithCorrectArgs();
	
	void testAddToCacheSimpleLogWithEmptyFilename();
	void testAddToCacheSimpleLogWithLineEqualsZero();
	void testAddToCacheSimpleLogWithNoArgs();
	void testAddToCacheSimpleLogWithFirstArgNotStr();
	void testAddToCacheSimpleLogWithArgEmptyStr();
	void testAddToCacheSimpleLogWithArgIsNull();
	void testAddToCacheSimpleLogWithArgWrongType();
	void testAddToCacheSimpleLogWithExcessArgs();
	void testAddToCacheSimpleLogWithFormatStrTooLarge();
	void testAddToCacheSimpleLogWithCorrectArgs();

	void testAddLogTypeWithPreformattedLogType();
	void testAddLogTypeWithGenericLogType();

	void testGetLevelWithoutLogTypesLoaded();
	void testGetLevelWithLogTypesLoaded();

	void testLogCacheWithLogTypesNotLoaded();
	void testLogCacheWithCout();
	void testLogCacheWithBadFile();
	void testLogCacheWithGoodFile();

	void testLogFullLogWithEmptyFilename();
	void testLogFullLogWithLineEqualsZero();
	void testLogFullLogWithGenLogNoArgs();
	void testLogFullLogWithPreLogNoArgs();
	void testLogFullLogWithFirstArgNotStr();
	void testLogFullLogWithArgEmptyStr();
	void testLogFullLogWithArgIsNull();
	void testLogFullLogWithArgWrongType();
	void testLogFullLogWithExcessArgs();
	void testLogFullLogWithFormatStrTooLarge();
	void testLogFullLogWithCorrectArgs();
	
	void testLogSimpleLogWithEmptyFilename();
	void testLogSimpleLogWithLineEqualsZero();
	void testLogSimpleLogWithNoArgs();
	void testLogSimpleLogWithFirstArgNotStr();
	void testLogSimpleLogWithArgEmptyStr();
	void testLogSimpleLogWithArgIsNull();
	void testLogSimpleLogWithArgWrongType();
	void testLogSimpleLogWithExcessArgs();
	void testLogSimpleLogWithFormatStrTooLarge();
	void testLogSimpleLogWithCorrectArgs();
	
	void testLogWithCout();
	void testLogWithBadFile();
	void testLogWithGoodFile();

    virtual void setUp( const std::string & INFile, const std::string & OUTFile );
    virtual void tearDown( const std::string & OUTFile );

    virtual void setUpSuite ( const std::string & INFile );
    virtual void tearDownSuite();

private:

	void vaListAddToCache(CU::DebugUtil::EDebugType type, CU::Logger& logger, const std::string& file, int line, bool simpleLog, ...);

	void setUpTestLevel(CU::Logger& logger);

	void setUpTestLogCache(CU::Logger& logger, int numMsgs, ...);

	int vaListLog(CU::DebugUtil::EDebugType type, CU::Logger& logger, const std::string& file, int line, std::ostream& outfile, bool simpleLog, ...);

    void RemoveFile( const std::string& filename );
    
    void RemoveFile( int fileHandle, const std::string& filename );
};


#endif // CPP_UNIT_TESTLOGGER_H

