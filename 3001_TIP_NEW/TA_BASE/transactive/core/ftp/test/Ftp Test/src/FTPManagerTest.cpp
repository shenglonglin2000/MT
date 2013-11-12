/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Ftp Test/src/FTPManagerTest.cpp $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This class exercises the FTPManager class in TA_FTP.
  *
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#pragma warning(disable:4101)
#endif // defined (_MSC_VER)

#include "FTPManagerTest.h"

///////////////////////////////////////////////////////
// Test Methods
///////////////////////////////////////////////////////

/**
  * Test: This tests to see if we can retreive a valid file.
  *
  * Expected: No problems.
  *
  * Preconditions: None.
  */
void FTPManagerTest::testRetreiveValidFile()
{
    std::cout << "\ttestRetreiveValidFile: ";

    try
    {
        std::vector<unsigned char> fileBuffer;

        // Retreive the file
        TA_Base_Core::FTPManager::getInstance().retrieveFile( this->m_serverAddress, this->m_userName, this->m_userPassword, this->m_fullPath, fileBuffer );

        Assert( fileBuffer.size() > 0 );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - Exception while retreiving file!" << std::endl;
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
}

/**
  * Test: This tests to see if we can retreive an invalid file.
  *
  * Expected: An exception to be thrown.
  *
  * Preconditions: None.
  */
void FTPManagerTest::testRetreiveInvalidFile()
{
    std::cout << "\ttestRetreiveInvalidFile: ";

    try
    {
        std::vector<unsigned char> fileBuffer;

        // Retreive the file
        TA_Base_Core::FTPManager::getInstance().retrieveFile( this->m_serverAddress, this->m_userName, this->m_userPassword, "im an invalid filename", fileBuffer );

        std::cout << "[FAILED] - No exception while retreiving invalid file!" << std::endl;
        Assert( false );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
    }

    std::cout << "[OK]" << std::endl;
}

///////////////////////////////////////////////////////
// Test Framework Methods
///////////////////////////////////////////////////////

void FTPManagerTest::setUpSuite( const std::string & inFile )
{
    std::cout << "Running FTPManager Test Suite..." << std::endl;

    // Set debug file so we don't get it to standard out.
    TA_Base_Core::DebugUtil::getInstance().setLevel( TA_Base_Core::DebugUtil::DebugDebug );
    TA_Base_Core::DebugUtil::getInstance().setFile( "./output/FTPManagerTest.txt" );
}

void FTPManagerTest::tearDownSuite()
{
}

void FTPManagerTest::setUp( const std::string & INFile, const std::string & OUTFile )
{
}

void FTPManagerTest::tearDown( const std::string & OUTFile )
{
}

TestSuite * FTPManagerTest::suite()
{
    TestSuite * testSuite = new TestSuite( "FTPManagerTest" );

    testSuite->addTest( new TestCaller< FTPManagerTest >( "testRetreiveValidFile", &FTPManagerTest::testRetreiveValidFile, this ) );
    testSuite->addTest( new TestCaller< FTPManagerTest >( "testRetreiveInvalidFile", &FTPManagerTest::testRetreiveInvalidFile, this ) );

    return testSuite;
}
