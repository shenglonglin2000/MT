/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/TestDebugUtilLogMacros.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#ifndef CPP_UNIT_TESTDEBUGUTILLOGMACROS_H
#define CPP_UNIT_TESTDEBUGUTILLOGMACROS_H

#include <string>
#include <stdarg.h>
#include "TestCase.h"
#include "TestFramework.h"
#include "core/utilities/src/DebugUtil.h"

class TestClass
{
public:
    TestClass(int index, int dep, std::string& any)
        : m_index(index), m_dep(dep), m_any(any) {}
    virtual ~TestClass() {}

    int m_index;
    int m_dep;
    std::string m_any;
};

class TestDebugUtilLogMacros : public TestCase
{
public:

    TestSuite * suite();

    TestDebugUtilLogMacros ( const std::string & name )
        : TestCase ( name )
        {
        }

    ~TestDebugUtilLogMacros()
        {
        }
	
	void testLOGWithGenericLog();
	void testLOGWithPreformattedLog();
	void testLOGWithMultipleLOGs();
	void testLOGWithMultipleLOGsInDiffFunctions();
	void testLOGWithMultipleThreads();

	void testLOGMOREWithMultipleLOGMOREs();
	void testLOGMOREWithMultipleThreads();

	void testLOGAndLOGMOREWithMultipleThreads();

    virtual void setUp( const std::string & INFile, const std::string & OUTFile );
    virtual void tearDown( const std::string & OUTFile );

    virtual void setUpSuite ( const std::string & INFile );
    virtual void tearDownSuite();

private:

    void callingLOGWithGenericLog();
	void callingLOGWithPreformattedLog();
};


#endif // CPP_UNIT_TESTDEBUGUTILLOGMACROS_H

