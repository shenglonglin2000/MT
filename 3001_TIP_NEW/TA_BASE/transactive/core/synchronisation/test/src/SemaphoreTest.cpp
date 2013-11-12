/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/SemaphoreTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Test method implementation for cppunit unit testing of the Semaphore
  * implementation.
  *
  */

#include "SemaphoreTest.h"

const int SemaphoreTest::SLEEP_PERIOD_MS = 1000;

/**
 * Constructor
 */
SemaphoreTest::SemaphoreTest ( const std::string & name )
    : TestCase ( name )
    , semaphore( NULL )
{
}

/**
 * Destructor
 */
SemaphoreTest::~SemaphoreTest()
{
    if( NULL != this->semaphore )
    {
        delete semaphore;
        this->semaphore = NULL;
    }
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *SemaphoreTest::suite()
{
    TestSuite * testSuite = new TestSuite( "SemaphoreTest" );

    testSuite->addTest( new TestCaller< SemaphoreTest >( "testPost", &SemaphoreTest::testPost, this ) );
    testSuite->addTest( new TestCaller< SemaphoreTest >( "testWait", &SemaphoreTest::testWait, this ) );
    testSuite->addTest( new TestCaller< SemaphoreTest >( "testTryWait", &SemaphoreTest::testTryWait, this ) );
    
    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void SemaphoreTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
    if( NULL == this->semaphore )
    {
        this->semaphore = new TA_Base_Core::Semaphore( 1 );
    }
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void SemaphoreTest::tearDown( const std::string & OUTFile )
{
    if( NULL != this->semaphore )
    {
        delete this->semaphore;
        this->semaphore = NULL;
    }
}

void SemaphoreTest::testWait(void)
{
    //
    // Test: This tests the wait(void) method in Semaphore
    // Expected: Normal return
    // Preconditions: Created semaphore with one resource
    //
    
    // The strategy to test this is to create two threads.  One will wait on
    // the semaphore instance member and then 1 second later, the other one
    // will too.  This is accomplished by reimplementing the
    // SemaphoreTestThread within this method so that it will wait on the
    // provided semaphore immediately.  The threads will then be inspected to
    // see who has the lock and who does not.  It is expected that the first
    // thread called nonBlockedThread will have the lock and that the second,
    // called blockedThread will not.  The threads will then be terminated.

    // Implementation of the SemaphoreTestThread
    class SemaphoreTestThreadImpl : public SemaphoreTestThread
    {
    public:
        SemaphoreTestThreadImpl( TA_Base_Core::Semaphore& semaphoreRef )
            : SemaphoreTestThread( semaphoreRef )
            , acquiredLock( false )
        {
        }

        virtual ~SemaphoreTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or be blocked in the attempt.
         */
        virtual void run()
        {
            this->acquiredLock = false;
            // Assume the lock on the semaphore.
            this->semaphore.wait();
            this->acquiredLock = true;
        }

        /**
         * inspect
         * Inspects the instance and returns whether the instance has the lock
         * on the semaphore.
         * @return Bool indicating whether the instance has acquired the lock.
         */
        virtual bool inspect()
        {
            return this->acquiredLock;
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the semaphore is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
            if( acquiredLock )
            {
                this->semaphore.post(); // Wake up any blocked thread.
            }
        }

    private:
        /**
         * Instance member to indicate whether the thread instance has
         * acquired the lock on the semaphore instance member.
         */
        bool acquiredLock;
    };

    // Create the threads.
    SemaphoreTestThreadImpl nonBlockedThread( *this->semaphore );
    SemaphoreTestThreadImpl blockedThread( *this->semaphore );

    // Start both the threads.
    nonBlockedThread.start();
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS ); // Must pause to allow the first
                                               // thread to acquire the lock.
    blockedThread.start();
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS ); // Give this thread a change to run

    // The nonBlockedThread should have the lock and the blockedThread not
    // have it.
    Assert( nonBlockedThread.inspect() );
    Assert( !blockedThread.inspect() );

    // Terminate the threads.
    nonBlockedThread.terminateAndWait();
    blockedThread.terminateAndWait();
}

