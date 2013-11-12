/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Ftp Test/src/FTPClientTest.h $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This class exercises the FTPClient class in TA_FTP.
  *
  */

#if !defined(_FTPCLIENTTEST_H_)
#define _FTPCLIENTTEST_H_

#include "core/ftp/src/FTPClient.h"
#include "core/utilities/src/DebugUtil.h"

#include "cots/CppUnit/src/TestFramework.h"


class FTPClientTest : public TestCase
{
public:
    FTPClientTest( std::string serverAddress, unsigned int serverPort, std::string userName, std::string userPassword, std::string fileName, std::string directory )
        : m_serverAddress(serverAddress), m_serverPort(serverPort), m_userName(userName), m_userPassword(userPassword), m_fileName(fileName), m_directory(directory), TestCase("FTPClientTest")
    {
    }

    ~FTPClientTest()
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
    void testConnectToValidServer();
    void testConnectToInvalidServer();
    void testValidLogin();
    void testInvalidLogin();
    void testChangeToValidDirectory();
    void testChangeToInvalidDirectory();
    void testRetreiveValidFile();
    void testRetreiveInvalidFile();
    void testSetFileType();

private:
    std::string m_serverAddress;
    unsigned int m_serverPort;
    std::string m_userName;
    std::string m_userPassword;
    std::string m_fileName;
    std::string m_directory;

};

#endif
