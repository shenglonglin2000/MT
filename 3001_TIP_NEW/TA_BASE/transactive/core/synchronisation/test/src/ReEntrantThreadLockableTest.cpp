/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ReEntrantThreadLockableTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Implementation of the NonReEntrantReEntrantThreadLockableTest test cases.
  *
  */

#include "ReEntrantThreadLockableTest.h"

const int ReEntrantThreadLockableTest::SLEEP_DELAY_MS = 1000;
const int ReEntrantThreadLockableTest::TOLERANCE = 5;
/**
 * Constructor
 */
ReEntrantThreadLockableTest::ReEntrantThreadLockableTest ( const std::string & name )
: TestCase( name )
{
}

/**
 * Destructor
 */
ReEntrantThreadLockableTest:: ~ReEntrantThreadLockableTest()
{
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *ReEntrantThreadLockableTest::suite()
{
    TestSuite * testSuite = new TestSuite( "ReEntrantThreadLockableTest" );

    testSuite->addTest( new TestCaller< ReEntrantThreadLockableTest >( "testAcquire1", &ReEntrantThreadLockableTest::testAcquire1, this ) );
    testSuite->addTest( new TestCaller< ReEntrantThreadLockableTest >( "testAcquire2", &ReEntrantThreadLockableTest::testAcquire2, this ) );
    testSuite->addTest( new TestCaller< ReEntrantThreadLockableTest >( "testRelease1", &ReEntrantThreadLockableTest::testRelease1, this ) );
    testSuite->addTest( new TestCaller< ReEntrantThreadLockableTest >( "testRelease2", &ReEntrantThreadLockableTest::testRelease2, this ) );

    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void ReEntrantThreadLockableTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void ReEntrantThreadLockableTest::tearDown( const std::string & OUTFile )
{
}


void ReEntrantThreadLockableTest::testAcquire1(void)
{
    //
    // Test: This tests the acquire(void) method in ReEntrantThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a ReEntrantThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::ReEntrantThreadLockable lock;

    try
    {
        lock.acquire();
        lock.release();
        Assert( true );
    }
    catch( ... )
    {
        Assert( false );
    }
}


void ReEntrantThreadLockableTest::testAcquire2(void)
{
    //
    // Test: This tests the acquire(void) method in ReEntrantThreadLockable
    // Expected: TA_Base_Core::AssertException
    // Preconditions: NONE
    //

    // The strategy to test this is to instantiate a ReEntrantThreadLockable
    // object and attempt to acquire the lock on it twice in succession.
    // Success is where there is no exception
    
    TA_Base_Core::ReEntrantThreadLockable lock;

    try
    {
        lock.acquire();
        lock.acquire();
        Assert( true );
    }
    catch( ... )
    {
        Assert( false );
    }
}

void ReEntrantThreadLockableTest::testRelease1(void)
{
    //
    // Test: This tests the release(void) method in ReEntrantThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a ReEntrantThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::ReEntrantThreadLockable lock;

    try
    {
        lock.acquire();
        lock.release();
        Assert( true );
    }
    catch( ... )
    {
        Assert( false );
    }
}


void ReEntrantThreadLockableTest::testRelease2(void)
{
    //
    // Test: This tests the release(void) method in ReEntrantThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock twise a ReEntrantThreadLockable instance.  Success is if a
    // exception is thrown.
    
    TA_Base_Core::ReEntrantThreadLockable lock;

    try
    {
        lock.acquire();
        lock.release();
        lock.release();
        Assert( false );
    }
    catch( ... )
    {
        Assert( true );
    }
}