void SemaphoreTest::testTryWait(void)
{
    //
    // Test: This tests the tryWait(void) method in Semaphore
    // Expected: Normal return
    // Preconditions: Created semaphore with one resource
    //

    // The strategy to test this is to create two threads.  One will tryWait
    // on the semaphore instance member and then 1 second later, the other one
    // will attempt a tryWait() operation.  This is accomplished by
    // reimplementing the SemaphoreTestThread within this method so that it
    // will tryWait on the provided semaphore immediately.  The threads will
    // then be inspected to see who has the lock and who does not.  It is
    // expected that the first thread called acquiringThread will have the
    // lock and that the second, called notAcquiringThread will not.  The
    // threads will then be terminated.

    // Implementation of the SemaphoreTestThread
    class SemaphoreTestThreadImpl : public SemaphoreTestThread
    {
    public:
        typedef enum { ACQUIRE, NOT_ACQUIRE } EXPECTED_RESULT;

        SemaphoreTestThreadImpl( TA_Base_Core::Semaphore& semaphoreRef,
                                 EXPECTED_RESULT res )
            : SemaphoreTestThread( semaphoreRef )
            , expected( false )
            , result( res )
        {
        }

        virtual ~SemaphoreTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or fail in the attempt.
         */
        virtual void run()
        {
            this->expected = false;
            // Assume the lock on the semaphore.
            switch( this->result )
            {
            case ACQUIRE:
                if( this->semaphore.tryWait() )
                {
                    this->expected = true;
                }
                break;
            case NOT_ACQUIRE:
                if( this->semaphore.tryWait() )
                {
                    this->expected = true;
                }
                break;
            }
        }

        /**
         * inspect
         * Inspects the instance and returns whether the instance received the
         * expected result.
         * @return Bool indicating whether the instance has acquired the lock.
         */
        virtual bool inspect()
        {
            return this->expected;
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the semaphore is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
            if( expected )
            {
                this->semaphore.post(); // Wake up any blocked thread.
            }
        }

    private:
        /**
         * Instance member to indicate whether the thread instance has
         * acquired the lock on the semaphore instance member.
         */
        bool expected;
        /**
         * The expected result.
         */
        EXPECTED_RESULT result;
    };

    // Create the threads.
    SemaphoreTestThreadImpl acquiringThread( *this->semaphore,
                                             SemaphoreTestThreadImpl::ACQUIRE );
    SemaphoreTestThreadImpl notAcquiringThread( *this->semaphore,
                                                SemaphoreTestThreadImpl::NOT_ACQUIRE );

    // Start both the threads.
    acquiringThread.start();
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS ); // Must pause to allow the first
                                                    // thread to acquire the lock.
    notAcquiringThread.start();
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS ); // Give the thread a chance to start

    // The nonBlockedThread should have the lock and the blockedThread not
    // have it.
    Assert( acquiringThread.inspect() );
    Assert( !notAcquiringThread.inspect() );

    // Terminate the threads.
    acquiringThread.terminateAndWait();
    notAcquiringThread.terminateAndWait();
}


void SemaphoreTest::testPost(void)
{
    //
    // Test: This tests the post(void) method in Semaphore
    // Expected: Normal return
    // Preconditions: Created semaphore with one resource
    //
    
    // The strategy to test this is to reinstantiate the semaphore so that it
    // has a count of zero.  Then create a thread that will wait on
    // the semaphore instance member and then 1 second later, invoke a post()
    // method on the sempahore.  The thread should then acquire the lock on
    // the semaphore and continue processing (actually exiting).

    // Implementation of the SemaphoreTestThread
    class SemaphoreTestThreadImpl : public SemaphoreTestThread
    {
    public:
        SemaphoreTestThreadImpl( TA_Base_Core::Semaphore& semaphoreRef )
            : SemaphoreTestThread( semaphoreRef )
            , acquiredLock( false )
        {
        }

        virtual ~SemaphoreTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or be blocked in the attempt.
         */
        virtual void run()
        {
            this->acquiredLock = false;
            // Assume the lock on the semaphore.
            this->semaphore.wait();
            this->acquiredLock = true;
        }

        /**
         * inspect
         * Inspects the instance and returns whether the instance has the lock
         * on the semaphore.
         * @return Bool indicating whether the instance has acquired the lock.
         */
        virtual bool inspect()
        {
            return this->acquiredLock;
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the semaphore is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
            if( acquiredLock )
            {
                this->semaphore.post(); // Wake up any blocked thread.
            }
        }

    private:
        /**
         * Instance member to indicate whether the thread instance has
         * acquired the lock on the semaphore instance member.
         */
        bool acquiredLock;
    };

    // Reinstantiate the semaphore with a count of one.
    if( NULL != this->semaphore )
    {
        delete this->semaphore;
        this->semaphore = NULL;
    }
    this->semaphore = new TA_Base_Core::Semaphore( 0 );


    // Create the thread.
    SemaphoreTestThreadImpl blockedThread( *this->semaphore );

    // Start the thread.
    blockedThread.start();

    // The thread should not have the lock.
    Assert( !blockedThread.inspect() );

    // Post to the semaphore, this should release the thread.
    this->semaphore->post();

    // Pause to allow the post to propagate.
    TA_Base_Core::Thread::sleep( 1000 );

    // The thread should now have the lock.
    Assert( blockedThread.inspect() );

    // Terminate the thread.
    blockedThread.terminateAndWait();
}


// SemaphoreTestThread definitions

SemaphoreTestThread::SemaphoreTestThread( TA_Base_Core::Semaphore &semaphoreRef )
: semaphore( semaphoreRef )
{
}

SemaphoreTestThread::~SemaphoreTestThread() {}
