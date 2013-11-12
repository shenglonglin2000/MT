/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Ftp Test/src/FTPReplyTest.h $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This class exercises the FTPReply class in TA_FTP.
  *
  */

#if !defined(_FTPREPLYTEST_H_)
#define _FTPREPLYTEST_H_

#include "core/ftp/src/FTPReply.h"
#include "core/utilities/src/DebugUtil.h"

#include "cots/CppUnit/src/TestFramework.h"


class FTPReplyTest : public TestCase
{
public:
    FTPReplyTest() : TestCase("FTPReplyTest")
    {
    }

    ~FTPReplyTest()
    {
    }

    /**
     * suite
     * 
     * This adds all the test methods to the suite of tests and returns it.
     *
     * @return TestSuite* A collection of all tests that can be run.
     */
    TestSuite *suite();

    /**
     * setUp
     * 
     * Initialises variables before each method is run.
     */
    void setUp( const std::string & INFile , const std::string & OUTFile );

    /**
     * tearDown
     * 
     * Destroys variables after each method is run.
     *
     */
    void tearDown( const std::string & OUTFile );

    /**
     * setUpSuite
     *
     * Initialises variables before test suite is run.
     */
    void setUpSuite( const std::string & inFile );

    /**
     * tearDownSuite
     *
     * Destroys variables after test suite is run.
     */
    void tearDownSuite();

protected:
    void testConstructor();
    void testIsLastReply();
    void testGetType();
    void testLogReply();

};

#endif