/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ThreadGuardTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Implementation of the ThreadGuardTest class.
  *
  */

#include "ThreadGuardTest.h"

const int ThreadGuardTest::SLEEP_DELAY_MS = 1000;
const int ThreadGuardTest::TOLERANCE = 5;
/**
 * Constructor
 */
ThreadGuardTest::ThreadGuardTest ( const std::string & name )
: TestCase( name )
{
}

/**
 * Destructor
 */
ThreadGuardTest:: ~ThreadGuardTest()
{
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *ThreadGuardTest::suite()
{
    TestSuite * testSuite = new TestSuite( "ThreadGuardTest" );

    testSuite->addTest( new TestCaller< ThreadGuardTest >( "testAcquire", &ThreadGuardTest::testAcquire, this ) );
    testSuite->addTest( new TestCaller< ThreadGuardTest >( "testRelease", &ThreadGuardTest::testRelease, this ) );


    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void ThreadGuardTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void ThreadGuardTest::tearDown( const std::string & OUTFile )
{
}


void ThreadGuardTest::testAcquire(void)
{
    //
    // Test: This tests the acquire(void) method in ThreadGuard
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
    class ThreadGuardTestThreadImpl : public ThreadGuardTestThread
    {
    public:
        ThreadGuardTestThreadImpl()
            : ThreadGuardTestThread()
        {
        }

        virtual ~ThreadGuardTestThreadImpl() {}

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
            TA_Base_Core::ThreadGuard( *this );
            TA_Base_Core::Thread::sleep( ThreadGuardTest::SLEEP_DELAY_MS );
            int i =0;
        }
    };

    // Create the thread
    ThreadGuardTestThreadImpl thread;

    // Start the thread
    thread.start();

    TA_Base_Core::Thread::sleep(10);

    // Acquire the lock and measure the amount of time it takes.
    long timeAttemptedToAcquireLock = time( NULL );
    thread.acquire();
    long timeFinishedAcquiringLock = time( NULL );

    Assert( timeFinishedAcquiringLock - timeAttemptedToAcquireLock < TOLERANCE );
    
    // Clean up
    thread.release();
    
    try
    {
        thread.terminateAndWait();
    }
    catch ( ... )
    {
        int i = 0;
    }
}


void ThreadGuardTest::testRelease(void)
{
    //
    // Test: This tests the release(void) method in ThreadGuard
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
    class ThreadGuardTestThreadImpl : public ThreadGuardTestThread
    {
    public:
        ThreadGuardTestThreadImpl()
            : ThreadGuardTestThread()
        {
        }

        virtual ~ThreadGuardTestThreadImpl() {}

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
            TA_Base_Core::ThreadGuard( *this );
            TA_Base_Core::Thread::sleep( ThreadGuardTest::SLEEP_DELAY_MS );
        }
    };

    // Create the thread
    ThreadGuardTestThreadImpl thread;

    // Start the thread
    thread.start();

    // Acquire the lock and measure the amount of time it takes.
    long timeAttemptedToAcquireLock = time( NULL );
    thread.acquire();
    long timeFinishedAcquiringLock = time( NULL );

    Assert( timeFinishedAcquiringLock - timeAttemptedToAcquireLock < TOLERANCE );
    
    // Clean up
    thread.release();
    thread.terminateAndWait();
}



// ThreadGuardTestThread definitions

ThreadGuardTestThread::ThreadGuardTestThread()
: Thread()
, ReEntrantThreadLockable()
{
}

ThreadGuardTestThread::~ThreadGuardTestThread() {}
