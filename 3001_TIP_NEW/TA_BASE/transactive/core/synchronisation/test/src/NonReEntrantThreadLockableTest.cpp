/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/NonReEntrantThreadLockableTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Implementation of the NonReEntrantNonReEntrantThreadLockableTest test cases.
  *
  */

#include "NonReEntrantThreadLockableTest.h"

const int NonReEntrantThreadLockableTest::SLEEP_DELAY_MS = 1000;
const int NonReEntrantThreadLockableTest::TOLERANCE = 5;
/**
 * Constructor
 */
NonReEntrantThreadLockableTest::NonReEntrantThreadLockableTest ( const std::string & name )
: TestCase( name )
{
}

/**
 * Destructor
 */
NonReEntrantThreadLockableTest:: ~NonReEntrantThreadLockableTest()
{
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *NonReEntrantThreadLockableTest::suite()
{
    TestSuite * testSuite = new TestSuite( "NonReEntrantThreadLockableTest" );

    testSuite->addTest( new TestCaller< NonReEntrantThreadLockableTest >( "testAcquire1", &NonReEntrantThreadLockableTest::testAcquire1, this ) );
    testSuite->addTest( new TestCaller< NonReEntrantThreadLockableTest >( "testAcquire2", &NonReEntrantThreadLockableTest::testAcquire2, this ) );
    testSuite->addTest( new TestCaller< NonReEntrantThreadLockableTest >( "testRelease1", &NonReEntrantThreadLockableTest::testRelease1, this ) );
    testSuite->addTest( new TestCaller< NonReEntrantThreadLockableTest >( "testRelease2", &NonReEntrantThreadLockableTest::testRelease2, this ) );

    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void NonReEntrantThreadLockableTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void NonReEntrantThreadLockableTest::tearDown( const std::string & OUTFile )
{
}


void NonReEntrantThreadLockableTest::testAcquire1(void)
{
    //
    // Test: This tests the acquire(void) method in NonReEntrantThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a NonReEntrantThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::NonReEntrantThreadLockable lock;

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


void NonReEntrantThreadLockableTest::testAcquire2(void)
{
    //
    // Test: This tests the acquire(void) method in NonReEntrantThreadLockable
    // Expected: TA_Base_Core::AssertException
    // Preconditions: NONE
    //

    // The strategy to test this is to instantiate a NonReEntrantThreadLockable
    // object and attempt to acquire the lock on it twice in succession.
    // Success is when we catch the resulting exception.
    
    TA_Base_Core::NonReEntrantThreadLockable lock;

    try
    {
        lock.acquire();
        lock.acquire();
        Assert( false );
    }
    catch( ... )
    {
        Assert( true );
    }
}

void NonReEntrantThreadLockableTest::testRelease1(void)
{
    //
    // Test: This tests the release(void) method in NonReEntrantThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a NonReEntrantThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::NonReEntrantThreadLockable lock;

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


void NonReEntrantThreadLockableTest::testRelease2(void)
{
    //
    // Test: This tests the release(void) method in NonReEntrantThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock twise a NonReEntrantThreadLockable instance.  Success is if a
    // exception is thrown.
    
    TA_Base_Core::NonReEntrantThreadLockable lock;

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

