/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestPreformattedLogType.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#ifndef CPP_UNIT_TESTPREFORMATTEDLOGTYPE_H
#define CPP_UNIT_TESTPREFORMATTEDLOGTYPE_H

#include <string>
#include <stdarg.h>
#include "TestCase.h"
#include "TestFramework.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/PreformattedLogType.h"

namespace CU = TA_Base_Core;

class TestPreformattedLogType : public TestCase
{
public:

    TestSuite * suite();

    TestPreformattedLogType ( const std::string & name )
        : TestCase ( name )
        {
        }

    ~TestPreformattedLogType()
        {
        }

	void TestConstructorWithEmptyFormatStr();
    void TestConstructorWithCorrectArgs();
	
    void TestGetCompleteLogMessageWithEmptyFilename();
	void TestGetCompleteLogMessageWithLineEqualsZero();
	void TestGetCompleteLogMessageWithNoArgs();
	void TestGetCompleteLogMessageWithArgEmptyString();
	void TestGetCompleteLogMessageWithArgNull();
	void TestGetCompleteLogMessageWithExcessArgs();
	void TestGetCompleteLogMessageWithLargeString();
	void TestGetCompleteLogMessageWithCorrectArgs();

	// Inherited methods
    void TestConstructMessageWithFilenameEmpty();
	void TestConstructMessageWithFilenameNull();
	void TestConstructMessageWithLineEqualsZero();
	void TestConstructMessageWithLineLessThanZero();
	void TestConstructMessageWithEmptyLevel();
	void TestConstructMessageWithEmptyMessage();
	void TestConstructMessageWithCorrectArgs();

    void TestGetSimpleMessageWithNoArgs();
	void TestGetSimpleMessageWithFirstArgNotString();
	void TestGetSimpleMessageWithExcessArgs();
	void TestGetSimpleMessageWithCorrectArgs();
    

    virtual void setUp( const std::string & INFile, const std::string & OUTFile );
    virtual void tearDown( const std::string & OUTFile );

    virtual void setUpSuite ( const std::string & INFile );
    virtual void tearDownSuite();

private:

	std::string VaListGetCompleteMsg ( CU::PreformattedLogType& preformattedLog, const std::string& file, int line, ... );

	std::string VaListGetSimpleMsg ( CU::PreformattedLogType& preformattedLog, int pholder, ... );

};


#endif // CPP_UNIT_TESTPREFORMATTEDLOGTYPE_H

