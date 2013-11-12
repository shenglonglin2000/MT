/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Ftp Test/src/FTPReplyTest.cpp $
  * @author:  Bradley Cleaver
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This class exercises the FTPReply class in TA_FTP.
  *
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#pragma warning(disable:4101)
#endif // defined (_MSC_VER)

#include "FTPReplyTest.h"

///////////////////////////////////////////////////////
// Test Methods
///////////////////////////////////////////////////////

/**
  * Test: This tests to see if the constructor detects erroneous
  *       data.
  *
  * Expected: Both attempts throw exceptions.
  *
  * Preconditions: None.
  */
void FTPReplyTest::testConstructor()
{
    std::cout << "\ttestConstructor: ";

    try
    {
        TA_Base_Core::FTPReply reply1( NULL );

        std::cout << "[FAILED] - Reply1 construction succeeded!" << std::endl;
        Assert( false );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
    }

    try
    {
        TA_Base_Core::FTPReply reply2( "no crlf" );

        std::cout << "[FAILED] - Reply2 construction succeeded!" << std::endl;
        Assert( false );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
    }

    std::cout << "[OK]" << std::endl;
}

/**
  * Test: This tests to see if multiline messages are successfully detected.
  *
  * Expected: All calls to isLastReply should return 'false'.
  *
  * Preconditions: None.
  */
