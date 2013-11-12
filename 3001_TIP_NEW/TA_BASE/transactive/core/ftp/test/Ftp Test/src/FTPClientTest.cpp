/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Ftp Test/src/FTPClientTest.cpp $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This class exercises the FTPClient class in TA_FTP.
  *
  */
#if defined(_MSC_VER)
#pragma warning(disable:4786)
#pragma warning(disable:4101)
#endif // defined (_MSC_VER)

#include "FTPClientTest.h"

///////////////////////////////////////////////////////
// Test Methods
///////////////////////////////////////////////////////

/**
  * Test: This tests to see if we can connect to a valid server.
  *
  * Expected: No problems.
  *
  * Preconditions: None.
  */
void FTPClientTest::testConnectToValidServer()
{
    std::cout << "\ttestConnectToValidServer: ";

    TA_Base_Core::FTPClient client;

    // If we successfully connect there should be no exceptions.
    try
    {
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

/**
  * Test: This tests to see if we can connect to an invalid server.
  *
  * Expected: An exception to be thrown by FTPClient::connectToServer.
  *
  * Preconditions: None.
  */
void FTPClientTest::testConnectToInvalidServer()
{
    std::cout << "\ttestConnectToInvalidServer: ";

    TA_Base_Core::FTPClient client;

    // If we successfully connect there should be no exceptions.
    try
    {
        client.connectToServer( "im an invalid host", this->m_serverPort );

        std::cout << "[FAILED] - Connected to an invalid server!" << std::endl;
        client.closeConnection();
        Assert( false );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        
    }

    std::cout << "[OK]" << std::endl;
}

/**
  * Test: This tests to see if we can login with valid details.
  *
  * Expected: No Problems.
  *
  * Preconditions: None.
  */
void FTPClientTest::testValidLogin()
{
    std::cout << "\ttestValidLogin: ";

    TA_Base_Core::FTPClient client;

    try
    {
        // Connect to the server
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    try
    {
        // Login
        client.userLogin( this->m_userName, this->m_userPassword );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't login to server!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

/**
  * Test: This tests to see if we can login with invalid details.
  *
  * Expected: An exception to be thrown.
  *
  * Preconditions: None.
  */
void FTPClientTest::testInvalidLogin()
{
    std::cout << "\ttestInvalidLogin: ";

    TA_Base_Core::FTPClient client;

    try
    {
        // Connect to the server
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    try
    {
        // Login
        client.userLogin( "abcdefg", "gfedcba" );

        std::cout << "[FAILED] - Logged into server with invalid u/p!" << std::endl;
        client.closeConnection();
        Assert( false );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

/**
  * Test: This tests to see if we can change directories.
  *
  * Expected: No Problems.
  *
  * Preconditions: None.
  */
void FTPClientTest::testChangeToValidDirectory()
{
    std::cout << "\ttestChangeToValidDirectory: ";

    TA_Base_Core::FTPClient client;

    try
    {
        // Connect to the server
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    try
    {
        // Login
        client.userLogin( this->m_userName, this->m_userPassword );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't login to server!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    try
    {
        // Change directory
        // TODO: This shouldn't be hardcoded!!
        client.changeDirectory( this->m_directory );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't change directory!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

/**
  * Test: This tests to see if we can change to an invalid directory.
  *
  * Expected: An exception to be thrown.
  *
  * Preconditions: None.
  */
void FTPClientTest::testChangeToInvalidDirectory()
{
    std::cout << "\ttestChangeToInvalidDirectory: ";

    TA_Base_Core::FTPClient client;

    try
    {
        // Connect to the server
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    try
    {
        // Login
        client.userLogin( this->m_userName, this->m_userPassword );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't login to server!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    try
    {
        // Change directory
        client.changeDirectory( "/asdfhksdu" );

        std::cout << "[FAILED] - Changed to an invalid directory!" << std::endl;
        client.closeConnection();
        Assert( false );

    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

/**
  * Test: This tests to see if we can download a valid file.
  *
  * Expected: No Problems.
  *
  * Preconditions: None.
  */
void FTPClientTest::testRetreiveValidFile()
{
    std::cout << "\ttestRetreiveValidFile: ";

    TA_Base_Core::FTPClient client;

    try
    {
        // Connect to the server
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    try
    {
        // Login
        client.userLogin( this->m_userName, this->m_userPassword );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't login to server!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    try
    {
        std::vector<unsigned char> file;

        // Download the file.
        client.retrieveFile( this->m_fileName, file );

        Assert( file.size() > 0 );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't retreive file!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

/**
  * Test: This tests to see if we can download an invalid file.
  *
  * Expected: An exception to be thrown.
  *
  * Preconditions: None.
  */
void FTPClientTest::testRetreiveInvalidFile()
{
    std::cout << "\ttestRetreiveInvalidFile: ";

    TA_Base_Core::FTPClient client;

    try
    {
        // Connect to the server
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    try
    {
        // Login
        client.userLogin( this->m_userName, this->m_userPassword );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't login to server!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    try
    {
        std::vector<unsigned char> file;

        // Download the file.
        client.retrieveFile( "im an invalid filename!", file );

        std::cout << "[FAILED] - Retreived an invalid file!" << std::endl;
        client.closeConnection();
        Assert( false );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

/**
  * Test: This tests to see if we can set the file type.
  *
  * Expected: No problems.
  *
  * Preconditions: None.
  */
void FTPClientTest::testSetFileType()
{
    std::cout << "\ttestSetFileType: ";

    TA_Base_Core::FTPClient client;

    try
    {
        // Connect to the server
        client.connectToServer( this->m_serverAddress, this->m_serverPort );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't connect to server!" << std::endl;
        Assert( false );
    }

    try
    {
        // Login
        client.userLogin( this->m_userName, this->m_userPassword );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't login to server!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    try
    {
        // Change file type
        client.setFileType( TA_Base_Core::FTPClient::Ascii );
        client.setFileType( TA_Base_Core::FTPClient::Image );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Couldn't set file type!" << std::endl;
        client.closeConnection();
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
    client.closeConnection();
}

///////////////////////////////////////////////////////
// Test Framework Methods
///////////////////////////////////////////////////////

void FTPClientTest::setUpSuite( const std::string & inFile )
{
    std::cout << "Running FTPClient Test Suite..." << std::endl;

    // Set debug file so we don't get it to standard out.
    TA_Base_Core::DebugUtil::getInstance().setLevel( TA_Base_Core::DebugUtil::DebugDebug );
    TA_Base_Core::DebugUtil::getInstance().setFile( "./output/FTPClientTest.txt" );
}

void FTPClientTest::tearDownSuite()
{
}

void FTPClientTest::setUp( const std::string & INFile, const std::string & OUTFile )
{
}

void FTPClientTest::tearDown( const std::string & OUTFile )
{
}

TestSuite * FTPClientTest::suite()
{
    TestSuite * testSuite = new TestSuite( "FTPClientTest" );

    testSuite->addTest( new TestCaller< FTPClientTest >( "testConnectToValidServer", &FTPClientTest::testConnectToValidServer, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testConnectToInvalidServer", &FTPClientTest::testConnectToInvalidServer, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testValidLogin", &FTPClientTest::testValidLogin, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testInvalidLogin", &FTPClientTest::testInvalidLogin, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testChangeToValidDirectory", &FTPClientTest::testChangeToValidDirectory, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testChangeToInvalidDirectory", &FTPClientTest::testChangeToInvalidDirectory, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testRetreiveValidFile", &FTPClientTest::testRetreiveValidFile, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testRetreiveInvalidFile", &FTPClientTest::testRetreiveInvalidFile, this ) );
    testSuite->addTest( new TestCaller< FTPClientTest >( "testSetFileType", &FTPClientTest::testSetFileType, this ) );

    return testSuite;
}
