/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ThreadLockableHolderVerifierTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Implementation of the ThreadLockableHolderVerifierTest class.
  *
  */

#include "core/synchronisation/src/ThreadLockableHolderVerifier.h"

#include "ThreadLockableHolderVerifierTest.h"

const int ThreadLockableHolderVerifierTest::SLEEP_DELAY_MS = 1000;
const int ThreadLockableHolderVerifierTest::TOLERANCE = 5;
/**
 * Constructor
 */
ThreadLockableHolderVerifierTest::ThreadLockableHolderVerifierTest ( const std::string & name )
: TestCase( name )
{
}

/**
 * Destructor
 */
ThreadLockableHolderVerifierTest:: ~ThreadLockableHolderVerifierTest()
{
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *ThreadLockableHolderVerifierTest::suite()
{
    TestSuite * testSuite = new TestSuite( "ThreadLockableHolderVerifierTest" );

    testSuite->addTest( new TestCaller< ThreadLockableHolderVerifierTest >( "testSetCurrentThreadAsLockHolder", &ThreadLockableHolderVerifierTest::testSetCurrentThreadAsLockHolder, this ) );
    testSuite->addTest( new TestCaller< ThreadLockableHolderVerifierTest >( "testIsCurrentThreadTheLockHolder1", &ThreadLockableHolderVerifierTest::testIsCurrentThreadTheLockHolder1, this ) );
    testSuite->addTest( new TestCaller< ThreadLockableHolderVerifierTest >( "testIsCurrentThreadTheLockHolder2", &ThreadLockableHolderVerifierTest::testIsCurrentThreadTheLockHolder2, this ) );


    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void ThreadLockableHolderVerifierTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void ThreadLockableHolderVerifierTest::tearDown( const std::string & OUTFile )
{
}


void ThreadLockableHolderVerifierTest::testSetCurrentThreadAsLockHolder(void)
{
    //
    // Test: This tests the setCurrentThreadAsLockHolder(void) method in 
    //       ThreadLockableHolderVerifier
    // Expected: Normal return
    // Preconditions: NONE
    //

    // The strategy to test this is to create a thread, make it execute a
    // critical section.  While executing this critical section, locking
    // itself of course, the thread will use the ThreadLockableHolderVerifier
    // instance member to set itself as the current thread as lock holder.
    // The method will then check to see that the thread IS the
    // lock holder by interrogating the public instance member that holds id
    // of the lock holder.

    class ThreadLockableHolderVerifierTestThreadImpl
        : public ThreadLockableHolderVerifierTestThread
    {
    public:
        ThreadLockableHolderVerifierTestThreadImpl( TA_Base_Core::ThreadIdWrapper& ver )
            : ThreadLockableHolderVerifierTestThread()
            , verifier( ver ), m_threadId(0)
        {
        }

        virtual ~ThreadLockableHolderVerifierTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or be blocked in the attempt.
         */
        virtual void run()
        {
            m_threadId = Thread::getCurrentThreadId();
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

        virtual unsigned long getCurrentThreadId()
        {
            return m_threadId;
        }

    private:
        /**
         * enterCriticalSection
         * The critical section method.  This will acquire the lock on itself
         * and then sleep for SLEEP_DELAY_MS.
         */
        void enterCriticalSection()
        {
            this->acquire();
            verifier.setCurrentThreadId();
            TA_Base_Core::Thread::sleep( ThreadLockableHolderVerifierTest::SLEEP_DELAY_MS );
            this->release();
        }

        /**
         * The lock holder verifier.
         */
        TA_Base_Core::ThreadIdWrapper& verifier;
        volatile unsigned int m_threadId;
    };

    TA_Base_Core::ThreadIdWrapper verifier;

    // Create the thread
    ThreadLockableHolderVerifierTestThreadImpl thread( verifier );

    // Start the thread
    thread.start();

    TA_Base_Core::Thread::sleep( ThreadLockableHolderVerifierTest::SLEEP_DELAY_MS / 2 );

    Assert( verifier.getCurrentThreadId() == thread.getCurrentThreadId() );
    
    // Clean up
    thread.terminateAndWait();
}


void ThreadLockableHolderVerifierTest::testIsCurrentThreadTheLockHolder1(void)
{
    //
    // Test: This tests the isCurrentThreadTheLockHolder(void) method in 
    //       ThreadLockableHolderVerifier
    // Expected: Normal return
    // Preconditions: Thread will hold the lock on itself.
    //

    // The strategy to test this method is to create and launch a thread.
    // This thread will then acquire the lock on itself and then set itself as
    // the holder of the lock.  It will be inspectable so that THIS thread can
    // check whether it is the holder of lock.
    class ThreadLockableHolderVerifierTestThreadImpl
        : public ThreadLockableHolderVerifierTestThread
    {
    public:
        ThreadLockableHolderVerifierTestThreadImpl( TA_Base_Core::ThreadIdWrapper& ver )
            : ThreadLockableHolderVerifierTestThread()
            , verifier( ver )
            , lockHeld( false )
        {
        }

        virtual ~ThreadLockableHolderVerifierTestThreadImpl() {}

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

        /**
         * inspect
         * Inspects the thread and sees if it is the holder of the lock.
         * @return boolean indicating whether or not the thread holds the
         *         lock.
         */
        bool inspect()
        {
            return this->lockHeld;
        }

    private:
        /**
         * enterCriticalSection
         * The critical section method.  This will acquire the lock on itself
         * and then sleep for SLEEP_DELAY_MS.
         */
        void enterCriticalSection()
        {
            this->acquire();
            verifier.setCurrentThreadId();
            lockHeld = verifier.isCurrentThreadId();
            TA_Base_Core::Thread::sleep( ThreadLockableHolderVerifierTest::SLEEP_DELAY_MS );
            this->release();
        }

        /**
         * The lock holder verifier.
         */
        TA_Base_Core::ThreadIdWrapper& verifier;
        /**
         * Flag indicating whether the lock is held or not.
         */
        bool lockHeld;
    };

    TA_Base_Core::ThreadIdWrapper verifier;

    // Create the thread
    ThreadLockableHolderVerifierTestThreadImpl thread( verifier );

    // Start the thread
    thread.start();

    TA_Base_Core::Thread::sleep( ThreadLockableHolderVerifierTest::SLEEP_DELAY_MS );

    Assert( thread.inspect() );
    
    // Clean up
    thread.terminateAndWait();
}


void ThreadLockableHolderVerifierTest::testIsCurrentThreadTheLockHolder2(void)
{
    //
    // Test: This tests the isCurrentThreadTheLockHolder(void) method in 
    //       ThreadLockableHolderVerifier
    // Expected: Normal return
    // Preconditions: Thread will NOT hold the lock on itself.
    //

    // The strategy to test this method is to create and launch a thread.
    // It will be inspectable so that THIS thread can check whether it is the
    // holder of lock.
    class ThreadLockableHolderVerifierTestThreadImpl
        : public ThreadLockableHolderVerifierTestThread
    {
    public:
        ThreadLockableHolderVerifierTestThreadImpl( TA_Base_Core::ThreadIdWrapper& ver )
            : ThreadLockableHolderVerifierTestThread()
            , verifier( ver )
            , lockHeld( false )
        {
        }

        virtual ~ThreadLockableHolderVerifierTestThreadImpl() {}

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

        /**
         * inspect
         * Inspects the thread and sees if it is the holder of the lock.
         * @return boolean indicating whether or not the thread holds the
         *         lock.
         */
        bool inspect()
        {
            return this->lockHeld;
        }

    private:
        /**
         * enterCriticalSection
         * The critical section method.  This will acquire the lock on itself
         * and then sleep for SLEEP_DELAY_MS.
         */
        void enterCriticalSection()
        {
            this->acquire();
            // This is really the only difference between this method and the
            // one above.
            // verifier.setCurrentThreadAsLockHolder();
            lockHeld = verifier.isCurrentThreadId();
            TA_Base_Core::Thread::sleep( ThreadLockableHolderVerifierTest::SLEEP_DELAY_MS );
            this->release();
        }

        /**
         * The lock holder verifier.
         */
        TA_Base_Core::ThreadIdWrapper& verifier;
        /**
         * Flag indicating whether the lock is held or not.
         */
        bool lockHeld;
    };

    TA_Base_Core::ThreadIdWrapper verifier;

    // Create the thread
    ThreadLockableHolderVerifierTestThreadImpl thread( verifier );

    // Start the thread
    thread.start();

    TA_Base_Core::Thread::sleep( ThreadLockableHolderVerifierTest::SLEEP_DELAY_MS );

    Assert( !thread.inspect() );
    
    // Clean up
    thread.terminateAndWait();
}
