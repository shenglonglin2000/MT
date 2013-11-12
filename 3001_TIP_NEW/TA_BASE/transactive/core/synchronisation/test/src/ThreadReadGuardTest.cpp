/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ThreadReadGuardTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Implementation of the ThreadReadGuardTest class.
  *
  */

#include "ThreadReadGuardTest.h"
#include "core/synchronisation/src/ThreadReadGuard.h"

const int ThreadReadGuardTest::SLEEP_DELAY_MS = 1000;
const int ThreadReadGuardTest::TOLERANCE = 5;
/**
 * Constructor
 */
ThreadReadGuardTest::ThreadReadGuardTest ( const std::string & name )
: TestCase( name )
{
}

/**
 * Destructor
 */
ThreadReadGuardTest:: ~ThreadReadGuardTest()
{
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *ThreadReadGuardTest::suite()
{
    TestSuite * testSuite = new TestSuite( "ThreadReadGuardTest" );

    testSuite->addTest( new TestCaller< ThreadReadGuardTest >( "testAcquire", &ThreadReadGuardTest::testAcquire, this ) );
    testSuite->addTest( new TestCaller< ThreadReadGuardTest >( "testRelease", &ThreadReadGuardTest::testRelease, this ) );


    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void ThreadReadGuardTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void ThreadReadGuardTest::tearDown( const std::string & OUTFile )
{
}


void ThreadReadGuardTest::testAcquire(void)
{
    //
    // Test: This tests the acquire(void) method in ThreadReadGuard
    // Expected: Normal return
    // Preconditions: NONE
    //

    // The strategy to test this is to create a thread, make it execute a
    // critical section.  While executing this critical section, locking
    // itself of course, THIS thread will attempt to acquire the lock on the
    // thread.  This will cause THIS thread to block.  The critical section
    // will simply be a sleep invocation of SLEEP_DELAY_MS time.  We will
    // test if the lock held correctly by testing amount of time between when
    // THIS thread invoked acquire on the thread instance and when it finally
    // acquired the lock.  The current tolerance will be TOLERANCE ms.
    class ThreadReadGuardTestThreadImpl : public ThreadReadGuardTestThread
    {
    public:
        ThreadReadGuardTestThreadImpl()
            : ThreadReadGuardTestThread()
        {
        }

        virtual ~ThreadReadGuardTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or be blocked in the attempt.
         */
        virtual void run()
        {
            this->enterCriticalSection();
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the semaphore is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
        }

    private:
        /**
         * enterCriticalSection
         * The critical section method.  This will acquire the lock on itself
         * and then sleep for SLEEP_DELAY_MS.
         */
        void enterCriticalSection()
        {
            TA_Base_Core::ThreadReadGuard( *this );
            TA_Base_Core::Thread::sleep( ThreadReadGuardTest::SLEEP_DELAY_MS );
        }
    };

    // Create the thread
    ThreadReadGuardTestThreadImpl thread;

    // Start the thread
    thread.start();

    // Acquire the lock and measure the amount of time it takes.
    long timeAttemptedToAcquireLock = time( NULL );
    thread.acquireRead();
    long timeFinishedAcquiringLock = time( NULL );

    Assert( timeFinishedAcquiringLock - timeAttemptedToAcquireLock < TOLERANCE );
    
    // Clean up
    thread.releaseRead();
    thread.terminateAndWait();
}


void ThreadReadGuardTest::testRelease(void)
{
    //
    // Test: This tests the release(void) method in ThreadReadGuard
    // Expected: Normal return
    // Preconditions: NONE
    //

    // The strategy to test this is to create a thread, make it execute a
    // critical section.  While executing this critical section, locking
    // itself of course, THIS thread will attempt to acquire the lock on the
    // thread.  This will cause THIS thread to block.  The critical section
    // will simply be a sleep invocation of SLEEP_DELAY_MS time.  We will
    // test if the lock held correctly by testing amount of time between when
    // THIS thread invoked acquire on the thread instance and when it finally
    // acquired the lock.  The current tolerance will be TOLERANCE ms.
    class ThreadReadGuardTestThreadImpl : public ThreadReadGuardTestThread
    {
    public:
        ThreadReadGuardTestThreadImpl()
            : ThreadReadGuardTestThread()
        {
        }

        virtual ~ThreadReadGuardTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or be blocked in the attempt.
         */
        virtual void run()
        {
            this->enterCriticalSection();
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the semaphore is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
        }

    private:
        /**
         * enterCriticalSection
         * The critical section method.  This will acquire the lock on itself
         * and then sleep for SLEEP_DELAY_MS.
         */
        void enterCriticalSection()
        {
            TA_Base_Core::ThreadReadGuard( *this );
            TA_Base_Core::Thread::sleep( ThreadReadGuardTest::SLEEP_DELAY_MS );
        }
    };

    // Create the thread
    ThreadReadGuardTestThreadImpl thread;

    // Start the thread
    thread.start();

    // Acquire the lock and measure the amount of time it takes.
    long timeAttemptedToAcquireLock = time( NULL );
    thread.acquireRead();
    long timeFinishedAcquiringLock = time( NULL );

    Assert( timeFinishedAcquiringLock - timeAttemptedToAcquireLock < TOLERANCE );
    
    // Clean up
    thread.releaseRead();
    thread.terminateAndWait();
}



// ThreadReadGuardTestThread definitions

ThreadReadGuardTestThread::ThreadReadGuardTestThread()
: Thread()
, ReadWriteThreadLockable()
{
}

ThreadReadGuardTestThread::~ThreadReadGuardTestThread() {}
