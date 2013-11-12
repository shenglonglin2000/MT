/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Ftp Test/src/FTPManagerTest.h $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This class exercises the FTPManager class in TA_FTP.
  *
  */

#if !defined(_FTPMANAGERTEST_H_)
#define _FTPMANAGERTEST_H_

#include "core/ftp/src/FTPManager.h"
#include "core/utilities/src/DebugUtil.h"

#include "cots/CppUnit/src/TestFramework.h"


class FTPManagerTest : public TestCase
{
public:
    FTPManagerTest( std::string serverAddress, unsigned int serverPort, std::string userName, std::string userPassword, std::string fullPath )
        : m_serverAddress(serverAddress), m_serverPort(serverPort), m_userName(userName), m_userPassword(userPassword), m_fullPath(fullPath), TestCase("FTPManagerTest")
    {
    }

    ~FTPManagerTest()
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
    void testRetreiveValidFile();
    void testRetreiveInvalidFile();

private:
    std::string m_serverAddress;
    unsigned int m_serverPort;
    std::string m_userName;
    std::string m_userPassword;
    std::string m_fullPath;

};

#endif