void FTPReplyTest::testIsLastReply()
{
    std::cout << "\ttestIsLastReply: ";

    try
    {
        // A message with no reply code should be multiline.
        TA_Base_Core::FTPReply reply1( "no reply code\r\n" );
        if ( reply1.isLastReply() )
        {
            std::cout << "[FAILED] - Reply1 not multiline!" << std::endl;
            Assert( false );
        }

        // A message with a '-' next to reply code should be multiline.
        TA_Base_Core::FTPReply reply2( "222- message\r\n" );
        if ( reply2.isLastReply() )
        {
            std::cout << "[FAILED] - Reply2 not multiline!" << std::endl;
            Assert( false );
        }

        // A messge with reply code starting with 1 should be multiline.
        TA_Base_Core::FTPReply reply3( "111 message\r\n" );
        if ( reply3.isLastReply() )
        {
            std::cout << "[FAILED] - Reply3 not multiline!" << std::endl;
            Assert( false );
        }

        // All these replies should NOT be multiline.
        TA_Base_Core::FTPReply reply4( "222 message\r\n" );
        if ( !reply4.isLastReply() )
        {
            std::cout << "[FAILED] - Reply4 is multiline!" << std::endl;
            Assert( false );
        }

        TA_Base_Core::FTPReply reply5( "333 message\r\n" );
        if ( !reply5.isLastReply() )
        {
            std::cout << "[FAILED] - Reply5 is multiline!" << std::endl;
            Assert( false );
        }
        
        TA_Base_Core::FTPReply reply6( "444 message\r\n" );
        if ( !reply6.isLastReply() )
        {
            std::cout << "[FAILED] - Reply6 is multiline!" << std::endl;
            Assert( false );
        }
        
        TA_Base_Core::FTPReply reply7( "555 message\r\n" );
        if ( !reply7.isLastReply() )
        {
            std::cout << "[FAILED] - Reply7 is multiline!" << std::endl;
            Assert( false );
        }
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - An exception occurred (" << tex.what() << ")!" << std::endl;
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
}

/**
  * Test: This tests to see the message types are successfully determined.
  *
  * Expected: No problems when valid codes, exceptions when not.
  *
  * Preconditions: None.
  */
void FTPReplyTest::testGetType()
{
    std::cout << "\ttestGetType: ";

    try
    {
        // Test for MultiLine_Part
        TA_Base_Core::FTPReply reply1( "message\r\n" );
        if ( reply1.getType() != TA_Base_Core::FTPReply::MultiLine_Part )
        {
            std::cout << "[FAILED] - Reply1 not MultiLine_Part!" << std::endl;
            Assert( false );
        }

        TA_Base_Core::FTPReply reply2( "123- message\r\n" );
        if ( reply2.getType() != TA_Base_Core::FTPReply::MultiLine_Part )
        {
            std::cout << "[FAILED] - Reply2 not MultiLine_Part!" << std::endl;
            Assert( false );
        }

        // Test for Positive_Preliminary
        TA_Base_Core::FTPReply reply3( "111 message\r\n" );
        if ( reply3.getType() != TA_Base_Core::FTPReply::Positive_Preliminary )
        {
            std::cout << "[FAILED] - Reply3 not Positive_Preliminary!" << std::endl;
            Assert( false );
        }

        // Test for Positive_Completion
        TA_Base_Core::FTPReply reply4( "222 message\r\n" );
        if ( reply4.getType() != TA_Base_Core::FTPReply::Positive_Completion )
        {
            std::cout << "[FAILED] - Reply4 not Positive_Completion!" << std::endl;
            Assert( false );
        }

        // Test for Positive_Intermediate
        TA_Base_Core::FTPReply reply5( "333 message\r\n" );
        if ( reply5.getType() != TA_Base_Core::FTPReply::Positive_Intermediate )
        {
            std::cout << "[FAILED] - Reply5 not Positive_Intermediate!" << std::endl;
            Assert( false );
        }

        // Test for Negative_Transient
        TA_Base_Core::FTPReply reply6( "444 message\r\n" );
        if ( reply6.getType() != TA_Base_Core::FTPReply::Negative_Transient )
        {
            std::cout << "[FAILED] - Reply6 not Negative_Transient!" << std::endl;
            Assert( false );
        }

        // Test for Negative_Permanent
        TA_Base_Core::FTPReply reply7( "555 message\r\n" );
        if ( reply7.getType() != TA_Base_Core::FTPReply::Negative_Permanent )
        {
            std::cout << "[FAILED] - Reply7 not Negative_Permanent!" << std::endl;
            Assert( false );
        }
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - An exception occurred (" << tex.what() << ")!" << std::endl;
        Assert( false );
    }

    try
    {
        // Test for invalid type.
        TA_Base_Core::FTPReply reply8( "666 message\r\n" );

        reply8.getType();

        std::cout << "[FAILED] - Reply8 not invalid!" << std::endl;
        Assert( false );
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
    }

    std::cout << "[OK]" << std::endl;
}

/**
  * Test: This tests to see if a valid log message is generated.
  *
  * Expected: No problems.
  *
  * Preconditions: None.
  */
void FTPReplyTest::testLogReply()
{
    std::cout << "\ttestLogReply: ";

    try
    {
        // Messages without a reply code should start with a space.
        TA_Base_Core::FTPReply reply1( "message\r\n" );
        std::string log1 = reply1.logReply();
        if ( log1[0] != ' ' )
        {
            std::cout << "[FAILED] - Reply1 log message invalid!" << std::endl;
            Assert( false );
        }

        // Messages with a reply code should start with the first number.
        TA_Base_Core::FTPReply reply2( "123 message\r\n" );
        std::string log2 = reply2.logReply();
        if ( log2[0] != '1' )
        {
            std::cout << "[FAILED] - Reply2 log message invalid!" << std::endl;
            Assert( false );
        }
    }
    catch ( TA_Base_Core::TransactiveException &tex )
    {
        std::cout << "[FAILED] - An exception occurred (" << tex.what() << ")!" << std::endl;
        Assert( false );
    }

    std::cout << "[OK]" << std::endl;
}

///////////////////////////////////////////////////////
// Test Framework Methods
///////////////////////////////////////////////////////

void FTPReplyTest::setUpSuite( const std::string & inFile )
{
    std::cout << "Running FTPReply Test Suite..." << std::endl;

    // Set debug file so we don't get it to standard out.
    TA_Base_Core::DebugUtil::getInstance().setLevel( TA_Base_Core::DebugUtil::DebugDebug );
    TA_Base_Core::DebugUtil::getInstance().setFile( "./output/FTPReplyTest.txt" );
}

void FTPReplyTest::tearDownSuite()
{
}

void FTPReplyTest::setUp( const std::string & INFile, const std::string & OUTFile )
{
}

void FTPReplyTest::tearDown( const std::string & OUTFile )
{
}

TestSuite * FTPReplyTest::suite()
{
    TestSuite * testSuite = new TestSuite( "FTPReplyTest" );

    testSuite->addTest( new TestCaller< FTPReplyTest >( "testConstructor", &FTPReplyTest::testConstructor, this ) );
    testSuite->addTest( new TestCaller< FTPReplyTest >( "testIsLastReply", &FTPReplyTest::testIsLastReply, this ) );
    testSuite->addTest( new TestCaller< FTPReplyTest >( "testGetType", &FTPReplyTest::testGetType, this ) );
    testSuite->addTest( new TestCaller< FTPReplyTest >( "testLogReply", &FTPReplyTest::testLogReply, this ) );

    return testSuite;
}
